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
// Created by wangyunlai.wyl on 2021/5/18.
//

#include "storage/common/index_meta.h"
#include "storage/common/field_meta.h"
#include "storage/common/table_meta.h"
#include "common/lang/string.h"
#include "common/log/log.h"
#include "rc.h"
#include "json/json.h"

const static Json::StaticString FIELD_NAME("name");
const static Json::StaticString FIELD_FIELD_NAME("field_name");
const static Json::StaticString UNIQUE_NAME("unique");

RC IndexMeta::init(const char *name, const std::vector<FieldMeta *>& field_metas,int _unique) {
  if (nullptr == name || common::is_blank(name)) {
    return RC::INVALID_ARGUMENT;
  }

  name_ = name;
  for(auto & field_meta : field_metas){
    field_.emplace_back(field_meta->name());
  }
  unique = _unique;
  return RC::SUCCESS;
}
void IndexMeta::to_json(Json::Value &json_value) const {
  json_value[FIELD_NAME] = name_;
  Json::Value fields;
  for(const auto & i : field_){
    Json::Value field;
    field = i;
    fields.append(field);
  }
  json_value[FIELD_FIELD_NAME] = fields;
  json_value[UNIQUE_NAME] = unique;
}

RC IndexMeta::from_json(TableMeta &table, const Json::Value &json_value, IndexMeta &index) {
  const Json::Value &name_value = json_value[FIELD_NAME];
  const Json::Value &field_value = json_value[FIELD_FIELD_NAME];
  const Json::Value &unique_value = json_value[UNIQUE_NAME];
  if (!name_value.isString()) {
    LOG_ERROR("Index name is not a string. json value=%s", name_value.toStyledString().c_str());
    return RC::GENERIC_ERROR;
  }
  if (!unique_value.isInt()) {
    LOG_ERROR("unique name is not a int. json value=%s", name_value.toStyledString().c_str());
    return RC::GENERIC_ERROR;
  }
  if (!field_value.isArray() || field_value.empty()) {
    LOG_ERROR("Field name of index [%s] is not a array. json value=%s",
              name_value.asCString(), field_value.toStyledString().c_str());
    return RC::GENERIC_ERROR;
  }
  int index_field_num = field_value.size();
  std::vector<FieldMeta *> fields(index_field_num);
  for(int i = 0; i < index_field_num; i++){
    if(!field_value[i].isString()){
      LOG_ERROR("Field name is not a string. json value=%s", field_value[i].toStyledString().c_str());
      return RC::GENERIC_ERROR;
    }

    fields[i] = table.field(field_value[i].asCString());

    if(fields[i] == nullptr){
      LOG_ERROR("Deserialize index [%s]: no such field: %s", name_value.asCString(), field_value[i].asCString());
      return RC::SCHEMA_FIELD_MISSING;
    }
  }

  int intvalue=unique_value.asInt();
  return index.init(name_value.asCString(), fields,intvalue);
}

const char *IndexMeta::name() const {
  return name_.c_str();
}

const char *IndexMeta::field(int i) const {
  if(i >= field_.size()){
    return nullptr;
  }
  return field_[i].c_str();
}

std::vector<std::string> IndexMeta::getFields(){
  return field_;
}
void IndexMeta::desc(std::ostream &os) const {
  os << "index name=" << name_
     << ", field=" ;
  for(const auto & i : field_){
    os << i << " ";
  }
}