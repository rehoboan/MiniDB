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
// Created by Wangyunlai on 2021/5/12.
//

#ifndef __OBSERVER_STORAGE_COMMON_TABLE_META_H__
#define __OBSERVER_STORAGE_COMMON_TABLE_META_H__

#include <string>
#include <vector>

#include "rc.h"
#include "storage/common/field_meta.h"
#include "storage/common/index_meta.h"
#include "common/lang/serializable.h"

class TableMeta : public common::Serializable {
public:
    TableMeta() = default;
    ~TableMeta() = default;

    TableMeta(TableMeta &other);

    void swap(TableMeta &other) noexcept;

    RC init(const char *name, int field_num, const AttrInfo attributes[]);

    RC add_index(const IndexMeta &index);

    static const char * null_field_name(){
      return "__null";
    }
    static int null_field_type(){
      return INTS;
    }
    static size_t null_field_len(){
      return sizeof(int);
    }
    static int null_field_offset(){
      return sizeof(int);
    }
public:
    const char * name() const;
    const FieldMeta * trx_field() const;
    FieldMeta * field(int index);
//    const FieldMeta * field(const char *name) const;
    const FieldMeta * find_field_by_offset(int offset) const;
    int getIndex(const char *name) const;
    std::vector<FieldMeta *> fields(std::vector<std::string> fields);

    int field_num() const;
    int sys_field_num() const;

    const IndexMeta * index(const char *name) const;
//    const IndexMeta * find_index_by_field(const char *field) const;
//    IndexMeta * find_index_by_field(std::vector<FieldMeta *> field_metas) ;
    const IndexMeta * find_index_by_field(std::vector<FieldMeta *> field_metas) const;
    FieldMeta * field(const char *name);

    IndexMeta * index(int i);
    int index_num() const;

    int record_size() const;

public:
    int  serialize(std::ostream &os) const override;
    int  deserialize(std::istream &is) override;
    int  get_serial_size() const override;
    void to_string(std::string &output) const override;
    void desc(std::ostream &os) const;

private:
    static RC init_sys_fields();
private:
    std::string   name_;
    std::vector<FieldMeta>  fields_; // 包含sys_fields
    std::vector<IndexMeta>  indexes_;

    int  record_size_ = 0;

    static std::vector<FieldMeta> sys_fields_;
};

#endif // __OBSERVER_STORAGE_COMMON_TABLE_META_H__