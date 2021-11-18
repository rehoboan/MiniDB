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

#ifndef __OBSERVER_STORAGE_COMMON_CONDITION_FILTER_H_
#define __OBSERVER_STORAGE_COMMON_CONDITION_FILTER_H_

#include "rc.h"
#include "sql/parser/parse.h"
#include "record_manager.h"
#include "common/log/log.h"
#include "storage/common/table.h"
#include "sql/executor/tuple.h"
#include "db.h"



struct Record;
class Table;

union ReturnValue {
    float value_f;
    char *value_s;
};

struct ConDesc {
    bool   is_attr;     // 是否属性，false 表示是值
    int    attr_length; // 如果是属性，表示属性值长度
    int    attr_offset; // 如果是属性，表示在记录中的偏移量
    void * value;       // 如果是值类型，这里记录值的数据
    int attr_type;
    int index;
};

void modify_return_value(int type, ReturnValue &ret, const char *data);
int compare_data(int left_type, const char *left_data, int right_type, const char *right_data);
const ReturnValue switch_data_type(int source_type, int target_type, const char *data);

class ConditionFilter {
public:

  virtual ~ConditionFilter();

  /**
   * Filter one record
   * @param rec
   * @return true means match condition, false means failed to match.
   */
  virtual bool filter(const Record &rec) const = 0;
  virtual bool filter(const Tuple &tuple, const TupleSchema &tuple_schema) const = 0;
  virtual bool filter(const Tuple &left_tuple, const TupleSchema &left_schema, 
                      const Tuple &right_tuple, const TupleSchema &right_schema) const = 0;

};

class DefaultConditionFilter : public ConditionFilter {
public:
    DefaultConditionFilter();
    ~DefaultConditionFilter() override;

//    RC init(const ConDesc &left, const ConDesc &right, AttrType attr_type, CompOp comp_op);
    RC init(const ConDesc &left, const ConDesc &right, int left_attr_type, int right_attr_type, CompOp comp_op);
    RC init(Table &table, const Condition &condition);


  bool filter(const Record &rec) const override;
  bool filter(const Tuple &tuple, const TupleSchema &tuple_schema) const override {return false;}
  bool filter(const Tuple &left_tuple, const TupleSchema &left_schema,
                      const Tuple &right_tuple, const TupleSchema &right_schema) const override {return false;}


public:
    const ConDesc &left() const {
      return left_;
    }

    const ConDesc &right() const {
      return right_;
    }

    CompOp comp_op() const {
      return comp_op_;
    }

private:
    ConDesc  left_{};
    ConDesc  right_{};
//    AttrType attr_type_ = UNDEFINED;
    int left_attr_type_{};
    int right_attr_type_{};
    CompOp   comp_op_ = NO_OP;


};

class JoinConditionFilter : public ConditionFilter {
public:
  JoinConditionFilter();
  ~JoinConditionFilter() override;

  RC init(const RelAttr &left, const RelAttr &right, CompOp comp_op);

  bool filter(const Tuple &tuple, const TupleSchema &tuple_schema) const override;
  bool filter(const Tuple &left_tuple, const TupleSchema &left_schema,
                      const Tuple &right_tuple, const TupleSchema &right_schema) const override;
  bool filter(const Record &rec) const override {return false;} //nothing to do here


private:
  RelAttr left_{};
  RelAttr right_{};
  CompOp comp_op_ = NO_OP;
};

class CompositeConditionFilter : public ConditionFilter {
public:
    CompositeConditionFilter() = default;
    ~CompositeConditionFilter() override;


    RC init(const ConditionFilter *filters[], int filter_num);
    RC init(Table &table, const Condition *conditions, int condition_num);
    bool filter(const Record &rec) const override;


  bool filter(const Tuple &tuple, const TupleSchema &tuple_schema) const override;

  bool filter(const Tuple &left_tuple, const TupleSchema &left_schema,
                      const Tuple &right_tuple, const TupleSchema &right_schema) const override;

public:
    int filter_num() const {
      return filter_num_;
    }
    const ConditionFilter &filter(int index) const {
      return *filters_[index];
    }

private:
    RC init(const ConditionFilter *filters[], int filter_num, bool own_memory);
private:
    const ConditionFilter **      filters_ = nullptr;
    int                           filter_num_ = 0;
    bool                          memory_owner_ = false; // filters_的内存是否由自己来控制
};

#endif // __OBSERVER_STORAGE_COMMON_CONDITION_FILTER_H_