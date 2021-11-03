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

#ifndef __OBSERVER_SQL_EXECUTOR_VALUE_H_
#define __OBSERVER_SQL_EXECUTOR_VALUE_H_

#include <string.h>

#include <string>
#include <ostream>
#include "sql/parser/parse.h"

class TupleValue {
public:
  TupleValue() = default;
  virtual ~TupleValue() = default;

  virtual void to_string(std::ostream &os) const = 0;
  virtual int compare(const TupleValue &other) const = 0;
  virtual const void *get_value() const = 0;
  virtual AttrType get_type() const = 0;
private:
};

class IntValue : public TupleValue {
public:
  explicit IntValue(int value) : value_(value), type_(INTS) {
  }

  void to_string(std::ostream &os) const override {
    os << value_;
  }

  int compare(const TupleValue &other) const override {
    const IntValue & int_other = (const IntValue &)other;
    return value_ - int_other.value_;
  }

  void set_value(int value);

  const void *get_value() const override;

  AttrType get_type() const override;

private:
  int value_;
  AttrType type_;
};

class FloatValue : public TupleValue {
public:
  explicit FloatValue(float value) : value_(value), type_(FLOATS) {
  }

  void to_string(std::ostream &os) const override {
    os << value_;
  }

  int compare(const TupleValue &other) const override {
    const FloatValue & float_other = (const FloatValue &)other;
    float result = value_ - float_other.value_;
    if (result > 0) { // 浮点数没有考虑精度问题
      return 1;
    }
    if (result < 0) {
      return -1;
    }
    return 0;
  }

  void set_value(float value);

  const void *get_value() const override;

  AttrType get_type() const override;

private:
  float value_;
  AttrType type_;
};

class StringValue : public TupleValue {
public:
  StringValue(const char *value, int len) : value_(value, len), type_(CHARS){
  }
  explicit StringValue(const char *value) : value_(value) {
  }

  void to_string(std::ostream &os) const override {
    os << value_;
  }

  int compare(const TupleValue &other) const override {
    const StringValue &string_other = (const StringValue &)other;
    return strcmp(value_.c_str(), string_other.value_.c_str());
  }

  void set_value(std::string &value);

  const void *get_value() const override;

  AttrType get_type() const override;
private:
  std::string value_;
  AttrType type_;
};

class DateValue : public TupleValue{
public:
    explicit DateValue(const char *value, int len) : value_(value, len), type_(DATES){
    }
    explicit DateValue(time_t value);

    void to_string(std::ostream &os) const override;

    void set_value(std::string &value);
    void set_value(time_t &value);

    time_t get_value_time_t() const;
    const void *get_value() const override;

    AttrType get_type() const override;

    int compare(const TupleValue &other) const override;

private:
    static time_t str_to_time_t(const std::string *str) ;
    static std::string time_t_to_str(time_t time) ;
private:
    std::string value_;
    AttrType type_;
};

#endif //__OBSERVER_SQL_EXECUTOR_VALUE_H_
