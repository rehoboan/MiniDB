/* Copyright (c) 2021 Xie Meiyi(xiemeiyi@hust.edu.cn) and OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

#include <cmath>
#include "sql/executor/value.h"

union ReturnValue {
    float value_f;
    char *value_s;
};

void modify_return_value(int type, ReturnValue &ret, const char *data){
  switch (type){
    case INTS:;
      break;
    case FLOATS:
      ret.value_f = *(float *)data;
      break;
    case CHARS:
      strcpy(ret.value_s, data);
      break;
    case DATES:
      strcpy(ret.value_s, data);
      break;
    default:
      break;
  }
}

std::string time_t_to_str(std::time_t time){
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


const ReturnValue switch_data_type(int source_type, int target_type, const char *data){
  ReturnValue res;
  modify_return_value(source_type, res, data);
  if(source_type == target_type){
    return res;
  }

  switch (source_type){
    case CHARS: {
      switch (target_type){
        case INTS:{
          // TODO
        }
          break;
        case FLOATS:{
          // TODO
        }
        default:
          break;
      }
    }
      break;
    case INTS: {
      switch (target_type){
        case CHARS:{
          // TODO
        }
          break;
        case FLOATS:{
          res.value_f = (float)*(int *)data;
        }
        default:

          break;
      }
    }
    case FLOATS: {
      switch (target_type){
        case CHARS:{
          // TODO
        }
          break;
        case INTS:{
        }
        default:
          break;
      }
    }
      break;
    default:
      break;

  }
  return res;
}


int compare_data(int left_type, const char *left_data, int right_type, const char *right_data){
  int res = 0;

  if (left_type == CHARS && right_type == CHARS){
    res = strcmp(left_data, right_data);
  }
  else if (left_type == CHARS || right_type == CHARS){
    return -1;
  }
  if (left_type == DATES && right_type == DATES){
    res = strcmp(left_data, right_data);
  }
  else if (left_type == DATES || right_type == DATES){
    return -1;
  }
  if(left_type == FLOATS || right_type == FLOATS){
    float left = switch_data_type(left_type, FLOATS, left_data).value_f;
    float right = switch_data_type(right_type, FLOATS, right_data).value_f;
    float diff = left - right;

    if(std::abs(diff) >= 0 && std::abs(diff) <= 0.000001){
      res = 0;
    }
    else if(diff < 0){
      res = -1;
    }
    else{
      res = 1;
    }
  }
  else if(left_type == INTS && right_type == INTS){
    int left = *(int*)left_data;
    int right = *(int*)right_data;
    res = left - right;
  }
  else{
    // TODO ????????????int ??????float ?????????float ??????int?????????
    if(left_type == FLOATS && right_type == INTS || left_type == INTS && right_type == FLOATS){
      float left = switch_data_type(left_type, FLOATS, left_data).value_f;
      float right = switch_data_type(right_type, FLOATS, right_data).value_f;
      float diff = left - right;
      if(abs(diff) >= 0 && abs(diff) <= 0.000001){
        res = 0;
      }
      else if(diff < 0){
        res = -1;
      }
      else{
        res = 1;
      }
    }
  }


  return res;
}


int in_op(int left_type, const char *left_data, int right_type, void *right_data_head, size_t right_data_num) {
  printf("get in in_op function\n");
  
  int res = 0;
  if(right_data_num == 0) {
    printf("get in in_op function and null value\n");
    //????????????not in???true
    return res;
  }
  switch (left_type) {
    case INTS: {
      int left = *(int*)left_data;
      if(right_type == INTS){
        int *rights = (int*)right_data_head;
        for(int i=0; i<right_data_num; i++){
          if(left == rights[i]) {
            return 1;
          }
        }        
      } else if(right_type == FLOATS){
        float *rights = (float*)right_data_head;
        for(int i=0; i<right_data_num; i++){
          if(std::abs(rights[i]-left)<=0.000001)
            return 1;
        }
      }
      return res;
    }
    case FLOATS: {
      float left = switch_data_type(left_type, FLOATS, left_data).value_f;
      if(right_type == FLOATS) {
        float* rights = (float*)right_data_head;
        for(int i=0; i<right_data_num; i++){
          float diff = left - rights[i];
          if(std::abs(diff)>=0 && std::abs(diff) <= 0.000001) {
            return 1;
          }
        }       
      } else if(right_type == INTS) {
        int* rights = (int *)right_data_head;
        for(int i=0; i<right_data_num; i++){
          float diff = left - rights[i];
          if(std::abs(diff)>=0 && std::abs(diff) <= 0.000001)
            return 1;
        }
      }

      return res;
    }
    case CHARS: {
      MultiValueLinkNode *right = (MultiValueLinkNode *)(right_data_head);
      while(right){
        if(!strcmp(left_data, right->value)){
          return 1;
        }
        right = right->next_value;
      }
      return res;
    }
    case DATES: {
      MultiValueLinkNode *right = (MultiValueLinkNode *)(right_data_head);
      while(right){
        const char *right_data = right->value;
        if(!strcmp(left_data, right_data)){
          return 1;
        }
        right = right->next_value;
      }
      return res;
    }
    default:
    break;
  }
  return res;
}




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
  os << round(value_*100)/100.0;
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
    if(other.get_type() != CHARS || is_null_){
        return -1;
    }
    return compare_data(type_, (char *)(((std::string *)get_value())->c_str()),
                        other.get_type(), (char *)(((std::string *)other.get_value())->c_str()));
}

bool StringValue::is_null() const {
    return is_null_;
}



DateValue::DateValue(std::time_t value){
    type_ = DATES;
    value_ = time_t_to_str(value);
}

std::time_t DateValue::str_to_time_t(const std::string *str) {
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
    std::time_t t_ = mktime(&tm_);

    return t_;
}

std::string DateValue::time_t_to_str(std::time_t time) {
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

    is_null_ = false;

}

void DateValue::set_value(std::time_t &value){
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

std::time_t DateValue::get_value_time_t() const{

    if(is_null_){
        return -1;
    }

    return str_to_time_t(&value_);
}

int DateValue::compare(const TupleValue &other) const  {

    if(is_null_){
        return -1;
    }
  
    if(other.get_type() != DATES){
        return -1;
    }
    int cmp = 0;
    std::time_t val = str_to_time_t(&value_);
    std::time_t other_val = str_to_time_t((std::string *)other.get_value());
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

