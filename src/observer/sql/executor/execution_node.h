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
// Created by Wangyunlai on 2021/5/13.
//

#ifndef __OBSERVER_SQL_EXECUTOR_EXECUTION_NODE_H_
#define __OBSERVER_SQL_EXECUTOR_EXECUTION_NODE_H_

#include <vector>
#include <unordered_map>
#include "storage/common/condition_filter.h"
#include "sql/executor/tuple.h"

class Table;
class Trx;

class ExecutionNode {
public:
  ExecutionNode() = default;
  virtual ~ExecutionNode() = default;

  virtual RC execute(TupleSet &tuple_set) = 0;
};

class SelectExeNode : public ExecutionNode {
public:
  SelectExeNode();
  virtual ~SelectExeNode();

  RC init(Trx *trx, Table *table, TupleSchema && tuple_schema, std::vector<DefaultConditionFilter *> &&condition_filters);

  RC execute(TupleSet &tuple_set) override;
private:
  Trx *trx_ = nullptr;
  Table  * table_;
  TupleSchema  tuple_schema_;
  std::vector<DefaultConditionFilter *> condition_filters_;
};

class JoinExeNode : public ExecutionNode {
public:
  JoinExeNode();
  virtual ~JoinExeNode();

  RC init(Trx *trx, 
          const TupleSet *left_table, const TupleSet *right_table,
          TupleSchema tuple_schema,
          std::vector<JoinConditionFilter*> condition_filters);

  RC execute(TupleSet &tuple_set) override;
  
private:
  Trx *trx_ = nullptr;
  const TupleSet *left_table_;
  const TupleSet *right_table_;
  TupleSchema tuple_schema_;
  std::vector<JoinConditionFilter*> condition_filters_;
};

class CartesianProductExeNode : public ExecutionNode {
public:
  CartesianProductExeNode();
  virtual ~CartesianProductExeNode();

  RC init(Trx *trx,
          const TupleSet *left_table, const TupleSet *right_table,
          const TupleSchema &tuple_schema);

  RC execute(TupleSet &tuple_set) override;

private:
  Trx *trx_ = nullptr;
  const TupleSet *left_table_;
  const TupleSet *right_table_;
  TupleSchema tuple_schema_;
};

class AggregationExeNode {
public:
  AggregationExeNode();
  virtual ~AggregationExeNode();

  RC init(Trx *trx,
          const TupleSet *table, std::vector<std::pair<const char *, AggInfo>> &&agg_infos);

//  RC execute(Tuple &tuple, std::vector<const char *> &agg_columns);
//  RC execute(std::vector<Tuple> tuples, std::vector<const char *> &agg_columns,
//               std::unordered_map<std::string, std::vector<Tuple>> group_map);
    RC execute(Tuple &tuple, std::vector<const char *> &agg_columns, std::vector<Tuple> *tuples_,
               const std::vector<std::pair<const char *, const char *>>& vector, std::vector<std::pair<const char *, int>> map);
private:
  RC init_index_map(std::unordered_map<const char *, int> &map);
  RC max(const TupleValue &value, AggValue &res);
  RC min(const TupleValue &value, AggValue &res);
  RC count(AggValue &res, bool is_null);
  RC avg(const TupleValue &value, AggValue &res, int size);


private:
  Trx *trx_ = nullptr;
  const TupleSet *table_;
  std::vector<std::pair<const char *, AggInfo>> agg_infos_;



};

 class ExprExeNode {
 public:
   RC init();
   RC execute();

 private:
   bool calculate(v1, op, v2);
 private:
   const TupleSet *table_;
   const Expression &expr_;
   expr_attr_infos_

 };

#endif //__OBSERVER_SQL_EXECUTOR_EXECUTION_NODE_H_
