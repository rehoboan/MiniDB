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
  const char *src_table_name = src_schema.field(0).table_name();
  if(strcmp(src_table_name, target_table_name)==0) {
    int idx = src_schema.index_of_field(target_table_name, target_tuple_field.field_name());
    if(idx != -1) {
      res_tuple.add(src_tuple.get_pointer(idx));
      return true;
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
          TupleSet *left_table, TupleSet *right_table,
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

  std::vector<Tuple> left_tuples = left_table_->tuples();
  std::vector<Tuple> right_tuples = right_table_->tuples();

  TupleSchema left_schema = left_table_->get_schema();
  TupleSchema right_schema = right_table_->get_schema();

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
                                TupleSet *left_table, TupleSet *right_table,
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

  std::vector<Tuple> left_tuples = left_table_->tuples();
  std::vector<Tuple> right_tuples = right_table_->tuples();

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

