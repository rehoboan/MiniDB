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


int compare_data(int left_type, const char *left_data,
                 int right_type, const char *right_data);

void IntValue::to_string(std::ostream &os) const{
    os << value_;
}
void IntValue::set_value(int value){
    value_ = value;
    is_null_ = false;
}
const void *IntValue::get_value() const{
    const int *value = &value_;
    return value;
}
int IntValue::get_type() const {
    return type_;
}

int IntValue::compare(const TupleValue &other) const {
    if(is_null_){
        return -1;
    }
    return compare_data(type_, (char *)get_value(), other.get_type(), (char *)(other.get_value()));
}

bool IntValue::is_null() const {
    return is_null_;
}

void FloatValue::to_string(std::ostream &os) const {
    os << value_;
}

void FloatValue::set_value(float value){
    value_ = value;
    is_null_ = false;
}

const void *FloatValue::get_value() const {
    const float *value = &value_;
    return value;
}

int FloatValue::get_type() const {
    return type_;
}

int FloatValue::compare(const TupleValue &other) const  {
    if(is_null_){
        return -1;
    }
    return compare_data(type_, (char *)get_value(), other.get_type(), (char *)(other.get_value()));
}

bool FloatValue::is_null() const {
    return is_null_;
}

void StringValue::to_string(std::ostream &os) const {
    os << value_;
}

void StringValue::set_value(std::string &value){
    value_.assign(value);
    is_null_ = false;
}

const void *StringValue::get_value() const {
    const std::string *value = &value_;
    return value;
}

int StringValue::get_type() const {
    return type_;
}

int StringValue::compare(const TupleValue &other) const {
    if(is_null_){
        return -1;
    }
    // TODO 暂不支持string和其它类型的比对
    if(other.get_type() != CHARS){
        return -1;
    }
    return compare_data(type_, (char *)(((std::string *)get_value())->c_str()),
                        other.get_type(), (char *)(((std::string *)other.get_value())->c_str()));
}

bool StringValue::is_null() const {
    return is_null_;
}


DateValue::DateValue(time_t value){
    type_ = DATES;
    value_ = time_t_to_str(value);
}

time_t DateValue::str_to_time_t(const std::string *str) const{
    const char *c = str->c_str();
    tm tm_;
    int year, month, day, hour, minute, second;
    hour = 0;
    minute = 0;
    second = 0;
    sscanf(c, "%d-%d-%d", &year, &month, &day);
    tm_.tm_year = year - 1900;                 // 年，由于tm结构体存储的是从1900年开始的时间，所以tm_year为int临时变量减去1900。
    tm_.tm_mon = month - 1;                    // 月，由于tm结构体的月份存储范围为0-11，所以tm_mon为int临时变量减去1。
    tm_.tm_mday = day;                         // 日。
    tm_.tm_hour = hour;                        // 时。
    tm_.tm_min = minute;                       // 分。
    tm_.tm_sec = second;                       // 秒。
    tm_.tm_isdst = 0;                          // 非夏令时。
    time_t t_ = mktime(&tm_);                  // 将tm结构体转换成time_t格式。

    return t_;                                 // 返回值。
}

std::string DateValue::time_t_to_str(time_t time) const{
    tm *tm_ = localtime(&time);                // 将time_t格式转换为tm结构体
    int year, month, day;// 定义时间的各个int临时变量。
    year = tm_->tm_year + 1900;                // 临时变量，年，由于tm结构体存储的是从1900年开始的时间，所以临时变量int为tm_year加上1900。
    month = tm_->tm_mon + 1;                   // 临时变量，月，由于tm结构体的月份存储范围为0-11，所以临时变量int为tm_mon加上1。
    day = tm_->tm_mday;                    // 临时变量，秒。
    char yearStr[5], monthStr[3], dayStr[3];// 定义时间的各个char*变量。
    sprintf(yearStr, "%d", year);              // 年。
    sprintf(monthStr, "%d", month);            // 月。
    sprintf(dayStr, "%d", day);                // 日。

    char c[11];                                // 定义总日期时间char*变量。
    sprintf(c, "%s-%s-%s", yearStr, monthStr, dayStr);// 将年月日时分秒合并。

    return std::string(c);                                // 返回转换日期时间后的string变量。
}

void DateValue::to_string(std::ostream &os) const {
    os << value_;
}

void DateValue::set_value(std::string &value){
    value_.assign(value);
    is_null_ = false;
}

void DateValue::set_value(time_t &value){
    value_ = time_t_to_str(value);
    is_null_ = false;
}

const void *DateValue::get_value() const {
    const std::string *value = &value_;
    return value;
}

int DateValue::get_type() const {
    return type_;
}

time_t DateValue::get_value_time_t() const{
    if(is_null_){
        return -1;
    }
    return str_to_time_t(&value_);
}

int DateValue::compare(const TupleValue &other) const  {
    if(is_null_){
        return -1;
    }
    // TODO 暂不支持DATES和其它类型的比对
    if(other.get_type() != DATES){
        return -1;
    }
    int cmp = 0;
    int val = str_to_time_t(&value_);
    int other_val = str_to_time_t((std::string *)other.get_value());
    if(val > other_val){
        cmp = 1;
    }
    else if(val < other_val){
        cmp = -1;
    }
    return cmp;
}

bool DateValue::is_null() const {
    return is_null_;
}