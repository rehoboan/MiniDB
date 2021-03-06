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

#include <limits.h>
#include <string.h>
#include <algorithm>
#include "storage/common/db.h"
#include "storage/common/table.h"
#include "storage/common/table_meta.h"
#include "common/log/log.h"
#include "common/lang/string.h"
#include "storage/default/disk_buffer_pool.h"
#include "storage/common/record_manager.h"
#include "storage/common/condition_filter.h"
#include "storage/common/meta_util.h"
#include "storage/common/index.h"
#include "storage/common/bplus_tree_index.h"
#include "storage/trx/trx.h"

Table::Table() :
        data_buffer_pool_(nullptr),
        file_id_(-1),
        record_handler_(nullptr) {
}

Table::~Table() {
  delete record_handler_;
  record_handler_ = nullptr;

  if (data_buffer_pool_ != nullptr && file_id_ >= 0) {
    data_buffer_pool_->close_file(file_id_);
    data_buffer_pool_ = nullptr;
  }

  LOG_INFO("Table has been closed: %s", name());
}

RC Table::create(const char *path, const char *name, const char *base_dir, int attribute_count, const AttrInfo attributes[]) {

  if (nullptr == name || common::is_blank(name)) {
    LOG_WARN("Name cannot be empty");
    return RC::INVALID_ARGUMENT;
  }
  LOG_INFO("Begin to create table %s:%s", base_dir, name);

  if (attribute_count <= 0 || nullptr == attributes) {
    LOG_WARN("Invalid arguments. table_name=%s, attribute_count=%d, attributes=%p",
             name, attribute_count, attributes);
    return RC::INVALID_ARGUMENT;
  }

  RC rc;

  // ?????? table_name.table???????????????????????????
  // ?????????????????????????????????

  int fd = ::open(path, O_WRONLY | O_CREAT | O_EXCL | O_CLOEXEC, 0600);
  if (-1 == fd) {
    if (EEXIST == errno) {
      LOG_ERROR("Failed to create table file, it has been created. %s, EEXIST, %s",
                path, strerror(errno));
      return RC::SCHEMA_TABLE_EXIST;
    }
    LOG_ERROR("Create table file failed. filename=%s, errmsg=%d:%s",
              path, errno, strerror(errno));
    return RC::IOERR;
  }

  close(fd);

  // ????????????
  if ((rc = table_meta_.init(name, attribute_count, attributes)) != RC::SUCCESS) {
    LOG_ERROR("Failed to init table meta. name:%s, ret:%d", name, rc);
    return rc; // delete table file
  }

  std::fstream fs;
  fs.open(path, std::ios_base::out | std::ios_base::binary);
  if (!fs.is_open()) {
    LOG_ERROR("Failed to open file for write. file name=%s, errmsg=%s", path, strerror(errno));
    return RC::IOERR;
  }

  // ???????????????????????????
  table_meta_.serialize(fs);
  fs.close();

  std::string data_file = std::string(base_dir) + "/" + name + TABLE_DATA_SUFFIX;
  data_buffer_pool_ = theGlobalDiskBufferPool();
  rc = data_buffer_pool_->create_file(data_file.c_str());
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to create disk buffer pool of data file. file name=%s", data_file.c_str());
    return rc;
  }

  rc = init_record_handler(base_dir);

  base_dir_ = base_dir;
  LOG_INFO("Successfully create table %s:%s", base_dir, name);
  return rc;
}

RC Table::drop(const char *path, const char *name, const char *base_dir) {

  if (nullptr == name || common::is_blank(name)) {
    LOG_WARN("Name cannot be empty");
    return RC::INVALID_ARGUMENT;
  }
  LOG_INFO("Begin to drop table %s:%s", base_dir, name);

  RC rc = RC::SUCCESS;

  //?????? table_name???meta?????????field meta index meta??????data??????
  //todo????????????????????????????????????????????????
  std::string data_file = std::string(base_dir) + "/" + name + TABLE_DATA_SUFFIX;
  if(remove(path)){
    rc = RC::IOERR_DELETE;
    LOG_ERROR("Failed to delete table meta file. name:%s, ret:%d", name, rc);
    return rc;
  } else {
    if(data_buffer_pool_ == nullptr)
      data_buffer_pool_ = theGlobalDiskBufferPool();
    //??????data file
    rc = data_buffer_pool_->delete_file(data_file.c_str());
    if(rc != RC::SUCCESS) {
      LOG_ERROR("Failed to delete data file. file name=%s, ret:%d", data_file.c_str(), rc);
      return rc;
    }
    //????????????index??????
    // ??????????????????????????????????????????????????????
    for(int i=0; i< table_meta_.index_num(); i++){
      const IndexMeta* idm = table_meta_.index(i);
      std::string index_file = index_data_file(base_dir_.c_str(), name, idm->name());
      rc = data_buffer_pool_->delete_file(index_file.c_str());
      if(rc != RC::SUCCESS) {
        LOG_ERROR("Failed to delete index file. file name %s,ret:%d", index_file.c_str(), rc);
        return rc;
      }
    }
  }

  LOG_INFO("Successfully drop table %s:%s", base_dir, name);
  return rc;
}

RC Table::open(const char *meta_file, const char *base_dir) {
  // ?????????????????????
  std::fstream fs;
  std::string meta_file_path = std::string(base_dir) + "/" + meta_file;
  fs.open(meta_file_path, std::ios_base::in | std::ios_base::binary);
  if (!fs.is_open()) {
    LOG_ERROR("Failed to open meta file for read. file name=%s, errmsg=%s", meta_file, strerror(errno));
    return RC::IOERR;
  }
  if (table_meta_.deserialize(fs) < 0) {
    LOG_ERROR("Failed to deserialize table meta. file name=%s", meta_file);
    return RC::GENERIC_ERROR;
  }
  fs.close();

  // ??????????????????
  RC rc = init_record_handler(base_dir);

  base_dir_ = base_dir;

  const int index_num = table_meta_.index_num();
  for (int i = 0; i < index_num; i++) {
    IndexMeta *index_meta = table_meta_.index(i);
    std::vector<FieldMeta *> field_metas = table_meta_.fields(index_meta->getFields());
    if (field_metas.size() == 0) {
      LOG_PANIC("Found invalid index meta info which has a non-exists field. table=%s, index=%s, field=%s",
                name(), index_meta->name(), index_meta->field(i));
      return RC::GENERIC_ERROR;
    }

    BplusTreeIndex *index = new BplusTreeIndex();
    std::string index_file = index_data_file(base_dir, name(), index_meta->name());
    rc = index->open(index_file.c_str(), *index_meta, field_metas);
    if (rc != RC::SUCCESS) {
      delete index;
      LOG_ERROR("Failed to open index. table=%s, index=%s, file=%s, rc=%d:%s",
                name(), index_meta->name(), index_file.c_str(), rc, strrc(rc));
      return rc;
    }
    indexes_.push_back(index);
  }
  return rc;
}

RC Table::commit_insert(Trx *trx, const RID &rid) {
  Record record;
  RC rc = record_handler_->get_record(&rid, &record);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  return trx->commit_insert(this, record);
}

RC Table::rollback_insert(Trx *trx, const RID &rid) {

  Record record;
  RC rc = record_handler_->get_record(&rid, &record);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  // remove all indexes
  rc = delete_entry_of_indexes(record.data, rid, true);
  if (rc != RC::SUCCESS && rc != RC::RECORD_INVALID_KEY) {
    LOG_ERROR("Failed to delete indexes of record(rid=%d.%d) while rollback insert, rc=%d:%s",
              rid.page_num, rid.slot_num, rc, strrc(rc));
  } else {
    rc = record_handler_->delete_record(&rid);
    if(rc != RC::SUCCESS && rc != RC::RECORD_RECORD_NOT_EXIST){
      return rc;
    }
  }
  return rc;
}

RC Table::insert_record(Trx *trx, Record *record) {
  RC rc = RC::SUCCESS;

  if (trx != nullptr) {
    trx->init_trx_info(this, *record);
  }
  rc = record_handler_->insert_record(record->data, table_meta_.record_size(), &record->rid);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Insert record failed. table name=%s, rc=%d:%s", table_meta_.name(), rc, strrc(rc));
    return rc;
  }

  if (trx != nullptr) {
    rc = trx->insert_record(this, record);
    if (rc != RC::SUCCESS) {
      LOG_ERROR("Failed to log operation(insertion) to trx");

      RC rc2 = record_handler_->delete_record(&record->rid);
      if (rc2 != RC::SUCCESS) {
        LOG_PANIC("Failed to rollback record data when insert index entries failed. table name=%s, rc=%d:%s",
                  name(), rc2, strrc(rc2));
      }
      return rc;
    }
  }

  rc = insert_entry_of_indexes(record->data, record->rid);
  if (rc==RECORD_DUPLICATE_KEY){//??????????????????
    RC rc2 = record_handler_->delete_record(&record->rid);
    if (rc2 != RC::SUCCESS) {
      LOG_PANIC("Failed to rollback record data when insert index entries failed. table name=%s, rc=%d:%s",
                name(), rc2, strrc(rc2));
    }
    return rc;
  }else if (rc != RC::SUCCESS) {
    RC rc2 = delete_entry_of_indexes(record->data, record->rid, true);
    if (rc2 != RC::SUCCESS) {
      LOG_PANIC("Failed to rollback index data when insert index entries failed. table name=%s, rc=%d:%s",
                name(), rc2, strrc(rc2));
    }
    rc2 = record_handler_->delete_record(&record->rid);
    if (rc2 != RC::SUCCESS) {
      LOG_PANIC("Failed to rollback record data when insert index entries failed. table name=%s, rc=%d:%s",
                name(), rc2, strrc(rc2));
    }
    return rc;
  }
  return rc;
}
RC Table::insert_record(Trx *trx, int value_num, const Value *values) {
  if (value_num <= 0 || nullptr == values ) {
    LOG_ERROR("Invalid argument. value num=%d, values=%p", value_num, values);
    return RC::INVALID_ARGUMENT;
  }

  char *record_data;
  RC rc = make_record(value_num, values, record_data);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to create a record. rc=%d:%s", rc, strrc(rc));
    return rc;
  }
  Record record;
  record.data = record_data;
  // record.valid = true;
  rc = insert_record(trx, &record);
  delete[] record_data;
  return rc;
}

const char *Table::name() const {
  return table_meta_.name();
}

TableMeta &Table::table_meta() {
  return table_meta_;
}

//?????????????????????????????????
std::string Table::getText(RID rid){
  std::string ans;
  int begin = 2;
  FieldMeta * fieldmeta0 = table_meta_.field(begin + 0);//??????
  FieldMeta * fieldmeta1 = table_meta_.field(begin + 1);//??????
  FieldMeta * fieldmeta2 = table_meta_.field(begin + 2);//??????
  FieldMeta * fieldmeta3 = table_meta_.field(begin + 3);//?????????
  while(true){
    Record r;
    record_handler_->get_record(&rid, &r);

    //???????????????record
    rid.page_num = *(int*)(r.data + fieldmeta0->offset());
    rid.slot_num = *(int*)(r.data + fieldmeta1->offset());
    int len = *(int*)(r.data + fieldmeta2->offset());
    ans.append(r.data + fieldmeta3->offset(), len);
    if(rid.page_num == -1 || rid.slot_num == -1){
      break;
    }
  }

  return ans;
}
RID Table::insertText(const char * text, int len){

  //???text???len?????????value???value_num
  int left = len; //?????????
  int has = 0;
  Value values[4];
  values[0].data = malloc(sizeof(int));
  values[1].data = malloc(sizeof(int));
  values[2].data = malloc(sizeof(int));
  values[3].data = malloc(TEXT_LEN);
  RID rid;
  RID res;
  bool first = true;
  int value_num = 4;
  while(left > 0){//??????????????????
    int one = ((left%TEXT_LEN==0)? (TEXT_LEN):(left%TEXT_LEN));

    //??????one?????????
    //??????value
    values[0].type = INTS;
    values[1].type = INTS;
    values[2].type = INTS;
    values[3].type = CHARS;
    if(first){
      *((int*)values[0].data) = -1;
      *((int*)values[1].data) = -1;
      first = false;
    }else{
      *((int*)values[0].data) = rid.page_num;
      *((int*)values[1].data) = rid.slot_num;
    }
    *((int*)values[2].data) = one;
    memcpy(values[3].data, text + left - one, one);

    char *record_data;
    RC rc = make_record(value_num, values, record_data);
    if(rc != SUCCESS){
      LOG_ERROR("ERROR. \n");
    }
    rc = record_handler_->insert_record(record_data, table_meta_.record_size(), &rid);
    if(rc != SUCCESS){
      LOG_ERROR("ERROR. \n");
    }
    delete [] record_data;
    left -= one;
  }

  free(values[0].data);
  free(values[1].data);
  free(values[2].data);
  free(values[3].data);
  return rid;
}
RC Table::deleteText(RID rid){
  RC rc;
  int begin = 2;
  FieldMeta * fieldmeta0 = table_meta_.field(begin + 0);//??????
  FieldMeta * fieldmeta1 = table_meta_.field(begin + 1);//??????
  FieldMeta * fieldmeta2 = table_meta_.field(begin + 2);//??????
  FieldMeta * fieldmeta3 = table_meta_.field(begin + 3);//?????????
  while(true){
    Record r;
    RID next_rid;
    rc = record_handler_->get_record(&rid, &r);
    if(rc == SUCCESS){

    }
    //???????????????record
    next_rid.page_num = *(int*)(r.data + fieldmeta0->offset());
    next_rid.slot_num = *(int*)(r.data + fieldmeta1->offset());


    rc = record_handler_->delete_record(&rid);
    if(rc == SUCCESS){
      LOG_ERROR("ERROR. \n");
    }
    if(next_rid.page_num == -1 || next_rid.slot_num == -1){//??????
      break;
    }else{
      rid = next_rid;
    }
  }
  return SUCCESS;
}
//RC Table::update_record(const char *attribute_name, const Value *value, Record *record){
//  //??????update??????
//  FieldMeta *filedmeta=table_meta_.field(attribute_name);
//  if(filedmeta==nullptr){
//    return RC::GENERIC_ERROR;
//  }
//  if(filedmeta->type()!=value->type){
//    return RC::SCHEMA_FIELD_TYPE_MISMATCH;
//  }
//  char *old=record->data+filedmeta->offset();
//  memcpy(old,value->data,filedmeta->len());
//
//  mark_dirty(record->rid.page_num);
//
//  return RC::SUCCESS;
//}

int FIT[6][6]{
        {0,0,0,0,0,0},
        {0,1,0,0,0,1},
        {0,0,1,0,0,0},
        {0,0,0,1,0,0},
        {0,0,0,0,1,0},
        {0,1,0,0,0,1}
};

RC Table::make_record(int value_num, const Value *values, char * &record_out) {
  // ??????????????????????????????
  if (value_num + table_meta_.sys_field_num() != table_meta_.field_num()) {
    return RC::SCHEMA_FIELD_MISSING;
  }
  int null_v=0;
  const int normal_field_start_index = table_meta_.sys_field_num();
  for (int i = 0; i < value_num; i++) {
    FieldMeta *field = table_meta_.field(i + normal_field_start_index);
    const Value &value = values[i];
    LOG_INFO("SSS value type. field name=%s, type=%d, given=%d",
             field->name(), field->type(), value.type);

    //????????????
    if (value.type == NULL_VALUE){
      if(ALLOW_NULL(field->type())!=0){
        null_v|=(1<<i);
        continue;
      }else{
        LOG_ERROR("Invalid value null. field name=%s, type=%d, but given=%d",
                  field->name(), field->type(), value.type);
        return RC::SCHEMA_FIELD_TYPE_MISMATCH;
      }
    }

    if (FIT[TYPE(field->type())][TYPE(value.type)] ==0)  {
      LOG_ERROR("Invalid value type. field name=%s, type=%d, but given=%d",
                field->name(), field->type(), value.type);
      return RC::SCHEMA_FIELD_TYPE_MISMATCH;
    }

  }

  // ????????????????????????
  int record_size = table_meta_.record_size();
  char *record = new char [record_size];

  for (int i = 0; i < value_num; i++) {
    FieldMeta *field = table_meta_.field(i + normal_field_start_index);
    const Value &value = values[i];
    if(null_v&(1<<i)){
      continue;
    }
    //text??????
    if(TYPE(field->type()) == TEXTS){
      size_t len = strlen((char *) value.data);
      RID rid = sys_tbs->insertText((char*)value.data, len < MAX_TEXT_LEN ? len : MAX_TEXT_LEN);
      *(int*)(record + field->offset()) = rid.page_num;
      *(int*)(record + field->offset() + 4) = rid.slot_num;
      //??????
      continue;
    }
    memcpy(record + field->offset(), value.data, field->len());
  }
  //??????null???
  FieldMeta *field = table_meta_.field(TableMeta::null_field_name());
  *(int*)(record + field->offset()) = null_v;
  record_out = record;
  return RC::SUCCESS;
}

RC Table::init_record_handler(const char *base_dir) {
  std::string data_file = std::string(base_dir) + "/" + table_meta_.name() + TABLE_DATA_SUFFIX;
  if (nullptr == data_buffer_pool_) {
    data_buffer_pool_ = theGlobalDiskBufferPool();
  }

  int data_buffer_pool_file_id;
  RC rc = data_buffer_pool_->open_file(data_file.c_str(), &data_buffer_pool_file_id);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to open disk buffer pool for file:%s. rc=%d:%s",
              data_file.c_str(), rc, strrc(rc));
    return rc;
  }

  record_handler_ = new RecordFileHandler();
  rc = record_handler_->init(*data_buffer_pool_, data_buffer_pool_file_id);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to init record handler. rc=%d:%s", rc, strrc(rc));
    return rc;
  }

  file_id_ = data_buffer_pool_file_id;
  return rc;
}

/**
 * ????????????Record???????????????????????????
 */
class RecordReaderScanAdapter {
public:
    explicit RecordReaderScanAdapter(void (*record_reader)(const char *data, void *context), void *context)
            : record_reader_(record_reader), context_(context){
    }

    void consume(const Record *record) {
      record_reader_(record->data, context_);
    }
private:
    void (*record_reader_)(const char *, void *);
    void *context_;
};
static RC scan_record_reader_adapter(Record *record, void *context) {
  RecordReaderScanAdapter &adapter = *(RecordReaderScanAdapter *)context;
  adapter.consume(record);
  return RC::SUCCESS;
}

RC Table::scan_record(Trx *trx, ConditionFilter *filter, int limit, void *context, void (*record_reader)(const char *data, void *context)) {
  RecordReaderScanAdapter adapter(record_reader, context);
  return scan_record(trx, filter, limit, (void *)&adapter, scan_record_reader_adapter);
}

RC Table::scan_record(Trx *trx, ConditionFilter *filter, int limit, void *context, RC (*record_reader)(Record *record, void *context)) {
  if (nullptr == record_reader) {
    return RC::INVALID_ARGUMENT;
  }

  if (0 == limit) {
    return RC::SUCCESS;
  }

  if (limit < 0) {
    limit = INT_MAX;
  }

  IndexScanner *index_scanner = find_index_for_scan(filter);
  if (index_scanner != nullptr) {
    return scan_record_by_index(trx, index_scanner, filter, limit, context, record_reader);
  }

  RC rc = RC::SUCCESS;
  RecordFileScanner scanner;
  rc = scanner.open_scan(*data_buffer_pool_, file_id_, filter);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("failed to open scanner. file id=%d. rc=%d:%s", file_id_, rc, strrc(rc));
    return rc;
  }

  int record_count = 0;
  Record record;
  rc = scanner.get_first_record(&record);
  for ( ; RC::SUCCESS == rc && record_count < limit; rc = scanner.get_next_record(&record)) {

    if (trx == nullptr || trx->is_visible(this, &record)) {
      rc = record_reader(&record, context);
      if (rc != RC::SUCCESS) {
        break;
      }
      record_count++;
    }

  }

  if (RC::RECORD_EOF == rc) {
    rc = RC::SUCCESS;
  } else {
    LOG_ERROR("failed to scan record. file id=%d, rc=%d:%s", file_id_, rc, strrc(rc));
  }
  scanner.close_scan();
  return rc;
}

RC Table::scan_record_by_index(Trx *trx, IndexScanner *scanner, ConditionFilter *filter, int limit, void *context,
                               RC (*record_reader)(Record *, void *)) {
  RC rc = RC::SUCCESS;
  RID rid;
  Record record;
  int record_count = 0;
  while (record_count < limit) {
    rc = scanner->next_entry(&rid);
    if (rc != RC::SUCCESS) {
      if (RC::RECORD_EOF == rc) {
        rc = RC::SUCCESS;
        break;
      }
      LOG_ERROR("Failed to scan table by index. rc=%d:%s", rc, strrc(rc));
      break;
    }

    rc = record_handler_->get_record(&rid, &record);
    if (rc != RC::SUCCESS) {
      LOG_ERROR("Failed to fetch record of rid=%d:%d, rc=%d:%s", rid.page_num, rid.slot_num, rc, strrc(rc));
      break;
    }

    if ((trx == nullptr || trx->is_visible(this, &record)) && (filter == nullptr || filter->filter(record))) {
      rc = record_reader(&record, context);
      if (rc != RC::SUCCESS) {
        LOG_TRACE("Record reader break the table scanning. rc=%d:%s", rc, strrc(rc));
        break;
      }
    }

    record_count++;
  }

  scanner->destroy();
  return rc;
}

class IndexInserter {
public:
    explicit IndexInserter(Index *index) : index_(index) {
    }

    RC insert_index(const Record *record) {
      //??????????????????
      std::vector<FieldMeta> fieldmetas = index_->field_metas();
      int max_size = 0;
      for(auto & field : fieldmetas){
        max_size += field.len();
      }
      char r[max_size];
      int offset = 0;
      for(auto & field_meta : fieldmetas){
        memcpy(r + offset, record->data + field_meta.offset(), field_meta.len());
        offset += field_meta.len();
      }
      return index_->insert_entry(r, &record->rid,index_->getUnique());
    }
private:
    Index * index_;
};

static RC insert_index_record_reader_adapter(Record *record, void *context) {
  IndexInserter &inserter = *(IndexInserter *)context;
  return inserter.insert_index(record);
}

RC Table::create_index(Trx *trx, const char *index_name, char *const attribute_names[],int len, int unique) {

  //????????????????????????
  if (index_name == nullptr || common::is_blank(index_name)) {
    return RC::INVALID_ARGUMENT;
  }

  //????????????????????????
  if (table_meta_.index(index_name) != nullptr){
    return RC::SCHEMA_INDEX_EXIST;
  }

  //????????????????????????????????????
  std::vector<FieldMeta *> field_metas;
  for(int i = 0; i< len; i++){
    if(attribute_names[i] == nullptr || common::is_blank(attribute_names[i])){
      return RC::INVALID_ARGUMENT;
    }
    FieldMeta *field_meta = table_meta_.field(attribute_names[i]);
    if(!field_meta){
      return RC::SCHEMA_FIELD_MISSING;
    }
    field_metas.push_back(field_meta);
  }
  //???????????????????????????
  if(table_meta_.find_index_by_field(field_metas)){
    return RC::SCHEMA_INDEX_EXIST;
  }

  IndexMeta new_index_meta;
  RC rc = new_index_meta.init(index_name, field_metas,unique);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  // ????????????????????????
  BplusTreeIndex *index = new BplusTreeIndex();
  std::string index_file = index_data_file(base_dir_.c_str(), name(), index_name);
  rc = index->create(index_file.c_str(), new_index_meta, field_metas);
  if (rc != RC::SUCCESS) {
    delete index;
    LOG_ERROR("Failed to create bplus tree index. file name=%s, rc=%d:%s", index_file.c_str(), rc, strrc(rc));
    return rc;
  }

  // ????????????????????????????????????????????????
  IndexInserter index_inserter(index);
  rc = scan_record(trx, nullptr, -1, &index_inserter, insert_index_record_reader_adapter);
  if (rc != RC::SUCCESS) {
    // rollback
    delete index;
    LOG_ERROR("Failed to insert index to all records. table=%s, rc=%d:%s", name(), rc, strrc(rc));
    return rc;
  }
  indexes_.push_back(index);

  TableMeta new_table_meta(table_meta_);
  rc = new_table_meta.add_index(new_index_meta);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to add index (%s) on table (%s). error=%d:%s", index_name, name(), rc, strrc(rc));
    return rc;
  }
  // ???????????????????????????
  std::string tmp_file = table_meta_file(base_dir_.c_str(), name()) + ".tmp";
  std::fstream fs;
  fs.open(tmp_file, std::ios_base::out | std::ios_base::binary | std::ios_base::trunc);
  if (!fs.is_open()) {
    LOG_ERROR("Failed to open file for write. file name=%s, errmsg=%s", tmp_file.c_str(), strerror(errno));
    return RC::IOERR; // ?????????????????????????????????????????????
  }
  if (new_table_meta.serialize(fs) < 0) {
    LOG_ERROR("Failed to dump new table meta to file: %s. sys err=%d:%s", tmp_file.c_str(), errno, strerror(errno));
    return RC::IOERR;
  }
  fs.close();

  // ???????????????????????????
  std::string meta_file = table_meta_file(base_dir_.c_str(), name());
  int ret = rename(tmp_file.c_str(), meta_file.c_str());
  if (ret != 0) {
    LOG_ERROR("Failed to rename tmp meta file (%s) to normal meta file (%s) while creating index (%s) on table (%s). " \
              "system error=%d:%s", tmp_file.c_str(), meta_file.c_str(), index_name, name(), errno, strerror(errno));
    return RC::IOERR;
  }

  table_meta_.swap(new_table_meta);

  LOG_INFO("add a new index (%s) on the table (%s)", index_name, name());

  return rc;
}

class RecordUpdater {
public:

    RecordUpdater(Table &table, Trx *trx, const char *attribute_name, const Value *value):value_(value),attribute_name_(attribute_name),table_(table),trx_(trx){
    }

    RC update_record(Record *record) {
      RC rc;
      rc = table_.update_record(trx_, record, attribute_name_, value_);
      if (rc == RC::SUCCESS) {
        updated_count_++;
      }else if(rc == RC::RECORD){
        rc = RC::SUCCESS;
      }
      return rc;
    }

    int updated_count() const {
      return updated_count_;
    }

private:
    const Value *value_;
    const char *attribute_name_;
    Table & table_;
    Trx *trx_;
    int updated_count_ = 0;
  
};

static RC record_reader_update_adapter(Record *record, void *context) {
  RecordUpdater &record_updater = *(RecordUpdater *)context;
  return record_updater.update_record(record);
}



RC Table::update_record(Trx *trx, ConditionFilter *filter, const char *attribute_name, const Value *value,  int *updated_count) {
  RecordUpdater updater(*this, trx, attribute_name, value);
  RC rc = scan_record(trx, filter, -1, &updater, record_reader_update_adapter);
  if (updated_count != nullptr) {
    *updated_count = updater.updated_count();
  }
  return rc;
}

RC Table::commit_update(Trx *trx, const RID &rid){
  Record record;
  RC rc = record_handler_->get_record(&rid, &record);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  return trx->commit_update(this, record);
}

RC Table::update_record(Trx *trx, Record *record, const char *attribute_name, const Value *value) {
  int32_t record_trx_id;
  bool record_deleted;
  Trx::get_record_trx_id(this, *record, record_trx_id, record_deleted);
  if(trx->get_trx_id() == record_trx_id && record_trx_id != 0){
    return RC::RECORD;

  }

  RC rc = delete_record(trx, record);
  if(rc != RC::SUCCESS){
    return rc;
  }

  //??????????????????value
  int value_num = 0;
  Value values[MAX_NUM];
  int val_null = *(int*)(record->data + TableMeta::null_field_offset());
  int sys_num = table_meta_.sys_field_num();

  bool succ = false;

  for(int i = sys_num; i < table_meta_.field_num(); i++){
    FieldMeta * filedmeta = table_meta_.field(i);
    int j = i - sys_num;
    int len = 0;

    if(strcmp(attribute_name, filedmeta->name()) == 0){//?????????????????????????????????
      succ = true;
      if(TYPE(filedmeta->type()) == TEXTS){
        len = strlen((char*)value->data);

        RID rid;
        rid.page_num = *(int*)(record->data + filedmeta->offset());
        rid.slot_num = *(int*)(record->data + filedmeta->offset()+4);
        //???????????????TEXT??????
        sys_tbs->deleteText(rid);
        values[j].data = new char[len+1];
        ((char*)values[j].data)[len] = 0; //????????????0
      }else{
        len = filedmeta->len();
        values[j].data = new char[len];
      }

      values[j].type = value->type;
      memcpy(values[j].data, value->data, len);
    }else{

      if((val_null&(1<<(j))) == 0){
        values[j].type = TYPE(filedmeta->type());
      }else{//???
        values[j].data = new char[filedmeta->len()];
        values[j].type = NULL_VALUE;
        continue;
      }

      if(TYPE(filedmeta->type()) == TEXTS){

        //???????????????text??????????????????
        RID rid;
        rid.page_num = *(int*)(record->data + filedmeta->offset());
        rid.slot_num = *(int*)(record->data + filedmeta->offset()+4);
        std::string tmp = sys_tbs->getText(rid);
        len = tmp.size();
        values[j].data = new char[len];
        values[j].type = CHARS;
        memcpy(values[j].data, tmp.c_str(), len);

        //??????
        rc = sys_tbs->deleteText(rid);
        if(rc != SUCCESS){

        }
      }else{
        len = filedmeta->len();
        values[j].data = new char[len];
        memcpy(values[j].data, record->data + filedmeta->offset(), len);
      }

    }
    value_num ++;
  }
  if(!succ){
    return RC::GENERIC_ERROR;
  }
  //???????????????
  rc = insert_record(trx, value_num, values);

  //??????value??????
  for(int i = 0; i < value_num; i++){
    delete [] values[i].data;
  }
  return rc;
}



class RecordDeleter {
public:
    RecordDeleter(Table &table, Trx *trx) : table_(table), trx_(trx) {
    }

    RC delete_record(Record *record) {
      RC rc = RC::SUCCESS;
      rc = table_.delete_record(trx_, record);
      //???????????????text???????????????
      TableMeta &tablemeta = table_.table_meta();

      for(int i = tablemeta.sys_field_num(); i < tablemeta.field_num(); i++){
        FieldMeta *fm = tablemeta.field(i);
        if(TYPE(fm->type()) == TEXTS){
          RID rid;
          rid.page_num = *(int*)(record->data + fm->offset());
          rid.slot_num = *(int*)(record->data + fm->offset() + sizeof(int));
          rc = sys_tbs->deleteText(rid);
          if(rc != SUCCESS){
            return rc;
          }
        }
      }
      if (rc == RC::SUCCESS) {
        deleted_count_++;
      }
      return rc;
    }

    int deleted_count() const {
      return deleted_count_;
    }

private:
    Table & table_;
    Trx *trx_;
    int deleted_count_ = 0;
};

static RC record_reader_delete_adapter(Record *record, void *context) {
  RecordDeleter &record_deleter = *(RecordDeleter *)context;
  return record_deleter.delete_record(record);
}

RC Table::delete_record(Trx *trx, ConditionFilter *filter, int *deleted_count) {
  RecordDeleter deleter(*this, trx);
  RC rc = scan_record(trx, filter, -1, &deleter, record_reader_delete_adapter);
  if (deleted_count != nullptr) {
    *deleted_count = deleter.deleted_count();
  }
  return rc;
}

RC Table::delete_record(Trx *trx, Record *record) {
  RC rc = RC::SUCCESS;
  if (trx != nullptr) {
    rc = trx->delete_record(this, record);
  } else {
    rc = delete_entry_of_indexes(record->data, record->rid, false);// ???????????? refer to commit_delete
    if (rc != RC::SUCCESS) {
      LOG_ERROR("Failed to delete indexes of record (rid=%d.%d). rc=%d:%s",
                record->rid.page_num, record->rid.slot_num, rc, strrc(rc));
    } else {
      rc = record_handler_->delete_record(&record->rid);
    }
  }
  return rc;
}

RC Table::commit_delete(Trx *trx, const RID &rid) {
  RC rc = RC::SUCCESS;
  Record record;
  rc = record_handler_->get_record(&rid, &record);
  if (rc != RC::SUCCESS) {
    return rc;
  }
  rc = delete_entry_of_indexes(record.data, record.rid, false);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to delete indexes of record(rid=%d.%d). rc=%d:%s",
              rid.page_num, rid.slot_num, rc, strrc(rc));// panic?
  }

  rc = record_handler_->delete_record(&rid);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  return rc;
}

RC Table::rollback_delete(Trx *trx, const RID &rid) {
  RC rc = RC::SUCCESS;
  Record record;
  rc = record_handler_->get_record(&rid, &record);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  return trx->rollback_delete(this, record); // update record in place
}

RC Table::insert_entry_of_indexes(const char *record, const RID &rid) {
  RC rc = RC::SUCCESS;
  for (Index *index : indexes_) {
    //??????????????????
    std::vector<FieldMeta> fieldmetas = index->field_metas();
    char r[table_meta_.record_size()];
    int offset = 0;
    for(auto & field_meta : fieldmetas){
      memcpy(r + offset, record + field_meta.offset(), field_meta.len());
      offset += field_meta.len();
    }
    rc = index->insert_entry(r, &rid,index->getUnique());
    if (rc != RC::SUCCESS) {
      break;
    }
  }
  return rc;
}

RC Table::delete_entry_of_indexes(const char *record, const RID &rid, bool error_on_not_exists) {
  RC rc = RC::SUCCESS;
  for (Index *index : indexes_) {
    //??????????????????
    std::vector<FieldMeta> fieldmetas = index->field_metas();
    char r[table_meta_.record_size()];
    int offset = 0;
    for(auto & field_meta : fieldmetas){
      memcpy(r + offset, record + field_meta.offset(), field_meta.len());
      offset += field_meta.len();
    }
    rc = index->delete_entry(r, &rid);
    if (rc != RC::SUCCESS) {
      if (rc != RC::RECORD_INVALID_KEY || !error_on_not_exists) {
        break;
      }
    }
  }
  return rc;
}

Index *Table::find_index(const char *index_name) const {
  for (Index *index: indexes_) {
    if (0 == strcmp(index->index_meta().name(), index_name)) {
      return index;
    }
  }
  return nullptr;
}

IndexScanner *Table::find_index_for_scan_multi(const ConditionFilter *filter){
  const CompositeConditionFilter *composite = dynamic_cast<const CompositeConditionFilter *>(filter);
  if(composite == nullptr){
    return nullptr;
  }
  char target_s[table_meta_.record_size()];


  Index * target_index = nullptr;
  CompOp target_op = EQUAL_TO;
  //????????????????????????
  //?????????????????????<???>???????????????
  //????????????????????????======
  for(Index *index : indexes_){
    //????????????????????????
    //?????????????????????
    std::vector<FieldMeta> fields = index->field_metas();
    int i;
    int offset = 0;
    char s[table_meta_.record_size()];
    CompOp op ;
    bool succ = false;
    for(i = 0; i < fields.size(); i++){
      FieldMeta &field = fields[i];

      int j;
      for(j = 0; j < composite->filter_num(); j++){
        const DefaultConditionFilter * deffilter = dynamic_cast<const DefaultConditionFilter *>
        (&(composite->filter(j)));
        const ConDesc *field_cond_desc = nullptr;
        const ConDesc *value_cond_desc = nullptr;
        if (deffilter->left().is_attr && !deffilter->right().is_attr) {//????????????????????????
          field_cond_desc = &deffilter->left();
          value_cond_desc = &deffilter->right();
        } else if (deffilter->right().is_attr && !deffilter->left().is_attr) {
          field_cond_desc = &deffilter->right();
          value_cond_desc = &deffilter->left();
        }
        if (field_cond_desc->attr_offset != field.offset() || field_cond_desc == nullptr || value_cond_desc == nullptr) {
          continue;
        }

        if(deffilter->comp_op() == EQUAL_TO){//find it
          if(value_cond_desc->attr_type != NULL_VALUE){
            memcpy(s + offset, value_cond_desc->value, field_cond_desc->attr_length);
            offset += field_cond_desc->attr_length;
          }
          op = deffilter->comp_op();
          break;
        }else if(deffilter->comp_op() != NOT_EQUAL && deffilter->comp_op() <= GREAT_THAN){
          if(value_cond_desc->attr_type != NULL_VALUE){
            memcpy(s + offset, value_cond_desc->value, field_cond_desc->attr_length);
            offset += field_cond_desc->attr_length;
          }

          op = deffilter->comp_op();
          break;
        }
      }
      if(j == composite->filter_num()){//?????????
        break;
      }else{
        if(op == EQUAL_TO){

        }else{
          if(i == 0){//????????????????????????????????????
            i++;
          }
          break;
        }
      }
    }

    //?????????????????????
    //??????????????????????????????
    //??????==????????????
    if(i == fields.size()){
      target_index = index;
      target_op = op;
      memcpy(target_s, s, sizeof(s));
      break;
    }

  }

  if(target_index == nullptr){
    return nullptr;
  }else{
    return target_index->create_scanner(target_op, target_s);
  }
}



IndexScanner *Table::find_index_for_scan(const ConditionFilter *filter) {
  if (nullptr == filter) {
    return nullptr;
  }

  // TODO remove dynamic_cast
  /*const DefaultConditionFilter *default_condition_filter = dynamic_cast<const DefaultConditionFilter *>(filter);
  if (default_condition_filter != nullptr) {
    return find_index_for_scan(*default_condition_filter);
  }*/


  IndexScanner *scanner= find_index_for_scan_multi(filter);
  if (scanner != nullptr) {
    return scanner; // TODO ???????????????????????????????????????????????????=
  }

  return nullptr;
}

RC Table::sync() {
  RC rc = data_buffer_pool_->flush_all_pages(file_id_);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to flush table's data pages. table=%s, rc=%d:%s", name(), rc, strrc(rc));
    return rc;
  }

  for (Index *index: indexes_) {
    rc = index->sync();
    if (rc != RC::SUCCESS) {
      LOG_ERROR("Failed to flush index's pages. table=%s, index=%s, rc=%d:%s",
                name(), index->index_meta().name(), rc, strrc(rc));
      return rc;
    }
  }
  LOG_INFO("Sync table over. table=%s", name());
  return rc;
}
