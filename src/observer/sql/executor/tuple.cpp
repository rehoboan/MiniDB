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

#include "sql/executor/tuple.h"
#include <algorithm>
#include <sstream>

Tuple::Tuple(const Tuple &other) {
  LOG_PANIC("Copy constructor of tuple is not supported");
  exit(1);
}

Tuple::Tuple(Tuple &&other) noexcept : values_(std::move(other.values_)) {
}

Tuple & Tuple::operator=(Tuple &&other) noexcept {
  if (&other == this) {
    return *this;
  }

  values_.clear();
  values_.swap(other.values_);
  return *this;
}

Tuple::~Tuple() {
}

// add (Value && value)
void Tuple::add(TupleValue *value) {
  values_.emplace_back(value);
}
void Tuple::add(const std::shared_ptr<TupleValue> &other) {
  values_.emplace_back(other);
}
void Tuple::add(int value) {
  add(new IntValue(value));
}

void Tuple::add(float value) {
  add(new FloatValue(value));
}

void Tuple::add(){
  add(new StringValue());
}

void Tuple::add(const char *s, int len) {
  add(new StringValue(s, len));
}

void Tuple::add(time_t value){
  add(new DateValue(value));
}

////////////////////////////////////////////////////////////////////////////////

std::string TupleField::to_string() const {
  return std::string(table_name_) + "." + field_name_ + std::to_string(type_);
}

////////////////////////////////////////////////////////////////////////////////
void TupleSchema::from_table(Table *table, TupleSchema &schema) {
  const char *table_name = table->name();
  TableMeta &table_meta = table->table_meta();
  const int field_num = table_meta.field_num();
  for (int i = 0; i < field_num; i++) {
    FieldMeta *field_meta = table_meta.field(i);
    if (field_meta->visible()) {
      schema.add(TYPE(field_meta->type()), table_name, field_meta->name());
    }
  }
}

void TupleSchema::add(int type, const char *table_name, const char *field_name) {
  fields_.emplace_back(type, table_name, field_name);
}

void TupleSchema::add_if_not_exists(int type, const char *table_name, const char *field_name) {
  for (const auto &field: fields_) {
    if (0 == strcmp(field.table_name(), table_name) &&
        0 == strcmp(field.field_name(), field_name)) {
      return;
    }
  }

  add(type, table_name, field_name);
}

void TupleSchema::append(const TupleSchema &other) {
  fields_.reserve(fields_.size() + other.fields_.size());
  for (const auto &field: other.fields_) {
    fields_.emplace_back(field);
  }
}

int TupleSchema::index_of_field(const char *table_name, const char *field_name) const {
  const int size = fields_.size();
  for (int i = 0; i < size; i++) {
    const TupleField &field = fields_[i];
    if (0 == strcmp(field.table_name(), table_name) && 0 == strcmp(field.field_name(), field_name)) {
      return i;
    }
  }
  return -1;
}

void TupleSchema::print(std::ostream &os) const {
  if (fields_.empty()) {
    os << "No schema";
    return;
  }

  // 判断有多张表还是只有一张表
  std::set<std::string> table_names;
  for (const auto &field: fields_) {
    table_names.insert(field.table_name());
  }

  for (std::vector<TupleField>::const_iterator iter = fields_.begin(), end = --fields_.end();
       iter != end; ++iter) {
    if (table_names.size() > 1) {
      os << iter->table_name() << ".";
    }
    os << iter->field_name() << " | ";
  }

  if (table_names.size() > 1) {
    os << fields_.back().table_name() << ".";
  }
  os << fields_.back().field_name() << std::endl;
}

/////////////////////////////////////////////////////////////////////////////
TupleSet::TupleSet(TupleSet &&other) : tuples_(std::move(other.tuples_)), schema_(other.schema_){
  other.schema_.clear();
}

TupleSet &TupleSet::operator=(TupleSet &&other) {
  if (this == &other) {
    return *this;
  }

  schema_.clear();
  schema_.append(other.schema_);
  other.schema_.clear();

  tuples_.clear();
  tuples_.swap(other.tuples_);
  return *this;
}

void TupleSet::add(Tuple &&tuple) {
  tuples_.emplace_back(std::move(tuple));
}

void TupleSet::clear() {
  tuples_.clear();
  schema_.clear();
}

void TupleSet::print(std::ostream &os) const {
  if (schema_.fields().empty()) {
    LOG_WARN("Got empty schema");
    return;
  }

  schema_.print(os);

  for (const Tuple &item : tuples_) {
    const std::vector<std::shared_ptr<TupleValue>> &values = item.values();
    for (std::vector<std::shared_ptr<TupleValue>>::const_iterator iter = values.begin(), end = --values.end();
         iter != end; ++iter) {
      (*iter)->to_string(os);
      os << " | ";
    }
    values.back()->to_string(os);
    os << std::endl;
  }
}


void TupleSet::print(std::ostream &os, std::vector<std::pair<const char *, const char *>> &select_columns, bool is_multi_table) {
  if (schema_.fields().empty() || select_columns.empty()) {
    LOG_WARN("Got empty schema");
    return;
  }


  std::vector<int> select_columns_id;
  for(int i=0; i<select_columns.size(); i++) {
    int idx = schema_.index_of_field(select_columns[i].first, select_columns[i].second);
    if(idx == -1) {
      LOG_WARN("The column of required columns is non-exist in the table");
      return;
    }
    select_columns_id.push_back(idx);
  }
  //print schema format
  for(int i=0; i<select_columns_id.size()-1; i++) {
    if(is_multi_table){
        os<<select_columns[i].first<<".";
    }
    os<<select_columns[i].second<<" | ";
  }
  if(is_multi_table) {
    os<<select_columns.back().first<<".";
  }
  os<<select_columns.back().second<<std::endl;

  //print select result

  for (const Tuple &item : tuples_) {
    const std::vector<std::shared_ptr<TupleValue>> &values = item.values();
    for(int i=0; i<select_columns_id.size()-1; i++) {
      int idx = select_columns_id[i];
      values[idx]->to_string(os);
      os << " | ";
    }
    int idx = select_columns_id.back();
    values[idx]->to_string(os);
    os << std::endl;
  }
  
}

void TupleSet::set_schema(const TupleSchema &schema) {
  schema_ = schema;
}

const TupleSchema &TupleSet::get_schema() const {
  return schema_;
}

bool TupleSet::is_empty() const {
  return tuples_.empty();
}

int TupleSet::size() const {
  return tuples_.size();
}

const Tuple &TupleSet::get(int index) const {
  return tuples_[index];
}

const std::vector<Tuple> &TupleSet::tuples() const {
  return tuples_;
}

//bool TupleSet::comparison(const Tuple &t1,const Tuple &t2){
//  if(order_num==1){
//
//  }
//
//}


RC TupleSet::sort(SubSelects subselects) {
  TupleSchema schema = schema_;
  for (int i = 0; i < subselects.order_num; ++i) {
    int field_index;
    if (subselects.order_des[i].relation_name == nullptr) {
      field_index = schema.index_of_field(subselects.relations[0], subselects.order_des[i].attribute_name);
    } else {
      field_index = schema.index_of_field(subselects.order_des[i].relation_name, subselects.order_des[i].attribute_name);
    }
    if (field_index == -1) {
      return RC::SCHEMA_FIELD_NOT_EXIST;
    }
  }

  std::sort(tuples_.begin(), tuples_.end(),
              [subselects, schema](const Tuple &t1, const Tuple &t2) {
                  int i = 0;
                  int ret = 0;
                  while (true){
                    int field_index;
                    if (subselects.order_des[i].relation_name == nullptr) {
                      field_index = schema.index_of_field(subselects.relations[0], subselects.order_des[i].attribute_name);
                    } else {
                      field_index = schema.index_of_field(subselects.order_des[i].relation_name, subselects.order_des[i].attribute_name);
                    }
                    ret = t1.get(field_index).compare(t2.get(field_index));
                    i++;
                    if(ret != 0 || i==subselects.order_num){
                      break;
                    }
                  }
                  if (subselects.order_des[i-1].type == kOrderDesc) return ret > 0;
                  else return ret < 0;

  }

    );
  return RC::SUCCESS;

}

RC  TupleSet::set_group_by(SubSelects subselects, std::unordered_map<std::string,TupleSet> &group_map) {

  int field_index;
  std::vector<int> group_index_v;
  for (int i = 0; i < subselects.group_num; ++i) {
    if (subselects.group_des[i].relation_name == nullptr) {
      field_index = schema_.index_of_field(subselects.relations[0], subselects.group_des[i].attribute_name);
    } else {
      field_index = schema_.index_of_field(subselects.group_des[i].relation_name, subselects.group_des[i].attribute_name);
    }
    if (field_index == -1){
      return RC::SCHEMA_FIELD_NOT_EXIST;
    }

    group_index_v.push_back(field_index);
  }

  for(Tuple &tuple : tuples_) {
    std::stringstream key;
    for (int & group_index : group_index_v){
       tuple.get(group_index).to_string(key);
    }
    group_map[key.str()];
  }

  for(Tuple &tuple : tuples_) {
    std::stringstream key;
    for (int & group_index : group_index_v){
      tuple.get(group_index).to_string(key);
    }
    group_map[key.str()].add(std::move(tuple));
  }
  return RC::SUCCESS;
}


/////////////////////////////////////////////////////////////////////////////
TupleRecordConverter::TupleRecordConverter(Table *table, TupleSet &tuple_set) :
        table_(table), tuple_set_(tuple_set){
}

void TupleRecordConverter::add_record(const char *record) {
  const TupleSchema &schema = tuple_set_.schema();
  Tuple tuple;
  TableMeta &table_meta = table_->table_meta();
  // null域的元信息
  FieldMeta *null_field_meta = table_meta.field(TableMeta::null_field_name());//field信息
  int null_v = *(int*)(record + null_field_meta->offset() );
  // 行的null域值
  for (const TupleField &field : schema.fields()) {//需要提取的列
    FieldMeta *field_meta = table_meta.field(field.field_name());//field信息
    // assert field_meta !=nullptr

    int index = table_meta.getIndex(field.field_name()) - 2;
    if(index == -1){
      continue;//erro
    }
    if(null_v&(1<<index)){//空值
      // 现在当做Cstring来处理
      tuple.add();
      continue;
    }
    int type = field_meta->type();
    RID rid;
    switch (TYPE(type)) {
      case INTS: {
        int value = *(int*)(record + field_meta->offset());
        tuple.add(value);
      }
        break;
      case FLOATS: {
        float value = *(float *)(record + field_meta->offset());
        tuple.add(value);
      }
        break;
      case CHARS: {
        const char *s = record + field_meta->offset();  // 现在当做Cstring来处理
        tuple.add(s, strlen(s));
      }
        break;
      case DATES: {
        const char *s = record + field_meta->offset();  // 现在当做Cstring来处理
        std::shared_ptr<DateValue> p(new DateValue(s,strlen(s)));
        tuple.add(p);
      }
        break;
      case TEXTS: {

        rid.page_num = *(int*)(record + field_meta->offset());
        rid.slot_num = *(int*)(record + field_meta->offset()+4);
        std::string ans = sys_tbs->getText(rid);
        tuple.add(ans.c_str(), ans.length());
      }
        break;
      default: {
        LOG_PANIC("Unsupported field type. type=%d", field_meta->type());
      }
    }
  }

  tuple_set_.add(std::move(tuple));
}


