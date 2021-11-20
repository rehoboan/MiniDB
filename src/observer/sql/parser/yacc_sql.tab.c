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


#line 148 "yacc_sql.tab.c"

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

#include "yacc_sql.tab.h"
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
  YYSYMBOL_ORDER = 16,                     /* ORDER  */
  YYSYMBOL_BY = 17,                        /* BY  */
  YYSYMBOL_ASC = 18,                       /* ASC  */
  YYSYMBOL_DESC = 19,                      /* DESC  */
  YYSYMBOL_GROUP = 20,                     /* GROUP  */
  YYSYMBOL_SHOW = 21,                      /* SHOW  */
  YYSYMBOL_SYNC = 22,                      /* SYNC  */
  YYSYMBOL_INSERT = 23,                    /* INSERT  */
  YYSYMBOL_DELETE = 24,                    /* DELETE  */
  YYSYMBOL_UPDATE = 25,                    /* UPDATE  */
  YYSYMBOL_LBRACE = 26,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 27,                    /* RBRACE  */
  YYSYMBOL_COMMA = 28,                     /* COMMA  */
  YYSYMBOL_TRX_BEGIN = 29,                 /* TRX_BEGIN  */
  YYSYMBOL_TRX_COMMIT = 30,                /* TRX_COMMIT  */
  YYSYMBOL_TRX_ROLLBACK = 31,              /* TRX_ROLLBACK  */
  YYSYMBOL_INT_T = 32,                     /* INT_T  */
  YYSYMBOL_STRING_T = 33,                  /* STRING_T  */
  YYSYMBOL_FLOAT_T = 34,                   /* FLOAT_T  */
  YYSYMBOL_DATE_T = 35,                    /* DATE_T  */
  YYSYMBOL_TEXT_T = 36,                    /* TEXT_T  */
  YYSYMBOL_UNIQUE = 37,                    /* UNIQUE  */
  YYSYMBOL_HELP = 38,                      /* HELP  */
  YYSYMBOL_EXIT = 39,                      /* EXIT  */
  YYSYMBOL_DOT = 40,                       /* DOT  */
  YYSYMBOL_INTO = 41,                      /* INTO  */
  YYSYMBOL_VALUES = 42,                    /* VALUES  */
  YYSYMBOL_FROM = 43,                      /* FROM  */
  YYSYMBOL_WHERE = 44,                     /* WHERE  */
  YYSYMBOL_AND = 45,                       /* AND  */
  YYSYMBOL_SET = 46,                       /* SET  */
  YYSYMBOL_ON = 47,                        /* ON  */
  YYSYMBOL_LOAD = 48,                      /* LOAD  */
  YYSYMBOL_DATA = 49,                      /* DATA  */
  YYSYMBOL_INFILE = 50,                    /* INFILE  */
  YYSYMBOL_IS = 51,                        /* IS  */
  YYSYMBOL_NOT = 52,                       /* NOT  */
  YYSYMBOL_NULLABLE = 53,                  /* NULLABLE  */
  YYSYMBOL_NULL_T = 54,                    /* NULL_T  */
  YYSYMBOL_EQ = 55,                        /* EQ  */
  YYSYMBOL_LT = 56,                        /* LT  */
  YYSYMBOL_GT = 57,                        /* GT  */
  YYSYMBOL_LE = 58,                        /* LE  */
  YYSYMBOL_GE = 59,                        /* GE  */
  YYSYMBOL_NE = 60,                        /* NE  */
  YYSYMBOL_IN = 61,                        /* IN  */
  YYSYMBOL_NUMBER = 62,                    /* NUMBER  */
  YYSYMBOL_FLOAT = 63,                     /* FLOAT  */
  YYSYMBOL_DATE = 64,                      /* DATE  */
  YYSYMBOL_ID = 65,                        /* ID  */
  YYSYMBOL_PATH = 66,                      /* PATH  */
  YYSYMBOL_SSS = 67,                       /* SSS  */
  YYSYMBOL_STAR = 68,                      /* STAR  */
  YYSYMBOL_STRING_V = 69,                  /* STRING_V  */
  YYSYMBOL_YYACCEPT = 70,                  /* $accept  */
  YYSYMBOL_commands = 71,                  /* commands  */
  YYSYMBOL_command = 72,                   /* command  */
  YYSYMBOL_exit = 73,                      /* exit  */
  YYSYMBOL_help = 74,                      /* help  */
  YYSYMBOL_sync = 75,                      /* sync  */
  YYSYMBOL_begin = 76,                     /* begin  */
  YYSYMBOL_commit = 77,                    /* commit  */
  YYSYMBOL_rollback = 78,                  /* rollback  */
  YYSYMBOL_drop_table = 79,                /* drop_table  */
  YYSYMBOL_show_tables = 80,               /* show_tables  */
  YYSYMBOL_desc_table = 81,                /* desc_table  */
  YYSYMBOL_create_index = 82,              /* create_index  */
  YYSYMBOL_field_list = 83,                /* field_list  */
  YYSYMBOL_field = 84,                     /* field  */
  YYSYMBOL_drop_index = 85,                /* drop_index  */
  YYSYMBOL_create_table = 86,              /* create_table  */
  YYSYMBOL_attr_def_list = 87,             /* attr_def_list  */
  YYSYMBOL_attr_def = 88,                  /* attr_def  */
  YYSYMBOL_null_value = 89,                /* null_value  */
  YYSYMBOL_number = 90,                    /* number  */
  YYSYMBOL_type = 91,                      /* type  */
  YYSYMBOL_ID_get = 92,                    /* ID_get  */
  YYSYMBOL_insert = 93,                    /* insert  */
  YYSYMBOL_row_list = 94,                  /* row_list  */
  YYSYMBOL_row = 95,                       /* row  */
  YYSYMBOL_value_list = 96,                /* value_list  */
  YYSYMBOL_value = 97,                     /* value  */
  YYSYMBOL_delete = 98,                    /* delete  */
  YYSYMBOL_update = 99,                    /* update  */
  YYSYMBOL_select = 100,                   /* select  */
  YYSYMBOL_subselect = 101,                /* subselect  */
  YYSYMBOL_pushdown = 102,                 /* pushdown  */
  YYSYMBOL_pushup = 103,                   /* pushup  */
  YYSYMBOL_select_attr = 104,              /* select_attr  */
  YYSYMBOL_attr_list = 105,                /* attr_list  */
  YYSYMBOL_select_from = 106,              /* select_from  */
  YYSYMBOL_rel_list = 107,                 /* rel_list  */
  YYSYMBOL_select_join = 108,              /* select_join  */
  YYSYMBOL_join_list = 109,                /* join_list  */
  YYSYMBOL_where = 110,                    /* where  */
  YYSYMBOL_opt_group = 111,                /* opt_group  */
  YYSYMBOL_column_ref_commalist = 112,     /* column_ref_commalist  */
  YYSYMBOL_column_ref = 113,               /* column_ref  */
  YYSYMBOL_opt_order = 114,                /* opt_order  */
  YYSYMBOL_order_list = 115,               /* order_list  */
  YYSYMBOL_orderby = 116,                  /* orderby  */
  YYSYMBOL_opt_order_type = 117,           /* opt_order_type  */
  YYSYMBOL_condition_list = 118,           /* condition_list  */
  YYSYMBOL_condition = 119,                /* condition  */
  YYSYMBOL_comOp = 120,                    /* comOp  */
  YYSYMBOL_load_data = 121                 /* load_data  */
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
#define YYLAST   324

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  70
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  52
/* YYNRULES -- Number of rules.  */
#define YYNRULES  143
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  325

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   324


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
      65,    66,    67,    68,    69
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   180,   180,   182,   186,   187,   188,   189,   190,   191,
     192,   193,   194,   195,   196,   197,   198,   199,   200,   201,
     202,   206,   211,   216,   222,   228,   234,   240,   246,   252,
     260,   265,   271,   273,   278,   284,   291,   300,   302,   306,
     318,   331,   332,   335,   340,   343,   344,   345,   346,   347,
     350,   359,   376,   377,   382,   387,   389,   394,   397,   400,
     403,   407,   414,   424,   435,   453,   466,   483,   489,   495,
     501,   507,   513,   520,   526,   532,   538,   544,   550,   556,
     562,   568,   576,   578,   585,   592,   597,   602,   607,   612,
     617,   622,   627,   632,   638,   640,   646,   648,   652,   654,
     660,   662,   666,   668,   671,   672,   676,   677,   681,   686,
     694,   696,   699,   700,   702,   703,   708,   715,   716,   717,
     720,   722,   726,   748,   769,   790,   813,   835,   857,   877,
     890,   902,   913,   926,   927,   928,   929,   930,   931,   932,
     933,   934,   935,   939
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
  "INDEX", "SELECT", "ORDER", "BY", "ASC", "DESC", "GROUP", "SHOW", "SYNC",
  "INSERT", "DELETE", "UPDATE", "LBRACE", "RBRACE", "COMMA", "TRX_BEGIN",
  "TRX_COMMIT", "TRX_ROLLBACK", "INT_T", "STRING_T", "FLOAT_T", "DATE_T",
  "TEXT_T", "UNIQUE", "HELP", "EXIT", "DOT", "INTO", "VALUES", "FROM",
  "WHERE", "AND", "SET", "ON", "LOAD", "DATA", "INFILE", "IS", "NOT",
  "NULLABLE", "NULL_T", "EQ", "LT", "GT", "LE", "GE", "NE", "IN", "NUMBER",
  "FLOAT", "DATE", "ID", "PATH", "SSS", "STAR", "STRING_V", "$accept",
  "commands", "command", "exit", "help", "sync", "begin", "commit",
  "rollback", "drop_table", "show_tables", "desc_table", "create_index",
  "field_list", "field", "drop_index", "create_table", "attr_def_list",
  "attr_def", "null_value", "number", "type", "ID_get", "insert",
  "row_list", "row", "value_list", "value", "delete", "update", "select",
  "subselect", "pushdown", "pushup", "select_attr", "attr_list",
  "select_from", "rel_list", "select_join", "join_list", "where",
  "opt_group", "column_ref_commalist", "column_ref", "opt_order",
  "order_list", "orderby", "opt_order_type", "condition_list", "condition",
  "comOp", "load_data", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-239)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-105)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -239,    27,  -239,    22,    23,     3,   -35,    30,    42,    33,
      21,     5,    81,    82,    92,   102,   103,    62,  -239,  -239,
    -239,  -239,  -239,  -239,  -239,  -239,  -239,  -239,  -239,  -239,
    -239,  -239,  -239,  -239,  -239,  -239,    72,    77,   111,    95,
      97,   132,   135,   140,   141,    -7,  -239,   131,   170,   185,
    -239,   124,   126,   151,  -239,  -239,  -239,  -239,  -239,   146,
     172,   152,   136,   197,   199,    67,   138,   139,   142,    17,
     143,  -239,   144,  -239,  -239,   163,   162,   145,   147,   148,
     153,   164,  -239,  -239,    36,   188,    46,    61,    94,   186,
     190,   191,   193,    41,   192,    19,   162,   162,   195,    29,
     219,   168,   183,  -239,   198,   150,   201,   160,   192,   165,
     192,   192,   166,   192,   167,   192,   169,   122,   171,   173,
     174,   175,  -239,  -239,   217,   176,  -239,  -239,    84,   209,
     101,   205,  -239,  -239,  -239,  -239,  -239,    93,  -239,   120,
     120,   220,   200,  -239,   101,   225,   148,   215,  -239,  -239,
    -239,  -239,  -239,   -12,   178,   218,  -239,   221,  -239,  -239,
     222,  -239,   223,  -239,   224,    96,   226,   119,   129,   130,
     192,   181,   227,   230,   236,   236,   228,   195,   251,   194,
     206,   196,  -239,  -239,  -239,  -239,  -239,  -239,  -239,    64,
      45,   202,   233,    29,  -239,   162,   203,   198,   258,   204,
     208,  -239,  -239,  -239,   235,   178,   192,   192,   192,   192,
     192,   207,   192,   192,   210,   192,   211,   192,   212,  -239,
     231,  -239,   214,   247,   262,   266,   101,   243,   205,  -239,
     120,  -239,  -239,  -239,  -239,  -239,   234,  -239,   240,  -239,
    -239,   200,   268,   270,  -239,  -239,  -239,   254,  -239,   178,
     255,   235,  -239,  -239,  -239,  -239,  -239,   256,  -239,  -239,
     257,  -239,   259,  -239,   260,    29,   245,   261,  -239,   229,
    -239,  -239,   228,  -239,  -239,    76,   232,   237,  -239,  -239,
    -239,     1,   235,   285,   263,   192,   192,   192,   192,   200,
     238,   214,    20,   264,  -239,   253,  -239,  -239,  -239,  -239,
    -239,  -239,  -239,   288,  -239,  -239,  -239,  -239,   286,  -239,
    -239,  -239,  -239,   239,  -239,   229,  -239,   241,  -239,  -239,
      60,   264,  -239,  -239,  -239
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     1,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     3,    20,
      19,    14,    15,    16,    17,     9,    10,    11,    12,    13,
       8,     5,     7,     6,     4,    18,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    82,    70,     0,     0,     0,
      23,     0,     0,     0,    24,    25,    26,    22,    21,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    71,    94,    29,    28,     0,   102,     0,     0,     0,
       0,     0,    27,    35,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    82,    82,    96,   102,   102,     0,     0,
       0,     0,     0,    50,    37,     0,     0,     0,    82,     0,
      82,    82,     0,    82,     0,    82,     0,     0,     0,     0,
       0,     0,    83,    72,     0,     0,    95,    99,    66,   104,
       0,    52,    68,    57,    58,    59,    60,     0,    61,     0,
       0,     0,   120,    62,     0,     0,     0,     0,    45,    46,
      47,    48,    49,    41,     0,     0,    74,     0,    73,    76,
       0,    78,     0,    80,     0,     0,     0,     0,     0,     0,
      82,     0,    96,     0,   110,   110,    55,     0,     0,     0,
     140,     0,   133,   134,   135,   136,   137,   138,   141,     0,
       0,     0,     0,     0,   103,   102,     0,    37,     0,     0,
       0,    42,    40,    34,    32,     0,    82,    82,    82,    82,
      82,     0,    82,    82,     0,    82,     0,    82,     0,    84,
       0,    97,     0,     0,     0,     0,     0,     0,    52,    51,
       0,   139,   142,   124,   122,   129,   125,   123,   131,    69,
      67,   120,     0,     0,    38,    36,    44,     0,    43,     0,
       0,    32,    75,    77,    79,    81,    86,     0,    85,    88,
       0,    90,     0,    92,     0,     0,   108,   105,   106,   114,
      64,    65,    55,    54,    53,     0,     0,     0,   121,    63,
     143,    41,    32,     0,     0,    82,    82,    82,    82,   120,
       0,     0,   119,   112,    56,     0,   126,   130,   127,   132,
      39,    33,    30,     0,    87,    89,    91,    93,   100,   109,
     107,   117,   118,     0,   115,   114,   111,     0,    31,   101,
     119,   112,   128,   116,   113
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -239,  -239,  -239,  -239,  -239,  -239,  -239,  -239,  -239,  -239,
    -239,  -239,  -239,  -238,  -177,  -239,  -239,    98,   154,    18,
    -239,  -239,  -239,  -239,    70,   128,    35,  -128,  -239,  -239,
     177,  -186,  -239,  -239,  -239,   -93,  -239,   137,  -239,     0,
     -92,   182,  -239,    10,   149,   -11,    -3,    -6,  -222,  -185,
    -133,  -239
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     1,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,   250,   204,    29,    30,   147,   104,   202,
     247,   153,   105,    31,   178,   131,   227,   139,    32,    33,
      34,   140,   141,   240,    47,    71,    96,   126,    97,   127,
     100,   174,   267,   268,   224,   316,   293,   314,   194,   142,
     189,    35
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     122,   123,   176,   235,   128,   129,   190,   191,   241,    41,
      42,    43,    44,   284,   199,   156,   195,   158,   159,   278,
     161,    69,   163,    89,    90,    91,    92,     2,   251,   124,
      48,     3,     4,    70,    36,    39,    37,    40,   311,   312,
     200,   201,     5,    49,   301,    50,     6,   125,     7,     8,
       9,    10,    11,   200,   201,   132,    12,    13,    14,    38,
     313,   234,   237,   108,    52,    15,    16,   308,    45,    69,
      53,    46,   282,   111,    51,    17,   109,   219,   311,   312,
     289,   121,    93,   133,    54,    55,   112,  -104,   113,   297,
     132,   134,   135,   136,   137,    56,   138,   275,   272,   133,
    -104,   114,   132,   242,   173,    57,    58,   134,   135,   136,
     236,    59,   138,   252,   253,   254,   255,   256,   133,   258,
     259,   115,   261,   210,   263,    62,   134,   135,   136,   233,
     133,   138,    84,   179,   116,    85,   211,    60,   134,   135,
     136,   295,    61,   138,   180,   181,   213,   296,   182,   183,
     184,   185,   186,   187,   188,   133,   215,   217,    65,   214,
      63,    66,    64,   134,   135,   136,    67,    68,   138,   216,
     218,   180,   181,    73,    72,   182,   183,   184,   185,   186,
     187,   188,   148,   149,   150,   151,   152,   165,    74,    75,
     166,    76,   304,   305,   306,   307,    78,    77,    79,    80,
      82,    81,    83,    86,    87,    98,    99,    88,    94,    95,
     101,   107,   117,   103,   102,   110,   118,   119,   106,   120,
      69,   130,   143,   144,   145,   155,   146,   154,   171,   173,
     157,   160,   162,   177,   164,     5,   167,   196,   168,   169,
     170,   172,   198,   203,   205,   193,   220,   222,   206,   207,
     208,   209,   223,   212,   229,   125,   226,   232,   231,   230,
     239,   245,   248,   249,   269,   270,   246,   238,   243,   271,
     273,   279,   257,   280,   276,   260,   262,   264,   265,   266,
     277,   281,   283,   285,   286,   290,   287,   288,   302,   291,
     303,   318,   315,   317,   292,   244,   124,   298,   274,   300,
     197,   310,   299,   309,   320,   228,   322,   294,   319,   221,
     324,   175,   321,     0,   323,     0,     0,     0,   192,     0,
       0,     0,     0,     0,   225
};

static const yytype_int16 yycheck[] =
{
      93,    94,   130,   189,    96,    97,   139,   140,   193,     6,
       7,     8,     9,   251,    26,   108,   144,   110,   111,   241,
     113,    28,   115,     6,     7,     8,     9,     0,   205,    10,
      65,     4,     5,    40,    12,    12,    14,    14,    18,    19,
      52,    53,    15,    13,   282,     3,    19,    28,    21,    22,
      23,    24,    25,    52,    53,    26,    29,    30,    31,    37,
      40,   189,   190,    27,    43,    38,    39,   289,    65,    28,
      65,    68,   249,    27,    41,    48,    40,   170,    18,    19,
     265,    40,    65,    54,     3,     3,    40,     3,    27,   275,
      26,    62,    63,    64,    65,     3,    67,   230,   226,    54,
      16,    40,    26,   195,    20,     3,     3,    62,    63,    64,
      65,    49,    67,   206,   207,   208,   209,   210,    54,   212,
     213,    27,   215,    27,   217,    14,    62,    63,    64,    65,
      54,    67,    65,    40,    40,    68,    40,    65,    62,    63,
      64,    65,    65,    67,    51,    52,    27,   275,    55,    56,
      57,    58,    59,    60,    61,    54,    27,    27,    26,    40,
      65,    26,    65,    62,    63,    64,    26,    26,    67,    40,
      40,    51,    52,     3,    43,    55,    56,    57,    58,    59,
      60,    61,    32,    33,    34,    35,    36,    65,     3,    65,
      68,    65,   285,   286,   287,   288,    50,    46,    26,    47,
       3,    65,     3,    65,    65,    42,    44,    65,    65,    65,
      65,    47,    26,    65,    67,    27,    26,    26,    65,    26,
      28,    26,     3,    55,    41,    65,    28,    26,    11,    20,
      65,    65,    65,    28,    65,    15,    65,    12,    65,    65,
      65,    65,    27,    65,    26,    45,    65,    17,    27,    27,
      27,    27,    16,    27,     3,    28,    28,    61,    52,    65,
      27,     3,    54,    28,    17,     3,    62,    65,    65,     3,
      27,     3,    65,     3,    40,    65,    65,    65,    47,    65,
      40,    27,    27,    27,    27,    40,    27,    27,     3,    28,
      27,     3,    28,    40,    65,   197,    10,    65,   228,   281,
     146,   291,    65,    65,    65,   177,    65,   272,   308,   172,
     321,   129,   315,    -1,   320,    -1,    -1,    -1,   141,    -1,
      -1,    -1,    -1,    -1,   175
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    71,     0,     4,     5,    15,    19,    21,    22,    23,
      24,    25,    29,    30,    31,    38,    39,    48,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    85,
      86,    93,    98,    99,   100,   121,    12,    14,    37,    12,
      14,     6,     7,     8,     9,    65,    68,   104,    65,    13,
       3,    41,    43,    65,     3,     3,     3,     3,     3,    49,
      65,    65,    14,    65,    65,    26,    26,    26,    26,    28,
      40,   105,    43,     3,     3,    65,    65,    46,    50,    26,
      47,    65,     3,     3,    65,    68,    65,    65,    65,     6,
       7,     8,     9,    65,    65,    65,   106,   108,    42,    44,
     110,    65,    67,    65,    88,    92,    65,    47,    27,    40,
      27,    27,    40,    27,    40,    27,    40,    26,    26,    26,
      26,    40,   105,   105,    10,    28,   107,   109,   110,   110,
      26,    95,    26,    54,    62,    63,    64,    65,    67,    97,
     101,   102,   119,     3,    55,    41,    28,    87,    32,    33,
      34,    35,    36,    91,    26,    65,   105,    65,   105,   105,
      65,   105,    65,   105,    65,    65,    68,    65,    65,    65,
      65,    11,    65,    20,   111,   111,    97,    28,    94,    40,
      51,    52,    55,    56,    57,    58,    59,    60,    61,   120,
     120,   120,   100,    45,   118,    97,    12,    88,    27,    26,
      52,    53,    89,    65,    84,    26,    27,    27,    27,    27,
      27,    40,    27,    27,    40,    27,    40,    27,    40,   105,
      65,   107,    17,    16,   114,   114,    28,    96,    95,     3,
      65,    52,    61,    65,    97,   101,    65,    97,    65,    27,
     103,   119,   110,    65,    87,     3,    62,    90,    54,    28,
      83,    84,   105,   105,   105,   105,   105,    65,   105,   105,
      65,   105,    65,   105,    65,    47,    65,   112,   113,    17,
       3,     3,    97,    27,    94,   120,    40,    40,   118,     3,
       3,    27,    84,    27,    83,    27,    27,    27,    27,   119,
      40,    28,    65,   116,    96,    65,    97,   101,    65,    65,
      89,    83,     3,    27,   105,   105,   105,   105,   118,    65,
     113,    18,    19,    40,   117,    28,   115,    40,     3,   109,
      65,   116,    65,   117,   115
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    70,    71,    71,    72,    72,    72,    72,    72,    72,
      72,    72,    72,    72,    72,    72,    72,    72,    72,    72,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    82,    83,    83,    84,    85,    86,    87,    87,    88,
      88,    89,    89,    89,    90,    91,    91,    91,    91,    91,
      92,    93,    94,    94,    95,    96,    96,    97,    97,    97,
      97,    97,    98,    99,   100,   100,   100,   101,   102,   103,
     104,   104,   104,   104,   104,   104,   104,   104,   104,   104,
     104,   104,   105,   105,   105,   105,   105,   105,   105,   105,
     105,   105,   105,   105,   106,   106,   107,   107,   108,   108,
     109,   109,   110,   110,   111,   111,   112,   112,   113,   113,
     114,   114,   115,   115,   116,   116,   116,   117,   117,   117,
     118,   118,   119,   119,   119,   119,   119,   119,   119,   119,
     119,   119,   119,   120,   120,   120,   120,   120,   120,   120,
     120,   120,   120,   121
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
       1,     1,     5,     8,     8,     8,     5,     3,     1,     1,
       1,     2,     4,     5,     5,     7,     5,     7,     5,     7,
       5,     7,     0,     3,     5,     6,     6,     8,     6,     8,
       6,     8,     6,     8,     0,     2,     0,     3,     0,     2,
       0,     7,     0,     3,     0,     3,     1,     3,     1,     3,
       0,     4,     0,     3,     0,     2,     4,     1,     1,     0,
       0,     3,     3,     3,     3,     3,     5,     5,     7,     3,
       5,     3,     5,     1,     1,     1,     1,     1,     1,     2,
       1,     1,     2,     8
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
#line 206 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_EXIT;//"exit";
    }
#line 1488 "yacc_sql.tab.c"
    break;

  case 22: /* help: HELP SEMICOLON  */
#line 211 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_HELP;//"help";
    }
#line 1496 "yacc_sql.tab.c"
    break;

  case 23: /* sync: SYNC SEMICOLON  */
#line 216 "yacc_sql.y"
                   {
      CONTEXT->ssql->flag = SCF_SYNC;
    }
#line 1504 "yacc_sql.tab.c"
    break;

  case 24: /* begin: TRX_BEGIN SEMICOLON  */
#line 222 "yacc_sql.y"
                        {
      CONTEXT->ssql->flag = SCF_BEGIN;
    }
#line 1512 "yacc_sql.tab.c"
    break;

  case 25: /* commit: TRX_COMMIT SEMICOLON  */
#line 228 "yacc_sql.y"
                         {
      CONTEXT->ssql->flag = SCF_COMMIT;
    }
#line 1520 "yacc_sql.tab.c"
    break;

  case 26: /* rollback: TRX_ROLLBACK SEMICOLON  */
#line 234 "yacc_sql.y"
                           {
      CONTEXT->ssql->flag = SCF_ROLLBACK;
    }
#line 1528 "yacc_sql.tab.c"
    break;

  case 27: /* drop_table: DROP TABLE ID SEMICOLON  */
#line 240 "yacc_sql.y"
                            {
        CONTEXT->ssql->flag = SCF_DROP_TABLE;//"drop_table";
        drop_table_init(&CONTEXT->ssql->sstr.drop_table, (yyvsp[-1].string));
    }
#line 1537 "yacc_sql.tab.c"
    break;

  case 28: /* show_tables: SHOW TABLES SEMICOLON  */
#line 246 "yacc_sql.y"
                          {
      CONTEXT->ssql->flag = SCF_SHOW_TABLES;
    }
#line 1545 "yacc_sql.tab.c"
    break;

  case 29: /* desc_table: DESC ID SEMICOLON  */
#line 252 "yacc_sql.y"
                      {
      CONTEXT->ssql->flag = SCF_DESC_TABLE;
      desc_table_init(&CONTEXT->ssql->sstr.desc_table, (yyvsp[-1].string));
    }
#line 1554 "yacc_sql.tab.c"
    break;

  case 30: /* create_index: CREATE INDEX ID ON ID LBRACE field field_list RBRACE SEMICOLON  */
#line 261 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-7].string), (yyvsp[-5].string), CONTEXT->field_names, CONTEXT->index_field_num, 0);
		}
#line 1563 "yacc_sql.tab.c"
    break;

  case 31: /* create_index: CREATE UNIQUE INDEX ID ON ID LBRACE field field_list RBRACE SEMICOLON  */
#line 266 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-7].string), (yyvsp[-5].string), CONTEXT->field_names, CONTEXT->index_field_num, 1);
                }
#line 1572 "yacc_sql.tab.c"
    break;

  case 33: /* field_list: COMMA field field_list  */
#line 273 "yacc_sql.y"
                               {

    	}
#line 1580 "yacc_sql.tab.c"
    break;

  case 34: /* field: ID  */
#line 278 "yacc_sql.y"
          {
    		CONTEXT->field_names[CONTEXT->index_field_num++]=(yyvsp[0].string);
    	}
#line 1588 "yacc_sql.tab.c"
    break;

  case 35: /* drop_index: DROP INDEX ID SEMICOLON  */
#line 285 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_DROP_INDEX;//"drop_index";
			drop_index_init(&CONTEXT->ssql->sstr.drop_index, (yyvsp[-1].string));
		}
#line 1597 "yacc_sql.tab.c"
    break;

  case 36: /* create_table: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE SEMICOLON  */
#line 292 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_CREATE_TABLE;//"create_table";
			// CONTEXT->ssql->sstr.create_table.attribute_count = CONTEXT->value_length;
			create_table_init_name(&CONTEXT->ssql->sstr.create_table, (yyvsp[-5].string));
			//临时变量清零
			CONTEXT->value_length = 0;
		}
#line 1609 "yacc_sql.tab.c"
    break;

  case 38: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 302 "yacc_sql.y"
                                   {    }
#line 1615 "yacc_sql.tab.c"
    break;

  case 39: /* attr_def: ID_get type LBRACE number RBRACE null_value  */
#line 307 "yacc_sql.y"
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
#line 1631 "yacc_sql.tab.c"
    break;

  case 40: /* attr_def: ID_get type null_value  */
#line 319 "yacc_sql.y"
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
#line 1647 "yacc_sql.tab.c"
    break;

  case 42: /* null_value: NULLABLE  */
#line 332 "yacc_sql.y"
                 {
		CONTEXT->nullable = true;
	}
#line 1655 "yacc_sql.tab.c"
    break;

  case 43: /* null_value: NOT NULL_T  */
#line 335 "yacc_sql.y"
                   {

	}
#line 1663 "yacc_sql.tab.c"
    break;

  case 44: /* number: NUMBER  */
#line 340 "yacc_sql.y"
                       {(yyval.number) = (yyvsp[0].number);}
#line 1669 "yacc_sql.tab.c"
    break;

  case 45: /* type: INT_T  */
#line 343 "yacc_sql.y"
              { (yyval.number)=INTS; }
#line 1675 "yacc_sql.tab.c"
    break;

  case 46: /* type: STRING_T  */
#line 344 "yacc_sql.y"
                  { (yyval.number)=CHARS; }
#line 1681 "yacc_sql.tab.c"
    break;

  case 47: /* type: FLOAT_T  */
#line 345 "yacc_sql.y"
                 { (yyval.number)=FLOATS; }
#line 1687 "yacc_sql.tab.c"
    break;

  case 48: /* type: DATE_T  */
#line 346 "yacc_sql.y"
                { (yyval.number)=DATES; }
#line 1693 "yacc_sql.tab.c"
    break;

  case 49: /* type: TEXT_T  */
#line 347 "yacc_sql.y"
                { (yyval.number)=TEXTS; }
#line 1699 "yacc_sql.tab.c"
    break;

  case 50: /* ID_get: ID  */
#line 351 "yacc_sql.y"
        {
		char *temp=(yyvsp[0].string);
		snprintf(CONTEXT->id, sizeof(CONTEXT->id), "%s", temp);
	}
#line 1708 "yacc_sql.tab.c"
    break;

  case 51: /* insert: INSERT INTO ID VALUES row row_list SEMICOLON  */
#line 360 "yacc_sql.y"
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
#line 1728 "yacc_sql.tab.c"
    break;

  case 53: /* row_list: COMMA row row_list  */
#line 377 "yacc_sql.y"
                                {
	}
#line 1735 "yacc_sql.tab.c"
    break;

  case 54: /* row: LBRACE value value_list RBRACE  */
#line 382 "yacc_sql.y"
                                        {
		CONTEXT->row_end[CONTEXT->row_num++]=CONTEXT->value_length;
	}
#line 1743 "yacc_sql.tab.c"
    break;

  case 56: /* value_list: COMMA value value_list  */
#line 389 "yacc_sql.y"
                              {
  		// CONTEXT->values[CONTEXT->value_length++] = *$2;
	  }
#line 1751 "yacc_sql.tab.c"
    break;

  case 57: /* value: NULL_T  */
#line 394 "yacc_sql.y"
          {
		value_init_null(&CONTEXT->values[CONTEXT->value_length++]);
	}
#line 1759 "yacc_sql.tab.c"
    break;

  case 58: /* value: NUMBER  */
#line 397 "yacc_sql.y"
           {
  		value_init_integer(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].number));
		}
#line 1767 "yacc_sql.tab.c"
    break;

  case 59: /* value: FLOAT  */
#line 400 "yacc_sql.y"
          {
  		value_init_float(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].floats));
		}
#line 1775 "yacc_sql.tab.c"
    break;

  case 60: /* value: DATE  */
#line 403 "yacc_sql.y"
          {
    			(yyvsp[0].string) = substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      		value_init_date(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].string));
    		}
#line 1784 "yacc_sql.tab.c"
    break;

  case 61: /* value: SSS  */
#line 407 "yacc_sql.y"
         {
			(yyvsp[0].string) = substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
  		value_init_string(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].string));
		}
#line 1793 "yacc_sql.tab.c"
    break;

  case 62: /* delete: DELETE FROM ID where SEMICOLON  */
#line 415 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_DELETE;//"delete";
			deletes_init_relation(&CONTEXT->ssql->sstr.deletion, (yyvsp[-2].string));
			deletes_set_conditions(&CONTEXT->ssql->sstr.deletion,
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;
    }
#line 1805 "yacc_sql.tab.c"
    break;

  case 63: /* update: UPDATE ID SET ID EQ value where SEMICOLON  */
#line 425 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_UPDATE;//"update";
			Value *value = &CONTEXT->values[0];
			updates_init(&CONTEXT->ssql->sstr.update, (yyvsp[-6].string), (yyvsp[-4].string), value,
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;
		}
#line 1817 "yacc_sql.tab.c"
    break;

  case 64: /* select: SELECT select_attr FROM select_from where opt_group opt_order SEMICOLON  */
#line 436 "yacc_sql.y"
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
#line 1838 "yacc_sql.tab.c"
    break;

  case 65: /* select: SELECT select_attr FROM select_join where opt_group opt_order SEMICOLON  */
#line 454 "yacc_sql.y"
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
#line 1855 "yacc_sql.tab.c"
    break;

  case 66: /* select: SELECT select_attr FROM select_from where  */
#line 467 "yacc_sql.y"
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
#line 1874 "yacc_sql.tab.c"
    break;

  case 67: /* subselect: pushdown select pushup  */
#line 484 "yacc_sql.y"
        {
		debug_subselect();
	}
#line 1882 "yacc_sql.tab.c"
    break;

  case 68: /* pushdown: LBRACE  */
#line 489 "yacc_sql.y"
               {
		push_down();
		CONTEXT->condition_level++;
	}
#line 1891 "yacc_sql.tab.c"
    break;

  case 69: /* pushup: RBRACE  */
#line 495 "yacc_sql.y"
               {
		push_up();
		CONTEXT->condition_level--;
	}
#line 1900 "yacc_sql.tab.c"
    break;

  case 70: /* select_attr: STAR  */
#line 501 "yacc_sql.y"
         {
			RelAttr attr;
			relation_attr_init(&attr, NULL, "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr, CONTEXT->attr_level);
			CONTEXT->attr_level++;
		}
#line 1911 "yacc_sql.tab.c"
    break;

  case 71: /* select_attr: ID attr_list  */
#line 507 "yacc_sql.y"
                   {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr, CONTEXT->attr_level);
			CONTEXT->attr_level++;
		}
#line 1922 "yacc_sql.tab.c"
    break;

  case 72: /* select_attr: ID DOT ID attr_list  */
#line 513 "yacc_sql.y"
                              {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr, CONTEXT->attr_level);
			CONTEXT->attr_level++;
		}
#line 1933 "yacc_sql.tab.c"
    break;

  case 73: /* select_attr: COUNT LBRACE STAR RBRACE attr_list  */
#line 520 "yacc_sql.y"
                                             {
			RelAttr attr;
			relation_attr_with_agg_init(&attr, "COUNT", NULL, "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr, CONTEXT->attr_level);
			CONTEXT->attr_level++;
		}
#line 1944 "yacc_sql.tab.c"
    break;

  case 74: /* select_attr: COUNT LBRACE ID RBRACE attr_list  */
#line 526 "yacc_sql.y"
                                           {
			RelAttr attr;
			relation_attr_with_agg_init(&attr, "COUNT", NULL, (yyvsp[-2].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr, CONTEXT->attr_level);
			CONTEXT->attr_level++;
		}
#line 1955 "yacc_sql.tab.c"
    break;

  case 75: /* select_attr: COUNT LBRACE ID DOT ID RBRACE attr_list  */
#line 532 "yacc_sql.y"
                                                  {
			RelAttr attr;
			relation_attr_with_agg_init(&attr, "COUNT", (yyvsp[-4].string), (yyvsp[-2].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr, CONTEXT->attr_level);
			CONTEXT->attr_level++;
		}
#line 1966 "yacc_sql.tab.c"
    break;

  case 76: /* select_attr: MAX LBRACE ID RBRACE attr_list  */
#line 538 "yacc_sql.y"
                                         {
			RelAttr attr;
			relation_attr_with_agg_init(&attr, "MAX", NULL, (yyvsp[-2].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr, CONTEXT->attr_level);
			CONTEXT->attr_level++;
		}
#line 1977 "yacc_sql.tab.c"
    break;

  case 77: /* select_attr: MAX LBRACE ID DOT ID RBRACE attr_list  */
#line 544 "yacc_sql.y"
                                                {
			RelAttr attr;
			relation_attr_with_agg_init(&attr, "MAX", (yyvsp[-4].string), (yyvsp[-2].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr, CONTEXT->attr_level);
			CONTEXT->attr_level++;
		}
#line 1988 "yacc_sql.tab.c"
    break;

  case 78: /* select_attr: MIN LBRACE ID RBRACE attr_list  */
#line 550 "yacc_sql.y"
                                         {
			RelAttr attr;
			relation_attr_with_agg_init(&attr, "MIN", NULL, (yyvsp[-2].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr, CONTEXT->attr_level);
			CONTEXT->attr_level++;
		}
#line 1999 "yacc_sql.tab.c"
    break;

  case 79: /* select_attr: MIN LBRACE ID DOT ID RBRACE attr_list  */
#line 556 "yacc_sql.y"
                                                {
			RelAttr attr;
			relation_attr_with_agg_init(&attr, "MIN", (yyvsp[-4].string), (yyvsp[-2].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr, CONTEXT->attr_level);
			CONTEXT->attr_level++;
		}
#line 2010 "yacc_sql.tab.c"
    break;

  case 80: /* select_attr: AVG LBRACE ID RBRACE attr_list  */
#line 562 "yacc_sql.y"
                                         {
			RelAttr attr;
			relation_attr_with_agg_init(&attr, "AVG", NULL, (yyvsp[-2].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr, CONTEXT->attr_level);
			CONTEXT->attr_level++;
		}
#line 2021 "yacc_sql.tab.c"
    break;

  case 81: /* select_attr: AVG LBRACE ID DOT ID RBRACE attr_list  */
#line 568 "yacc_sql.y"
                                                {
			RelAttr attr;
			relation_attr_with_agg_init(&attr, "AVG", (yyvsp[-4].string), (yyvsp[-2].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr, CONTEXT->attr_level);
			CONTEXT->attr_level++;
		}
#line 2032 "yacc_sql.tab.c"
    break;

  case 83: /* attr_list: COMMA ID attr_list  */
#line 578 "yacc_sql.y"
                         {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr, CONTEXT->attr_level);
     	  // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length].relation_name = NULL;
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length++].attribute_name=$2;
      }
#line 2044 "yacc_sql.tab.c"
    break;

  case 84: /* attr_list: COMMA ID DOT ID attr_list  */
#line 585 "yacc_sql.y"
                                {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr, CONTEXT->attr_level);
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length].attribute_name=$4;
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length++].relation_name=$2;
  	  }
#line 2056 "yacc_sql.tab.c"
    break;

  case 85: /* attr_list: COMMA COUNT LBRACE STAR RBRACE attr_list  */
#line 592 "yacc_sql.y"
                                                   {
			RelAttr attr;
			relation_attr_with_agg_init(&attr, "COUNT", NULL, "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr, CONTEXT->attr_level);
	  }
#line 2066 "yacc_sql.tab.c"
    break;

  case 86: /* attr_list: COMMA COUNT LBRACE ID RBRACE attr_list  */
#line 597 "yacc_sql.y"
                                                 {
			RelAttr attr;
			relation_attr_with_agg_init(&attr, "COUNT", NULL, (yyvsp[-2].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr, CONTEXT->attr_level);
	}
#line 2076 "yacc_sql.tab.c"
    break;

  case 87: /* attr_list: COMMA COUNT LBRACE ID DOT ID RBRACE attr_list  */
#line 602 "yacc_sql.y"
                                                        {
			RelAttr attr;
			relation_attr_with_agg_init(&attr, "COUNT", (yyvsp[-4].string), (yyvsp[-2].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr, CONTEXT->attr_level);
	}
#line 2086 "yacc_sql.tab.c"
    break;

  case 88: /* attr_list: COMMA MAX LBRACE ID RBRACE attr_list  */
#line 607 "yacc_sql.y"
                                               {
			RelAttr attr;
			relation_attr_with_agg_init(&attr, "MAX", NULL, (yyvsp[-2].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr, CONTEXT->attr_level);
	}
#line 2096 "yacc_sql.tab.c"
    break;

  case 89: /* attr_list: COMMA MAX LBRACE ID DOT ID RBRACE attr_list  */
#line 612 "yacc_sql.y"
                                                      {
			RelAttr attr;
			relation_attr_with_agg_init(&attr, "MAX", (yyvsp[-4].string), (yyvsp[-2].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr, CONTEXT->attr_level);
	}
#line 2106 "yacc_sql.tab.c"
    break;

  case 90: /* attr_list: COMMA MIN LBRACE ID RBRACE attr_list  */
#line 617 "yacc_sql.y"
                                               {
			RelAttr attr;
			relation_attr_with_agg_init(&attr, "MIN", NULL, (yyvsp[-2].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr, CONTEXT->attr_level);
	}
#line 2116 "yacc_sql.tab.c"
    break;

  case 91: /* attr_list: COMMA MIN LBRACE ID DOT ID RBRACE attr_list  */
#line 622 "yacc_sql.y"
                                                      {
			RelAttr attr;
			relation_attr_with_agg_init(&attr, "MIN", (yyvsp[-4].string), (yyvsp[-2].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr, CONTEXT->attr_level);
	}
#line 2126 "yacc_sql.tab.c"
    break;

  case 92: /* attr_list: COMMA AVG LBRACE ID RBRACE attr_list  */
#line 627 "yacc_sql.y"
                                               {
			RelAttr attr;
			relation_attr_with_agg_init(&attr, "AVG", NULL, (yyvsp[-2].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr, CONTEXT->attr_level);
	}
#line 2136 "yacc_sql.tab.c"
    break;

  case 93: /* attr_list: COMMA AVG LBRACE ID DOT ID RBRACE attr_list  */
#line 632 "yacc_sql.y"
                                                      {
			RelAttr attr;
			relation_attr_with_agg_init(&attr, "AVG", (yyvsp[-4].string), (yyvsp[-2].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr, CONTEXT->attr_level);
	}
#line 2146 "yacc_sql.tab.c"
    break;

  case 95: /* select_from: ID rel_list  */
#line 641 "yacc_sql.y"
        {
		selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-1].string), CONTEXT->from_level);
		CONTEXT->from_level++;
	}
#line 2155 "yacc_sql.tab.c"
    break;

  case 97: /* rel_list: COMMA ID rel_list  */
#line 648 "yacc_sql.y"
                        {
				selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-1].string), CONTEXT->from_level);
		  }
#line 2163 "yacc_sql.tab.c"
    break;

  case 99: /* select_join: ID join_list  */
#line 655 "yacc_sql.y"
        {
		selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-1].string), CONTEXT->from_level);
		CONTEXT->from_level++;
	}
#line 2172 "yacc_sql.tab.c"
    break;

  case 101: /* join_list: INNER JOIN ID ON condition condition_list join_list  */
#line 662 "yacc_sql.y"
                                                              {
		selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-4].string), CONTEXT->from_level);
	}
#line 2180 "yacc_sql.tab.c"
    break;

  case 108: /* column_ref: ID  */
#line 681 "yacc_sql.y"
                   {
		GroupByDescription group;
		relation_group_init(&group,NULL,(yyvsp[0].string));
		CONTEXT->groups[CONTEXT->group_num++] = group;
		}
#line 2190 "yacc_sql.tab.c"
    break;

  case 109: /* column_ref: ID DOT ID  */
#line 686 "yacc_sql.y"
                         {
		GroupByDescription group;
		relation_group_init(&group,(yyvsp[-2].string),(yyvsp[0].string));
		CONTEXT->groups[CONTEXT->group_num++] = group;

	}
#line 2201 "yacc_sql.tab.c"
    break;

  case 115: /* orderby: ID opt_order_type  */
#line 703 "yacc_sql.y"
                   {
	OrderDescription order;
	relation_order_init(&order, NULL, (yyvsp[-1].string), CONTEXT->order_type);
        CONTEXT->orders[CONTEXT->order_num++] = order;
}
#line 2211 "yacc_sql.tab.c"
    break;

  case 116: /* orderby: ID DOT ID opt_order_type  */
#line 708 "yacc_sql.y"
                         {
	OrderDescription order;
	relation_order_init(&order, (yyvsp[-3].string), (yyvsp[-1].string), CONTEXT->order_type);
        CONTEXT->orders[CONTEXT->order_num++] = order;
}
#line 2221 "yacc_sql.tab.c"
    break;

  case 117: /* opt_order_type: ASC  */
#line 715 "yacc_sql.y"
                     { CONTEXT->order_type = kOrderAsc; }
#line 2227 "yacc_sql.tab.c"
    break;

  case 118: /* opt_order_type: DESC  */
#line 716 "yacc_sql.y"
       { CONTEXT->order_type = kOrderDesc; }
#line 2233 "yacc_sql.tab.c"
    break;

  case 119: /* opt_order_type: %empty  */
#line 717 "yacc_sql.y"
              { CONTEXT->order_type = kOrderAsc; }
#line 2239 "yacc_sql.tab.c"
    break;

  case 122: /* condition: ID comOp value  */
#line 727 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));

			Value *right_value = &(CONTEXT->values[CONTEXT->value_length - 1]);

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
#line 2265 "yacc_sql.tab.c"
    break;

  case 123: /* condition: value comOp value  */
#line 749 "yacc_sql.y"
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
#line 2290 "yacc_sql.tab.c"
    break;

  case 124: /* condition: ID comOp ID  */
#line 770 "yacc_sql.y"
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
#line 2315 "yacc_sql.tab.c"
    break;

  case 125: /* condition: value comOp ID  */
#line 791 "yacc_sql.y"
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
#line 2342 "yacc_sql.tab.c"
    break;

  case 126: /* condition: ID DOT ID comOp value  */
#line 814 "yacc_sql.y"
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
#line 2368 "yacc_sql.tab.c"
    break;

  case 127: /* condition: value comOp ID DOT ID  */
#line 836 "yacc_sql.y"
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
#line 2394 "yacc_sql.tab.c"
    break;

  case 128: /* condition: ID DOT ID comOp ID DOT ID  */
#line 858 "yacc_sql.y"
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
#line 2418 "yacc_sql.tab.c"
    break;

  case 129: /* condition: ID comOp subselect  */
#line 878 "yacc_sql.y"
        {
		RelAttr left_attr;
		relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));

		value_init_subselect(&CONTEXT->values[CONTEXT->value_length++]);
		Condition condition;
		condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 0, NULL, &(CONTEXT->values[CONTEXT->value_length - 1]));
		selects_append_condition(&CONTEXT->ssql->sstr.selection, &condition, CONTEXT->condition_level);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;


	}
#line 2435 "yacc_sql.tab.c"
    break;

  case 130: /* condition: ID DOT ID comOp subselect  */
#line 891 "yacc_sql.y"
        {
		
		RelAttr left_attr;
		relation_attr_init(&left_attr, (yyvsp[-4].string), (yyvsp[-2].string));

		value_init_subselect(&CONTEXT->values[CONTEXT->value_length++]);
		Condition condition;
		condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 0, NULL, &(CONTEXT->values[CONTEXT->value_length - 1]));
		selects_append_condition(&CONTEXT->ssql->sstr.selection, &condition, CONTEXT->condition_level);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
	}
#line 2451 "yacc_sql.tab.c"
    break;

  case 131: /* condition: subselect comOp ID  */
#line 903 "yacc_sql.y"
        {
		RelAttr left_attr;
		relation_attr_init(&left_attr, NULL, (yyvsp[0].string));

		value_init_subselect(&CONTEXT->values[CONTEXT->value_length++]);
		Condition condition;
		condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 0, NULL, &(CONTEXT->values[CONTEXT->value_length - 1]));
		selects_append_condition(&CONTEXT->ssql->sstr.selection, &condition, CONTEXT->condition_level);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
	}
#line 2466 "yacc_sql.tab.c"
    break;

  case 132: /* condition: subselect comOp ID DOT ID  */
#line 914 "yacc_sql.y"
        {
		RelAttr left_attr;
		relation_attr_init(&left_attr, (yyvsp[-2].string), (yyvsp[0].string));

		value_init_subselect(&CONTEXT->values[CONTEXT->value_length++]);
		Condition condition;
		condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 0, NULL, &(CONTEXT->values[CONTEXT->value_length - 1]));
		selects_append_condition(&CONTEXT->ssql->sstr.selection, &condition, CONTEXT->condition_level);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
	}
#line 2481 "yacc_sql.tab.c"
    break;

  case 133: /* comOp: EQ  */
#line 926 "yacc_sql.y"
         { CONTEXT->comp = EQUAL_TO; }
#line 2487 "yacc_sql.tab.c"
    break;

  case 134: /* comOp: LT  */
#line 927 "yacc_sql.y"
         { CONTEXT->comp = LESS_THAN; }
#line 2493 "yacc_sql.tab.c"
    break;

  case 135: /* comOp: GT  */
#line 928 "yacc_sql.y"
         { CONTEXT->comp = GREAT_THAN; }
#line 2499 "yacc_sql.tab.c"
    break;

  case 136: /* comOp: LE  */
#line 929 "yacc_sql.y"
         { CONTEXT->comp = LESS_EQUAL; }
#line 2505 "yacc_sql.tab.c"
    break;

  case 137: /* comOp: GE  */
#line 930 "yacc_sql.y"
         { CONTEXT->comp = GREAT_EQUAL; }
#line 2511 "yacc_sql.tab.c"
    break;

  case 138: /* comOp: NE  */
#line 931 "yacc_sql.y"
         { CONTEXT->comp = NOT_EQUAL; }
#line 2517 "yacc_sql.tab.c"
    break;

  case 139: /* comOp: IS NOT  */
#line 932 "yacc_sql.y"
             {CONTEXT->comp = OP_IS_NOT; }
#line 2523 "yacc_sql.tab.c"
    break;

  case 140: /* comOp: IS  */
#line 933 "yacc_sql.y"
         {CONTEXT->comp = OP_IS; }
#line 2529 "yacc_sql.tab.c"
    break;

  case 141: /* comOp: IN  */
#line 934 "yacc_sql.y"
             { CONTEXT->comp = OP_IN; }
#line 2535 "yacc_sql.tab.c"
    break;

  case 142: /* comOp: NOT IN  */
#line 935 "yacc_sql.y"
                 {CONTEXT->comp = OP_NOT_IN; }
#line 2541 "yacc_sql.tab.c"
    break;

  case 143: /* load_data: LOAD DATA INFILE SSS INTO TABLE ID SEMICOLON  */
#line 940 "yacc_sql.y"
                {
		  CONTEXT->ssql->flag = SCF_LOAD_DATA;
			load_data_init(&CONTEXT->ssql->sstr.load_data, (yyvsp[-1].string), (yyvsp[-4].string));
		}
#line 2550 "yacc_sql.tab.c"
    break;


#line 2554 "yacc_sql.tab.c"

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

#line 945 "yacc_sql.y"

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
