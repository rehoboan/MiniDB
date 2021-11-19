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
// Created by Wangyunlai on 2021/5/14.
//

#include "sql/executor/execution_node.h"
#include "storage/common/table.h"
#include "common/log/log.h"

SelectExeNode::SelectExeNode() : table_(nullptr) {
}

SelectExeNode::~SelectExeNode() {
  for (DefaultConditionFilter * &filter : condition_filters_) {
    delete filter;
  }
  condition_filters_.clear();
}

RC SelectExeNode::init(Trx *trx, Table *table, TupleSchema &&tuple_schema, std::vector<DefaultConditionFilter *> &&condition_filters) {
  trx_ = trx;
  table_ = table;
  tuple_schema_ = tuple_schema;
  condition_filters_ = std::move(condition_filters);
  return RC::SUCCESS;
}

void record_reader(const char *data, void *context) {
  TupleRecordConverter *converter = (TupleRecordConverter *)context;
  converter->add_record(data);
}
RC SelectExeNode::execute(TupleSet &tuple_set) {
  CompositeConditionFilter condition_filter;
  condition_filter.init((const ConditionFilter **)condition_filters_.data(), condition_filters_.size());

  tuple_set.clear();
  tuple_set.set_schema(tuple_schema_);
  TupleRecordConverter converter(table_, tuple_set);
  return table_->scan_record(trx_, &condition_filter, -1, (void *)&converter, record_reader);
}

//insert value of src depends on the target field
bool make_tuple(const Tuple& src_tuple, const TupleSchema& src_schema, 
                const char *target_table_name, TupleField& target_tuple_field,
                Tuple &res_tuple) {
  for(TupleField src_field : src_schema.fields()) {
    const char *src_table_name = src_field.table_name();
    if(strcmp(src_table_name, target_table_name)==0) {
      int idx = src_schema.index_of_field(target_table_name, target_tuple_field.field_name());
      if(idx != -1) {
        res_tuple.add(src_tuple.get_pointer(idx));
        return true;
      }
    }  
  }
  return false;
}

JoinExeNode::JoinExeNode() : left_table_(nullptr), right_table_(nullptr) {

}

JoinExeNode::~JoinExeNode() {
  for (JoinConditionFilter * &filter : condition_filters_) {
    delete filter;
  }
  condition_filters_.clear();
}


RC JoinExeNode::init(Trx *trx, 
          const TupleSet *left_table, const TupleSet *right_table,
          TupleSchema tuple_schema,
          std::vector<JoinConditionFilter*> condition_filters) {
  trx_ = trx;
  left_table_ = left_table;
  right_table_ = right_table;
  tuple_schema_ = tuple_schema;
  condition_filters_ = condition_filters;
  
  return RC::SUCCESS;
}

RC JoinExeNode::execute(TupleSet &tuple_set) {
  CompositeConditionFilter condition_filter;
  condition_filter.init((const ConditionFilter **) condition_filters_.data(), condition_filters_.size());

  tuple_set.clear();
  tuple_set.set_schema(tuple_schema_);

  const std::vector<Tuple> &left_tuples = left_table_->tuples();
  const std::vector<Tuple> &right_tuples = right_table_->tuples();

  const TupleSchema &left_schema = left_table_->get_schema();
  const TupleSchema &right_schema = right_table_->get_schema();

  for(int i=0; i<left_table_->size(); i++) {
    for(int j=0; j<right_table_->size(); j++) {
      bool res1 = condition_filter.filter(left_tuples[i], left_schema, right_tuples[j],
                              right_schema);
      if(res1) {
        Tuple res_tuple;
        for(TupleField tuple_field: tuple_schema_.fields()) {
          const char *table_name = tuple_field.table_name();
          bool updated_left = make_tuple(left_tuples[i], left_schema, table_name, tuple_field, res_tuple);
          if(!updated_left) {
            bool updated_right = make_tuple(right_tuples[j], right_schema, table_name, tuple_field, res_tuple);
            if(!updated_right){
              LOG_ERROR("Schema field of join table mismatch with left and right table. fieldname:%s,tablename:%s", tuple_field.field_name(), table_name);
              return RC::SCHEMA_FIELD_NOT_EXIST;              
            }            
          }
        }
        tuple_set.add(std::move(res_tuple));
      }
    }
  }
  return RC::SUCCESS;
}

CartesianProductExeNode::CartesianProductExeNode() : left_table_(nullptr), right_table_(nullptr) {

}

CartesianProductExeNode::~CartesianProductExeNode() {

}

RC CartesianProductExeNode::init(Trx *trx, 
                                const TupleSet *left_table, const TupleSet *right_table,
                                const TupleSchema &tuple_schema) {
  trx_ = trx;
  left_table_ = left_table;
  right_table_ = right_table;
  tuple_schema_ = tuple_schema;
  return RC::SUCCESS;
}

RC CartesianProductExeNode::execute(TupleSet &tuple_set) {
  tuple_set.clear();
  tuple_set.set_schema(tuple_schema_);

  const std::vector<Tuple> &left_tuples = left_table_->tuples();
  const std::vector<Tuple> &right_tuples = right_table_->tuples();

  TupleSchema left_schema = left_table_->get_schema();
  TupleSchema right_schema = right_table_->get_schema();


  for(int i=0; i<left_table_->size(); i++) {
    for(int j=0; j<right_table_->size(); j++) {
      Tuple res_tuple;
      for(TupleField tuple_field : tuple_schema_.fields()) {
        const char *table_name = tuple_field.table_name();
        bool res1 = make_tuple(left_tuples[i], left_schema, table_name, tuple_field, res_tuple);
        if(!res1) {
          bool res2 = make_tuple(right_tuples[j], right_schema, table_name, tuple_field, res_tuple);
          if(!res2) {
            LOG_ERROR("Schema field of join table mismatch with left and right table. fieldname:%s,tablename:%s", tuple_field.field_name(), table_name);
            return RC::SCHEMA_FIELD_NOT_EXIST;   
          }
        }
      }
      tuple_set.add(std::move(res_tuple));
    }
  }
  return RC::SUCCESS;
}
AggregationExeNode::AggregationExeNode() : table_(nullptr){

}

AggregationExeNode::~AggregationExeNode() {

}



RC AggregationExeNode::init(Trx *trx, const TupleSet *table, std::vector<std::pair<const char *, AggInfo>> &&agg_infos){
  trx_ = trx;
  table_ = table;
  agg_infos_ = agg_infos;
  return RC::SUCCESS;
  
}

RC AggregationExeNode::execute(Tuple &tuple, std::vector<const char *> &agg_columns) {
  RC rc = RC::SUCCESS;
  //<aggname, attr index in tuple>
  std::unordered_map<const char *, int> map;
  rc = init_index_map(map);

  
  std::vector<AggValue> res;
  std::unordered_map<const char *, int> avg_count; //对相关列进行avg的计数操作
  for(int i=0; i < agg_infos_.size(); i++) {
    AggValue value;
    //agg(table.attr)
    const char *agg_column_name = agg_infos_[i].first;
    AggInfo &agg_info = agg_infos_[i].second;
    //counts默认为int，剩下需要根据attr type判断
    if(agg_info.type == COUNTS) {
      value.values.int_value = 0;
      value.value_idx = 1;
    } else {
      int field_index = map[agg_column_name];
      int type = table_->get_schema().field(field_index).type();

      switch (type){
        case INTS:
          if(agg_info.type == AVGS) {
            value.value_idx = 2;
          } else {
            value.value_idx = 1;
          }
          break;
        case FLOATS:
          value.value_idx = 2;
          break;
        case CHARS:
          value.value_idx = 3;
          break;
        case DATES:
          value.value_idx = 4;
        default:
          break;
      }
      value.values.int_value = NULL_VALUE;
    }
    res.push_back(value);

    if(agg_info.type == AVGS){
      avg_count[agg_column_name] = 0;
    }
    
  }
  //执行聚合操作  对每一个元组为单位进行操作
  const std::vector<Tuple> &tuples = table_->tuples();
  for(const Tuple &tuple : tuples) {
    for(int i=0; i<agg_infos_.size(); i++) {
      std::pair<const char *, AggInfo> pair = agg_infos_[i];
      const char *agg_column_name = pair.first;
      AggType type = pair.second.type;
      int idx = map[agg_column_name];
      if(idx == -1) {
        //count in star mode
        rc  = count(res[i], false);
      } else {
        //get tuple value
        const TupleValue &tuple_value = tuple.get(idx);
        if(type == AVGS){
          if(!tuple_value.is_null()) {
            avg_count[agg_column_name] += 1;
          }
        }
        switch(type){
          case COUNTS: {
            if(!tuple_value.is_null())
              rc = count(res[i], false);
            else 
              rc = count(res[i], true);            
          }
          break;
          case MAXS:
            rc = max(tuple_value, res[i]);
          break;
          case MINS:
            rc = min(tuple_value, res[i]);
          break;
          case AVGS: {
            rc = avg(tuple_value, res[i], avg_count[agg_column_name]);
          break;
          }
          default:
            rc = RC::MISUSE;
          break;
        }
      }
    }
  }

  if(rc != RC::SUCCESS)
    return rc;

  // 以tuple的形式组织聚合结果

  for(int i=0; i < agg_infos_.size(); i++) {
    AggValue agg_value = res[i];
    const char * agg_column_name = agg_infos_[i].first;
    agg_columns.push_back(agg_column_name);
    bool is_init = (agg_value.values.int_value != NULL_VALUE);

    if(!is_init){
      //聚合列都是null时，聚合函数的结果为null
      tuple.add();
    }
    else {
      switch(agg_value.value_idx) {
        case 1:{ //int
          tuple.add(agg_value.values.int_value);
        }
        break;
        case 2: { //float
          tuple.add(agg_value.values.float_value);
        }
        break;
        case 3: { //string
          tuple.add(agg_value.values.string_value, 
                  strlen(agg_value.values.string_value));
        }
        break;
        case 4: {//dates
          tuple.add(agg_value.values.date_value);
        }

        default:
        break;
      }      
    }
  }
  
  return rc;
}

RC AggregationExeNode::init_index_map(std::unordered_map<const char *, int> &map) {
  //get schema of tuple
  TupleSchema schema = table_->get_schema();
  for(auto iter = agg_infos_.begin(); iter != agg_infos_.end(); iter++) {
    const char *agg_column_name = iter->first;
    AggInfo agg_info = iter->second;
    int field_index = -1;
    if(strcmp(agg_info.attr_name, "*")!=0){
      field_index = schema.index_of_field(agg_info.relation_name, agg_info.attr_name);
      //不能对字符串进行avg聚合
      if(schema.field(field_index).type() == CHARS && agg_info.type == AVGS) {
        return RC::MISUSE;
      }
    }
    map[agg_column_name] = field_index;
  }
  return RC::SUCCESS; 
}
RC AggregationExeNode::max(const TupleValue &value, AggValue &res) {
  bool is_init = (res.values.int_value != NULL_VALUE);
  int type = value.get_type();

  if(!value.is_null()){
    switch(type){
      case INTS:{
        int value_int = *(int *)value.get_value();
        if(is_init) {
          res.values.int_value = std::max(res.values.int_value, value_int);  
        } else {
          res.values.int_value = value_int;
        }
      }
      break;
      case FLOATS:{
        float value_float = *(float *)value.get_value();
        if(is_init) {
          res.values.float_value = std::max(res.values.float_value, value_float);
        } else {
          res.values.float_value = value_float;
        }
      }
      break;
      case CHARS:{
        const char * value_char = ((std::string *)value.get_value())->c_str();
        if(is_init){
          if(strcmp(value_char, res.values.string_value) > 0) {
            res.values.string_value = value_char;
          }
        }else {
          res.values.string_value = value_char;
        }
      }
      break;
      case DATES:{
        time_t value_time = ((const DateValue&)value).get_value_time_t();
        if(is_init){
          if(value_time > res.values.date_value) {
            res.values.date_value = value_time;
          }
        } else {
          res.values.date_value = value_time;
        }
      }
      break;
      default:
        return RC::MISUSE;
    }    
  }


  return RC::SUCCESS;
}


RC AggregationExeNode::min(const TupleValue &value, AggValue &res) {
  bool is_init = (res.values.int_value != NULL_VALUE);
  int type = value.get_type();

  if(!value.is_null()){
    switch(type){
      case INTS:{
        int value_int = *(int *)value.get_value();
        if(is_init) {
          res.values.int_value = std::min(res.values.int_value, value_int);          
        } else {
          res.values.int_value = value_int;
        }
      }
      break;
      case FLOATS:{
        float value_float = *(float *)value.get_value();
        if(is_init) {
          res.values.float_value = std::min(res.values.float_value, value_float);        
        } else {
          res.values.float_value = value_float;
        }
      }
      break;
      case CHARS:{
        const char * value_char = ((std::string *)value.get_value())->c_str();
        if(is_init) {
          if(strcmp(value_char, res.values.string_value) < 0) {
            res.values.string_value = value_char;
          }        
        } else {
          res.values.string_value = value_char;
        }

      }
      break;
      case DATES:{
        time_t value_time = ((const DateValue&)value).get_value_time_t();
        if(is_init){
          if(value_time < res.values.date_value) {
            res.values.date_value = value_time;
          }
        } else {
          res.values.date_value = value_time;
        }      
      }
      break;
      default:
      return RC::MISUSE;
    }    
  }
  return RC::SUCCESS;
}

RC AggregationExeNode::count(AggValue &res, bool is_null){
  if(!is_null){
    res.values.int_value += 1;
  }

  return RC::SUCCESS;
}


RC AggregationExeNode::avg(const TupleValue &value, AggValue &res, int size){
  bool is_init = (res.values.int_value != NULL_VALUE);
  int type = value.get_type();
  if(!value.is_null()){
    switch(type){
      case INTS:{
        int value_int = *(int *)value.get_value();
        if(is_init) {
          res.values.float_value = (res.values.float_value * (size - 1) + value_int) / size;
        } else {
          res.values.float_value = (float)value_int;
        }
      }
      break;

      case FLOATS:{
        int value_float = *(float  *)value.get_value();
        if(is_init){
          res.values.float_value = (res.values.float_value * (size -1) + value_float) / size;
        } else {
          res.values.float_value = value_float;
        }
      }
      break;

      case CHARS:{
        //char 不支持avg操作
        return RC::MISUSE;
      }
      break;
      case DATES:{
        time_t value_time = ((const DateValue&)value).get_value_time_t();
        if(is_init){
          res.values.date_value = (res.values.date_value * (size-1) + value_time) / size;
        } else {
          res.values.date_value = value_time;
        }
      }
      break;
      default:
        break;
    }    
  }

  return RC::SUCCESS;
}


