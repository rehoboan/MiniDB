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
// Created by Longda on 2021/4/13.
//

#ifndef __OBSERVER_SQL_PARSER_PARSE_H__
#define __OBSERVER_SQL_PARSER_PARSE_H__

#include "rc.h"
#include "sql/parser/parse_defs.h"
template<class T>
struct MultiValueLinkNode {
  T value;

  MultiValueLinkNode<T> *next_value;

  MultiValueLinkNode(): next_value(nullptr){}
};

RC parse(const char *st, Query *sqln);

#endif //__OBSERVER_SQL_PARSER_PARSE_H__

