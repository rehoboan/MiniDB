
%{

#include "sql/parser/parse_defs.h"
#include "sql/parser/yacc_sql.tab.h"
#include "sql/parser/lex.yy.h"
// #include "common/log/log.h" // 包含C++中的头文件

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct ParserContext {
  Query * ssql;
  //size_t select_length;
  size_t condition_length;
  size_t condition_level;
  size_t from_level;
  size_t attr_level;
  size_t value_length;
  Value values[MAX_VALUE_NUM];
  size_t row_num;
  int row_end[MAX_ROW];

  bool nullable;

  char *field_names[MAX_INDEX_FIELD];
  int index_field_num;

  Condition conditions[MAX_NUM];
  CompOp comp[MAX_SELECTS_NUM];
  char id[MAX_NUM];

  size_t    order_num;
  OrderDescription orders[MAX_NUM];
  OrderType	order_type;

  size_t	group_num;
  GroupByDescription	groups[MAX_NUM];


} ParserContext;

//获取子串
char *substr(const char *s,int n1,int n2)/*从s中提取下标为n1~n2的字符组成一个新字符串，然后返回这个新串的首地址*/
{
  char *sp = malloc(sizeof(char) * (n2 - n1 + 2));
  int i, j = 0;
  for (i = n1; i <= n2; i++) {
    sp[j++] = s[i];
  }
  sp[j] = 0;
  return sp;
}

void yyerror(yyscan_t scanner, const char *str)
{
  ParserContext *context = (ParserContext *)(yyget_extra(scanner));
  query_reset(context->ssql);
  context->ssql->flag = SCF_ERROR;
  context->condition_length = 0;
  context->condition_level = 0;
  context->attr_level = 0;
  context->from_level = 0;
  context->value_length = 0;
  context->ssql->sstr.insertion.value_num = 0;
  printf("parse sql failed. error=%s", str);
}

ParserContext *get_context(yyscan_t scanner)
{
  return (ParserContext *)yyget_extra(scanner);
}

#define CONTEXT get_context(scanner)

%}

%define api.pure full
%lex-param { yyscan_t scanner }
%parse-param { void *scanner }

//标识tokens
%token  SEMICOLON
        CREATE
        DROP
		COUNT
		MAX
		MIN
		AVG

		INNER
		JOIN
        TABLE
        TABLES
        INDEX
        SELECT

		ORDER
		BY
		ASC
		DESC

		GROUP

        SHOW
        SYNC
        INSERT
        DELETE
        UPDATE
        LBRACE
        RBRACE
        COMMA
        TRX_BEGIN
        TRX_COMMIT
        TRX_ROLLBACK
        INT_T
        STRING_T
        FLOAT_T

        DATE_T //DATE
        TEXT_T //TEXT
        UNIQUE



        HELP
        EXIT
        DOT //QUOTE
        INTO
        VALUES
        FROM
        WHERE
        AND
        SET
        ON
        LOAD
        DATA
        INFILE

	IS
	NOT
	NULLABLE
	NULL_T

        EQ
        LT
        GT
        LE
        GE
        NE
		IN

%union {
  struct _Attr *attr;
  struct _Condition *condition1;
  struct _Value *value1;
  struct _OrderDescription *order;
  char *string;
  int number;
  float floats;
  struct expression_ *expressions;
}

%token <number> NUMBER
%token <floats> FLOAT
%token <string>	DATE
%token <string> ID
%token <string> PATH
%token <string> SSS
%token <string> STAR
%token <string> STRING_V
//非终结符

%type <number> type;
%type <condition1> condition;
%type <value1> value;
%type <number> number;
%type <expressions> expression_cluster;
%type <expressions> expression;
%type <expressions> primary_expression;

%left ADD MINUS
%left STAR DIV
%%

commands:		//commands or sqls. parser starts here.
    /* empty */
    | commands command
    ;

command:
	  select
	| insert
	| update
	| delete
	| create_table
	| drop_table
	| show_tables
	| desc_table
	| create_index
	| drop_index
	| sync
	| begin
	| commit
	| rollback
	| load_data
	| help
	| exit
    ;

exit:
    EXIT SEMICOLON {
        CONTEXT->ssql->flag=SCF_EXIT;//"exit";
    };

help:
    HELP SEMICOLON {
        CONTEXT->ssql->flag=SCF_HELP;//"help";
    };

sync:
    SYNC SEMICOLON {
      CONTEXT->ssql->flag = SCF_SYNC;
    }
    ;

begin:
    TRX_BEGIN SEMICOLON {
      CONTEXT->ssql->flag = SCF_BEGIN;
    }
    ;

commit:
    TRX_COMMIT SEMICOLON {
      CONTEXT->ssql->flag = SCF_COMMIT;
    }
    ;

rollback:
    TRX_ROLLBACK SEMICOLON {
      CONTEXT->ssql->flag = SCF_ROLLBACK;
    }
    ;

drop_table:		/*drop table 语句的语法解析树*/
    DROP TABLE ID SEMICOLON {
        CONTEXT->ssql->flag = SCF_DROP_TABLE;//"drop_table";
        drop_table_init(&CONTEXT->ssql->sstr.drop_table, $3);
    };

show_tables:
    SHOW TABLES SEMICOLON {
      CONTEXT->ssql->flag = SCF_SHOW_TABLES;
    }
    ;

desc_table:
    DESC ID SEMICOLON {
      CONTEXT->ssql->flag = SCF_DESC_TABLE;
      desc_table_init(&CONTEXT->ssql->sstr.desc_table, $2);
    }
    ;

create_index:		/*create index 语句的语法解析树*/
//    CREATE INDEX ID ON ID LBRACE ID RBRACE SEMICOLON
	CREATE INDEX ID ON ID LBRACE field field_list RBRACE SEMICOLON
		{
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, $3, $5, CONTEXT->field_names, CONTEXT->index_field_num, 0);
		}
    |CREATE UNIQUE INDEX ID ON ID LBRACE field field_list RBRACE SEMICOLON
                {
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, $4, $6, CONTEXT->field_names, CONTEXT->index_field_num, 1);
                }
    ;
field_list:

    	|COMMA field field_list{

    	}
    	;
field:
    	ID{
    		CONTEXT->field_names[CONTEXT->index_field_num++]=$1;
    	}
    	;

drop_index:			/*drop index 语句的语法解析树*/
    DROP INDEX ID  SEMICOLON
		{
			CONTEXT->ssql->flag=SCF_DROP_INDEX;//"drop_index";
			drop_index_init(&CONTEXT->ssql->sstr.drop_index, $3);
		}
    ;
create_table:		/*create table 语句的语法解析树*/
    CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE SEMICOLON
		{
			CONTEXT->ssql->flag=SCF_CREATE_TABLE;//"create_table";
			// CONTEXT->ssql->sstr.create_table.attribute_count = CONTEXT->value_length;
			create_table_init_name(&CONTEXT->ssql->sstr.create_table, $3);
			//临时变量清零
			CONTEXT->value_length = 0;
		}
    ;
attr_def_list:
    /* empty */
    | COMMA attr_def attr_def_list {    }
    ;

attr_def:
    ID_get type LBRACE number RBRACE null_value
		{
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, $2, $4, CONTEXT->nullable);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name =(char*)malloc(sizeof(char));
			// strcpy(CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name, CONTEXT->id);
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].type = $2;
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].length = $4;
			CONTEXT->value_length++;
			CONTEXT->nullable = false;
		}
    |ID_get type null_value
		{
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, $2, 4, CONTEXT->nullable);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name=(char*)malloc(sizeof(char));
			// strcpy(CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name, CONTEXT->id);
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].type=$2;
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].length=4; // default attribute length
			CONTEXT->value_length++;
			CONTEXT->nullable = false;
		}
    ;
null_value:
	|NULLABLE{
		CONTEXT->nullable = true;
	}
	|NOT NULL_T{

	}
	;
number:
		NUMBER {$$ = $1;}
		;
type:
	INT_T { $$=INTS; }
       | STRING_T { $$=CHARS; }
       | FLOAT_T { $$=FLOATS; }
       | DATE_T { $$=DATES; }
       | TEXT_T { $$=TEXTS; }
       ;
ID_get:
	ID
	{
		char *temp=$1;
		snprintf(CONTEXT->id, sizeof(CONTEXT->id), "%s", temp);
	}
	;


insert:				/*insert   语句的语法解析树*/
    INSERT INTO ID VALUES row row_list SEMICOLON
		{
			// CONTEXT->values[CONTEXT->value_length++] = *$6;

			CONTEXT->ssql->flag=SCF_INSERT;//"insert";
			// CONTEXT->ssql->sstr.insertion.relation_name = $3;
			// CONTEXT->ssql->sstr.insertion.value_num = CONTEXT->value_length;
			// for(i = 0; i < CONTEXT->value_length; i++){
			// 	CONTEXT->ssql->sstr.insertion.values[i] = CONTEXT->values[i];
      // }
			inserts_init(&CONTEXT->ssql->sstr.insertion, $3, CONTEXT->values, CONTEXT->value_length, CONTEXT->row_end, CONTEXT->row_num);

      //临时变量清零
      CONTEXT->value_length=0;
      CONTEXT->row_num=0;
    }

row_list:
	| COMMA	row row_list	{
	}
	;

row:
	LBRACE value value_list RBRACE	{
		CONTEXT->row_end[CONTEXT->row_num++]=CONTEXT->value_length;
	}
	;

value_list:
    /* empty */
    | COMMA value value_list  {
  		// CONTEXT->values[CONTEXT->value_length++] = *$2;
	  }
    ;
value:
    NULL_T{
		value_init_null(&CONTEXT->values[CONTEXT->value_length++]);
	}
    |NUMBER{
  		value_init_integer(&CONTEXT->values[CONTEXT->value_length++], $1);
		}
    |FLOAT{
  		value_init_float(&CONTEXT->values[CONTEXT->value_length++], $1);
		}
    |DATE {
    			$1 = substr($1,1,strlen($1)-2);
      		value_init_date(&CONTEXT->values[CONTEXT->value_length++], $1);
    		}
    |SSS {
			$1 = substr($1,1,strlen($1)-2);
  		value_init_string(&CONTEXT->values[CONTEXT->value_length++], $1);
		}
    ;

delete:		/*  delete 语句的语法解析树*/
    DELETE FROM ID where SEMICOLON
		{
			CONTEXT->ssql->flag = SCF_DELETE;//"delete";
			deletes_init_relation(&CONTEXT->ssql->sstr.deletion, $3);
			deletes_set_conditions(&CONTEXT->ssql->sstr.deletion,
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;
    }
    ;
update:			/*  update 语句的语法解析树*/
    UPDATE ID SET ID EQ value where SEMICOLON
		{
			CONTEXT->ssql->flag = SCF_UPDATE;//"update";
			Value *value = &CONTEXT->values[0];
			updates_init(&CONTEXT->ssql->sstr.update, $2, $4, value,
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;
		}
    ;
select:				/*  select 语句的语法解析树*/

    SELECT select_attr FROM select_from where opt_group opt_order SEMICOLON
	{
			// CONTEXT->ssql->sstr.selection.relations[CONTEXT->from_length++]=$4;
			selects_append_orders(&CONTEXT->ssql->sstr.selection, CONTEXT->orders, CONTEXT->order_num, 0);
			selects_append_groups(&CONTEXT->ssql->sstr.selection, CONTEXT->groups, CONTEXT->group_num, 0);

			CONTEXT->ssql->flag=SCF_SELECT;//"select";

			update_select_num(&CONTEXT->ssql->sstr.selection);

			//临时变量清零
			CONTEXT->condition_length=0;
			CONTEXT->value_length = 0;
			CONTEXT->order_num = 0;
			CONTEXT->group_num = 0;

	}

	| SELECT select_attr FROM select_join where opt_group opt_order SEMICOLON
	{
		selects_append_orders(&CONTEXT->ssql->sstr.selection, CONTEXT->orders, CONTEXT->order_num, 0);
		selects_append_groups(&CONTEXT->ssql->sstr.selection, CONTEXT->groups, CONTEXT->group_num, 0);
		CONTEXT->ssql->flag = SCF_SELECT;

		update_select_num(&CONTEXT->ssql->sstr.selection);
		//临时变量清0
		CONTEXT->condition_length = 0;
		CONTEXT->value_length = 0;
		CONTEXT->order_num = 0;
		CONTEXT->group_num = 0;
	}
    | SELECT select_attr FROM select_from where 
		{
			//中间层子查询
			// CONTEXT->ssql->sstr.selection.relations[CONTEXT->from_length++]=$4;

			son_query();

			CONTEXT->ssql->flag=SCF_SELECT;//"select";

			update_select_num(&CONTEXT->ssql->sstr.selection);

			//临时变量清零
			CONTEXT->condition_length=0;
			CONTEXT->value_length = 0;
	}
	;
subselect:
	pushdown select pushup
	{
		debug_subselect();
	}
	;
pushdown:
	LBRACE {
		push_down();
		CONTEXT->condition_level++;
	}
	;
pushup:
	RBRACE {
		push_up();
		CONTEXT->condition_level--;
	}
	;
select_attr:
    STAR {
			RelAttr attr;
			relation_attr_init(&attr, NULL, "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr, CONTEXT->attr_level);
			CONTEXT->attr_level++;
		}
	| expression_cluster attr_list{
			selects_append_expression(&CONTEXT->ssql->sstr.selection, $1, CONTEXT->attr_level);
			CONTEXT->attr_level++;
	}

    	| ID attr_list {
			RelAttr attr;
			relation_attr_init(&attr, NULL, $1);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr, CONTEXT->attr_level);
			CONTEXT->attr_level++;
		}
  	| ID DOT ID attr_list {
			RelAttr attr;
			relation_attr_init(&attr, $1, $3);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr, CONTEXT->attr_level);
			CONTEXT->attr_level++;
		}
	
	| COUNT LBRACE STAR RBRACE attr_list {
			RelAttr attr;
			relation_attr_with_agg_init(&attr, "COUNT", NULL, "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr, CONTEXT->attr_level);
			CONTEXT->attr_level++;
		}
	| COUNT LBRACE ID RBRACE attr_list {
			RelAttr attr;
			relation_attr_with_agg_init(&attr, "COUNT", NULL, $3);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr, CONTEXT->attr_level);
			CONTEXT->attr_level++;
		}
	| COUNT LBRACE ID DOT ID RBRACE attr_list {
			RelAttr attr;
			relation_attr_with_agg_init(&attr, "COUNT", $3, $5);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr, CONTEXT->attr_level);
			CONTEXT->attr_level++;
		}
	| MAX LBRACE ID RBRACE attr_list {
			RelAttr attr;
			relation_attr_with_agg_init(&attr, "MAX", NULL, $3);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr, CONTEXT->attr_level);
			CONTEXT->attr_level++;
		}	
	| MAX LBRACE ID DOT ID RBRACE attr_list {
			RelAttr attr;
			relation_attr_with_agg_init(&attr, "MAX", $3, $5);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr, CONTEXT->attr_level);
			CONTEXT->attr_level++;
		}
	| MIN LBRACE ID RBRACE attr_list {
			RelAttr attr;
			relation_attr_with_agg_init(&attr, "MIN", NULL, $3);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr, CONTEXT->attr_level);
			CONTEXT->attr_level++;
		}
	| MIN LBRACE ID DOT ID RBRACE attr_list {
			RelAttr attr;
			relation_attr_with_agg_init(&attr, "MIN", $3, $5);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr, CONTEXT->attr_level);
			CONTEXT->attr_level++;
		}
	| AVG LBRACE ID RBRACE attr_list {
			RelAttr attr;
			relation_attr_with_agg_init(&attr, "AVG", NULL, $3);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr, CONTEXT->attr_level);
			CONTEXT->attr_level++;
		}
	| AVG LBRACE ID DOT ID RBRACE attr_list {
			RelAttr attr;
			relation_attr_with_agg_init(&attr, "AVG", $3, $5);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr, CONTEXT->attr_level);
			CONTEXT->attr_level++;
		}	
    ;

attr_list:
    /* empty */
    | COMMA expression_cluster attr_list{
			selects_append_expression(&CONTEXT->ssql->sstr.selection, $2, CONTEXT->attr_level);
    }
    | COMMA ID attr_list {
			RelAttr attr;
			relation_attr_init(&attr, NULL, $2);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr, CONTEXT->attr_level);
     	  // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length].relation_name = NULL;
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length++].attribute_name=$2;
      }
    | COMMA ID DOT ID attr_list {
			RelAttr attr;
			relation_attr_init(&attr, $2, $4);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr, CONTEXT->attr_level);
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length].attribute_name=$4;
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length++].relation_name=$2;
  	  }
	| COMMA COUNT LBRACE STAR RBRACE attr_list {
			RelAttr attr;
			relation_attr_with_agg_init(&attr, "COUNT", NULL, "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr, CONTEXT->attr_level);
	  }
	| COMMA COUNT LBRACE ID RBRACE attr_list {
			RelAttr attr;
			relation_attr_with_agg_init(&attr, "COUNT", NULL, $4);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr, CONTEXT->attr_level);
	}
	| COMMA COUNT LBRACE ID DOT ID RBRACE attr_list {
			RelAttr attr;
			relation_attr_with_agg_init(&attr, "COUNT", $4, $6);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr, CONTEXT->attr_level);
	}
	| COMMA MAX LBRACE ID RBRACE attr_list {
			RelAttr attr;
			relation_attr_with_agg_init(&attr, "MAX", NULL, $4);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr, CONTEXT->attr_level);
	}
	| COMMA MAX LBRACE ID DOT ID RBRACE attr_list {
			RelAttr attr;
			relation_attr_with_agg_init(&attr, "MAX", $4, $6);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr, CONTEXT->attr_level);
	}
	| COMMA MIN LBRACE ID RBRACE attr_list {
			RelAttr attr;
			relation_attr_with_agg_init(&attr, "MIN", NULL, $4);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr, CONTEXT->attr_level);
	}
	| COMMA MIN LBRACE ID DOT ID RBRACE attr_list {
			RelAttr attr;
			relation_attr_with_agg_init(&attr, "MIN", $4, $6);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr, CONTEXT->attr_level);
	}
	| COMMA AVG LBRACE ID RBRACE attr_list {
			RelAttr attr;
			relation_attr_with_agg_init(&attr, "AVG", NULL, $4);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr, CONTEXT->attr_level);
	} 
	| COMMA AVG LBRACE ID DOT ID RBRACE attr_list {
			RelAttr attr;
			relation_attr_with_agg_init(&attr, "AVG", $4, $6);
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr, CONTEXT->attr_level);
	}
	;
select_from:
	/* empty */
	| ID rel_list
	{
		selects_append_relation(&CONTEXT->ssql->sstr.selection, $1, CONTEXT->from_level);
		CONTEXT->from_level++;
	}
	;
rel_list:
    /* empty */
    | COMMA ID rel_list {
				selects_append_relation(&CONTEXT->ssql->sstr.selection, $2, CONTEXT->from_level);
		  }
    ;
select_join:
	/* empty */
	| ID join_list
	{
		selects_append_relation(&CONTEXT->ssql->sstr.selection, $1, CONTEXT->from_level);
		CONTEXT->from_level++;
	}
	;
join_list:
	/* empty */
	| INNER JOIN ID ON condition condition_list join_list {
		selects_append_relation(&CONTEXT->ssql->sstr.selection, $3, CONTEXT->from_level);
	}
	;
where:
    /* empty */
    | WHERE condition condition_list
    ;

opt_group:
	|GROUP BY column_ref_commalist
	;

column_ref_commalist:
		column_ref
	|	column_ref_commalist COMMA column_ref
	;

column_ref:
		ID {
		GroupByDescription group;
		relation_group_init(&group,NULL,$1);
		CONTEXT->groups[CONTEXT->group_num++] = group;
		}
	|	ID DOT ID{
		GroupByDescription group;
		relation_group_init(&group,$1,$3);
		CONTEXT->groups[CONTEXT->group_num++] = group;

	}
	;

opt_order:
		/* empty */
	|	ORDER BY orderby order_list
	;

order_list:
	|COMMA orderby order_list
	;
orderby:
| ID opt_order_type{
	OrderDescription order;
	relation_order_init(&order, NULL, $1, CONTEXT->order_type);
        CONTEXT->orders[CONTEXT->order_num++] = order;
}
|ID DOT ID opt_order_type{
	OrderDescription order;
	relation_order_init(&order, $1, $3, CONTEXT->order_type);
        CONTEXT->orders[CONTEXT->order_num++] = order;
}


opt_order_type : ASC { CONTEXT->order_type = kOrderAsc; }
| DESC { CONTEXT->order_type = kOrderDesc; }
| /* empty */ { CONTEXT->order_type = kOrderAsc; }
;

condition_list:
    /* empty */
    | AND condition condition_list
    ;

condition:
    ID comOp value
		{
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, $1);

			Value *right_value = &(CONTEXT->values[CONTEXT->value_length - 1]);

			Condition condition;
			condition_init(&condition, CONTEXT->comp[CONTEXT->condition_level], 1, &left_attr, NULL, 0, NULL, right_value, NULL, NULL, 0, 0);
			selects_append_condition(&CONTEXT->ssql->sstr.selection, &condition, CONTEXT->condition_level);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;

		}
		|value comOp value
		{
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 2];
			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

			Condition condition;
			condition_init(&condition, CONTEXT->comp[CONTEXT->condition_level], 0, NULL, left_value, 0, NULL, right_value, NULL, NULL, 0, 0);
			selects_append_condition(&CONTEXT->ssql->sstr.selection, &condition, CONTEXT->condition_level);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			// $$ = ( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 0;
			// $$->left_attr.relation_name=NULL;
			// $$->left_attr.attribute_name=NULL;
			// $$->left_value = *$1;
			// $$->comp = CONTEXT->comp;
			// $$->right_is_attr = 0;
			// $$->right_attr.relation_name = NULL;
			// $$->right_attr.attribute_name = NULL;
			// $$->right_value = *$3;

		}
		|ID comOp ID
		{
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, $1);
			RelAttr right_attr;
			relation_attr_init(&right_attr, NULL, $3);

			Condition condition;
			condition_init(&condition, CONTEXT->comp[CONTEXT->condition_level], 1, &left_attr, NULL, 1, &right_attr, NULL, NULL, NULL, 0, 0);
			selects_append_condition(&CONTEXT->ssql->sstr.selection, &condition, CONTEXT->condition_level);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;
			// $$->left_attr.relation_name=NULL;
			// $$->left_attr.attribute_name=$1;
			// $$->comp = CONTEXT->comp;
			// $$->right_is_attr = 1;
			// $$->right_attr.relation_name=NULL;
			// $$->right_attr.attribute_name=$3;

		}
    |value comOp ID
		{
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];
			RelAttr right_attr;
			relation_attr_init(&right_attr, NULL, $3);

			Condition condition;
			condition_init(&condition, CONTEXT->comp[CONTEXT->condition_level], 0, NULL, left_value, 1, &right_attr, NULL, NULL, NULL, 0, 0);
			selects_append_condition(&CONTEXT->ssql->sstr.selection, &condition, CONTEXT->condition_level);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;

			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 0;
			// $$->left_attr.relation_name=NULL;
			// $$->left_attr.attribute_name=NULL;
			// $$->left_value = *$1;
			// $$->comp=CONTEXT->comp;

			// $$->right_is_attr = 1;
			// $$->right_attr.relation_name=NULL;
			// $$->right_attr.attribute_name=$3;

		}
    |ID DOT ID comOp value
		{
			RelAttr left_attr;
			relation_attr_init(&left_attr, $1, $3);
			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

			Condition condition;
			condition_init(&condition, CONTEXT->comp[CONTEXT->condition_level], 1, &left_attr, NULL, 0, NULL, right_value, NULL, NULL, 0, 0);
			selects_append_condition(&CONTEXT->ssql->sstr.selection, &condition, CONTEXT->condition_level);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;

			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;
			// $$->left_attr.relation_name=$1;
			// $$->left_attr.attribute_name=$3;
			// $$->comp=CONTEXT->comp;
			// $$->right_is_attr = 0;   //属性值
			// $$->right_attr.relation_name=NULL;
			// $$->right_attr.attribute_name=NULL;
			// $$->right_value =*$5;

    }
    |value comOp ID DOT ID
		{
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];

			RelAttr right_attr;
			relation_attr_init(&right_attr, $3, $5);

			Condition condition;
			condition_init(&condition, CONTEXT->comp[CONTEXT->condition_level], 0, NULL, left_value, 1, &right_attr, NULL, NULL, NULL, 0, 0);
			selects_append_condition(&CONTEXT->ssql->sstr.selection, &condition, CONTEXT->condition_level);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 0;//属性值
			// $$->left_attr.relation_name=NULL;
			// $$->left_attr.attribute_name=NULL;
			// $$->left_value = *$1;
			// $$->comp =CONTEXT->comp;
			// $$->right_is_attr = 1;//属性
			// $$->right_attr.relation_name = $3;
			// $$->right_attr.attribute_name = $5;

    }
    |ID DOT ID comOp ID DOT ID
		{
			RelAttr left_attr;
			relation_attr_init(&left_attr, $1, $3);
			RelAttr right_attr;
			relation_attr_init(&right_attr, $5, $7);

			Condition condition;
			condition_init(&condition, CONTEXT->comp[CONTEXT->condition_level], 1, &left_attr, NULL, 1, &right_attr, NULL, NULL, NULL, 0, 0);
			selects_append_condition(&CONTEXT->ssql->sstr.selection, &condition, CONTEXT->condition_level);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;		//属性
			// $$->left_attr.relation_name=$1;
			// $$->left_attr.attribute_name=$3;
			// $$->comp =CONTEXT->comp;
			// $$->right_is_attr = 1;		//属性
			// $$->right_attr.relation_name=$5;
			// $$->right_attr.attribute_name=$7;
    }
	| ID comOp subselect 
	{
		RelAttr left_attr;
		relation_attr_init(&left_attr, NULL, $1);

		value_init_subselect(&CONTEXT->values[CONTEXT->value_length++]);
		Condition condition;
		condition_init(&condition, CONTEXT->comp[CONTEXT->condition_level], 1, &left_attr, NULL, 0, NULL, &(CONTEXT->values[CONTEXT->value_length - 1]), NULL, NULL, 0, 0);
		selects_append_condition(&CONTEXT->ssql->sstr.selection, &condition, CONTEXT->condition_level);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;


	}
	| ID DOT ID comOp subselect
	{
		
		RelAttr left_attr;
		relation_attr_init(&left_attr, $1, $3);

		value_init_subselect(&CONTEXT->values[CONTEXT->value_length++]);
		Condition condition;
		condition_init(&condition, CONTEXT->comp[CONTEXT->condition_level], 1, &left_attr, NULL, 0, NULL, &(CONTEXT->values[CONTEXT->value_length - 1]), NULL, NULL, 0, 0);
		selects_append_condition(&CONTEXT->ssql->sstr.selection, &condition, CONTEXT->condition_level);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
	}
	| subselect comOp ID
	{
		RelAttr left_attr;
		relation_attr_init(&left_attr, NULL, $3);

		value_init_subselect(&CONTEXT->values[CONTEXT->value_length++]);
		switch_comp(&CONTEXT->comp[CONTEXT->condition_level]);
		Condition condition;
		condition_init(&condition, CONTEXT->comp[CONTEXT->condition_level], 1, &left_attr, NULL, 0, NULL, &(CONTEXT->values[CONTEXT->value_length - 1]), NULL, NULL, 0, 0);
		selects_append_condition(&CONTEXT->ssql->sstr.selection, &condition, CONTEXT->condition_level);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
	}
	| subselect comOp ID DOT ID
	{
		RelAttr left_attr;
		relation_attr_init(&left_attr, $3, $5);

		value_init_subselect(&CONTEXT->values[CONTEXT->value_length++]);
		switch_comp(&CONTEXT->comp[CONTEXT->condition_level]);
		Condition condition;
		condition_init(&condition, CONTEXT->comp[CONTEXT->condition_level], 1, &left_attr, NULL, 0, NULL, &(CONTEXT->values[CONTEXT->value_length - 1]), NULL, NULL, 0, 0);
		selects_append_condition(&CONTEXT->ssql->sstr.selection, &condition, CONTEXT->condition_level);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
	}
	| ID comOp expression_cluster{
		RelAttr left_attr;
		relation_attr_init(&left_attr, NULL, $1);

		Condition condition;
		condition_init(&condition, CONTEXT->comp[CONTEXT->condition_level], 1, &left_attr, NULL, 0, NULL, NULL, NULL, $3, 0, 1);

		selects_append_condition(&CONTEXT->ssql->sstr.selection, &condition, CONTEXT->condition_level);
                CONTEXT->conditions[CONTEXT->condition_length++] = condition;

	}
	| ID DOT ID comOp expression_cluster{
		RelAttr left_attr;
        	relation_attr_init(&left_attr, $1, $3);

        	Condition condition;
                condition_init(&condition, CONTEXT->comp[CONTEXT->condition_level], 1, &left_attr, NULL, 0, NULL, NULL, NULL, $5, 0, 1);

                selects_append_condition(&CONTEXT->ssql->sstr.selection, &condition, CONTEXT->condition_level);
                CONTEXT->conditions[CONTEXT->condition_length++] = condition;

	}
	| value comOp expression_cluster{
		Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];

		Condition condition;
                condition_init(&condition, CONTEXT->comp[CONTEXT->condition_level], 0, NULL, left_value, 0, NULL, NULL, NULL, $3, 0, 1);

                selects_append_condition(&CONTEXT->ssql->sstr.selection, &condition, CONTEXT->condition_level);
                CONTEXT->conditions[CONTEXT->condition_length++] = condition;

	}
	| expression_cluster comOp ID{
		RelAttr right_attr;
                relation_attr_init(&right_attr, NULL, $3);

                Condition condition;
                condition_init(&condition, CONTEXT->comp[CONTEXT->condition_level], 0, NULL, NULL, 1, &right_attr, NULL, $1, NULL, 1, 0);

                selects_append_condition(&CONTEXT->ssql->sstr.selection, &condition, CONTEXT->condition_level);
                CONTEXT->conditions[CONTEXT->condition_length++] = condition;

	}
	| expression_cluster comOp ID DOT ID{
		RelAttr right_attr;
                relation_attr_init(&right_attr, $3, $5);

                Condition condition;
                condition_init(&condition, CONTEXT->comp[CONTEXT->condition_level], 0, NULL, NULL, 1, &right_attr, NULL, $1, NULL, 1, 0);

                selects_append_condition(&CONTEXT->ssql->sstr.selection, &condition, CONTEXT->condition_level);
                CONTEXT->conditions[CONTEXT->condition_length++] = condition;
	}
	| expression_cluster comOp value{
		Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

		Condition condition;
                condition_init(&condition, CONTEXT->comp[CONTEXT->condition_level], 0, NULL, NULL, 0, NULL, right_value, $1, NULL, 1, 0);

                selects_append_condition(&CONTEXT->ssql->sstr.selection, &condition, CONTEXT->condition_level);
                CONTEXT->conditions[CONTEXT->condition_length++] = condition;

	}
	| expression_cluster comOp expression_cluster
	{
		Condition condition;
		condition_init(&condition, CONTEXT->comp[CONTEXT->condition_level], 0, NULL, NULL, 0, NULL, NULL, $1, $3, 1, 1);

		selects_append_condition(&CONTEXT->ssql->sstr.selection, &condition, CONTEXT->condition_level);
                CONTEXT->conditions[CONTEXT->condition_length++] = condition;
	}
    ;

expression_cluster:
	| LBRACE expression RBRACE
	{
		$$ = $2;
	}
	| expression STAR expression
	{
		Expression *exp = malloc(sizeof(Expression));
		expression_init(exp,3,$1,$3);
		$$ = exp;
	}
	| expression DIV expression
	{
		Expression *exp = malloc(sizeof(Expression));
		expression_init(exp,4,$1,$3);
		$$ = exp;
	}
	  expression ADD expression
	{
		Expression *exp = malloc(sizeof(Expression));
		expression_init(exp,1,$1,$3);
		$$ = exp;
	}
	| expression MINUS expression
	{
		Expression *exp = malloc(sizeof(Expression));
		expression_init(exp,2,$1,$3);
		$$ = exp;
	}

	;
expression:


	expression_cluster
	{
		$$ = $1;
	}
	|primary_expression{
		$$ = $1;
	}
	;

primary_expression:
	NUMBER
	{
		Expression *exp = malloc(sizeof(Expression));
		Value value;
		value_init_integer(&value,$1);
		expression_init_val(exp, &value);
		$$ = exp;
	}
	| FLOAT
	{
		Expression *exp = malloc(sizeof(Expression));
		Value value;
                value_init_float(&value, $1);
		expression_init_val(exp,&value);
		$$ = exp;
	}
	| ID
	{
		RelAttr attr;
		relation_attr_init(&attr, NULL, $1);
		Expression *exp = malloc(sizeof(Expression));
		expression_init_attr(exp,&attr);
		$$ = exp;
    }
    | ID DOT ID{
		RelAttr attr;
		relation_attr_init(&attr, $3, $1);
		Expression *exp = malloc(sizeof(Expression));
		expression_init_attr(exp,&attr);
		$$ = exp;
  	}
//    	| ID DOT STAR{
//		RelAttr attr;
//		relation_attr_init(&attr, $1, '*');
//		Expression *exp = malloc(sizeof(Expression));
//		expression_init_attr(exp,attr);
//		$$ = exp;
//            }
	;

comOp:
      EQ { CONTEXT->comp[CONTEXT->condition_level] = EQUAL_TO; }
    | LT { CONTEXT->comp[CONTEXT->condition_level] = LESS_THAN; }
    | GT { CONTEXT->comp[CONTEXT->condition_level] = GREAT_THAN; }
    | LE { CONTEXT->comp[CONTEXT->condition_level] = LESS_EQUAL; }
    | GE { CONTEXT->comp[CONTEXT->condition_level] = GREAT_EQUAL; }
    | NE { CONTEXT->comp[CONTEXT->condition_level] = NOT_EQUAL; }
    | IS NOT {CONTEXT->comp[CONTEXT->condition_level] = OP_IS_NOT; }
    | IS {CONTEXT->comp[CONTEXT->condition_level] = OP_IS; }
	| IN { CONTEXT->comp[CONTEXT->condition_level] = OP_IN; }
	| NOT IN {CONTEXT->comp[CONTEXT->condition_level] = OP_NOT_IN; }
    ;

load_data:
		LOAD DATA INFILE SSS INTO TABLE ID SEMICOLON
		{
		  CONTEXT->ssql->flag = SCF_LOAD_DATA;
			load_data_init(&CONTEXT->ssql->sstr.load_data, $7, $4);
		}
		;
%%
//_____________________________________________________________________
extern void scan_string(const char *str, yyscan_t scanner);

int sql_parse(const char *s, Query *sqls){
	ParserContext context;
	memset(&context, 0, sizeof(context));

	yyscan_t scanner;
	yylex_init_extra(&context, &scanner);
	context.ssql = sqls;
	scan_string(s, scanner);
	int result = yyparse(scanner);
	yylex_destroy(scanner);
	return result;
}
