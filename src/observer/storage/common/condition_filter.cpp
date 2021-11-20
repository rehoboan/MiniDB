/* Copyright (c) 2021 Xie Meiyi(xiemeiyi@hust.edu.cn) and OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Wangyunlai on 2021/5/7.
//


#include "condition_filter.h"

using namespace common;

ConditionFilter::~ConditionFilter()
= default;

DefaultConditionFilter::DefaultConditionFilter()
{
  left_.is_attr = false;
  left_.attr_length = 0;
  left_.attr_offset = 0;
  left_.value = nullptr;

  right_.is_attr = false;
  right_.attr_length = 0;
  right_.attr_offset = 0;
  right_.value = nullptr;
}

DefaultConditionFilter::~DefaultConditionFilter()
= default;

RC DefaultConditionFilter::init(const ConDesc &left, const ConDesc &right, int left_attr_type, int right_attr_type, CompOp comp_op)
{
  if (left_attr_type < CHARS || left_attr_type > TEXTS) {
    LOG_ERROR("Invalid condition with unsupported attribute type of left: %d", left_attr_type);
    return RC::INVALID_ARGUMENT;
  }
  if (right_attr_type < CHARS || right_attr_type > TEXTS) {
    LOG_ERROR("Invalid condition with unsupported attribute type of right: %d", right_attr_type);
    return RC::INVALID_ARGUMENT;
  }


  left_ = left;
  right_ = right;
  left_attr_type_ = left_attr_type;
  right_attr_type_ = right_attr_type;
  comp_op_ = comp_op;
  return RC::SUCCESS;
}
/*          undefined chars ints floats dates texts
undefined      1        1    1     1      1     1
    chars      1        1    0     0      0     1
     ints      1        0    1     1      0     0
   floats      1        0    1     1      0     0
    dates      1        0    0     0      1     0
    texts      1        1    0     0      0     1
*/
int field_type_compare_compatible_table[TEXTS+1][TEXTS+1]={
        {1,1,1,1,1,1},
        {1,1,0,0,0,1},
        {1,0,1,1,0,0},
        {1,0,1,1,0,0},
        {1,0,0,0,1,0},
        {1,1,0,0,0,1}
};

RC DefaultConditionFilter::init(Table &table, const Condition &condition)
{
  std::cout<<"DefaultConditionFilter::init"<<std::endl;
  TableMeta &table_meta = table.table_meta();
  ConDesc left{};
  ConDesc right{};

  int type_left;
  int type_right;

  if (1 == condition.left_is_attr) {
    left.is_attr = true;
    const FieldMeta *field_left = table_meta.field(condition.left_attr.attribute_name);
    if (nullptr == field_left) {
      LOG_WARN("No such field in condition. %s.%s", table.name(), condition.left_attr.attribute_name);
      return RC::SCHEMA_FIELD_MISSING;
    }
    left.attr_length = field_left->len();
    left.attr_offset = field_left->offset();
    left.attr_type = field_left->type();
    left.index = table_meta.getIndex(condition.left_attr.attribute_name) - 2;

    left.value = nullptr;
    left.value_num = 0;

    type_left = field_left->type();
  } else {
    left.is_attr = false;
    left.value = condition.left_value.data; // 校验type 或者转换类型
    left.attr_type = condition.left_value.type;
    type_left = condition.left_value.type;
    left.value_num = condition.left_value.num;
  }

  if (1 == condition.right_is_attr) {
    right.is_attr = true;
    const FieldMeta *field_right = table_meta.field(condition.right_attr.attribute_name);
    if (nullptr == field_right) {
      LOG_WARN("No such field in condition. %s.%s", table.name(), condition.right_attr.attribute_name);
      return RC::SCHEMA_FIELD_MISSING;
    }
    right.attr_length = field_right->len();
    right.attr_offset = field_right->offset();
    type_right = field_right->type();
    right.attr_type = field_right->type();
    right.value = nullptr;
    right.value_num = 0;
  } else {
    right.is_attr = false;
    right.value = condition.right_value.data;
    right.value_num = condition.right_value.num;
    //子查询返回空表，在这里给空value的类型赋值
    type_right = (right.value_num) ? condition.right_value.type : type_left;
    std::cout<<"right_value_name"<<right.value_num<<std::endl;
    right.attr_type = condition.right_value.type;
    right.attr_length = 0;
    right.attr_offset = 0;
  }
  std::cout<<"type_left"<<type_left<<std::endl;
  std::cout<<"type_right"<<type_right<<std::endl;
  std::cout<<"type mismatch?"<<std::endl;

  if (!field_type_compare_compatible_table[TYPE(type_left)][TYPE(type_right)]) {
    std::cout<<"************can not compare***********"<<std::endl;
    LOG_WARN("Can not compare. %d and %d", type_left, type_right);
    return RC::SCHEMA_FIELD_TYPE_MISMATCH;
  } else if((condition.comp==OP_IN || condition.comp==OP_NOT_IN)) {
    if((type_left != type_right)) {
      if(!(type_left == FLOATS && type_right==INTS || type_left == INTS && type_right ==FLOATS)) {
        LOG_WARN("IN operation type mismatch");
        return RC::MISUSE;
      }
    }
  }
  
  left_ = std::move(left);
  right_ = std::move(right);
  left_attr_type_ = type_left;
  right_attr_type_ = type_right;
  comp_op_ = condition.comp;
  return RC::SUCCESS;
//  return init(left, right, static_cast<AttrType>(type_left), condition.comp);
}

//int sign(double l, double r){
//  if(l - r <0){
//    return -1;
//  }else if(l - r >0){
//    return 1;
//  }else{
//    return 0;
//  }
//}

bool compare_res_with_op(CompOp op, int cmp_result, bool has_null){
  switch (op){
    case EQUAL_TO:
      return !has_null && (0 == cmp_result);
    case OP_IS:
      return has_null && (0 == cmp_result);
    case LESS_EQUAL:
      return !has_null && (cmp_result <= 0);
    case NOT_EQUAL:
      return !has_null && (cmp_result != 0);
    case OP_IS_NOT:
      return has_null && (cmp_result != 0);
    case LESS_THAN:
      return !has_null && (cmp_result < 0);
    case GREAT_EQUAL:
      return !has_null && (cmp_result >= 0);
    case GREAT_THAN:
      return !has_null && (cmp_result > 0);
    case OP_IN:
      return !has_null && (cmp_result > 0);
    case OP_NOT_IN:
      return !has_null && (cmp_result == 0);

    default:
      break;
  }
  return false;
}

bool DefaultConditionFilter::filter(const Record &rec) const
{
  std::string tmp;
  const char *left_value;
  bool left_null;
  bool right_null;
  const char *right_value;
  //左类型
  int left_type = left_attr_type_;
  //右类型
  int right_type = right_attr_type_;
  if (left_.is_attr) { // value
    left_value = (char *)(rec.data + left_.attr_offset);
    //查看是否为空的状态
    char * data = rec.data;
    int null_v = *(int*)(data+TableMeta::null_field_offset());
    left_null = (null_v & (1 << left_.index));
    if(!left_null && TYPE(left_attr_type_) == TEXTS){//左边不为空
      left_type = CHARS;
      RID rid{};
      rid.page_num = *(int*)(left_value);
      rid.slot_num = *(int*)(left_value+4);
      tmp = sys_tbs->getText(rid);
      left_value = tmp.c_str();
    }} else {
    left_value = (char *)left_.value;
    left_null = (left_attr_type_ == NULL_VALUE);
  }
  if (right_.is_attr) {
    right_value = (char *)(rec.data + right_.attr_offset);
    char * data = rec.data;
    int null_v = *(int*)(data+TableMeta::null_field_offset());
    right_null = (null_v & (1 << right_.index));
    if(!right_null && TYPE(right_attr_type_) == TEXTS){
      right_type = CHARS;
      RID rid{};
      rid.page_num = *(int*)(right_value);
      rid.slot_num = *(int*)(right_value+4);
      std::string tmp_ = sys_tbs->getText(rid);
      right_value = tmp_.c_str();
    }
  }else {
    //这里即使油表为值，也仍然有可能为空
    if(right_.value_num == 0 && comp_op_ < OP_NOT_IN) {
      //直接返回false
      return false;
    }else if(comp_op_ < OP_IN) {
      right_value = (char *)right_.value;
    }
    right_null = (right_attr_type_ == NULL_VALUE);
  }
  int res;
  if(left_null || right_null){
    res = (left_null ^ right_null);
  }else{
    if(comp_op_ < OP_IN) {
      res = compare_data(TYPE(left_type), left_value,
                        TYPE(right_type),right_value);
    } else if(comp_op_ == OP_IN || comp_op_== OP_NOT_IN) {
      //todo 在这里执行in操作，in允许int 和float之间比较
      //assert(left_type == right_type);
      res = in_op(TYPE(left_type), left_value,
                  TYPE(right_type), right_.value, right_.value_num);
    }
  }

  return compare_res_with_op(comp_op_, res, left_null || right_null);
}




JoinConditionFilter::JoinConditionFilter() = default;

JoinConditionFilter::~JoinConditionFilter() = default;


RC JoinConditionFilter::init(const RelAttr &left, const RelAttr &right, CompOp comp_op) {
  left_ = left;
  right_ = right;
  comp_op_ = comp_op;
  return RC::SUCCESS;
}

bool JoinConditionFilter::filter(const Tuple &tuple, const TupleSchema &tuple_schema) const {
  int res_op = 0;
  int idx1 = tuple_schema.index_of_field(left_.relation_name, left_.attribute_name);
  int idx2 = tuple_schema.index_of_field(right_.relation_name, right_.attribute_name);
  TupleValue *left_value = tuple.get_pointer(idx1).get();
  TupleValue *right_value = tuple.get_pointer(idx2).get();
  if(left_value && right_value)
    res_op = left_value->compare(*right_value);

  switch (comp_op_) {
  case EQUAL_TO:
    return 0 == res_op;
  case LESS_EQUAL:
    return res_op <= 0;
  case NOT_EQUAL:
    return res_op != 0;
  case LESS_THAN:
    return res_op < 0;
  case GREAT_EQUAL:
    return res_op >= 0;
  case GREAT_THAN:
    return res_op > 0;

  default:
    break;
  }

  LOG_PANIC("Never should print this.");
  return res_op;  // should not go here
    
}
bool JoinConditionFilter::filter(const Tuple &left_tuple, const TupleSchema &left_schema, 
                      const Tuple &right_tuple, const TupleSchema &right_schema) const {
  int res_op;
  int idx1 = left_schema.index_of_field(left_.relation_name, left_.attribute_name);
  int idx2 = right_schema.index_of_field(right_.relation_name, right_.attribute_name);

  TupleValue *left_value = left_tuple.get_pointer(idx1).get();
  TupleValue *right_value = right_tuple.get_pointer(idx2).get();
  res_op = left_value->compare(*right_value);

  switch (comp_op_) {
  case EQUAL_TO:
    return 0 == res_op;
  case LESS_EQUAL:
    return res_op <= 0;
  case NOT_EQUAL:
    return res_op != 0;
  case LESS_THAN:
    return res_op < 0;
  case GREAT_EQUAL:
    return res_op >= 0;
  case GREAT_THAN:
    return res_op > 0;

  default:
    break;
  }

  LOG_PANIC("Never should print this.");
  return res_op;  // should not go here
}


CompositeConditionFilter::~CompositeConditionFilter()
{
  if (memory_owner_) {
    delete[] filters_;
    filters_ = nullptr;
  }
}

RC CompositeConditionFilter::init(const ConditionFilter *filters[], int filter_num, bool own_memory)
{
  filters_ = filters;
  filter_num_ = filter_num;
  memory_owner_ = own_memory;
  return RC::SUCCESS;
}
RC CompositeConditionFilter::init(const ConditionFilter *filters[], int filter_num)
{
  return init(filters, filter_num, false);
}

RC CompositeConditionFilter::init(Table &table, const Condition *conditions, int condition_num)
{
  if (condition_num == 0) {
    return RC::SUCCESS;
  }
  if (conditions == nullptr) {
    return RC::INVALID_ARGUMENT;
  }

  RC rc;
  auto **condition_filters = new ConditionFilter *[condition_num];
  for (int i = 0; i < condition_num; i++) {
    auto *default_condition_filter = new DefaultConditionFilter();
    rc = default_condition_filter->init(table, conditions[i]);
    if (rc != RC::SUCCESS) {
      delete default_condition_filter;
      for (int j = i - 1; j >= 0; j--) {
        delete condition_filters[j];
        condition_filters[j] = nullptr;
      }
      delete[] condition_filters;
      return rc;
    }
    condition_filters[i] = default_condition_filter;
  }
  return init((const ConditionFilter **)condition_filters, condition_num, true);
}

bool CompositeConditionFilter::filter(const Record &rec) const
{
  for (int i = 0; i < filter_num_; i++) {
    if (!filters_[i]->filter(rec)) {
      return false;
    }
  }
  return true;
}


bool CompositeConditionFilter::filter(const Tuple &tuple, const TupleSchema &tuple_schema) const {
  for(int i = 0; i<filter_num_; i++) {
    if(!filters_[i]->filter(tuple, tuple_schema)) {
      return false;
    }
  }
  return true;
}

bool CompositeConditionFilter::filter(const Tuple &left_tuple, const TupleSchema &left_schema, 
                      const Tuple &right_tuple, const TupleSchema &right_schema) const {
  for(int i=0; i<filter_num_; i++) {
    if(!filters_[i]->filter(left_tuple, left_schema, right_tuple, right_schema)) {
      return false;
    }
  }
  return true;

                      }





