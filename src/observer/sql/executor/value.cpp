/* Copyright (c) 2021 Xie Meiyi(xiemeiyi@hust.edu.cn) and OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */
#include "sql/executor/value.h"

void IntValue::set_value(int value){
    value_ = value;
}

const void *IntValue::get_value() const{
    const int *value = &value_;
    return value;
}

AttrType IntValue::get_type() const {
    return type_;
}

void FloatValue::set_value(float value){
    value_ = value;
}

const void *FloatValue::get_value() const{
    const float *value = &value_;
    return value;
}

AttrType FloatValue::get_type() const {
    return type_;
}

void StringValue::set_value(std::string &value) {
    value_.assign(value);
}

const void *StringValue::get_value() const {
    const std::string *value = &value_;
    return value;
}

AttrType StringValue::get_type() const {
    return type_;
}


DateValue::DateValue(time_t value){
    type_ = DATES;
    value_ = time_t_to_str(value);
}

time_t DateValue::str_to_time_t(const std::string *str) {
    const char *s = str->c_str();
    tm tm_{};
    int year, month, day;
    sscanf(s,"%d-%d-%d",&year,&month,&day);

    tm_.tm_year = year - 1900;
    tm_.tm_mon = month - 1;
    tm_.tm_mday = day;
    tm_.tm_hour = 0;
    tm_.tm_min = 0;
    tm_.tm_sec = 0;
    tm_.tm_isdst = 0;
    time_t t_ = mktime(&tm_);

    return t_;
}

std::string DateValue::time_t_to_str(time_t time) {
    tm *tm_ = localtime(&time);
    int year, month, day;
    year = tm_->tm_year + 1900;
    month = tm_->tm_mon + 1;
    day = tm_->tm_mday;
    char yearStr[5], monthStr[3], dayStr[3];
    sprintf(yearStr, "%d", year);
    sprintf(monthStr, "%d", month);
    sprintf(dayStr, "%d", day);

    char c[11];
    sprintf(c, "%s-%s-%s", yearStr, monthStr, dayStr);

    return {c};
}

void DateValue::to_string(std::ostream &os) const {
    os << value_;
}

void DateValue::set_value(std::string &value){
    value_.assign(value);
    //is_null_ = false;
}

void DateValue::set_value(time_t &value){
    value_ = time_t_to_str(value);
    //is_null_ = false;
}

const void *DateValue::get_value() const {
    const std::string *value = &value_;
    return value;
}

AttrType DateValue::get_type() const {
    return type_;
}

time_t DateValue::get_value_time_t() const{
    // if(is_null_){
    //     return -1;
    // }
    return str_to_time_t(&value_);
}

int DateValue::compare(const TupleValue &other) const  {
    // if(is_null_){
    //     return -1;
    // }
    if(other.get_type() != DATES){
        return -1;
    }
    int cmp = 0;
    time_t val = str_to_time_t(&value_);
    time_t other_val = str_to_time_t((std::string *)other.get_value());
    if(val > other_val){
        cmp = 1;
    }
    else if(val < other_val){
        cmp = -1;
    }
    return cmp;
}

// bool DateValue::is_null() const {
//     return is_null_;
// }

