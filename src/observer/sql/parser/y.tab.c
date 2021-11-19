/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 2

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 2 "yacc_sql.y"


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
  CompOp comp;
	char id[MAX_NUM];
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


#line 139 "y.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif


/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    SEMICOLON = 258,               /* SEMICOLON  */
    CREATE = 259,                  /* CREATE  */
    DROP = 260,                    /* DROP  */
    COUNT = 261,                   /* COUNT  */
    MAX = 262,                     /* MAX  */
    MIN = 263,                     /* MIN  */
    AVG = 264,                     /* AVG  */
    INNER = 265,                   /* INNER  */
    JOIN = 266,                    /* JOIN  */
    TABLE = 267,                   /* TABLE  */
    TABLES = 268,                  /* TABLES  */
    INDEX = 269,                   /* INDEX  */
    SELECT = 270,                  /* SELECT  */
    DESC = 271,                    /* DESC  */
    SHOW = 272,                    /* SHOW  */
    SYNC = 273,                    /* SYNC  */
    INSERT = 274,                  /* INSERT  */
    DELETE = 275,                  /* DELETE  */
    UPDATE = 276,                  /* UPDATE  */
    LBRACE = 277,                  /* LBRACE  */
    RBRACE = 278,                  /* RBRACE  */
    COMMA = 279,                   /* COMMA  */
    TRX_BEGIN = 280,               /* TRX_BEGIN  */
    TRX_COMMIT = 281,              /* TRX_COMMIT  */
    TRX_ROLLBACK = 282,            /* TRX_ROLLBACK  */
    INT_T = 283,                   /* INT_T  */
    STRING_T = 284,                /* STRING_T  */
    FLOAT_T = 285,                 /* FLOAT_T  */
    DATE_T = 286,                  /* DATE_T  */
    TEXT_T = 287,                  /* TEXT_T  */
    UNIQUE = 288,                  /* UNIQUE  */
    HELP = 289,                    /* HELP  */
    EXIT = 290,                    /* EXIT  */
    DOT = 291,                     /* DOT  */
    INTO = 292,                    /* INTO  */
    VALUES = 293,                  /* VALUES  */
    FROM = 294,                    /* FROM  */
    WHERE = 295,                   /* WHERE  */
    AND = 296,                     /* AND  */
    SET = 297,                     /* SET  */
    ON = 298,                      /* ON  */
    LOAD = 299,                    /* LOAD  */
    DATA = 300,                    /* DATA  */
    INFILE = 301,                  /* INFILE  */
    IS = 302,                      /* IS  */
    NOT = 303,                     /* NOT  */
    NULLABLE = 304,                /* NULLABLE  */
    NULL_T = 305,                  /* NULL_T  */
    EQ = 306,                      /* EQ  */
    LT = 307,                      /* LT  */
    GT = 308,                      /* GT  */
    LE = 309,                      /* LE  */
    GE = 310,                      /* GE  */
    NE = 311,                      /* NE  */
    IN = 312,                      /* IN  */
    NUMBER = 313,                  /* NUMBER  */
    FLOAT = 314,                   /* FLOAT  */
    DATE = 315,                    /* DATE  */
    ID = 316,                      /* ID  */
    PATH = 317,                    /* PATH  */
    SSS = 318,                     /* SSS  */
    STAR = 319,                    /* STAR  */
    STRING_V = 320                 /* STRING_V  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define SEMICOLON 258
#define CREATE 259
#define DROP 260
#define COUNT 261
#define MAX 262
#define MIN 263
#define AVG 264
#define INNER 265
#define JOIN 266
#define TABLE 267
#define TABLES 268
#define INDEX 269
#define SELECT 270
#define DESC 271
#define SHOW 272
#define SYNC 273
#define INSERT 274
#define DELETE 275
#define UPDATE 276
#define LBRACE 277
#define RBRACE 278
#define COMMA 279
#define TRX_BEGIN 280
#define TRX_COMMIT 281
#define TRX_ROLLBACK 282
#define INT_T 283
#define STRING_T 284
#define FLOAT_T 285
#define DATE_T 286
#define TEXT_T 287
#define UNIQUE 288
#define HELP 289
#define EXIT 290
#define DOT 291
#define INTO 292
#define VALUES 293
#define FROM 294
#define WHERE 295
#define AND 296
#define SET 297
#define ON 298
#define LOAD 299
#define DATA 300
#define INFILE 301
#define IS 302
#define NOT 303
#define NULLABLE 304
#define NULL_T 305
#define EQ 306
#define LT 307
#define GT 308
#define LE 309
#define GE 310
#define NE 311
#define IN 312
#define NUMBER 313
#define FLOAT 314
#define DATE 315
#define ID 316
#define PATH 317
#define SSS 318
#define STAR 319
#define STRING_V 320

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 138 "yacc_sql.y"

  struct _Attr *attr;
  struct _Condition *condition1;
  struct _Value *value1;
  char *string;
  int number;
  float floats;

#line 328 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif




int yyparse (void *scanner);



/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_SEMICOLON = 3,                  /* SEMICOLON  */
  YYSYMBOL_CREATE = 4,                     /* CREATE  */
  YYSYMBOL_DROP = 5,                       /* DROP  */
  YYSYMBOL_COUNT = 6,                      /* COUNT  */
  YYSYMBOL_MAX = 7,                        /* MAX  */
  YYSYMBOL_MIN = 8,                        /* MIN  */
  YYSYMBOL_AVG = 9,                        /* AVG  */
  YYSYMBOL_INNER = 10,                     /* INNER  */
  YYSYMBOL_JOIN = 11,                      /* JOIN  */
  YYSYMBOL_TABLE = 12,                     /* TABLE  */
  YYSYMBOL_TABLES = 13,                    /* TABLES  */
  YYSYMBOL_INDEX = 14,                     /* INDEX  */
  YYSYMBOL_SELECT = 15,                    /* SELECT  */
  YYSYMBOL_DESC = 16,                      /* DESC  */
  YYSYMBOL_SHOW = 17,                      /* SHOW  */
  YYSYMBOL_SYNC = 18,                      /* SYNC  */
  YYSYMBOL_INSERT = 19,                    /* INSERT  */
  YYSYMBOL_DELETE = 20,                    /* DELETE  */
  YYSYMBOL_UPDATE = 21,                    /* UPDATE  */
  YYSYMBOL_LBRACE = 22,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 23,                    /* RBRACE  */
  YYSYMBOL_COMMA = 24,                     /* COMMA  */
  YYSYMBOL_TRX_BEGIN = 25,                 /* TRX_BEGIN  */
  YYSYMBOL_TRX_COMMIT = 26,                /* TRX_COMMIT  */
  YYSYMBOL_TRX_ROLLBACK = 27,              /* TRX_ROLLBACK  */
  YYSYMBOL_INT_T = 28,                     /* INT_T  */
  YYSYMBOL_STRING_T = 29,                  /* STRING_T  */
  YYSYMBOL_FLOAT_T = 30,                   /* FLOAT_T  */
  YYSYMBOL_DATE_T = 31,                    /* DATE_T  */
  YYSYMBOL_TEXT_T = 32,                    /* TEXT_T  */
  YYSYMBOL_UNIQUE = 33,                    /* UNIQUE  */
  YYSYMBOL_HELP = 34,                      /* HELP  */
  YYSYMBOL_EXIT = 35,                      /* EXIT  */
  YYSYMBOL_DOT = 36,                       /* DOT  */
  YYSYMBOL_INTO = 37,                      /* INTO  */
  YYSYMBOL_VALUES = 38,                    /* VALUES  */
  YYSYMBOL_FROM = 39,                      /* FROM  */
  YYSYMBOL_WHERE = 40,                     /* WHERE  */
  YYSYMBOL_AND = 41,                       /* AND  */
  YYSYMBOL_SET = 42,                       /* SET  */
  YYSYMBOL_ON = 43,                        /* ON  */
  YYSYMBOL_LOAD = 44,                      /* LOAD  */
  YYSYMBOL_DATA = 45,                      /* DATA  */
  YYSYMBOL_INFILE = 46,                    /* INFILE  */
  YYSYMBOL_IS = 47,                        /* IS  */
  YYSYMBOL_NOT = 48,                       /* NOT  */
  YYSYMBOL_NULLABLE = 49,                  /* NULLABLE  */
  YYSYMBOL_NULL_T = 50,                    /* NULL_T  */
  YYSYMBOL_EQ = 51,                        /* EQ  */
  YYSYMBOL_LT = 52,                        /* LT  */
  YYSYMBOL_GT = 53,                        /* GT  */
  YYSYMBOL_LE = 54,                        /* LE  */
  YYSYMBOL_GE = 55,                        /* GE  */
  YYSYMBOL_NE = 56,                        /* NE  */
  YYSYMBOL_IN = 57,                        /* IN  */
  YYSYMBOL_NUMBER = 58,                    /* NUMBER  */
  YYSYMBOL_FLOAT = 59,                     /* FLOAT  */
  YYSYMBOL_DATE = 60,                      /* DATE  */
  YYSYMBOL_ID = 61,                        /* ID  */
  YYSYMBOL_PATH = 62,                      /* PATH  */
  YYSYMBOL_SSS = 63,                       /* SSS  */
  YYSYMBOL_STAR = 64,                      /* STAR  */
  YYSYMBOL_STRING_V = 65,                  /* STRING_V  */
  YYSYMBOL_YYACCEPT = 66,                  /* $accept  */
  YYSYMBOL_commands = 67,                  /* commands  */
  YYSYMBOL_command = 68,                   /* command  */
  YYSYMBOL_exit = 69,                      /* exit  */
  YYSYMBOL_help = 70,                      /* help  */
  YYSYMBOL_sync = 71,                      /* sync  */
  YYSYMBOL_begin = 72,                     /* begin  */
  YYSYMBOL_commit = 73,                    /* commit  */
  YYSYMBOL_rollback = 74,                  /* rollback  */
  YYSYMBOL_drop_table = 75,                /* drop_table  */
  YYSYMBOL_show_tables = 76,               /* show_tables  */
  YYSYMBOL_desc_table = 77,                /* desc_table  */
  YYSYMBOL_create_index = 78,              /* create_index  */
  YYSYMBOL_field_list = 79,                /* field_list  */
  YYSYMBOL_field = 80,                     /* field  */
  YYSYMBOL_drop_index = 81,                /* drop_index  */
  YYSYMBOL_create_table = 82,              /* create_table  */
  YYSYMBOL_attr_def_list = 83,             /* attr_def_list  */
  YYSYMBOL_attr_def = 84,                  /* attr_def  */
  YYSYMBOL_null_value = 85,                /* null_value  */
  YYSYMBOL_number = 86,                    /* number  */
  YYSYMBOL_type = 87,                      /* type  */
  YYSYMBOL_ID_get = 88,                    /* ID_get  */
  YYSYMBOL_insert = 89,                    /* insert  */
  YYSYMBOL_row_list = 90,                  /* row_list  */
  YYSYMBOL_row = 91,                       /* row  */
  YYSYMBOL_value_list = 92,                /* value_list  */
  YYSYMBOL_value = 93,                     /* value  */
  YYSYMBOL_delete = 94,                    /* delete  */
  YYSYMBOL_update = 95,                    /* update  */
  YYSYMBOL_select = 96,                    /* select  */
  YYSYMBOL_subselect = 97,                 /* subselect  */
  YYSYMBOL_pushdown = 98,                  /* pushdown  */
  YYSYMBOL_pushup = 99,                    /* pushup  */
  YYSYMBOL_select_attr = 100,              /* select_attr  */
  YYSYMBOL_attr_list = 101,                /* attr_list  */
  YYSYMBOL_select_from = 102,              /* select_from  */
  YYSYMBOL_rel_list = 103,                 /* rel_list  */
  YYSYMBOL_select_join = 104,              /* select_join  */
  YYSYMBOL_join_list = 105,                /* join_list  */
  YYSYMBOL_where = 106,                    /* where  */
  YYSYMBOL_condition_list = 107,           /* condition_list  */
  YYSYMBOL_condition = 108,                /* condition  */
  YYSYMBOL_comOp = 109,                    /* comOp  */
  YYSYMBOL_load_data = 110                 /* load_data  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   285

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  66
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  45
/* YYNRULES -- Number of rules.  */
#define YYNRULES  124
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  293

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   320


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   164,   164,   166,   170,   171,   172,   173,   174,   175,
     176,   177,   178,   179,   180,   181,   182,   183,   184,   185,
     186,   190,   195,   200,   206,   212,   218,   224,   230,   236,
     244,   249,   255,   257,   262,   268,   275,   284,   286,   290,
     302,   315,   316,   319,   324,   327,   328,   329,   330,   331,
     334,   343,   360,   361,   366,   371,   373,   378,   381,   384,
     387,   391,   398,   408,   418,   434,   445,   451,   456,   461,
     468,   474,   481,   487,   493,   499,   505,   511,   517,   523,
     529,   537,   539,   546,   553,   558,   563,   568,   573,   578,
     583,   588,   593,   599,   601,   607,   609,   613,   615,   621,
     623,   627,   629,   633,   635,   640,   662,   683,   704,   727,
     749,   771,   791,   804,   819,   820,   821,   822,   823,   824,
     825,   826,   827,   828,   832
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "SEMICOLON", "CREATE",
  "DROP", "COUNT", "MAX", "MIN", "AVG", "INNER", "JOIN", "TABLE", "TABLES",
  "INDEX", "SELECT", "DESC", "SHOW", "SYNC", "INSERT", "DELETE", "UPDATE",
  "LBRACE", "RBRACE", "COMMA", "TRX_BEGIN", "TRX_COMMIT", "TRX_ROLLBACK",
  "INT_T", "STRING_T", "FLOAT_T", "DATE_T", "TEXT_T", "UNIQUE", "HELP",
  "EXIT", "DOT", "INTO", "VALUES", "FROM", "WHERE", "AND", "SET", "ON",
  "LOAD", "DATA", "INFILE", "IS", "NOT", "NULLABLE", "NULL_T", "EQ", "LT",
  "GT", "LE", "GE", "NE", "IN", "NUMBER", "FLOAT", "DATE", "ID", "PATH",
  "SSS", "STAR", "STRING_V", "$accept", "commands", "command", "exit",
  "help", "sync", "begin", "commit", "rollback", "drop_table",
  "show_tables", "desc_table", "create_index", "field_list", "field",
  "drop_index", "create_table", "attr_def_list", "attr_def", "null_value",
  "number", "type", "ID_get", "insert", "row_list", "row", "value_list",
  "value", "delete", "update", "select", "subselect", "pushdown", "pushup",
  "select_attr", "attr_list", "select_from", "rel_list", "select_join",
  "join_list", "where", "condition_list", "condition", "comOp",
  "load_data", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-222)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -222,   117,  -222,    15,    91,     1,   -33,    20,    35,    46,
      61,    -5,   101,   116,   126,   128,   137,    75,  -222,  -222,
    -222,  -222,  -222,  -222,  -222,  -222,  -222,  -222,  -222,  -222,
    -222,  -222,  -222,  -222,  -222,  -222,    45,    80,   143,   109,
     110,   140,   150,   151,   152,    30,  -222,   141,   176,   178,
    -222,   121,   122,   142,  -222,  -222,  -222,  -222,  -222,   139,
     164,   144,   127,   186,   187,   -29,   130,   131,   132,    17,
     133,  -222,   134,  -222,  -222,   158,   157,   138,   135,   145,
     146,   159,  -222,  -222,    -2,   177,    13,    16,    19,   179,
     181,   182,   183,   103,   184,     6,   157,   157,   188,    65,
     206,   160,   175,  -222,   189,   118,   192,   154,   184,   155,
     184,   184,   156,   184,   161,   184,   162,    37,   163,   165,
     166,   167,  -222,  -222,   207,   168,  -222,  -222,   216,   217,
     -13,   197,  -222,  -222,  -222,  -222,    39,  -222,   112,   190,
    -222,   -13,   213,   145,   209,  -222,  -222,  -222,  -222,  -222,
      -8,   169,   211,  -222,   212,  -222,  -222,   214,  -222,   215,
    -222,   218,    40,   219,    41,    66,    76,   184,   173,   220,
    -222,  -222,   221,   188,   233,   185,   191,   193,  -222,  -222,
    -222,  -222,  -222,  -222,  -222,     9,    95,    65,  -222,   157,
     194,   189,   237,   195,   198,  -222,  -222,  -222,   223,   169,
     184,   184,   184,   184,   184,   196,   184,   184,   199,   184,
     200,   184,   201,  -222,   208,  -222,   -13,   226,   197,  -222,
     112,  -222,  -222,  -222,  -222,  -222,  -222,   228,   222,  -222,
     190,   249,   251,  -222,  -222,  -222,   236,  -222,   169,   240,
     223,  -222,  -222,  -222,  -222,  -222,   241,  -222,  -222,   242,
    -222,   243,  -222,   244,    65,   221,  -222,  -222,    21,   245,
     210,  -222,  -222,  -222,    12,   223,   253,   246,   184,   184,
     184,   184,   190,  -222,   234,  -222,  -222,  -222,  -222,  -222,
    -222,  -222,  -222,   269,  -222,  -222,  -222,  -222,   263,   224,
    -222,  -222,  -222
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,     0,     1,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     3,    20,
      19,    14,    15,    16,    17,     9,    10,    11,    12,    13,
       8,     5,     7,     6,     4,    18,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    81,    69,     0,     0,     0,
      23,     0,     0,     0,    24,    25,    26,    22,    21,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    70,    93,    29,    28,     0,   101,     0,     0,     0,
       0,     0,    27,    35,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    81,    81,    95,   101,   101,     0,     0,
       0,     0,     0,    50,    37,     0,     0,     0,    81,     0,
      81,    81,     0,    81,     0,    81,     0,     0,     0,     0,
       0,     0,    82,    71,     0,     0,    94,    98,     0,     0,
       0,    52,    57,    58,    59,    60,     0,    61,     0,   103,
      62,     0,     0,     0,     0,    45,    46,    47,    48,    49,
      41,     0,     0,    73,     0,    72,    75,     0,    77,     0,
      79,     0,     0,     0,     0,     0,     0,    81,     0,    95,
      64,    65,    55,     0,     0,     0,   121,     0,   114,   115,
     116,   117,   118,   119,   122,     0,     0,     0,   102,   101,
       0,    37,     0,     0,     0,    42,    40,    34,    32,     0,
      81,    81,    81,    81,    81,     0,    81,    81,     0,    81,
       0,    81,     0,    83,     0,    96,     0,     0,    52,    51,
       0,   120,   123,    67,   107,   105,   112,     0,   108,   106,
     103,     0,     0,    38,    36,    44,     0,    43,     0,     0,
      32,    74,    76,    78,    80,    85,     0,    84,    87,     0,
      89,     0,    91,     0,     0,    55,    54,    53,     0,     0,
       0,   104,    63,   124,    41,    32,     0,     0,    81,    81,
      81,    81,   103,    56,     0,   109,   113,    68,    66,   110,
      39,    33,    30,     0,    86,    88,    90,    92,    99,     0,
      31,   100,   111
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -222,  -222,  -222,  -222,  -222,  -222,  -222,  -222,  -222,  -222,
    -222,  -222,  -222,  -221,  -187,  -222,  -222,    83,   136,    11,
    -222,  -222,  -222,  -222,    58,   104,    23,  -128,  -222,  -222,
      53,    24,  -222,  -222,  -222,   -93,  -222,   114,  -222,    -7,
     -92,  -219,  -181,  -135,  -222
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     1,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,   239,   198,    29,    30,   144,   104,   196,
     236,   150,   105,    31,   174,   131,   217,   138,    32,    33,
      34,   226,   227,   278,    47,    71,    96,   126,    97,   127,
     100,   188,   139,   185,    35
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     122,   123,   172,   186,   128,   129,   230,    41,    42,    43,
      44,   261,   240,   189,   193,   153,   124,   155,   156,   267,
     158,   108,   160,    89,    90,    91,    92,    36,    48,    37,
     125,   223,    84,    49,   109,    85,   111,   132,    50,   113,
     194,   195,   115,   223,   281,   133,   134,   135,    38,   112,
     137,   265,   114,   288,    69,   116,    53,   225,   229,   132,
     194,   195,    45,   204,   207,    46,    70,   133,   134,   135,
     224,   132,   137,   272,   213,   175,   205,   208,    93,   133,
     134,   135,   274,    51,   137,   258,   176,   177,   255,   209,
     178,   179,   180,   181,   182,   183,   184,   231,   162,   211,
      52,   163,   210,    39,    54,    40,    60,   241,   242,   243,
     244,   245,   212,   247,   248,   132,   250,     2,   252,    55,
      59,     3,     4,   133,   134,   135,   136,    69,   137,    56,
     275,    57,     5,     6,     7,     8,     9,    10,    11,   121,
      58,    61,    12,    13,    14,   132,   145,   146,   147,   148,
     149,    15,    16,   133,   134,   135,   228,    62,   137,   176,
     177,    17,    65,   178,   179,   180,   181,   182,   183,   184,
      63,    64,    66,    67,    68,   284,   285,   286,   287,    73,
      72,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    86,    87,    88,    94,    95,    98,    99,   102,   101,
     110,   117,   107,   118,   119,   120,   103,   106,    69,   140,
     130,   141,   142,   143,   151,   152,   154,   157,   168,   170,
     171,   173,   159,   161,   164,   190,   165,   166,   167,   169,
     197,   187,   192,   199,   214,   200,   219,   201,   202,   221,
     234,   203,   206,     5,   125,   216,   220,   238,   237,   256,
     222,   254,   262,   235,   263,   232,   282,   246,   260,   264,
     249,   251,   253,   266,   268,   269,   270,   271,   277,   283,
     289,   279,   290,   124,   233,   280,   257,   218,   273,   191,
     259,   291,   276,   215,     0,   292
};

static const yytype_int16 yycheck[] =
{
      93,    94,   130,   138,    96,    97,   187,     6,     7,     8,
       9,   230,   199,   141,    22,   108,    10,   110,   111,   240,
     113,    23,   115,     6,     7,     8,     9,    12,    61,    14,
      24,    22,    61,    13,    36,    64,    23,    50,     3,    23,
      48,    49,    23,    22,   265,    58,    59,    60,    33,    36,
      63,   238,    36,   272,    24,    36,    61,   185,   186,    50,
      48,    49,    61,    23,    23,    64,    36,    58,    59,    60,
      61,    50,    63,   254,   167,    36,    36,    36,    61,    58,
      59,    60,    61,    37,    63,   220,    47,    48,   216,    23,
      51,    52,    53,    54,    55,    56,    57,   189,    61,    23,
      39,    64,    36,    12,     3,    14,    61,   200,   201,   202,
     203,   204,    36,   206,   207,    50,   209,     0,   211,     3,
      45,     4,     5,    58,    59,    60,    61,    24,    63,     3,
     258,     3,    15,    16,    17,    18,    19,    20,    21,    36,
       3,    61,    25,    26,    27,    50,    28,    29,    30,    31,
      32,    34,    35,    58,    59,    60,    61,    14,    63,    47,
      48,    44,    22,    51,    52,    53,    54,    55,    56,    57,
      61,    61,    22,    22,    22,   268,   269,   270,   271,     3,
      39,     3,    61,    61,    42,    46,    22,    43,    61,     3,
       3,    61,    61,    61,    61,    61,    38,    40,    63,    61,
      23,    22,    43,    22,    22,    22,    61,    61,    24,     3,
      22,    51,    37,    24,    22,    61,    61,    61,    11,     3,
       3,    24,    61,    61,    61,    12,    61,    61,    61,    61,
      61,    41,    23,    22,    61,    23,     3,    23,    23,    48,
       3,    23,    23,    15,    24,    24,    61,    24,    50,    23,
      57,    43,     3,    58,     3,    61,     3,    61,    36,    23,
      61,    61,    61,    23,    23,    23,    23,    23,    23,    23,
      36,    61,     3,    10,   191,   264,   218,   173,   255,   143,
     227,   288,   258,   169,    -1,    61
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    67,     0,     4,     5,    15,    16,    17,    18,    19,
      20,    21,    25,    26,    27,    34,    35,    44,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    81,
      82,    89,    94,    95,    96,   110,    12,    14,    33,    12,
      14,     6,     7,     8,     9,    61,    64,   100,    61,    13,
       3,    37,    39,    61,     3,     3,     3,     3,     3,    45,
      61,    61,    14,    61,    61,    22,    22,    22,    22,    24,
      36,   101,    39,     3,     3,    61,    61,    42,    46,    22,
      43,    61,     3,     3,    61,    64,    61,    61,    61,     6,
       7,     8,     9,    61,    61,    61,   102,   104,    38,    40,
     106,    61,    63,    61,    84,    88,    61,    43,    23,    36,
      23,    23,    36,    23,    36,    23,    36,    22,    22,    22,
      22,    36,   101,   101,    10,    24,   103,   105,   106,   106,
      22,    91,    50,    58,    59,    60,    61,    63,    93,   108,
       3,    51,    37,    24,    83,    28,    29,    30,    31,    32,
      87,    22,    61,   101,    61,   101,   101,    61,   101,    61,
     101,    61,    61,    64,    61,    61,    61,    61,    11,    61,
       3,     3,    93,    24,    90,    36,    47,    48,    51,    52,
      53,    54,    55,    56,    57,   109,   109,    41,   107,    93,
      12,    84,    23,    22,    48,    49,    85,    61,    80,    22,
      23,    23,    23,    23,    23,    36,    23,    23,    36,    23,
      36,    23,    36,   101,    61,   103,    24,    92,    91,     3,
      61,    48,    57,    22,    61,    93,    97,    98,    61,    93,
     108,   106,    61,    83,     3,    58,    86,    50,    24,    79,
      80,   101,   101,   101,   101,   101,    61,   101,   101,    61,
     101,    61,   101,    61,    43,    93,    23,    90,   109,    96,
      36,   107,     3,     3,    23,    80,    23,    79,    23,    23,
      23,    23,   108,    92,    61,    93,    97,    23,    99,    61,
      85,    79,     3,    23,   101,   101,   101,   101,   107,    36,
       3,   105,    61
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    66,    67,    67,    68,    68,    68,    68,    68,    68,
      68,    68,    68,    68,    68,    68,    68,    68,    68,    68,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    78,    79,    79,    80,    81,    82,    83,    83,    84,
      84,    85,    85,    85,    86,    87,    87,    87,    87,    87,
      88,    89,    90,    90,    91,    92,    92,    93,    93,    93,
      93,    93,    94,    95,    96,    96,    97,    98,    99,   100,
     100,   100,   100,   100,   100,   100,   100,   100,   100,   100,
     100,   101,   101,   101,   101,   101,   101,   101,   101,   101,
     101,   101,   101,   102,   102,   103,   103,   104,   104,   105,
     105,   106,   106,   107,   107,   108,   108,   108,   108,   108,
     108,   108,   108,   108,   109,   109,   109,   109,   109,   109,
     109,   109,   109,   109,   110
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     2,     2,     2,     2,     2,     4,     3,     3,
      10,    11,     0,     3,     1,     4,     8,     0,     3,     6,
       3,     0,     1,     2,     1,     1,     1,     1,     1,     1,
       1,     7,     0,     3,     4,     0,     3,     1,     1,     1,
       1,     1,     5,     8,     6,     6,     3,     1,     1,     1,
       2,     4,     5,     5,     7,     5,     7,     5,     7,     5,
       7,     0,     3,     5,     6,     6,     8,     6,     8,     6,
       8,     6,     8,     0,     2,     0,     3,     0,     2,     0,
       7,     0,     3,     0,     3,     3,     3,     3,     3,     5,
       5,     7,     3,     5,     1,     1,     1,     1,     1,     1,
       2,     1,     1,     2,     8
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (scanner, YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, scanner); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, void *scanner)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (scanner);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, void *scanner)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep, scanner);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule, void *scanner)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)], scanner);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule, scanner); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, void *scanner)
{
  YY_USE (yyvaluep);
  YY_USE (scanner);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}






/*----------.
| yyparse.  |
`----------*/

int
yyparse (void *scanner)
{
/* Lookahead token kind.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

    /* Number of syntax errors so far.  */
    int yynerrs = 0;

    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex (&yylval, scanner);
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 21: /* exit: EXIT SEMICOLON  */
#line 190 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_EXIT;//"exit";
    }
#line 1621 "y.tab.c"
    break;

  case 22: /* help: HELP SEMICOLON  */
#line 195 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_HELP;//"help";
    }
#line 1629 "y.tab.c"
    break;

  case 23: /* sync: SYNC SEMICOLON  */
#line 200 "yacc_sql.y"
                   {
      CONTEXT->ssql->flag = SCF_SYNC;
    }
#line 1637 "y.tab.c"
    break;

  case 24: /* begin: TRX_BEGIN SEMICOLON  */
#line 206 "yacc_sql.y"
                        {
      CONTEXT->ssql->flag = SCF_BEGIN;
    }
#line 1645 "y.tab.c"
    break;

  case 25: /* commit: TRX_COMMIT SEMICOLON  */
#line 212 "yacc_sql.y"
                         {
      CONTEXT->ssql->flag = SCF_COMMIT;
    }
#line 1653 "y.tab.c"
    break;

  case 26: /* rollback: TRX_ROLLBACK SEMICOLON  */
#line 218 "yacc_sql.y"
                           {
      CONTEXT->ssql->flag = SCF_ROLLBACK;
    }
#line 1661 "y.tab.c"
    break;

  case 27: /* drop_table: DROP TABLE ID SEMICOLON  */
#line 224 "yacc_sql.y"
                            {
        CONTEXT->ssql->flag = SCF_DROP_TABLE;//"drop_table";
        drop_table_init(&CONTEXT->ssql->sstr.drop_table, (yyvsp[-1].string));
    }
#line 1670 "y.tab.c"
    break;

  case 28: /* show_tables: SHOW TABLES SEMICOLON  */
#line 230 "yacc_sql.y"
                          {
      CONTEXT->ssql->flag = SCF_SHOW_TABLES;
    }
#line 1678 "y.tab.c"
    break;

  case 29: /* desc_table: DESC ID SEMICOLON  */
#line 236 "yacc_sql.y"
                      {
      CONTEXT->ssql->flag = SCF_DESC_TABLE;
      desc_table_init(&CONTEXT->ssql->sstr.desc_table, (yyvsp[-1].string));
    }
#line 1687 "y.tab.c"
    break;

  case 30: /* create_index: CREATE INDEX ID ON ID LBRACE field field_list RBRACE SEMICOLON  */
#line 245 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-7].string), (yyvsp[-5].string), CONTEXT->field_names, CONTEXT->index_field_num, 0);
		}
#line 1696 "y.tab.c"
    break;

  case 31: /* create_index: CREATE UNIQUE INDEX ID ON ID LBRACE field field_list RBRACE SEMICOLON  */
#line 250 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-7].string), (yyvsp[-5].string), CONTEXT->field_names, CONTEXT->index_field_num, 1);
                }
#line 1705 "y.tab.c"
    break;

  case 33: /* field_list: COMMA field field_list  */
#line 257 "yacc_sql.y"
                               {

    	}
#line 1713 "y.tab.c"
    break;

  case 34: /* field: ID  */
#line 262 "yacc_sql.y"
          {
    		CONTEXT->field_names[CONTEXT->index_field_num++]=(yyvsp[0].string);
    	}
#line 1721 "y.tab.c"
    break;

  case 35: /* drop_index: DROP INDEX ID SEMICOLON  */
#line 269 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_DROP_INDEX;//"drop_index";
			drop_index_init(&CONTEXT->ssql->sstr.drop_index, (yyvsp[-1].string));
		}
#line 1730 "y.tab.c"
    break;

  case 36: /* create_table: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE SEMICOLON  */
#line 276 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_CREATE_TABLE;//"create_table";
			// CONTEXT->ssql->sstr.create_table.attribute_count = CONTEXT->value_length;
			create_table_init_name(&CONTEXT->ssql->sstr.create_table, (yyvsp[-5].string));
			//临时变量清零
			CONTEXT->value_length = 0;
		}
#line 1742 "y.tab.c"
    break;

  case 38: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 286 "yacc_sql.y"
                                   {    }
#line 1748 "y.tab.c"
    break;

  case 39: /* attr_def: ID_get type LBRACE number RBRACE null_value  */
#line 291 "yacc_sql.y"
                {
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, (yyvsp[-4].number), (yyvsp[-2].number), CONTEXT->nullable);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name =(char*)malloc(sizeof(char));
			// strcpy(CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name, CONTEXT->id);
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].type = $2;
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].length = $4;
			CONTEXT->value_length++;
			CONTEXT->nullable = false;
		}
#line 1764 "y.tab.c"
    break;

  case 40: /* attr_def: ID_get type null_value  */
#line 303 "yacc_sql.y"
                {
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, (yyvsp[-1].number), 4, CONTEXT->nullable);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name=(char*)malloc(sizeof(char));
			// strcpy(CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name, CONTEXT->id);
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].type=$2;
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].length=4; // default attribute length
			CONTEXT->value_length++;
			CONTEXT->nullable = false;
		}
#line 1780 "y.tab.c"
    break;

  case 42: /* null_value: NULLABLE  */
#line 316 "yacc_sql.y"
                 {
		CONTEXT->nullable = true;
	}
#line 1788 "y.tab.c"
    break;

  case 43: /* null_value: NOT NULL_T  */
#line 319 "yacc_sql.y"
                   {

	}
#line 1796 "y.tab.c"
    break;

  case 44: /* number: NUMBER  */
#line 324 "yacc_sql.y"
                       {(yyval.number) = (yyvsp[0].number);}
#line 1802 "y.tab.c"
    break;

  case 45: /* type: INT_T  */
#line 327 "yacc_sql.y"
              { (yyval.number)=INTS; }
#line 1808 "y.tab.c"
    break;

  case 46: /* type: STRING_T  */
#line 328 "yacc_sql.y"
                  { (yyval.number)=CHARS; }
#line 1814 "y.tab.c"
    break;

  case 47: /* type: FLOAT_T  */
#line 329 "yacc_sql.y"
                 { (yyval.number)=FLOATS; }
#line 1820 "y.tab.c"
    break;

  case 48: /* type: DATE_T  */
#line 330 "yacc_sql.y"
                { (yyval.number)=DATES; }
#line 1826 "y.tab.c"
    break;

  case 49: /* type: TEXT_T  */
#line 331 "yacc_sql.y"
                { (yyval.number)=TEXTS; }
#line 1832 "y.tab.c"
    break;

  case 50: /* ID_get: ID  */
#line 335 "yacc_sql.y"
        {
		char *temp=(yyvsp[0].string);
		snprintf(CONTEXT->id, sizeof(CONTEXT->id), "%s", temp);
	}
#line 1841 "y.tab.c"
    break;

  case 51: /* insert: INSERT INTO ID VALUES row row_list SEMICOLON  */
#line 344 "yacc_sql.y"
                {
			// CONTEXT->values[CONTEXT->value_length++] = *$6;

			CONTEXT->ssql->flag=SCF_INSERT;//"insert";
			// CONTEXT->ssql->sstr.insertion.relation_name = $3;
			// CONTEXT->ssql->sstr.insertion.value_num = CONTEXT->value_length;
			// for(i = 0; i < CONTEXT->value_length; i++){
			// 	CONTEXT->ssql->sstr.insertion.values[i] = CONTEXT->values[i];
      // }
			inserts_init(&CONTEXT->ssql->sstr.insertion, (yyvsp[-4].string), CONTEXT->values, CONTEXT->value_length, CONTEXT->row_end, CONTEXT->row_num);

      //临时变量清零
      CONTEXT->value_length=0;
      CONTEXT->row_num=0;
    }
#line 1861 "y.tab.c"
    break;

  case 53: /* row_list: COMMA row row_list  */
#line 361 "yacc_sql.y"
                                {
	}
#line 1868 "y.tab.c"
    break;

  case 54: /* row: LBRACE value value_list RBRACE  */
#line 366 "yacc_sql.y"
                                        {
		CONTEXT->row_end[CONTEXT->row_num++]=CONTEXT->value_length;
	}
#line 1876 "y.tab.c"
    break;

  case 56: /* value_list: COMMA value value_list  */
#line 373 "yacc_sql.y"
                              {
  		// CONTEXT->values[CONTEXT->value_length++] = *$2;
	  }
#line 1884 "y.tab.c"
    break;

  case 57: /* value: NULL_T  */
#line 378 "yacc_sql.y"
          {
		value_init_null(&CONTEXT->values[CONTEXT->value_length++]);
	}
#line 1892 "y.tab.c"
    break;

  case 58: /* value: NUMBER  */
#line 381 "yacc_sql.y"
           {
  		value_init_integer(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].number));
		}
#line 1900 "y.tab.c"
    break;

  case 59: /* value: FLOAT  */
#line 384 "yacc_sql.y"
          {
  		value_init_float(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].floats));
		}
#line 1908 "y.tab.c"
    break;

  case 60: /* value: DATE  */
#line 387 "yacc_sql.y"
          {
    			(yyvsp[0].string) = substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      		value_init_date(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].string));
    		}
#line 1917 "y.tab.c"
    break;

  case 61: /* value: SSS  */
#line 391 "yacc_sql.y"
         {
			(yyvsp[0].string) = substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
  		value_init_string(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].string));
		}
#line 1926 "y.tab.c"
    break;

  case 62: /* delete: DELETE FROM ID where SEMICOLON  */
#line 399 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_DELETE;//"delete";
			deletes_init_relation(&CONTEXT->ssql->sstr.deletion, (yyvsp[-2].string));
			deletes_set_conditions(&CONTEXT->ssql->sstr.deletion,
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;
    }
#line 1938 "y.tab.c"
    break;

  case 63: /* update: UPDATE ID SET ID EQ value where SEMICOLON  */
#line 409 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_UPDATE;//"update";
			Value *value = &CONTEXT->values[0];
			updates_init(&CONTEXT->ssql->sstr.update, (yyvsp[-6].string), (yyvsp[-4].string), value,
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;
		}
#line 1950 "y.tab.c"
    break;

  case 64: /* select: SELECT select_attr FROM select_from where SEMICOLON  */
#line 419 "yacc_sql.y"
                {
			// CONTEXT->ssql->sstr.selection.relations[CONTEXT->from_length++]=$4;


			//CONTEXT->select_length++;

			CONTEXT->ssql->flag=SCF_SELECT;//"select";
			// CONTEXT->ssql->sstr.selection.attr_num = CONTEXT->select_length;

			update_select_num(&CONTEXT->ssql->sstr.selection);

			//临时变量清零
			CONTEXT->condition_length=0;
			CONTEXT->value_length = 0;
	}
#line 1970 "y.tab.c"
    break;

  case 65: /* select: SELECT select_attr FROM select_join where SEMICOLON  */
#line 435 "yacc_sql.y"
        {

		CONTEXT->ssql->flag = SCF_SELECT;

		//临时变量清0
		CONTEXT->condition_length = 0;
		CONTEXT->value_length = 0;
	}
#line 1983 "y.tab.c"
    break;

  case 66: /* subselect: pushdown select pushup  */
#line 446 "yacc_sql.y"
        {
		
	}
#line 1991 "y.tab.c"
    break;

  case 67: /* pushdown: LBRACE  */
#line 451 "yacc_sql.y"
               {
		CONTEXT->condition_level++;
	}
#line 1999 "y.tab.c"
    break;

  case 68: /* pushup: RBRACE  */
#line 456 "yacc_sql.y"
               {
		CONTEXT->condition_level--;
	}
#line 2007 "y.tab.c"
    break;

  case 69: /* select_attr: STAR  */
#line 461 "yacc_sql.y"
         {
			debug_subselect();
			RelAttr attr;
			relation_attr_init(&attr, NULL, "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr, CONTEXT->attr_level);
			CONTEXT->attr_level++;
		}
#line 2019 "y.tab.c"
    break;

  case 70: /* select_attr: ID attr_list  */
#line 468 "yacc_sql.y"
                   {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr, CONTEXT->attr_level);
			CONTEXT->attr_level++;
		}
#line 2030 "y.tab.c"
    break;

  case 71: /* select_attr: ID DOT ID attr_list  */
#line 474 "yacc_sql.y"
                              {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr, CONTEXT->attr_level);
			CONTEXT->attr_level++;
		}
#line 2041 "y.tab.c"
    break;

  case 72: /* select_attr: COUNT LBRACE STAR RBRACE attr_list  */
#line 481 "yacc_sql.y"
                                             {
			RelAttr attr;
			relation_attr_with_agg_init(&attr, "COUNT", NULL, "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr, CONTEXT->attr_level);
			CONTEXT->attr_level++;
		}
#line 2052 "y.tab.c"
    break;

  case 73: /* select_attr: COUNT LBRACE ID RBRACE attr_list  */
#line 487 "yacc_sql.y"
                                           {
			RelAttr attr;
			relation_attr_with_agg_init(&attr, "COUNT", NULL, (yyvsp[-2].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr, CONTEXT->attr_level);
			CONTEXT->attr_level++;
		}
#line 2063 "y.tab.c"
    break;

  case 74: /* select_attr: COUNT LBRACE ID DOT ID RBRACE attr_list  */
#line 493 "yacc_sql.y"
                                                  {
			RelAttr attr;
			relation_attr_with_agg_init(&attr, "COUNT", (yyvsp[-4].string), (yyvsp[-2].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr, CONTEXT->attr_level);
			CONTEXT->attr_level++;
		}
#line 2074 "y.tab.c"
    break;

  case 75: /* select_attr: MAX LBRACE ID RBRACE attr_list  */
#line 499 "yacc_sql.y"
                                         {
			RelAttr attr;
			relation_attr_with_agg_init(&attr, "MAX", NULL, (yyvsp[-2].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr, CONTEXT->attr_level);
			CONTEXT->attr_level++;
		}
#line 2085 "y.tab.c"
    break;

  case 76: /* select_attr: MAX LBRACE ID DOT ID RBRACE attr_list  */
#line 505 "yacc_sql.y"
                                                {
			RelAttr attr;
			relation_attr_with_agg_init(&attr, "MAX", (yyvsp[-4].string), (yyvsp[-2].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr, CONTEXT->attr_level);
			CONTEXT->attr_level++;
		}
#line 2096 "y.tab.c"
    break;

  case 77: /* select_attr: MIN LBRACE ID RBRACE attr_list  */
#line 511 "yacc_sql.y"
                                         {
			RelAttr attr;
			relation_attr_with_agg_init(&attr, "MIN", NULL, (yyvsp[-2].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr, CONTEXT->attr_level);
			CONTEXT->attr_level++;
		}
#line 2107 "y.tab.c"
    break;

  case 78: /* select_attr: MIN LBRACE ID DOT ID RBRACE attr_list  */
#line 517 "yacc_sql.y"
                                                {
			RelAttr attr;
			relation_attr_with_agg_init(&attr, "MIN", (yyvsp[-4].string), (yyvsp[-2].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr, CONTEXT->attr_level);
			CONTEXT->attr_level++;
		}
#line 2118 "y.tab.c"
    break;

  case 79: /* select_attr: AVG LBRACE ID RBRACE attr_list  */
#line 523 "yacc_sql.y"
                                         {
			RelAttr attr;
			relation_attr_with_agg_init(&attr, "AVG", NULL, (yyvsp[-2].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr, CONTEXT->attr_level);
			CONTEXT->attr_level++;
		}
#line 2129 "y.tab.c"
    break;

  case 80: /* select_attr: AVG LBRACE ID DOT ID RBRACE attr_list  */
#line 529 "yacc_sql.y"
                                                {
			RelAttr attr;
			relation_attr_with_agg_init(&attr, "MIN", (yyvsp[-4].string), (yyvsp[-2].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr, CONTEXT->attr_level);
			CONTEXT->attr_level++;
		}
#line 2140 "y.tab.c"
    break;

  case 82: /* attr_list: COMMA ID attr_list  */
#line 539 "yacc_sql.y"
                         {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr, CONTEXT->attr_level);
     	  // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length].relation_name = NULL;
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length++].attribute_name=$2;
      }
#line 2152 "y.tab.c"
    break;

  case 83: /* attr_list: COMMA ID DOT ID attr_list  */
#line 546 "yacc_sql.y"
                                {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr, CONTEXT->attr_level);
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length].attribute_name=$4;
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length++].relation_name=$2;
  	  }
#line 2164 "y.tab.c"
    break;

  case 84: /* attr_list: COMMA COUNT LBRACE STAR RBRACE attr_list  */
#line 553 "yacc_sql.y"
                                                   {
			RelAttr attr;
			relation_attr_with_agg_init(&attr, "COUNT", NULL, "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr, CONTEXT->attr_level);
	  }
#line 2174 "y.tab.c"
    break;

  case 85: /* attr_list: COMMA COUNT LBRACE ID RBRACE attr_list  */
#line 558 "yacc_sql.y"
                                                 {
			RelAttr attr;
			relation_attr_with_agg_init(&attr, "COUNT", NULL, (yyvsp[-2].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr, CONTEXT->attr_level);
	}
#line 2184 "y.tab.c"
    break;

  case 86: /* attr_list: COMMA COUNT LBRACE ID DOT ID RBRACE attr_list  */
#line 563 "yacc_sql.y"
                                                        {
			RelAttr attr;
			relation_attr_with_agg_init(&attr, "COUNT", (yyvsp[-4].string), (yyvsp[-2].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr, CONTEXT->attr_level);
	}
#line 2194 "y.tab.c"
    break;

  case 87: /* attr_list: COMMA MAX LBRACE ID RBRACE attr_list  */
#line 568 "yacc_sql.y"
                                               {
			RelAttr attr;
			relation_attr_with_agg_init(&attr, "MAX", NULL, (yyvsp[-2].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr, CONTEXT->attr_level);
	}
#line 2204 "y.tab.c"
    break;

  case 88: /* attr_list: COMMA MAX LBRACE ID DOT ID RBRACE attr_list  */
#line 573 "yacc_sql.y"
                                                      {
			RelAttr attr;
			relation_attr_with_agg_init(&attr, "MAX", (yyvsp[-4].string), (yyvsp[-2].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr, CONTEXT->attr_level);
	}
#line 2214 "y.tab.c"
    break;

  case 89: /* attr_list: COMMA MIN LBRACE ID RBRACE attr_list  */
#line 578 "yacc_sql.y"
                                               {
			RelAttr attr;
			relation_attr_with_agg_init(&attr, "MIN", NULL, (yyvsp[-2].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr, CONTEXT->attr_level);
	}
#line 2224 "y.tab.c"
    break;

  case 90: /* attr_list: COMMA MIN LBRACE ID DOT ID RBRACE attr_list  */
#line 583 "yacc_sql.y"
                                                      {
			RelAttr attr;
			relation_attr_with_agg_init(&attr, "MIN", (yyvsp[-4].string), (yyvsp[-2].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr, CONTEXT->attr_level);
	}
#line 2234 "y.tab.c"
    break;

  case 91: /* attr_list: COMMA AVG LBRACE ID RBRACE attr_list  */
#line 588 "yacc_sql.y"
                                               {
			RelAttr attr;
			relation_attr_with_agg_init(&attr, "AVG", NULL, (yyvsp[-2].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr, CONTEXT->attr_level);
	}
#line 2244 "y.tab.c"
    break;

  case 92: /* attr_list: COMMA AVG LBRACE ID DOT ID RBRACE attr_list  */
#line 593 "yacc_sql.y"
                                                      {
			RelAttr attr;
			relation_attr_with_agg_init(&attr, "AVG", (yyvsp[-4].string), (yyvsp[-2].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr, CONTEXT->attr_level);
	}
#line 2254 "y.tab.c"
    break;

  case 94: /* select_from: ID rel_list  */
#line 602 "yacc_sql.y"
        {
		selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-1].string), CONTEXT->from_level);
		CONTEXT->from_level++;
	}
#line 2263 "y.tab.c"
    break;

  case 96: /* rel_list: COMMA ID rel_list  */
#line 609 "yacc_sql.y"
                        {
				selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-1].string), CONTEXT->from_level);
		  }
#line 2271 "y.tab.c"
    break;

  case 98: /* select_join: ID join_list  */
#line 616 "yacc_sql.y"
        {
		select_append_relation(&CONTEXT->ssql->sstr.selection, &1, CONTEXT->from_level);
		CONTEXT->from_level++;
	}
#line 2280 "y.tab.c"
    break;

  case 100: /* join_list: INNER JOIN ID ON condition condition_list join_list  */
#line 623 "yacc_sql.y"
                                                              {
		selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-4].string), CONTEXT->from_level);
	}
#line 2288 "y.tab.c"
    break;

  case 102: /* where: WHERE condition condition_list  */
#line 629 "yacc_sql.y"
                                     {
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 2296 "y.tab.c"
    break;

  case 104: /* condition_list: AND condition condition_list  */
#line 635 "yacc_sql.y"
                                   {
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 2304 "y.tab.c"
    break;

  case 105: /* condition: ID comOp value  */
#line 641 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));

			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 0, NULL, right_value);
			selects_append_condition(&CONTEXT->ssql->sstr.selection, &condition, CONTEXT->condition_level);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			// $$ = ( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;
			// $$->left_attr.relation_name = NULL;
			// $$->left_attr.attribute_name= $1;
			// $$->comp = CONTEXT->comp;
			// $$->right_is_attr = 0;
			// $$->right_attr.relation_name = NULL;
			// $$->right_attr.attribute_name = NULL;
			// $$->right_value = *$3;

		}
#line 2330 "y.tab.c"
    break;

  case 106: /* condition: value comOp value  */
#line 663 "yacc_sql.y"
                {
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 2];
			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 0, NULL, left_value, 0, NULL, right_value);
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
#line 2355 "y.tab.c"
    break;

  case 107: /* condition: ID comOp ID  */
#line 684 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));
			RelAttr right_attr;
			relation_attr_init(&right_attr, NULL, (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 1, &right_attr, NULL);
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
#line 2380 "y.tab.c"
    break;

  case 108: /* condition: value comOp ID  */
#line 705 "yacc_sql.y"
                {
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];
			RelAttr right_attr;
			relation_attr_init(&right_attr, NULL, (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 0, NULL, left_value, 1, &right_attr, NULL);
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
#line 2407 "y.tab.c"
    break;

  case 109: /* condition: ID DOT ID comOp value  */
#line 728 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, (yyvsp[-4].string), (yyvsp[-2].string));
			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 0, NULL, right_value);
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
#line 2433 "y.tab.c"
    break;

  case 110: /* condition: value comOp ID DOT ID  */
#line 750 "yacc_sql.y"
                {
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];

			RelAttr right_attr;
			relation_attr_init(&right_attr, (yyvsp[-2].string), (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 0, NULL, left_value, 1, &right_attr, NULL);
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
#line 2459 "y.tab.c"
    break;

  case 111: /* condition: ID DOT ID comOp ID DOT ID  */
#line 772 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, (yyvsp[-6].string), (yyvsp[-4].string));
			RelAttr right_attr;
			relation_attr_init(&right_attr, (yyvsp[-2].string), (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 1, &right_attr, NULL);
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
#line 2483 "y.tab.c"
    break;

  case 112: /* condition: ID comOp subselect  */
#line 792 "yacc_sql.y"
        {
		RelAttr left_attr;
		relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));

		value_init_subselect(&CONTEXT->values[CONTEXT->value_length++]);
		Condition condition;
		condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 0, NULL, &CONTEXT->values[CONTEXT->value_length - 1]);
		selects_append_condition(&CONTEXT->ssql->sstr.selection, &condition, CONTEXT->condition_level);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;


	}
#line 2500 "y.tab.c"
    break;

  case 113: /* condition: ID DOT ID comOp subselect  */
#line 805 "yacc_sql.y"
        {
		
		RelAttr left_attr;
		relation_attr_init(&left_attr, (yyvsp[-4].string), (yyvsp[-2].string));

		value_init_subselect(&CONTEXT->values[CONTEXT->value_length++]);
		Condition condition;
		condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 0, NULL, &CONTEXT->values[CONTEXT->value_length - 1]);
		selects_append_condition(&CONTEXT->ssql->sstr.selection, &condition, CONTEXT->condition_level);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
	}
#line 2516 "y.tab.c"
    break;

  case 114: /* comOp: EQ  */
#line 819 "yacc_sql.y"
             { CONTEXT->comp = EQUAL_TO; }
#line 2522 "y.tab.c"
    break;

  case 115: /* comOp: LT  */
#line 820 "yacc_sql.y"
         { CONTEXT->comp = LESS_THAN; }
#line 2528 "y.tab.c"
    break;

  case 116: /* comOp: GT  */
#line 821 "yacc_sql.y"
         { CONTEXT->comp = GREAT_THAN; }
#line 2534 "y.tab.c"
    break;

  case 117: /* comOp: LE  */
#line 822 "yacc_sql.y"
         { CONTEXT->comp = LESS_EQUAL; }
#line 2540 "y.tab.c"
    break;

  case 118: /* comOp: GE  */
#line 823 "yacc_sql.y"
         { CONTEXT->comp = GREAT_EQUAL; }
#line 2546 "y.tab.c"
    break;

  case 119: /* comOp: NE  */
#line 824 "yacc_sql.y"
         { CONTEXT->comp = NOT_EQUAL; }
#line 2552 "y.tab.c"
    break;

  case 120: /* comOp: IS NOT  */
#line 825 "yacc_sql.y"
             {CONTEXT->comp = OP_IS_NOT; }
#line 2558 "y.tab.c"
    break;

  case 121: /* comOp: IS  */
#line 826 "yacc_sql.y"
         {CONTEXT->comp = OP_IS; }
#line 2564 "y.tab.c"
    break;

  case 122: /* comOp: IN  */
#line 827 "yacc_sql.y"
             { CONTEXT->comp = OP_IN; }
#line 2570 "y.tab.c"
    break;

  case 123: /* comOp: NOT IN  */
#line 828 "yacc_sql.y"
                 {CONTEXT->comp = OP_NOT_IN; }
#line 2576 "y.tab.c"
    break;

  case 124: /* load_data: LOAD DATA INFILE SSS INTO TABLE ID SEMICOLON  */
#line 833 "yacc_sql.y"
                {
		  CONTEXT->ssql->flag = SCF_LOAD_DATA;
			load_data_init(&CONTEXT->ssql->sstr.load_data, (yyvsp[-1].string), (yyvsp[-4].string));
		}
#line 2585 "y.tab.c"
    break;


#line 2589 "y.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (scanner, YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, scanner);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, scanner);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (scanner, YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, scanner);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, scanner);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 838 "yacc_sql.y"

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
