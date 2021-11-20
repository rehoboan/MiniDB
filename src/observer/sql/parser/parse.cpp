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

#include <mutex>
#include "sql/parser/parse.h"
#include "rc.h"
#include "common/log/log.h"

RC parse(char *st, Query *sqln);

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

void expression_init(Expression *expr, OperatorType operator_type, Expression *left_expr, Expression *right_expr){
  expr->left_expr = left_expr;
  expr->right_expr = right_expr;
  expr->operator_type = operator_type;
  expr->is_value = 0;
  expr->is_attr = 0;
  expr->is_operator = 1;
}

void expression_init_val(Expression *expr, Value *value){
  expr->value = *value;
  expr->right_expr = nullptr;
  expr->left_expr = nullptr;
  expr->is_value = 1;
  expr->is_attr = 0;
  expr->is_operator = 0;
}

void expression_init_attr(Expression *expr,RelAttr *attr){
  expr->attr = *attr;
  expr->right_expr = nullptr;
  expr->left_expr = nullptr;
  expr->is_value = 0;
  expr->is_attr = 1;
  expr->is_operator = 0;
}

void debug_subselect() {
  //std::cout<<"here comes in subselect parse tree"<<std::endl;
  printf("here comes in subselect parse tree\n");
}

void push_down() {
  printf("down to son query\n");
}

void push_up() {
  printf("up to father query\n");
}

void father_query() {
  printf("here comes to the father select\n");
}

void son_query() {
  printf("here comes to the son select\n");
}

void update_select_num(Selects *selects) {
  selects->select_num++;
}

void relation_attr_init(RelAttr *relation_attr, const char *relation_name, const char *attribute_name) {
  relation_attr->agg_name = nullptr;
  if (relation_name != nullptr) {
    relation_attr->relation_name = strdup(relation_name);
  } else {
    relation_attr->relation_name = nullptr;
  }
  relation_attr->attribute_name = strdup(attribute_name);
}

void relation_order_init(OrderDescription *order_desc, const char *relation_name, const char *attribute_name, OrderType order_type){
  if (relation_name != nullptr) {
    order_desc->relation_name = strdup(relation_name);
  } else {
    order_desc->relation_name = nullptr;
  }
  order_desc->attribute_name = strdup(attribute_name);
  order_desc->type = order_type;
}

void relation_group_init(GroupByDescription *group_desc,const char *relation_name,const char *attribute_name){
  if (relation_name != nullptr) {
    group_desc->relation_name = strdup(relation_name);
  } else {
    group_desc->relation_name = nullptr;
  }
  group_desc->attribute_name = strdup(attribute_name);
}

void relation_attr_with_agg_init(RelAttr *relation_attr, const char *agg_name,
                                const char *relation_name, const char *attribute_name) {
  relation_attr_init(relation_attr, relation_name, attribute_name);
  if(agg_name != nullptr)
      relation_attr->agg_name = strdup(agg_name);
}

void relation_attr_destroy(RelAttr *relation_attr) {
  free(relation_attr->relation_name);
  free(relation_attr->attribute_name);
  relation_attr->relation_name = nullptr;
  relation_attr->attribute_name = nullptr;
}

void value_init_null(Value *value){
    value->type = UNDEFINED | NULL_VALUE;
    value->data = malloc(sizeof(int));
    value->num = 1;
}

void value_init_integer(Value *value, int v) {
  value->type = INTS;
  value->data = malloc(sizeof(v));
  memcpy(value->data, &v, sizeof(v));
  value->num = 1;
}
void value_init_float(Value *value, float v) {
  value->type = FLOATS;
  value->data = malloc(sizeof(v));
  memcpy(value->data, &v, sizeof(v));
  value->num = 1;
}
void value_init_string(Value *value, const char *v) {
  value->type = CHARS;
  value->data = strdup(v);
  value->num = 1;
}

void value_init_date(Value *value, const char *v) {
    value->num= 1;

    int days[12]={31,28,31,30,31,30,31,31,30,31,30,31};

    value->type = DATES;
    value->data = malloc(MAX_DATE_LEN + 1);

    int year,month,day;
    sscanf(v,"%d-%d-%d",&year,&month,&day);
    bool valid_date = true;

    if(day > days[month-1]){
        valid_date = false;
    }

    if(month == 2 && day == 29) {
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
                valid_date = true;
        }
    }

    if (!valid_date){
        value->type = INTS;
        return;
    }

    int i = 0;
    char *record = (char*)value->data;
    uint len = strlen(v);
    for (int j = 0; j < len; ++j) {
        if(v[j] == '-'){
            record[i++] = v[j];
            if ((j >= len - 2) || !(v[j+2] >= '0' && v[j+2] <= '9')){
                record[i++] = '0';
            }
        }else{
                record[i++] = v[j];
        }
        record[i] = '\0';
    }
}

void value_init_subselect(Value *value) {
  value->type = SUBSELECT;
  value->data = nullptr;
  value->num = 0;
}

void value_destroy(Value *value) {
  switch (value->type){
    case INTS:
      free(value->data);
      break;
    case FLOATS:
      free(value->data);
      break;
    case DATES: {
      MultiValueLinkNode *p = (MultiValueLinkNode *)(value->data);
      while(p) {
        MultiValueLinkNode *pn = p->next_value;
        delete(p);
        p = pn;
      }
    }
      break;
    case CHARS: {
      MultiValueLinkNode *p = (MultiValueLinkNode *)(value->data);
      while(p) {
        MultiValueLinkNode *pn = p->next_value;
        delete(p);
        p = pn;
      }
    }
      break;
    default:
      break;
  }

  value->data = nullptr;
  value->type = UNDEFINED;
  value->num = 0;
}

void switch_comp(CompOp *comp){
  switch (*comp) {
    case LESS_THAN:
      *comp = GREAT_THAN;
      break;
    case GREAT_THAN:
     *comp = LESS_THAN;
     break;
    case LESS_EQUAL:
      *comp = GREAT_EQUAL;
      break;
    case GREAT_EQUAL:
      *comp = LESS_EQUAL;
      break;
    default:
      break;
  }
}


void condition_init(Condition *condition, CompOp comp, 
                    int left_is_attr, RelAttr *left_attr, Value *left_value,
                    int right_is_attr, RelAttr *right_attr, Value *right_value, Expression *left_expr,Expression *right_expr,
                    int left_is_expr, int right_is_expr
                    ) {
  condition->comp = comp;
  condition->left_is_attr = left_is_attr;
  condition->left_is_expr = left_is_expr;
  if (left_is_attr) {
    condition->left_attr = *left_attr;
  }else if (left_is_expr){
    condition->left_expr = left_expr;
  }else {
    condition->left_value = *left_value;
  }
  condition->right_is_attr = right_is_attr;
  condition->right_is_attr = right_is_expr;
  if (right_is_attr) {
    condition->right_attr = *right_attr;
  }else if(right_is_expr){
    condition->right_expr = right_expr;
  }else {
    condition->right_value = *right_value;
  }
  printf("condition->right_value.num%d\n", condition->right_value.num);
}

//void condition_init_expr(Condition *condition,,CompOp comp){
//  condition->comp = comp;
//  condition->left_expr = left_expr;
//  condition->right_expr = right_expr;
////  condition->left_is_expr = 1;
//}


void condition_destroy(Condition *condition) {
  if (condition->left_is_attr) {
    relation_attr_destroy(&condition->left_attr);
  } else {
    value_destroy(&condition->left_value);
  }
  if (condition->right_is_attr) {
    relation_attr_destroy(&condition->right_attr);
  } else {
    value_destroy(&condition->right_value);
  }
}

void attr_info_init(AttrInfo *attr_info, const char *name, int type, size_t length, bool nullable) {

    attr_info->name = strdup(name);

    if(nullable){
        attr_info->type = type | NULL_VALUE;
    }else{
        attr_info->type = type;
    }

    if(type == DATES){
        attr_info->length = MAX_DATE_LEN + 1;
    }else if(type == CHARS){
        attr_info->length = length + 1;
    }else if(type == TEXTS){
        attr_info->length = sizeof(int) * 2;
    }else{
        attr_info->length = length;
    }

}
void attr_info_destroy(AttrInfo *attr_info) {
  free(attr_info->name);
  attr_info->name = nullptr;
}

void selects_init(Selects *selects, ...);
void selects_append_attribute(Selects *selects, RelAttr *rel_attr, size_t select_num) {
  SubSelects &subselect = selects->subselects[select_num];
  subselect.attributes[subselect.attr_num++] = *rel_attr;
}
void selects_append_relation(Selects *selects, const char *relation_name, size_t select_num) {
  std::cout<<"select_num   "<<select_num<<std::endl;
  std::cout<<"relationname    "<<relation_name<<std::endl;
  SubSelects &subselect = selects->subselects[select_num];
    std::cout<<"relationnum     "<<subselect.relation_num<<std::endl;
  subselect.relations[subselect.relation_num++] = strdup(relation_name);
}

void selects_append_conditions(Selects *selects, Condition conditions[], size_t condition_num, size_t select_num) {
  SubSelects &subselect = selects->subselects[selects->select_num];
  assert(condition_num <= sizeof(subselect.conditions)/sizeof(subselect.conditions[0]));
  for (size_t i = 0; i < condition_num; i++) {
    subselect.conditions[i] = conditions[i];
  }
  subselect.condition_num = condition_num;
}

void selects_append_condition(Selects *selects, Condition *condition, size_t select_num) {
  SubSelects &subselect = selects->subselects[select_num];
  subselect.conditions[subselect.condition_num++] = *condition;
}

void selects_append_orders(Selects *selects, OrderDescription orders[], size_t order_num, size_t select_num){
  SubSelects &subselect = selects->subselects[select_num];
  for (size_t i = 0; i < order_num; i++) {
    subselect.order_des[i] = orders[i];
  }
  subselect.order_num = order_num;
}

void selects_append_groups(Selects *selects, GroupByDescription groups[], size_t group_num, size_t select_num){
  SubSelects &subselect = selects->subselects[select_num];
  for (size_t i = 0; i < group_num; i++) {
    subselect.group_des[i] = groups[i];
  }
  subselect.group_num = group_num;
}

void selects_append_expression(Selects *selects, Expression *expressions, size_t select_num){
  SubSelects &subselect = selects->subselects[select_num];
  subselect.expr_des[subselect.expr_num++] = *expressions;
}

void selects_destroy(Selects *selects) {
  //size_t select_num = selects->select_num;
  for(auto &subselect : selects->subselects) {
    for(size_t i = 0; i < subselect.attr_num; i++) {
      relation_attr_destroy(&subselect.attributes[i]);
    }
    subselect.attr_num = 0;

    for(size_t i = 0; i < subselect.relation_num; i++) {
      free(subselect.relations[i]);
      subselect.relations[i] = NULL;
    }
    subselect.relation_num = 0;

    for(size_t i = 0; i < subselect.condition_num; i++) {
      condition_destroy(&subselect.conditions[i]);
    }
    subselect.condition_num = 0;
  }

}

void inserts_init(Inserts *inserts, const char *relation_name, Value values[], size_t value_num, const int row_end[], size_t row_num) {
    inserts->relation_name = strdup(relation_name);
    for (int i = 0; i < value_num; i++) {
        inserts->values[i] = values[i];
    }
    inserts->value_num = value_num;
    for(int i = 0; i< row_num; i++) {
        inserts->row_end[i] = row_end[i];
    }
    inserts->row_num = row_num;
}
void inserts_destroy(Inserts *inserts) {
  free(inserts->relation_name);
  inserts->relation_name = nullptr;

  for (size_t i = 0; i < inserts->value_num; i++) {
    value_destroy(&inserts->values[i]);
  }
  inserts->value_num = 0;
}

void deletes_init_relation(Deletes *deletes, const char *relation_name) {
  deletes->relation_name = strdup(relation_name);
}

void deletes_set_conditions(Deletes *deletes, Condition conditions[], size_t condition_num) {
  assert(condition_num <= sizeof(deletes->conditions)/sizeof(deletes->conditions[0]));
  for (size_t i = 0; i < condition_num; i++) {
    deletes->conditions[i] = conditions[i];
  }
  deletes->condition_num = condition_num;
}
void deletes_destroy(Deletes *deletes) {
  for (size_t i = 0; i < deletes->condition_num; i++) {
    condition_destroy(&deletes->conditions[i]);
  }
  deletes->condition_num = 0;
  free(deletes->relation_name);
  deletes->relation_name = nullptr;
}

void updates_init(Updates *updates, const char *relation_name, const char *attribute_name,
                  Value *value, Condition conditions[], size_t condition_num) {
  updates->relation_name = strdup(relation_name);
  updates->attribute_name = strdup(attribute_name);
  updates->value = *value;

  assert(condition_num <= sizeof(updates->conditions)/sizeof(updates->conditions[0]));
  for (size_t i = 0; i < condition_num; i++) {
    updates->conditions[i] = conditions[i];
  }
  updates->condition_num = condition_num;
}

void updates_destroy(Updates *updates) {
  free(updates->relation_name);
  free(updates->attribute_name);
  updates->relation_name = nullptr;
  updates->attribute_name = nullptr;

  value_destroy(&updates->value);

  for (size_t i = 0; i < updates->condition_num; i++) {
    condition_destroy(&updates->conditions[i]);
  }
  updates->condition_num = 0;
}

void create_table_append_attribute(CreateTable *create_table, AttrInfo *attr_info) {
  create_table->attributes[create_table->attribute_count++] = *attr_info;
}
void create_table_init_name(CreateTable *create_table, const char *relation_name) {
  create_table->relation_name = strdup(relation_name);
}
void create_table_destroy(CreateTable *create_table) {
  for (size_t i = 0; i < create_table->attribute_count; i++) {
    attr_info_destroy(&create_table->attributes[i]);
  }
  create_table->attribute_count = 0;
  free(create_table->relation_name);
  create_table->relation_name = nullptr;
}

void drop_table_init(DropTable *drop_table, const char *relation_name) {
  drop_table->relation_name = strdup(relation_name);
}
void drop_table_destroy(DropTable *drop_table) {
  free(drop_table->relation_name);
  drop_table->relation_name = nullptr;
}

void create_index_init(CreateIndex *create_index, const char *index_name, 
                       const char *relation_name, const char *attr_name[], int len, char unique) {
    create_index->index_name = strdup(index_name);
    create_index->relation_name = strdup(relation_name);
    for(int i = 0; i < len; i++){
        create_index->attribute_name[i] = strdup(attr_name[i]);
    }
    create_index->index_field_num = len;
    create_index->unique = unique;
}
void create_index_destroy(CreateIndex *create_index) {
    free(create_index->index_name);
    free(create_index->relation_name);
    for(int i = 0;i < create_index->index_field_num; i++){
        free(create_index->attribute_name[i]);
        create_index->attribute_name[i] = nullptr;
    }

    create_index->index_name = nullptr;
    create_index->relation_name = nullptr;
}

void drop_index_init(DropIndex *drop_index, const char *index_name) {
  drop_index->index_name = strdup(index_name);
}
void drop_index_destroy(DropIndex *drop_index) {
  free((char *)drop_index->index_name);
  drop_index->index_name = nullptr;
}

void desc_table_init(DescTable *desc_table, const char *relation_name) {
  desc_table->relation_name = strdup(relation_name);
}

void desc_table_destroy(DescTable *desc_table) {
  free((char *)desc_table->relation_name);
  desc_table->relation_name = nullptr;
}

void load_data_init(LoadData *load_data, const char *relation_name, const char *file_name) {
  load_data->relation_name = strdup(relation_name);

  if (file_name[0] == '\'' || file_name[0] == '\"') {
    file_name++;
  }
  char *dup_file_name = strdup(file_name);
  int len = strlen(dup_file_name);
  if (dup_file_name[len - 1] == '\'' || dup_file_name[len - 1] == '\"') {
    dup_file_name[len - 1] = 0;
  }
  load_data->file_name = dup_file_name;
}

void load_data_destroy(LoadData *load_data) {
  free((char *)load_data->relation_name);
  free((char *)load_data->file_name);
  load_data->relation_name = nullptr;
  load_data->file_name = nullptr;
}

void query_init(Query *query) {
  query->flag = SCF_ERROR;
  memset(&query->sstr, 0, sizeof(query->sstr));
}

Query *query_create() {
  Query *query = (Query *)malloc(sizeof(Query));
  if (nullptr == query) {
    LOG_ERROR("Failed to alloc memroy for query. size=%ld", sizeof(Query));
    return nullptr;
  }

  query_init(query);
  return query;
}

void query_reset(Query *query) {
  switch (query->flag) {
    case SCF_SELECT: {
      selects_destroy(&query->sstr.selection);
    }
    break;
    case SCF_INSERT: {
      inserts_destroy(&query->sstr.insertion);
    }
    break;
    case SCF_DELETE: {
      deletes_destroy(&query->sstr.deletion);
    }
    break;
    case SCF_UPDATE: {
      updates_destroy(&query->sstr.update);
    }
    break;
    case SCF_CREATE_TABLE: {
      create_table_destroy(&query->sstr.create_table);
    }
    break;
    case SCF_DROP_TABLE: {
      drop_table_destroy(&query->sstr.drop_table);
    }
    break;
    case SCF_CREATE_INDEX: {
      create_index_destroy(&query->sstr.create_index);
    }
    break;
    case SCF_DROP_INDEX: {
      drop_index_destroy(&query->sstr.drop_index);
    }
    break;
    case SCF_SYNC: {

    }
    break;
    case SCF_SHOW_TABLES:
    break;

    case SCF_DESC_TABLE: {
      desc_table_destroy(&query->sstr.desc_table);
    }
    break;

    case SCF_LOAD_DATA: {
      load_data_destroy(&query->sstr.load_data);
    }
    break;
    case SCF_BEGIN:
    case SCF_COMMIT:
    case SCF_ROLLBACK:
    case SCF_HELP:
    case SCF_EXIT:
    case SCF_ERROR:
    break;
  }
}

void query_destroy(Query *query) {
  query_reset(query);
  free(query);
}
#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus

////////////////////////////////////////////////////////////////////////////////

extern "C" int sql_parse(const char *st, Query  *sqls);

RC parse(const char *st, Query *sqln) {
  sql_parse(st, sqln);

  if (sqln->flag == SCF_ERROR)
    return SQL_SYNTAX;
  else
    return SUCCESS;
}
