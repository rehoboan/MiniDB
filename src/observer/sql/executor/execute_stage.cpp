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

#include <string>
#include <sstream>

#include "execute_stage.h"

#include "common/io/io.h"
#include "common/log/log.h"
#include "common/seda/timer_stage.h"
#include "common/lang/string.h"
#include "session/session.h"
#include "event/storage_event.h"
#include "event/sql_event.h"
#include "event/session_event.h"
#include "event/execution_plan_event.h"
#include "sql/executor/execution_node.h"
#include "sql/executor/tuple.h"
#include "storage/common/table.h"
#include "storage/default/default_handler.h"
#include "storage/common/condition_filter.h"
#include "storage/trx/trx.h"

using namespace common;

struct hash_pair { 
    template <class T1, class T2> 
    size_t operator()(const std::pair<T1, T2>& p) const{ 
      auto hash1 = std::hash<T1>{}(p.first); 
      auto hash2 = std::hash<T2>{}(p.second);
      return hash1 ^ (hash2<<1); 
    } 
}; 
struct hash_string { 
    size_t operator()(const char *str) const{ 
      int num = 10;
      int hash = strlen(str);
      while(*(++str)){
        hash = num * 10 + (*str);
      }
      return hash & (0x7FFFFFFF); 
    } 
};

// struct equal_pair_string {
//     bool operator()(const std::pair<const char*, const char*> &a, const std::pair<const char*, const char*> &b) const{
//       std::cout<<a.first<<"   "<<b.first<<std::endl;
//     return strcmp(a.first, b.first)==0 && strcmp(a.second,b.second)==0;
//   }
// };

struct equal_string {
       bool operator()(const char* a,const char* b) const {
           return strcmp(a,b)==0;
     }
};



using TablePair = std::pair<const char *, const char *>;
//<<tl,tr>, [conds1, conds2...]>
using JoinConds = std::unordered_map<TablePair, std::vector<Condition>, hash_pair>;

//<tablename, tupleset>     
//using MapName2Value = std::unordered_map<const char *, TupleSet *, hash_string, equal_string>;
using MapName2Value = std::unordered_map<const char *, TupleSet *, hash_string, equal_string>;


//<tupleset, [t1,t2,........]>  连接后的临时表
using MapValue2Name = std::unordered_map<TupleSet *, std::vector<const char *>>;

void create_select_columns_with_star(const char *db, const Selects &selects, 
                                    std::vector<std::pair<const char *, const char *>> &select_columns);

                        
const char * create_agg_columns_name(const char *table_name, const char *attr_name, 
                                    const char *agg_name, bool display_table);

//create and init executor node
RC create_selection_executor(Trx *trx, const Selects &selects, const char *db, const char *table_name, SelectExeNode &select_node);

RC create_join_executor(Trx *trx, 
                        const TupleSet &left_table, const TupleSet &right_table,
                        std::vector<Condition> &conditions,
                        JoinExeNode &join_node,
                        SessionEvent *session_event);

RC create_cartesian_product_executor(Trx *trx, 
                                      const TupleSet &left_table, const TupleSet &right_table,
                                      CartesianProductExeNode &cartesian_product_node,
                                      SessionEvent *session_event);

RC create_aggregation_executor(Trx *trx,
                              const TupleSet &table,
                              std::vector<std::pair<const char *, AggInfo>> &agg_infos,
                              AggregationExeNode &agg_node,
                              SessionEvent *session_event);

RC check_select_metadata(const Selects &selects, const char *db, SessionEvent *session_event);

RC check_field(std::unordered_map<const char *, Table *, hash_string, equal_string>tables, const char *relation_name, const char *attr_name, SessionEvent *session_event);

//init join conditions
void init_join_conditions_between_tables(const Selects &selects, JoinConds &map);
//init map between tablename and filtered tuple sets
void init_kv_between_name_and_value(std::vector<TupleSet> &tuple_sets, 
                    MapName2Value &name2value, MapValue2Name &value2name);

void init_aggregation(const char *table_name, const char *attr_name, const char *agg_name, AggInfo & agg_info);

//join two tables depends on each join condition
RC join_tables(Trx *trx, 
              JoinConds &join_conditions,
              MapName2Value &name2value, MapValue2Name &value2name,
              SessionEvent *session_event, Session *session);
RC cartesian_product(Trx *trx,
                    const MapValue2Name &value2name,
                    TupleSet &res_table,
                    SessionEvent *session_event, Session *session);


//! Constructor
ExecuteStage::ExecuteStage(const char *tag) : Stage(tag) {}

//! Destructor
ExecuteStage::~ExecuteStage() {}

//! Parse properties, instantiate a stage object
Stage *ExecuteStage::make_stage(const std::string &tag) {
  ExecuteStage *stage = new (std::nothrow) ExecuteStage(tag.c_str());
  if (stage == nullptr) {
    LOG_ERROR("new ExecuteStage failed");
    return nullptr;
  }
  stage->set_properties();
  return stage;
}

//! Set properties for this object set in stage specific properties
bool ExecuteStage::set_properties() {
  //  std::string stageNameStr(stageName);
  //  std::map<std::string, std::string> section = theGlobalProperties()->get(
  //    stageNameStr);
  //
  //  std::map<std::string, std::string>::iterator it;
  //
  //  std::string key;

  return true;
}

//! Initialize stage params and validate outputs
bool ExecuteStage::initialize() {
  LOG_TRACE("Enter");

  std::list<Stage *>::iterator stgp = next_stage_list_.begin();
  default_storage_stage_ = *(stgp++);
  mem_storage_stage_ = *(stgp++);

  LOG_TRACE("Exit");
  return true;
}

//! Cleanup after disconnection
void ExecuteStage::cleanup() {
  LOG_TRACE("Enter");

  LOG_TRACE("Exit");
}

void ExecuteStage::handle_event(StageEvent *event) {
  LOG_TRACE("Enter\n");

  handle_request(event);

  LOG_TRACE("Exit\n");
  return;
}

void ExecuteStage::callback_event(StageEvent *event, CallbackContext *context) {
  LOG_TRACE("Enter\n");

  // here finish read all data from disk or network, but do nothing here.
  ExecutionPlanEvent *exe_event = static_cast<ExecutionPlanEvent *>(event);
  SQLStageEvent *sql_event = exe_event->sql_event();
  sql_event->done_immediate();

  LOG_TRACE("Exit\n");
  return;
}

void ExecuteStage::handle_request(common::StageEvent *event) {
  ExecutionPlanEvent *exe_event = static_cast<ExecutionPlanEvent *>(event);
  SessionEvent *session_event = exe_event->sql_event()->session_event();
  Query *sql = exe_event->sqls();
  const char *current_db = session_event->get_client()->session->get_current_db().c_str();

  CompletionCallback *cb = new (std::nothrow) CompletionCallback(this, nullptr);
  if (cb == nullptr) {
    LOG_ERROR("Failed to new callback for ExecutionPlanEvent");
    exe_event->done_immediate();
    return;
  }
  exe_event->push_callback(cb);

  switch (sql->flag) {
    case SCF_SELECT: { // se
      do_select(current_db, sql, exe_event->sql_event()->session_event());
      exe_event->done_immediate();
    }
    break;

    case SCF_INSERT:
    case SCF_UPDATE:
    case SCF_DELETE:
    case SCF_CREATE_TABLE:
    case SCF_SHOW_TABLES:
    case SCF_DESC_TABLE:
    case SCF_DROP_TABLE:
    case SCF_CREATE_INDEX:
    case SCF_DROP_INDEX: 
    case SCF_LOAD_DATA: {
      StorageEvent *storage_event = new (std::nothrow) StorageEvent(exe_event);
      if (storage_event == nullptr) {
        LOG_ERROR("Failed to new StorageEvent");
        event->done_immediate();
        return;
      }

      default_storage_stage_->handle_event(storage_event);
    }
    break;
    case SCF_SYNC: {
      RC rc = DefaultHandler::get_default().sync();
      session_event->set_response(strrc(rc));
      exe_event->done_immediate();
    }
    break;
    case SCF_BEGIN: {
      session_event->get_client()->session->set_trx_multi_operation_mode(true);
      session_event->set_response(strrc(RC::SUCCESS));
      exe_event->done_immediate();
    }
    break;
    case SCF_COMMIT: {
      Trx *trx = session_event->get_client()->session->current_trx();
      RC rc = trx->commit();
      session_event->get_client()->session->set_trx_multi_operation_mode(false);
      session_event->set_response(strrc(rc));
      exe_event->done_immediate();
    }
    break;
    case SCF_ROLLBACK: {
      Trx *trx = session_event->get_client()->session->current_trx();
      RC rc = trx->rollback();
      session_event->get_client()->session->set_trx_multi_operation_mode(false);
      session_event->set_response(strrc(rc));
      exe_event->done_immediate();
    }
    break;
    case SCF_HELP: {
      const char *response = "show tables;\n"
          "desc `table name`;\n"
          "create table `table name` (`column name` `column type`, ...);\n"
          "create index `index name` on `table` (`column`);\n"
          "insert into `table` values(`value1`,`value2`);\n"
          "update `table` set column=value [where `column`=`value`];\n"
          "delete from `table` [where `column`=`value`];\n"
          "select [ * | `columns` ] from `table`;\n";
      session_event->set_response(response);
      exe_event->done_immediate();
    }
    break;
    case SCF_EXIT: {
      // do nothing
      const char *response = "Unsupported\n";
      session_event->set_response(response);
      exe_event->done_immediate();
    }
    break;
    default: {
      exe_event->done_immediate();
      LOG_ERROR("Unsupported command=%d\n", sql->flag);
    }
  }
}

void end_trx_if_need(Session *session, Trx *trx, bool all_right) {
  if (!session->is_trx_multi_operation_mode()) {
    if (all_right) {
      trx->commit();
    } else {
      trx->rollback();
    }
  }
}

// 这里没有对输入的某些信息做合法性校验，比如查询的列名、where条件中的列名等，没有做必要的合法性校验
// 需要补充上这一部分. 校验部分也可以放在resolve，不过跟execution放一起也没有关系
RC ExecuteStage::do_select(const char *db, Query *sql, SessionEvent *session_event) {

  RC rc = RC::SUCCESS;
  Session *session = session_event->get_client()->session;
  Trx *trx = session->current_trx();
  const Selects &selects = sql->sstr.selection;
  //先进行原数据校验
  rc = check_select_metadata(selects, db, session_event);
  if(rc != RC::SUCCESS) {
    LOG_ERROR("select metadata check error");
    end_trx_if_need(session, trx, false);
    return rc;
  }
  // 把所有的表和只跟这张表关联的condition都拿出来，生成最底层的select 执行节点
  std::vector<SelectExeNode *> select_nodes;
  for (size_t i = 0; i < selects.relation_num; i++) {
    const char *table_name = selects.relations[i];
    SelectExeNode *select_node = new SelectExeNode;
    rc = create_selection_executor(trx, selects, db, table_name, *select_node);
    if (rc != RC::SUCCESS) {
      delete select_node;
      for (SelectExeNode *& tmp_node: select_nodes) {
        delete tmp_node;
      }
      end_trx_if_need(session, trx, false);
      return rc;
    }
    select_nodes.push_back(select_node);
  }

  if (select_nodes.empty()) {
    LOG_ERROR("No table given");
    end_trx_if_need(session, trx, false);
    return RC::SQL_SYNTAX;
  }

  std::vector<TupleSet> tuple_sets;
  for (SelectExeNode *&node : select_nodes) {
    TupleSet tuple_set;
    rc = node->execute(tuple_set);
    if (rc != RC::SUCCESS) {
      for (SelectExeNode *& tmp_node : select_nodes) {
        delete tmp_node;
      }
      end_trx_if_need(session, trx, false);
      return rc;
    } else {
      tuple_sets.push_back(std::move(tuple_set));
    }
  }
  for (SelectExeNode *& tmp_node: select_nodes) {
    delete tmp_node;
  }
  TupleSet res_table;
  if (tuple_sets.size() > 1) {
    // 本次查询了多张表，需要做join操作

    JoinConds join_conditions;
    init_join_conditions_between_tables(selects, join_conditions);


    MapName2Value name2value;
    MapValue2Name value2name;
    init_kv_between_name_and_value(tuple_sets, name2value, value2name);

    rc = join_tables(trx, join_conditions, name2value, value2name, session_event, session);
    if(rc == RC::SUCCESS) {
      if(value2name.size() > 1) {
        rc = cartesian_product(trx, value2name, res_table, session_event, session);
      } else if(value2name.size() == 1) {
        res_table = std::move(*value2name.begin()->first);
      } else {
        rc = RC::CORRUPT;
      }
    }
  } else {
    // 当前只查询一张表
    res_table = std::move(tuple_sets.front());
  }

  if(rc != RC::SUCCESS) {
    LOG_ERROR("Fail to execute join operation. ret=%d:%s", rc, strrc(rc));
  }


  // for (SelectExeNode *& tmp_node: select_nodes) {
  //   delete tmp_node;
  // }
  //<tablename, column name>
  std::vector<std::pair<const char *, const char *>> select_columns;
  //<aggregation column, agginfo>
  std::vector<std::pair<const char *, AggInfo>> agg_infos;

  bool is_multi_table = true;
  //处理带星号的查询,不支持多个属性和*同时出现
  if(selects.attr_num == 1 && strcmp(selects.attributes[0].attribute_name, "*") == 0 &&
      selects.attributes[0].agg_name == nullptr) {
    is_multi_table = !(selects.relation_num==1);
    create_select_columns_with_star(db, selects, select_columns);
  } else {
    for(int i = selects.attr_num - 1; i >= 0; i--) {
      const char *attr_name = selects.attributes[i].attribute_name;
      const char *relation_name = selects.attributes[i].relation_name;
      const char *agg_name = selects.attributes[i].agg_name;
      //如果显示查询多张表但是选择的属性列没有表名前缀，说明元数据校验有问题。
      if(relation_name == nullptr && selects.relation_num!=1 && agg_name==nullptr) {
          LOG_ERROR("No tablename prefix when operating multi table selection");
          continue;
      } else if(relation_name == nullptr && selects.relation_num==1) {
        relation_name = selects.relations[0];
        is_multi_table = false;
      }
      //如果该聚集函数名为空，只是普通选择列，将该列加入到selection columns中
      if(agg_name == nullptr)
        select_columns.emplace_back(relation_name, attr_name); 
      else {//如果是聚集函数列，构造聚集列名（判断是否是单表查询），初始化aggregation信息，加入到agg infos中
        bool display_table = !(selects.relation_num==1);
        const char *agg_column_name = create_agg_columns_name(relation_name, attr_name, agg_name, display_table);
        AggInfo agg_info;
        init_aggregation(relation_name, attr_name, agg_name, agg_info);        
        agg_infos.emplace_back(agg_column_name, agg_info);
      }
    }
  }
    //初始化并执行聚集操作
  bool is_agg = false;
  std::stringstream ss;
  if(select_columns.size()>0 && agg_infos.size()>0) {
    rc = RC::SQL_SYNTAX;
    char err[256];
    sprintf("aggregation function and column selection conflict", err);
    LOG_WARN("aggregation function and column selection conflict");
    session_event->set_response(err);
    return rc;
  } else if(agg_infos.size()>0) {
    is_agg = true;
  }
  if(!is_agg) {
    res_table.print(ss, select_columns, is_multi_table);
  } else {
    AggregationExeNode agg_node;
    rc = create_aggregation_executor(trx, res_table, agg_infos, agg_node, session_event);
    //agg_node.init(trx, &res_table, agg_infos);
    if(rc != RC::SUCCESS) {
      end_trx_if_need(session, trx, false);
      return rc;
    }
    Tuple agg_res;
    std::vector<const char *> agg_columns;
    rc = agg_node.execute(agg_res, agg_columns);
    if(rc != RC::SUCCESS) {
      end_trx_if_need(session, trx, false);
      return rc;
    }
    //print aggregation selection columns
    for(int i=0; i<agg_columns.size()-1; i++) {
      ss<<agg_columns[i] << " | ";
    }
    ss<<agg_columns.back()<<std::endl;

    //print data
    const std::vector<std::shared_ptr<TupleValue>> &values = agg_res.values();
    for(int i=0; i<agg_res.size()-1; i++) {
      values[i]->to_string(ss);
      ss<<" | ";
    }
    values.back()->to_string(ss);
    ss<<std::endl;
  }

  
  session_event->set_response(ss.str());
  end_trx_if_need(session, trx, true);
  return rc;
}


//join operation between two relation
RC join_tables(Trx *trx, 
              JoinConds &join_conditions,
              MapName2Value &name2value, MapValue2Name &value2name,
              SessionEvent *session_event, Session *session) {
  RC rc = RC::SUCCESS;
  for(auto iter = join_conditions.begin(); iter != join_conditions.end(); iter++) {
    JoinExeNode join_node;
    const char *left_table_name = iter->first.first;
    const char *right_table_name = iter->first.second;
    
    std::vector<Condition> conditions = std::move(iter->second); 
    if(name2value.count(left_table_name)==0)
      std::cout<<"couln't read left table"<<std::endl;
    if(name2value.count(right_table_name)==0)
      std::cout<<"couln't read right table"<<std::endl;
    rc = create_join_executor(trx,
                      *name2value[left_table_name],
                      *name2value[right_table_name],
                      conditions,
                      join_node,
                      session_event
                      );
    if(rc != RC::SUCCESS) {
      end_trx_if_need(session, trx, false);
      break;
    }
    TupleSet *join_table = new TupleSet();
    rc = join_node.execute(*join_table); //生成临时表
    if(rc != RC::SUCCESS) {
      end_trx_if_need(session, trx, false);
    }

    //更新到value2name中和name2value中
    TupleSet *old_left_table = name2value[left_table_name];
    std::vector<const char *>table_names = value2name[old_left_table];
    value2name.erase(old_left_table);

    TupleSet *old_right_table = name2value[right_table_name];
    if(old_right_table != old_left_table) {
      for(const char *name : value2name[old_right_table]) {
        table_names.emplace_back(std::move(name));
      }
      value2name.erase(old_right_table);
    }
    //更新value2name
    value2name[join_table] = table_names;
    //更新 name2value
    for (const char *name : table_names) {
      name2value[name] = join_table;
    }


  }
  return RC::SUCCESS;
}


RC cartesian_product(Trx *trx, const MapValue2Name &value2name, TupleSet &res_table, SessionEvent *session_event, Session *session) {
  RC rc = RC::SUCCESS;
  auto i = value2name.begin();
  
  TupleSet *left_table = i->first;
  i++;
  for(;i!=value2name.end(); i++){
    TupleSet join_tuple;
    TupleSet *right_table = i->first;
    CartesianProductExeNode cartesian_node;
    create_cartesian_product_executor(trx, *left_table, *right_table, cartesian_node, session_event);
    rc = cartesian_node.execute(join_tuple);
    if(rc != RC::SUCCESS) {
      end_trx_if_need(session, trx, false);
      break;      
    }
    if(i != ++value2name.begin())
      delete left_table;
    
    left_table = new TupleSet(std::move(join_tuple));
  }
  if(rc == RC::SUCCESS)
    res_table = std::move(*left_table);
  
  return rc;

}

bool match_table(const Selects &selects, const char *table_name_in_condition, const char *table_name_to_match) {
  if (table_name_in_condition != nullptr) {
    return 0 == strcmp(table_name_in_condition, table_name_to_match);
  }

  return selects.relation_num == 1;
}

static RC schema_add_field(Table *table, const char *field_name, TupleSchema &schema) {
  FieldMeta *field_meta = table->table_meta().field(field_name);
  if (nullptr == field_meta) {
    LOG_WARN("No such field. %s.%s", table->name(), field_name);
    return RC::SCHEMA_FIELD_MISSING;
  }

  schema.add_if_not_exists(field_meta->type(), table->name(), field_meta->name());
  return RC::SUCCESS;
}

void create_select_columns_with_star(const char *db, const Selects &selects, 
                                    std::vector<std::pair<const char *, const char *>> &select_columns) {
  for(int i=0; i<selects.relation_num; i++) {
    const char *table_name = selects.relations[i];
    Table * table = DefaultHandler::get_default().find_table(db, table_name);
    TableMeta &table_meta = table->table_meta();
    int field_num = table_meta.field_num();
    for(int i=0; i < field_num; i++) {
      FieldMeta *field_meta = table_meta.field(i);
      if(field_meta->visible()) {
        select_columns.emplace_back(table_name, field_meta->name());
      }
    }
  }
}
const char* create_agg_columns_name(const char *table_name, const char *attr_name, 
                                    const char *agg_name, bool display_table) {
  //display mode: aggname(tablename.attrname)
  //nondisplay mode: aggname(attriname)
  int table_name_len = 0;
  if(table_name != nullptr)
    table_name_len = strlen(table_name);
  //判断是否需要加上table前缀
  char* res_part1 = new char(table_name_len + 1 + strlen(attr_name));
  if(table_name_len && (display_table && strcmp(attr_name, "*")!=0)) {
    strncpy(res_part1, table_name, table_name_len);
    strcat(res_part1, ".");
    strcat(res_part1, attr_name);
  } else {
    strncpy(res_part1, attr_name, strlen(attr_name));
  }
  char *agg_columns_name = new char(strlen(res_part1) + 2 + strlen(agg_name));
  strncpy(agg_columns_name, agg_name, strlen(agg_name));
  strcat(agg_columns_name, "(");
  strcat(agg_columns_name, res_part1);
  strcat(agg_columns_name, ")");

  return agg_columns_name;
}


// 把所有的表和只跟这张表关联的condition都拿出来，生成最底层的select 执行节点
RC create_selection_executor(Trx *trx, const Selects &selects, const char *db, const char *table_name, SelectExeNode &select_node) {
  // 列出跟这张表关联的Attr
  TupleSchema schema;
  Table * table = DefaultHandler::get_default().find_table(db, table_name);
  if (nullptr == table) {
    LOG_WARN("No such table [%s] in db [%s]", table_name, db);
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }

  // for (int i = selects.attr_num - 1; i >= 0; i--) {
  //   const RelAttr &attr = selects.attributes[i];
  //   if (nullptr == attr.relation_name || 0 == strcmp(table_name, attr.relation_name)) {
  //     if (0 == strcmp("*", attr.attribute_name)) {
  //       // 列出这张表所有字段
  //       TupleSchema::from_table(table, schema);
  //       break; // 没有校验，给出* 之后，再写字段的错误
  //     } else {
  //       // 列出这张表相关字段
  //       RC rc = schema_add_field(table, attr.attribute_name, schema);
  //       if (rc != RC::SUCCESS) {
  //         return rc;
  //       }
  //     }
  //   }
  // }
  TupleSchema::from_table(table, schema);

  // 找出仅与此表相关的过滤条件, 或者都是值的过滤条件
  std::vector<DefaultConditionFilter *> condition_filters;
  for (size_t i = 0; i < selects.condition_num; i++) {
    const Condition &condition = selects.conditions[i];
    if ((condition.left_is_attr == 0 && condition.right_is_attr == 0) || // 两边都是值
        (condition.left_is_attr == 1 && condition.right_is_attr == 0 && match_table(selects, condition.left_attr.relation_name, table_name)) ||  // 左边是属性右边是值
        (condition.left_is_attr == 0 && condition.right_is_attr == 1 && match_table(selects, condition.right_attr.relation_name, table_name)) ||  // 左边是值，右边是属性名
        (condition.left_is_attr == 1 && condition.right_is_attr == 1 &&
            match_table(selects, condition.left_attr.relation_name, table_name) && match_table(selects, condition.right_attr.relation_name, table_name)) // 左右都是属性名，并且表名都符合
        ) {
      DefaultConditionFilter *condition_filter = new DefaultConditionFilter();
      RC rc = condition_filter->init(*table, condition);
      if (rc != RC::SUCCESS) {
        delete condition_filter;
        for (DefaultConditionFilter * &filter : condition_filters) {
          delete filter;
        }
        return rc;
      }
      condition_filters.push_back(condition_filter);
    }
  }

  return select_node.init(trx, table, std::move(schema), std::move(condition_filters));
}

RC create_join_executor(Trx *trx,
                        const TupleSet &left_table, const TupleSet &right_table,
                        std::vector<Condition> &conditions,
                        JoinExeNode &join_node,
                        SessionEvent *session_event) {
  //update join schema
  TupleSchema schema;
  schema.append(left_table.get_schema());
  if(&left_table != &right_table)
    schema.append(right_table.get_schema());
  
  //create join condition filter vector
  std::vector<JoinConditionFilter *> condition_filters;
  for(int i = 0; i < conditions.size(); i++) {
    JoinConditionFilter *condition_filter = new JoinConditionFilter();
    RelAttr left_relattr = conditions[i].left_attr;
    RelAttr right_relattr = conditions[i].right_attr;
    const CompOp& op = conditions[i].comp;
    RC rc = condition_filter->init(left_relattr, right_relattr, op);
    if(rc != RC::SUCCESS) {
      return rc;
    }
    condition_filters.push_back(condition_filter);
  }
  
  return join_node.init(trx, 
                  &left_table, &right_table,
                  std::move(schema), 
                  std::move(condition_filters));
}


RC create_cartesian_product_executor(Trx *trx, 
                                      const TupleSet &left_table, const TupleSet &right_table,
                                      CartesianProductExeNode &cartesian_product_node,
                                      SessionEvent *session_event) {
  TupleSchema schema;
  schema.append(left_table.get_schema());
  if(&left_table != &right_table)
    schema.append(right_table.get_schema());
  return cartesian_product_node.init(trx, &left_table, &right_table, schema);

}

RC create_aggregation_executor(Trx *trx,
                              const TupleSet &table,
                              std::vector<std::pair<const char *, AggInfo>> &agg_infos,
                              AggregationExeNode &agg_node,
                              SessionEvent *session_event) {
  return agg_node.init(trx, &table, std::move(agg_infos));                                
}


RC check_select_metadata(const Selects &selects, const char *db, SessionEvent *session_event) {  
  if(selects.relation_num <= 0){
    LOG_ERROR("No table given");
    return RC::SQL_SYNTAX;
  }
  if(selects.attr_num <= 0){
    LOG_ERROR("No column given");
    return RC::SQL_SYNTAX;
  }

  //检验表是否存在
  std::unordered_map<const char *, Table *, hash_string, equal_string> tables;
  for(int i=0; i < selects.relation_num; i++) {
    const char *table_name = selects.relations[i];
    Table *table = DefaultHandler::get_default().find_table(db, table_name);
    if(table == nullptr) {
      LOG_WARN("No such table [%s] in db [%s]", table_name, db);
      char err[256];
      sprintf(err, "FAILURE\n", table_name, db);
      session_event->set_response(err);
      return RC::SCHEMA_TABLE_NOT_EXIST;
    }
    tables[table_name] = table;
  }

  //检验查询列
  RC rc = RC::SUCCESS;
  for(int i=0; i < selects.attr_num; i++) {
    const RelAttr &attr = selects.attributes[i];
    const char *relation_name = attr.relation_name;
    const char *attr_name = attr.attribute_name;
    const char *agg_name = attr.agg_name;

    if(strcmp(attr_name, "*")==0) {
      if(agg_name != nullptr){
        continue;
      } else  if(selects.attr_num > 1) {
        //不允许*和其他选择列同时出现
        return RC::MISUSE;
      } else {
        break;
      }
    }

    // 如果是多表查询，判断是否列出表名
    if(tables.size()>1 && relation_name == nullptr) {
      LOG_WARN("select attribute [%s] in db [%s] should be given according table's name", attr_name, db);
      char err[256];
      sprintf(err, "Failure. select attribute [%s] in db [%s] should be given according table's name", attr_name, db);
      session_event->set_response(err);
      return RC::SQL_SYNTAX;
    }
    //检查 field是否存在
    rc = check_field(tables, relation_name, attr_name, session_event);
    if(rc != RC::SUCCESS) {
      return rc;
    }
  }
  //检查condition
  for(int i = 0; i < selects.condition_num; i++){
    const Condition &condition = selects.conditions[i];
    if(condition.left_is_attr) {
      const char *relation_name = condition.left_attr.relation_name;
      const char *attr_name = condition.left_attr.attribute_name;
      rc = check_field(tables, relation_name, attr_name, session_event);
      if(rc != RC::SUCCESS) {
        return rc;
      }
    }

    if(condition.right_is_attr) {
      const char *relation_name = condition.right_attr.relation_name;
      const char *attr_name = condition.right_attr.attribute_name;
      rc = check_field(tables, relation_name, attr_name, session_event);
      if(rc != RC::SUCCESS) {
        return rc;
      }
    }

  }

  return RC::SUCCESS;
}
//检查table中是否有该field
RC check_field(std::unordered_map<const char *, Table *, hash_string, equal_string>tables, 
            const char *relation_name, const char *attr_name, SessionEvent *session_event) {
  char err[256];
  if(tables.size()>1 && tables.count(relation_name)==0 ||
  tables.size()==1 && relation_name != nullptr && tables.count(relation_name)==0) {
    if(relation_name != nullptr) {
      LOG_WARN("Table [%s] is non-exist", relation_name);
      sprintf(err, "Failure! Table [%s] is non-exist\n", relation_name);
    } else {
      LOG_WARN("Please given the relation name of the column when you select many tables");
      sprintf(err, "Failure! Please given the relation name of the column when you select many tables");
    }
    session_event->set_response(err);
    return RC::SQL_SYNTAX;
  }
  
  Table *table;
  if(relation_name != nullptr) {
    table = tables[relation_name];
  } else {
    //前面校验没问题，那一定是单表查询
    table = tables.begin()->second;
  }
  //检查列是否存在
  const FieldMeta *field_meta = table->table_meta().field(attr_name);
  if(field_meta == nullptr) {
    LOG_WARN("No such field. %s.%s", relation_name, attr_name);
    sprintf(err, "Failure! No such field.\n");
    session_event->set_response(err);
    return RC::SCHEMA_FIELD_MISSING;
  }
  return RC::SUCCESS;
}

void init_join_conditions_between_tables(const Selects &selects, JoinConds &map) {
  for(int i=0; i<selects.condition_num; i++) {
    const Condition &condition = selects.conditions[i];
    const char *left_table_name = selects.conditions[i].left_attr.relation_name;
    const char *right_table_name = selects.conditions[i].right_attr.relation_name;
    //no table name or non-attr  won't be added to the join conditions
    if(left_table_name == nullptr || right_table_name == nullptr)
      continue;
    if(condition.left_is_attr == 0 || condition.right_is_attr ==0)
      continue;
    int cmp = strcmp(left_table_name, right_table_name);
    if(cmp != 0) {
      Condition new_condition;
      new_condition.comp = condition.comp;
      if(cmp > 0) {
        //exchange table
        const char *tmp = left_table_name;
        left_table_name = right_table_name;
        right_table_name = tmp;

        new_condition.left_is_attr = condition.right_is_attr;
        new_condition.left_value = condition.right_value;
        new_condition.left_attr = condition.right_attr;
        new_condition.right_is_attr = condition.left_is_attr;
        new_condition.right_value = condition.left_value;
        new_condition.right_attr = condition.left_attr;
      }
      else {
        new_condition.left_is_attr = condition.left_is_attr;
        new_condition.left_value = condition.left_value;
        new_condition.left_attr = condition.left_attr;
        new_condition.right_is_attr = condition.right_is_attr;
        new_condition.right_value = condition.right_value;
        new_condition.right_attr = condition.right_attr;        
      }

      TablePair pair(left_table_name, right_table_name);
      if(map.count(pair)==0) {
        std::vector<Condition> v;
        map[pair] = std::move(v);
      }
      map[pair].emplace_back(std::move(new_condition));
    }
  }
}
void init_kv_between_name_and_value(std::vector<TupleSet> &tuple_sets, 
                    MapName2Value &name2value, MapValue2Name &value2name) {

  for(int i=0; i<tuple_sets.size(); i++) {
    TupleSet *tuple_set = &tuple_sets[i];
    const char *table_name = tuple_set->get_schema().field(0).table_name();

    if(name2value.count(table_name) == 0) {
      name2value[table_name] = tuple_set;
    }
    if(value2name.count(tuple_set) == 0) {
      std::vector<const char *> n;
      n.push_back(table_name);
      value2name[tuple_set] = n;
    }
    else {
      value2name[tuple_set].push_back(table_name);
    }
  }
}
//init aggregation operation type
void init_aggregation(const char *table_name, const char *attr_name, const char *agg_name, AggInfo & agg_info) {
  agg_info.relation_name = table_name;
  agg_info.attr_name = attr_name;

  if(strcmp(agg_name, "COUNT")==0) {
    agg_info.type = AggType::COUNTS;
  } else if(strcmp(agg_name, "MAX")==0) {
    agg_info.type = AggType::MAXS;
  } else if(strcmp(agg_name, "MIN")==0) {
    agg_info.type = AggType::MINS;
  } else if(strcmp(agg_name, "AVG")==0) {
    agg_info.type = AggType::AVGS;
  } else {
    LOG_ERROR("here, type missing");
  }
}

