/* A Bison parser, made by GNU Bison 3.7.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
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
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.7.1"

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
  YYSYMBOL_ADD = 70,                       /* ADD  */
  YYSYMBOL_MINUS = 71,                     /* MINUS  */
  YYSYMBOL_DIV = 72,                       /* DIV  */
  YYSYMBOL_YYACCEPT = 73,                  /* $accept  */
  YYSYMBOL_commands = 74,                  /* commands  */
  YYSYMBOL_command = 75,                   /* command  */
  YYSYMBOL_exit = 76,                      /* exit  */
  YYSYMBOL_help = 77,                      /* help  */
  YYSYMBOL_sync = 78,                      /* sync  */
  YYSYMBOL_begin = 79,                     /* begin  */
  YYSYMBOL_commit = 80,                    /* commit  */
  YYSYMBOL_rollback = 81,                  /* rollback  */
  YYSYMBOL_drop_table = 82,                /* drop_table  */
  YYSYMBOL_show_tables = 83,               /* show_tables  */
  YYSYMBOL_desc_table = 84,                /* desc_table  */
  YYSYMBOL_create_index = 85,              /* create_index  */
  YYSYMBOL_field_list = 86,                /* field_list  */
  YYSYMBOL_field = 87,                     /* field  */
  YYSYMBOL_drop_index = 88,                /* drop_index  */
  YYSYMBOL_create_table = 89,              /* create_table  */
  YYSYMBOL_attr_def_list = 90,             /* attr_def_list  */
  YYSYMBOL_attr_def = 91,                  /* attr_def  */
  YYSYMBOL_null_value = 92,                /* null_value  */
  YYSYMBOL_number = 93,                    /* number  */
  YYSYMBOL_type = 94,                      /* type  */
  YYSYMBOL_ID_get = 95,                    /* ID_get  */
  YYSYMBOL_insert = 96,                    /* insert  */
  YYSYMBOL_row_list = 97,                  /* row_list  */
  YYSYMBOL_row = 98,                       /* row  */
  YYSYMBOL_value_list = 99,                /* value_list  */
  YYSYMBOL_value = 100,                    /* value  */
  YYSYMBOL_delete = 101,                   /* delete  */
  YYSYMBOL_update = 102,                   /* update  */
  YYSYMBOL_select = 103,                   /* select  */
  YYSYMBOL_subselect = 104,                /* subselect  */
  YYSYMBOL_pushdown = 105,                 /* pushdown  */
  YYSYMBOL_pushup = 106,                   /* pushup  */
  YYSYMBOL_select_attr = 107,              /* select_attr  */
  YYSYMBOL_attr_list = 108,                /* attr_list  */
  YYSYMBOL_select_from = 109,              /* select_from  */
  YYSYMBOL_rel_list = 110,                 /* rel_list  */
  YYSYMBOL_select_join = 111,              /* select_join  */
  YYSYMBOL_join_list = 112,                /* join_list  */
  YYSYMBOL_where = 113,                    /* where  */
  YYSYMBOL_opt_group = 114,                /* opt_group  */
  YYSYMBOL_column_ref_commalist = 115,     /* column_ref_commalist  */
  YYSYMBOL_column_ref = 116,               /* column_ref  */
  YYSYMBOL_opt_order = 117,                /* opt_order  */
  YYSYMBOL_order_list = 118,               /* order_list  */
  YYSYMBOL_orderby = 119,                  /* orderby  */
  YYSYMBOL_opt_order_type = 120,           /* opt_order_type  */
  YYSYMBOL_condition_list = 121,           /* condition_list  */
  YYSYMBOL_condition = 122,                /* condition  */
  YYSYMBOL_expression_cluster = 123,       /* expression_cluster  */
  YYSYMBOL_expression = 124,               /* expression  */
  YYSYMBOL_primary_expression = 125,       /* primary_expression  */
  YYSYMBOL_comOp = 126,                    /* comOp  */
  YYSYMBOL_load_data = 127                 /* load_data  */
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
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
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
#define YYLAST   354

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  73
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  55
/* YYNRULES -- Number of rules.  */
#define YYNRULES  155
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  347

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   327


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
      65,    66,    67,    68,    69,    70,    71,    72
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   187,   187,   189,   193,   194,   195,   196,   197,   198,
     199,   200,   201,   202,   203,   204,   205,   206,   207,   208,
     209,   213,   218,   223,   229,   235,   241,   247,   253,   259,
     267,   272,   278,   280,   285,   291,   298,   307,   309,   313,
     325,   338,   339,   342,   347,   350,   351,   352,   353,   354,
     357,   366,   383,   384,   389,   394,   396,   401,   404,   407,
     410,   414,   421,   431,   442,   460,   473,   490,   496,   502,
     508,   514,   519,   525,   532,   538,   544,   550,   556,   562,
     568,   574,   580,   587,   590,   592,   595,   602,   609,   614,
     619,   624,   629,   634,   639,   644,   649,   655,   657,   663,
     665,   669,   671,   677,   679,   683,   685,   688,   689,   693,
     694,   698,   703,   711,   713,   716,   717,   719,   720,   725,
     732,   733,   734,   737,   739,   743,   765,   786,   807,   830,
     852,   874,   894,   907,   919,   929,   933,   939,   946,   952,
     960,   966,   974,   982,   990,  1007,  1008,  1009,  1010,  1011,
    1012,  1013,  1014,  1015,  1016,  1020
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
  "FLOAT", "DATE", "ID", "PATH", "SSS", "STAR", "STRING_V", "ADD", "MINUS",
  "DIV", "$accept", "commands", "command", "exit", "help", "sync", "begin",
  "commit", "rollback", "drop_table", "show_tables", "desc_table",
  "create_index", "field_list", "field", "drop_index", "create_table",
  "attr_def_list", "attr_def", "null_value", "number", "type", "ID_get",
  "insert", "row_list", "row", "value_list", "value", "delete", "update",
  "select", "subselect", "pushdown", "pushup", "select_attr", "attr_list",
  "select_from", "rel_list", "select_join", "join_list", "where",
  "opt_group", "column_ref_commalist", "column_ref", "opt_order",
  "order_list", "orderby", "opt_order_type", "condition_list", "condition",
  "expression_cluster", "expression", "primary_expression", "comOp",
  "load_data", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327
};
#endif

#define YYPACT_NINF (-258)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-143)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -258,    87,  -258,    11,   129,     3,   -39,    25,    50,    22,
      31,    20,    91,   112,   119,   125,   135,    99,  -258,  -258,
    -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,
    -258,  -258,  -258,  -258,  -258,  -258,    89,    98,   170,   121,
     128,   136,   169,   176,   190,    82,  -258,  -258,     2,  -258,
     178,   197,   142,  -258,   223,   224,  -258,   163,   164,   184,
    -258,  -258,  -258,  -258,  -258,   181,   206,   186,   171,   231,
     232,   -37,   172,   173,   174,   200,   214,    13,   177,  -258,
     179,  -258,    82,    82,    82,    82,  -258,  -258,   201,   202,
     180,   182,   183,   185,   204,  -258,  -258,    -3,   220,     0,
      61,    73,   187,  -258,   227,   228,   233,   234,    55,   197,
       4,     8,   202,   202,  -258,  -258,  -258,  -258,   235,   -13,
     259,   208,   225,  -258,   236,   139,   239,   203,   197,   205,
     197,   197,   207,   197,   209,   197,   210,  -258,    -1,   211,
     212,   213,   215,  -258,  -258,  -258,   256,   216,  -258,  -258,
      83,   249,   134,   243,  -258,   147,   152,  -258,   109,  -258,
     148,   237,   148,  -258,   134,   261,   183,   252,  -258,  -258,
    -258,  -258,  -258,    -9,   218,   258,  -258,   260,  -258,  -258,
     262,  -258,   263,  -258,   264,    93,   265,    96,    97,   100,
       4,   221,   257,   271,   277,   277,  -258,  -258,   266,   235,
     292,   238,   244,   240,  -258,  -258,  -258,  -258,  -258,  -258,
    -258,    67,   127,   -13,  -258,     7,   202,   241,   236,   294,
     242,   245,  -258,  -258,  -258,   270,   218,   197,   197,   197,
     197,   197,   246,   197,   197,   247,   197,   248,   197,   250,
    -258,   253,  -258,   251,   285,   302,   304,   134,   281,   243,
    -258,   148,  -258,  -258,  -258,  -258,  -258,  -258,   295,   269,
    -258,   237,  -258,   311,   314,  -258,  -258,  -258,   291,  -258,
     218,   293,   270,  -258,  -258,  -258,  -258,  -258,   296,  -258,
    -258,   297,  -258,   298,  -258,   299,   -13,   279,   300,  -258,
     267,  -258,  -258,   266,  -258,  -258,    88,   303,   268,  -258,
    -258,  -258,    37,   270,   318,   307,   197,   197,   197,   197,
     237,   272,   251,    16,   301,  -258,   282,  -258,  -258,  -258,
    -258,  -258,  -258,  -258,  -258,   324,  -258,  -258,  -258,  -258,
     321,  -258,  -258,  -258,  -258,   273,  -258,   267,  -258,   274,
    -258,  -258,    86,   301,  -258,  -258,  -258
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     1,     0,     0,    83,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     3,    20,
      19,    14,    15,    16,    17,     9,    10,    11,    12,    13,
       8,     5,     7,     6,     4,    18,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   141,   142,   143,    70,
       0,    84,     0,   140,     0,     0,    23,     0,     0,     0,
      24,    25,    26,    22,    21,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   143,     0,     0,     0,    72,
      97,    71,     0,     0,     0,     0,    29,    28,     0,   105,
       0,     0,     0,     0,     0,    27,    35,     0,     0,     0,
       0,     0,     0,   135,     0,     0,     0,     0,   143,    84,
     144,    99,   105,   105,   136,   138,   139,   137,     0,     0,
       0,     0,     0,    50,    37,     0,     0,     0,    84,     0,
      84,    84,     0,    84,     0,    84,     0,   144,     0,     0,
       0,     0,     0,    86,    85,    73,     0,     0,    98,   102,
      66,   107,     0,    52,    57,    58,    59,    60,   143,    61,
       0,   123,     0,    62,     0,     0,     0,     0,    45,    46,
      47,    48,    49,    41,     0,     0,    75,     0,    74,    77,
       0,    79,     0,    81,     0,     0,     0,     0,     0,     0,
     144,     0,    99,     0,   113,   113,    58,    59,    55,     0,
       0,     0,   152,     0,   145,   146,   147,   148,   149,   150,
     153,     0,     0,     0,   106,     0,   105,     0,    37,     0,
       0,     0,    42,    40,    34,    32,     0,    84,    84,    84,
      84,    84,     0,    84,    84,     0,    84,     0,    84,     0,
      87,     0,   100,     0,     0,     0,     0,     0,     0,    52,
      51,   144,   151,   154,    68,   127,   125,   132,     0,   128,
     126,   123,   134,     0,     0,    38,    36,    44,     0,    43,
       0,     0,    32,    76,    78,    80,    82,    89,     0,    88,
      91,     0,    93,     0,    95,     0,     0,   111,   108,   109,
     117,    64,    65,    55,    54,    53,     0,     0,     0,   124,
      63,   155,    41,    32,     0,     0,    84,    84,    84,    84,
     123,     0,     0,   122,   115,    56,     0,   129,   133,    69,
      67,   130,    39,    33,    30,     0,    90,    92,    94,    96,
     103,   112,   110,   120,   121,     0,   118,   117,   114,     0,
      31,   104,   122,   115,   131,   119,   116
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,  -258,
    -258,  -258,  -258,  -257,  -210,  -258,  -258,   117,   175,    34,
    -258,  -258,  -258,  -258,    94,   141,    49,  -150,  -258,  -258,
      90,    48,  -258,  -258,  -258,   -51,  -258,   153,  -258,    17,
    -109,   195,  -258,    38,   154,     9,    14,    12,  -255,  -205,
      -4,    74,  -258,  -155,  -258
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,   271,   225,    29,    30,   167,   124,   223,
     268,   173,   125,    31,   200,   153,   248,   160,    32,    33,
      34,   257,   258,   320,    50,    79,   112,   148,   113,   149,
     120,   194,   288,   289,   245,   338,   314,   336,   214,   161,
     162,    52,    53,   211,    35
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      81,    51,   198,   150,   151,   212,   299,   215,   261,    41,
      42,    43,    44,    45,   216,   305,   272,   220,   146,   104,
     105,   106,   107,    36,   128,    37,    54,   131,    97,    45,
      77,    98,    77,    45,   333,   334,   147,   129,    55,    45,
     132,   154,    78,   221,   222,   -84,   323,   -84,    38,   155,
     156,   157,   158,    56,   159,   330,   335,   143,   144,   145,
     303,   256,   260,    57,   185,    46,    47,   186,    48,    46,
      47,    49,    75,   109,    58,    46,    47,   176,   108,   178,
     179,   310,   181,    77,   183,    59,  -107,     2,   133,   221,
     222,     3,     4,   254,    60,   142,   296,   293,   -84,  -107,
     135,   134,     5,   193,   333,   334,     6,   263,     7,     8,
       9,    10,    11,   136,   254,    61,    12,    13,    14,    76,
     231,   154,    62,   234,   236,    15,    16,   238,    63,   196,
     197,   157,   255,   232,   159,    17,   235,   237,    64,   240,
     239,    39,   154,    40,    46,    47,   317,    75,    65,   201,
     196,   197,   157,   316,    66,   159,   114,   115,   116,   117,
     202,   203,    71,    67,   204,   205,   206,   207,   208,   209,
     210,   168,   169,   170,   171,   172,   273,   274,   275,   276,
     277,   154,   279,   280,    68,   282,    69,   284,   154,   196,
     197,   157,   259,    70,   159,    72,   196,   197,   157,   202,
     203,   159,    73,   204,   205,   206,   207,   208,   209,   210,
      82,   262,    83,    84,    85,  -141,    74,  -141,  -141,  -141,
    -142,    80,  -142,  -142,  -142,    77,    86,    87,    88,    89,
      90,    91,    92,    93,    95,    96,    94,    99,   100,   101,
     102,   103,   110,   118,   111,   121,   119,   130,   123,   122,
     126,   127,   137,   138,   139,   326,   327,   328,   329,   140,
     141,   152,   163,   164,   166,   174,   165,   191,   175,   193,
     177,   199,   180,   217,   182,   184,   187,   188,   189,   219,
     190,   192,   213,   224,   226,   147,   241,   227,   243,   228,
     229,   230,   233,   244,   247,   250,   252,   266,   270,   269,
     286,   253,   290,   251,   267,   291,   264,   292,   294,   298,
       5,   278,   281,   283,   300,   285,   287,   301,   302,   311,
     304,   324,   339,   306,   307,   308,   309,   340,   312,   337,
     319,   146,   313,   321,   325,   265,   322,   331,   342,   344,
     249,   218,   315,   295,   318,   242,   195,   341,   297,   246,
     332,   343,   346,     0,   345
};

static const yytype_int16 yycheck[] =
{
      51,     5,   152,   112,   113,   160,   261,   162,   213,     6,
       7,     8,     9,    26,   164,   272,   226,    26,    10,     6,
       7,     8,     9,    12,    27,    14,    65,    27,    65,    26,
      28,    68,    28,    26,    18,    19,    28,    40,    13,    26,
      40,    54,    40,    52,    53,    43,   303,    43,    37,    62,
      63,    64,    65,     3,    67,   310,    40,   108,   109,   110,
     270,   211,   212,    41,    65,    62,    63,    68,    65,    62,
      63,    68,    65,    77,    43,    62,    63,   128,    65,   130,
     131,   286,   133,    28,   135,    65,     3,     0,    27,    52,
      53,     4,     5,    26,     3,    40,   251,   247,    43,    16,
      27,    40,    15,    20,    18,    19,    19,   216,    21,    22,
      23,    24,    25,    40,    26,     3,    29,    30,    31,    45,
      27,    54,     3,    27,    27,    38,    39,    27,     3,    62,
      63,    64,    65,    40,    67,    48,    40,    40,     3,   190,
      40,    12,    54,    14,    62,    63,   296,    65,    49,    40,
      62,    63,    64,    65,    65,    67,    82,    83,    84,    85,
      51,    52,    26,    65,    55,    56,    57,    58,    59,    60,
      61,    32,    33,    34,    35,    36,   227,   228,   229,   230,
     231,    54,   233,   234,    14,   236,    65,   238,    54,    62,
      63,    64,    65,    65,    67,    26,    62,    63,    64,    51,
      52,    67,    26,    55,    56,    57,    58,    59,    60,    61,
      68,   215,    70,    71,    72,    68,    26,    70,    71,    72,
      68,    43,    70,    71,    72,    28,     3,     3,    65,    65,
      46,    50,    26,    47,     3,     3,    65,    65,    65,    65,
      40,    27,    65,    42,    65,    65,    44,    27,    65,    67,
      65,    47,    65,    26,    26,   306,   307,   308,   309,    26,
      26,    26,     3,    55,    28,    26,    41,    11,    65,    20,
      65,    28,    65,    12,    65,    65,    65,    65,    65,    27,
      65,    65,    45,    65,    26,    28,    65,    27,    17,    27,
      27,    27,    27,    16,    28,     3,    52,     3,    28,    54,
      47,    61,    17,    65,    62,     3,    65,     3,    27,    40,
      15,    65,    65,    65,     3,    65,    65,     3,    27,    40,
      27,     3,    40,    27,    27,    27,    27,     3,    28,    28,
      27,    10,    65,    65,    27,   218,   302,    65,    65,    65,
     199,   166,   293,   249,   296,   192,   151,   330,   258,   195,
     312,   337,   343,    -1,   342
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    74,     0,     4,     5,    15,    19,    21,    22,    23,
      24,    25,    29,    30,    31,    38,    39,    48,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    88,
      89,    96,   101,   102,   103,   127,    12,    14,    37,    12,
      14,     6,     7,     8,     9,    26,    62,    63,    65,    68,
     107,   123,   124,   125,    65,    13,     3,    41,    43,    65,
       3,     3,     3,     3,     3,    49,    65,    65,    14,    65,
      65,    26,    26,    26,    26,    65,   124,    28,    40,   108,
      43,   108,    68,    70,    71,    72,     3,     3,    65,    65,
      46,    50,    26,    47,    65,     3,     3,    65,    68,    65,
      65,    65,    40,    27,     6,     7,     8,     9,    65,   123,
      65,    65,   109,   111,   124,   124,   124,   124,    42,    44,
     113,    65,    67,    65,    91,    95,    65,    47,    27,    40,
      27,    27,    40,    27,    40,    27,    40,    65,    26,    26,
      26,    26,    40,   108,   108,   108,    10,    28,   110,   112,
     113,   113,    26,    98,    54,    62,    63,    64,    65,    67,
     100,   122,   123,     3,    55,    41,    28,    90,    32,    33,
      34,    35,    36,    94,    26,    65,   108,    65,   108,   108,
      65,   108,    65,   108,    65,    65,    68,    65,    65,    65,
      65,    11,    65,    20,   114,   114,    62,    63,   100,    28,
      97,    40,    51,    52,    55,    56,    57,    58,    59,    60,
      61,   126,   126,    45,   121,   126,   100,    12,    91,    27,
      26,    52,    53,    92,    65,    87,    26,    27,    27,    27,
      27,    27,    40,    27,    27,    40,    27,    40,    27,    40,
     108,    65,   110,    17,    16,   117,   117,    28,    99,    98,
       3,    65,    52,    61,    26,    65,   100,   104,   105,    65,
     100,   122,   123,   113,    65,    90,     3,    62,    93,    54,
      28,    86,    87,   108,   108,   108,   108,   108,    65,   108,
     108,    65,   108,    65,   108,    65,    47,    65,   115,   116,
      17,     3,     3,   100,    27,    97,   126,   103,    40,   121,
       3,     3,    27,    87,    27,    86,    27,    27,    27,    27,
     122,    40,    28,    65,   119,    99,    65,   100,   104,    27,
     106,    65,    92,    86,     3,    27,   108,   108,   108,   108,
     121,    65,   116,    18,    19,    40,   120,    28,   118,    40,
       3,   112,    65,   119,    65,   120,   118
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    73,    74,    74,    75,    75,    75,    75,    75,    75,
      75,    75,    75,    75,    75,    75,    75,    75,    75,    75,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    85,    86,    86,    87,    88,    89,    90,    90,    91,
      91,    92,    92,    92,    93,    94,    94,    94,    94,    94,
      95,    96,    97,    97,    98,    99,    99,   100,   100,   100,
     100,   100,   101,   102,   103,   103,   103,   104,   105,   106,
     107,   107,   107,   107,   107,   107,   107,   107,   107,   107,
     107,   107,   107,   107,   108,   108,   108,   108,   108,   108,
     108,   108,   108,   108,   108,   108,   108,   109,   109,   110,
     110,   111,   111,   112,   112,   113,   113,   114,   114,   115,
     115,   116,   116,   117,   117,   118,   118,   119,   119,   119,
     120,   120,   120,   121,   121,   122,   122,   122,   122,   122,
     122,   122,   122,   122,   122,   123,   123,   123,   123,   123,
     124,   125,   125,   125,   125,   126,   126,   126,   126,   126,
     126,   126,   126,   126,   126,   127
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     2,     2,     2,     2,     2,     4,     3,     3,
      10,    11,     0,     3,     1,     4,     8,     0,     3,     6,
       3,     0,     1,     2,     1,     1,     1,     1,     1,     1,
       1,     7,     0,     3,     4,     0,     3,     1,     1,     1,
       1,     1,     5,     8,     8,     8,     5,     3,     1,     1,
       1,     2,     2,     4,     5,     5,     7,     5,     7,     5,
       7,     5,     7,     0,     0,     3,     3,     5,     6,     6,
       8,     6,     8,     6,     8,     6,     8,     0,     2,     0,
       3,     0,     2,     0,     7,     0,     3,     0,     3,     1,
       3,     1,     3,     0,     4,     0,     3,     0,     2,     4,
       1,     1,     0,     0,     3,     3,     3,     3,     3,     5,
       5,     7,     3,     5,     3,     3,     3,     3,     3,     3,
       1,     1,     1,     1,     3,     1,     1,     1,     1,     1,
       1,     2,     1,     1,     2,     8
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


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

/* This macro is provided for backward compatibility. */
# ifndef YY_LOCATION_PRINT
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif


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
  YYUSE (yyoutput);
  YYUSE (scanner);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yykind < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yykind], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yykind);
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
  YYUSE (yyvaluep);
  YYUSE (scanner);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yykind);
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
    goto yyexhaustedlab;
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
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
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
#line 213 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_EXIT;//"exit";
    }
#line 1512 "yacc_sql.tab.c"
    break;

  case 22: /* help: HELP SEMICOLON  */
#line 218 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_HELP;//"help";
    }
#line 1520 "yacc_sql.tab.c"
    break;

  case 23: /* sync: SYNC SEMICOLON  */
#line 223 "yacc_sql.y"
                   {
      CONTEXT->ssql->flag = SCF_SYNC;
    }
#line 1528 "yacc_sql.tab.c"
    break;

  case 24: /* begin: TRX_BEGIN SEMICOLON  */
#line 229 "yacc_sql.y"
                        {
      CONTEXT->ssql->flag = SCF_BEGIN;
    }
#line 1536 "yacc_sql.tab.c"
    break;

  case 25: /* commit: TRX_COMMIT SEMICOLON  */
#line 235 "yacc_sql.y"
                         {
      CONTEXT->ssql->flag = SCF_COMMIT;
    }
#line 1544 "yacc_sql.tab.c"
    break;

  case 26: /* rollback: TRX_ROLLBACK SEMICOLON  */
#line 241 "yacc_sql.y"
                           {
      CONTEXT->ssql->flag = SCF_ROLLBACK;
    }
#line 1552 "yacc_sql.tab.c"
    break;

  case 27: /* drop_table: DROP TABLE ID SEMICOLON  */
#line 247 "yacc_sql.y"
                            {
        CONTEXT->ssql->flag = SCF_DROP_TABLE;//"drop_table";
        drop_table_init(&CONTEXT->ssql->sstr.drop_table, (yyvsp[-1].string));
    }
#line 1561 "yacc_sql.tab.c"
    break;

  case 28: /* show_tables: SHOW TABLES SEMICOLON  */
#line 253 "yacc_sql.y"
                          {
      CONTEXT->ssql->flag = SCF_SHOW_TABLES;
    }
#line 1569 "yacc_sql.tab.c"
    break;

  case 29: /* desc_table: DESC ID SEMICOLON  */
#line 259 "yacc_sql.y"
                      {
      CONTEXT->ssql->flag = SCF_DESC_TABLE;
      desc_table_init(&CONTEXT->ssql->sstr.desc_table, (yyvsp[-1].string));
    }
#line 1578 "yacc_sql.tab.c"
    break;

  case 30: /* create_index: CREATE INDEX ID ON ID LBRACE field field_list RBRACE SEMICOLON  */
#line 268 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-7].string), (yyvsp[-5].string), CONTEXT->field_names, CONTEXT->index_field_num, 0);
		}
#line 1587 "yacc_sql.tab.c"
    break;

  case 31: /* create_index: CREATE UNIQUE INDEX ID ON ID LBRACE field field_list RBRACE SEMICOLON  */
#line 273 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-7].string), (yyvsp[-5].string), CONTEXT->field_names, CONTEXT->index_field_num, 1);
                }
#line 1596 "yacc_sql.tab.c"
    break;

  case 33: /* field_list: COMMA field field_list  */
#line 280 "yacc_sql.y"
                               {

    	}
#line 1604 "yacc_sql.tab.c"
    break;

  case 34: /* field: ID  */
#line 285 "yacc_sql.y"
          {
    		CONTEXT->field_names[CONTEXT->index_field_num++]=(yyvsp[0].string);
    	}
#line 1612 "yacc_sql.tab.c"
    break;

  case 35: /* drop_index: DROP INDEX ID SEMICOLON  */
#line 292 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_DROP_INDEX;//"drop_index";
			drop_index_init(&CONTEXT->ssql->sstr.drop_index, (yyvsp[-1].string));
		}
#line 1621 "yacc_sql.tab.c"
    break;

  case 36: /* create_table: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE SEMICOLON  */
#line 299 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_CREATE_TABLE;//"create_table";
			// CONTEXT->ssql->sstr.create_table.attribute_count = CONTEXT->value_length;
			create_table_init_name(&CONTEXT->ssql->sstr.create_table, (yyvsp[-5].string));
			//临时变量清零
			CONTEXT->value_length = 0;
		}
#line 1633 "yacc_sql.tab.c"
    break;

  case 38: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 309 "yacc_sql.y"
                                   {    }
#line 1639 "yacc_sql.tab.c"
    break;

  case 39: /* attr_def: ID_get type LBRACE number RBRACE null_value  */
#line 314 "yacc_sql.y"
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
#line 1655 "yacc_sql.tab.c"
    break;

  case 40: /* attr_def: ID_get type null_value  */
#line 326 "yacc_sql.y"
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
#line 1671 "yacc_sql.tab.c"
    break;

  case 42: /* null_value: NULLABLE  */
#line 339 "yacc_sql.y"
                 {
		CONTEXT->nullable = true;
	}
#line 1679 "yacc_sql.tab.c"
    break;

  case 43: /* null_value: NOT NULL_T  */
#line 342 "yacc_sql.y"
                   {

	}
#line 1687 "yacc_sql.tab.c"
    break;

  case 44: /* number: NUMBER  */
#line 347 "yacc_sql.y"
                       {(yyval.number) = (yyvsp[0].number);}
#line 1693 "yacc_sql.tab.c"
    break;

  case 45: /* type: INT_T  */
#line 350 "yacc_sql.y"
              { (yyval.number)=INTS; }
#line 1699 "yacc_sql.tab.c"
    break;

  case 46: /* type: STRING_T  */
#line 351 "yacc_sql.y"
                  { (yyval.number)=CHARS; }
#line 1705 "yacc_sql.tab.c"
    break;

  case 47: /* type: FLOAT_T  */
#line 352 "yacc_sql.y"
                 { (yyval.number)=FLOATS; }
#line 1711 "yacc_sql.tab.c"
    break;

  case 48: /* type: DATE_T  */
#line 353 "yacc_sql.y"
                { (yyval.number)=DATES; }
#line 1717 "yacc_sql.tab.c"
    break;

  case 49: /* type: TEXT_T  */
#line 354 "yacc_sql.y"
                { (yyval.number)=TEXTS; }
#line 1723 "yacc_sql.tab.c"
    break;

  case 50: /* ID_get: ID  */
#line 358 "yacc_sql.y"
        {
		char *temp=(yyvsp[0].string);
		snprintf(CONTEXT->id, sizeof(CONTEXT->id), "%s", temp);
	}
#line 1732 "yacc_sql.tab.c"
    break;

  case 51: /* insert: INSERT INTO ID VALUES row row_list SEMICOLON  */
#line 367 "yacc_sql.y"
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
#line 1752 "yacc_sql.tab.c"
    break;

  case 53: /* row_list: COMMA row row_list  */
#line 384 "yacc_sql.y"
                                {
	}
#line 1759 "yacc_sql.tab.c"
    break;

  case 54: /* row: LBRACE value value_list RBRACE  */
#line 389 "yacc_sql.y"
                                        {
		CONTEXT->row_end[CONTEXT->row_num++]=CONTEXT->value_length;
	}
#line 1767 "yacc_sql.tab.c"
    break;

  case 56: /* value_list: COMMA value value_list  */
#line 396 "yacc_sql.y"
                              {
  		// CONTEXT->values[CONTEXT->value_length++] = *$2;
	  }
#line 1775 "yacc_sql.tab.c"
    break;

  case 57: /* value: NULL_T  */
#line 401 "yacc_sql.y"
          {
		value_init_null(&CONTEXT->values[CONTEXT->value_length++]);
	}
#line 1783 "yacc_sql.tab.c"
    break;

  case 58: /* value: NUMBER  */
#line 404 "yacc_sql.y"
           {
  		value_init_integer(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].number));
		}
#line 1791 "yacc_sql.tab.c"
    break;

  case 59: /* value: FLOAT  */
#line 407 "yacc_sql.y"
          {
  		value_init_float(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].floats));
		}
#line 1799 "yacc_sql.tab.c"
    break;

  case 60: /* value: DATE  */
#line 410 "yacc_sql.y"
          {
    			(yyvsp[0].string) = substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      		value_init_date(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].string));
    		}
#line 1808 "yacc_sql.tab.c"
    break;

  case 61: /* value: SSS  */
#line 414 "yacc_sql.y"
         {
			(yyvsp[0].string) = substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
  		value_init_string(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].string));
		}
#line 1817 "yacc_sql.tab.c"
    break;

  case 62: /* delete: DELETE FROM ID where SEMICOLON  */
#line 422 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_DELETE;//"delete";
			deletes_init_relation(&CONTEXT->ssql->sstr.deletion, (yyvsp[-2].string));
			deletes_set_conditions(&CONTEXT->ssql->sstr.deletion,
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;
    }
#line 1829 "yacc_sql.tab.c"
    break;

  case 63: /* update: UPDATE ID SET ID EQ value where SEMICOLON  */
#line 432 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_UPDATE;//"update";
			Value *value = &CONTEXT->values[0];
			updates_init(&CONTEXT->ssql->sstr.update, (yyvsp[-6].string), (yyvsp[-4].string), value,
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;
		}
#line 1841 "yacc_sql.tab.c"
    break;

  case 64: /* select: SELECT select_attr FROM select_from where opt_group opt_order SEMICOLON  */
#line 443 "yacc_sql.y"
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
#line 1862 "yacc_sql.tab.c"
    break;

  case 65: /* select: SELECT select_attr FROM select_join where opt_group opt_order SEMICOLON  */
#line 461 "yacc_sql.y"
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
#line 1879 "yacc_sql.tab.c"
    break;

  case 66: /* select: SELECT select_attr FROM select_from where  */
#line 474 "yacc_sql.y"
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
#line 1898 "yacc_sql.tab.c"
    break;

  case 67: /* subselect: pushdown select pushup  */
#line 491 "yacc_sql.y"
        {
		debug_subselect();
	}
#line 1906 "yacc_sql.tab.c"
    break;

  case 68: /* pushdown: LBRACE  */
#line 496 "yacc_sql.y"
               {
		push_down();
		CONTEXT->condition_level++;
	}
#line 1915 "yacc_sql.tab.c"
    break;

  case 69: /* pushup: RBRACE  */
#line 502 "yacc_sql.y"
               {
		push_up();
		CONTEXT->condition_level--;
	}
#line 1924 "yacc_sql.tab.c"
    break;

  case 70: /* select_attr: STAR  */
#line 508 "yacc_sql.y"
             {
			RelAttr attr;
			relation_attr_init(&attr, NULL, "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr, CONTEXT->attr_level);
			CONTEXT->attr_level++;
		}
#line 1935 "yacc_sql.tab.c"
    break;

  case 71: /* select_attr: expression_cluster attr_list  */
#line 514 "yacc_sql.y"
                                      {
			selects_append_expression(&CONTEXT->ssql->sstr.selection, (yyvsp[-1].expressions), CONTEXT->attr_level);
			CONTEXT->attr_level++;
	}
#line 1944 "yacc_sql.tab.c"
    break;

  case 72: /* select_attr: ID attr_list  */
#line 519 "yacc_sql.y"
                       {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr, CONTEXT->attr_level);
			CONTEXT->attr_level++;
		}
#line 1955 "yacc_sql.tab.c"
    break;

  case 73: /* select_attr: ID DOT ID attr_list  */
#line 525 "yacc_sql.y"
                              {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr, CONTEXT->attr_level);
			CONTEXT->attr_level++;
		}
#line 1966 "yacc_sql.tab.c"
    break;

  case 74: /* select_attr: COUNT LBRACE STAR RBRACE attr_list  */
#line 532 "yacc_sql.y"
                                             {
			RelAttr attr;
			relation_attr_with_agg_init(&attr, "COUNT", NULL, "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr, CONTEXT->attr_level);
			CONTEXT->attr_level++;
		}
#line 1977 "yacc_sql.tab.c"
    break;

  case 75: /* select_attr: COUNT LBRACE ID RBRACE attr_list  */
#line 538 "yacc_sql.y"
                                           {
			RelAttr attr;
			relation_attr_with_agg_init(&attr, "COUNT", NULL, (yyvsp[-2].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr, CONTEXT->attr_level);
			CONTEXT->attr_level++;
		}
#line 1988 "yacc_sql.tab.c"
    break;

  case 76: /* select_attr: COUNT LBRACE ID DOT ID RBRACE attr_list  */
#line 544 "yacc_sql.y"
                                                  {
			RelAttr attr;
			relation_attr_with_agg_init(&attr, "COUNT", (yyvsp[-4].string), (yyvsp[-2].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr, CONTEXT->attr_level);
			CONTEXT->attr_level++;
		}
#line 1999 "yacc_sql.tab.c"
    break;

  case 77: /* select_attr: MAX LBRACE ID RBRACE attr_list  */
#line 550 "yacc_sql.y"
                                         {
			RelAttr attr;
			relation_attr_with_agg_init(&attr, "MAX", NULL, (yyvsp[-2].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr, CONTEXT->attr_level);
			CONTEXT->attr_level++;
		}
#line 2010 "yacc_sql.tab.c"
    break;

  case 78: /* select_attr: MAX LBRACE ID DOT ID RBRACE attr_list  */
#line 556 "yacc_sql.y"
                                                {
			RelAttr attr;
			relation_attr_with_agg_init(&attr, "MAX", (yyvsp[-4].string), (yyvsp[-2].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr, CONTEXT->attr_level);
			CONTEXT->attr_level++;
		}
#line 2021 "yacc_sql.tab.c"
    break;

  case 79: /* select_attr: MIN LBRACE ID RBRACE attr_list  */
#line 562 "yacc_sql.y"
                                         {
			RelAttr attr;
			relation_attr_with_agg_init(&attr, "MIN", NULL, (yyvsp[-2].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr, CONTEXT->attr_level);
			CONTEXT->attr_level++;
		}
#line 2032 "yacc_sql.tab.c"
    break;

  case 80: /* select_attr: MIN LBRACE ID DOT ID RBRACE attr_list  */
#line 568 "yacc_sql.y"
                                                {
			RelAttr attr;
			relation_attr_with_agg_init(&attr, "MIN", (yyvsp[-4].string), (yyvsp[-2].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr, CONTEXT->attr_level);
			CONTEXT->attr_level++;
		}
#line 2043 "yacc_sql.tab.c"
    break;

  case 81: /* select_attr: AVG LBRACE ID RBRACE attr_list  */
#line 574 "yacc_sql.y"
                                         {
			RelAttr attr;
			relation_attr_with_agg_init(&attr, "AVG", NULL, (yyvsp[-2].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr, CONTEXT->attr_level);
			CONTEXT->attr_level++;
		}
#line 2054 "yacc_sql.tab.c"
    break;

  case 82: /* select_attr: AVG LBRACE ID DOT ID RBRACE attr_list  */
#line 580 "yacc_sql.y"
                                                {
			RelAttr attr;
			relation_attr_with_agg_init(&attr, "AVG", (yyvsp[-4].string), (yyvsp[-2].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr, CONTEXT->attr_level);
			CONTEXT->attr_level++;
		}
#line 2065 "yacc_sql.tab.c"
    break;

  case 85: /* attr_list: COMMA expression_cluster attr_list  */
#line 592 "yacc_sql.y"
                                        {
			selects_append_expression(&CONTEXT->ssql->sstr.selection, (yyvsp[-1].expressions), CONTEXT->attr_level);
    }
#line 2073 "yacc_sql.tab.c"
    break;

  case 86: /* attr_list: COMMA ID attr_list  */
#line 595 "yacc_sql.y"
                         {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr, CONTEXT->attr_level);
     	  // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length].relation_name = NULL;
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length++].attribute_name=$2;
      }
#line 2085 "yacc_sql.tab.c"
    break;

  case 87: /* attr_list: COMMA ID DOT ID attr_list  */
#line 602 "yacc_sql.y"
                                {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr, CONTEXT->attr_level);
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length].attribute_name=$4;
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length++].relation_name=$2;
  	  }
#line 2097 "yacc_sql.tab.c"
    break;

  case 88: /* attr_list: COMMA COUNT LBRACE STAR RBRACE attr_list  */
#line 609 "yacc_sql.y"
                                                   {
			RelAttr attr;
			relation_attr_with_agg_init(&attr, "COUNT", NULL, "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr, CONTEXT->attr_level);
	  }
#line 2107 "yacc_sql.tab.c"
    break;

  case 89: /* attr_list: COMMA COUNT LBRACE ID RBRACE attr_list  */
#line 614 "yacc_sql.y"
                                                 {
			RelAttr attr;
			relation_attr_with_agg_init(&attr, "COUNT", NULL, (yyvsp[-2].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr, CONTEXT->attr_level);
	}
#line 2117 "yacc_sql.tab.c"
    break;

  case 90: /* attr_list: COMMA COUNT LBRACE ID DOT ID RBRACE attr_list  */
#line 619 "yacc_sql.y"
                                                        {
			RelAttr attr;
			relation_attr_with_agg_init(&attr, "COUNT", (yyvsp[-4].string), (yyvsp[-2].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr, CONTEXT->attr_level);
	}
#line 2127 "yacc_sql.tab.c"
    break;

  case 91: /* attr_list: COMMA MAX LBRACE ID RBRACE attr_list  */
#line 624 "yacc_sql.y"
                                               {
			RelAttr attr;
			relation_attr_with_agg_init(&attr, "MAX", NULL, (yyvsp[-2].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr, CONTEXT->attr_level);
	}
#line 2137 "yacc_sql.tab.c"
    break;

  case 92: /* attr_list: COMMA MAX LBRACE ID DOT ID RBRACE attr_list  */
#line 629 "yacc_sql.y"
                                                      {
			RelAttr attr;
			relation_attr_with_agg_init(&attr, "MAX", (yyvsp[-4].string), (yyvsp[-2].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr, CONTEXT->attr_level);
	}
#line 2147 "yacc_sql.tab.c"
    break;

  case 93: /* attr_list: COMMA MIN LBRACE ID RBRACE attr_list  */
#line 634 "yacc_sql.y"
                                               {
			RelAttr attr;
			relation_attr_with_agg_init(&attr, "MIN", NULL, (yyvsp[-2].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr, CONTEXT->attr_level);
	}
#line 2157 "yacc_sql.tab.c"
    break;

  case 94: /* attr_list: COMMA MIN LBRACE ID DOT ID RBRACE attr_list  */
#line 639 "yacc_sql.y"
                                                      {
			RelAttr attr;
			relation_attr_with_agg_init(&attr, "MIN", (yyvsp[-4].string), (yyvsp[-2].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr, CONTEXT->attr_level);
	}
#line 2167 "yacc_sql.tab.c"
    break;

  case 95: /* attr_list: COMMA AVG LBRACE ID RBRACE attr_list  */
#line 644 "yacc_sql.y"
                                               {
			RelAttr attr;
			relation_attr_with_agg_init(&attr, "AVG", NULL, (yyvsp[-2].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr, CONTEXT->attr_level);
	}
#line 2177 "yacc_sql.tab.c"
    break;

  case 96: /* attr_list: COMMA AVG LBRACE ID DOT ID RBRACE attr_list  */
#line 649 "yacc_sql.y"
                                                      {
			RelAttr attr;
			relation_attr_with_agg_init(&attr, "AVG", (yyvsp[-4].string), (yyvsp[-2].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr, CONTEXT->attr_level);
	}
#line 2187 "yacc_sql.tab.c"
    break;

  case 98: /* select_from: ID rel_list  */
#line 658 "yacc_sql.y"
        {
		selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-1].string), CONTEXT->from_level);
		CONTEXT->from_level++;
	}
#line 2196 "yacc_sql.tab.c"
    break;

  case 100: /* rel_list: COMMA ID rel_list  */
#line 665 "yacc_sql.y"
                        {
				selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-1].string), CONTEXT->from_level);
		  }
#line 2204 "yacc_sql.tab.c"
    break;

  case 102: /* select_join: ID join_list  */
#line 672 "yacc_sql.y"
        {
		selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-1].string), CONTEXT->from_level);
		CONTEXT->from_level++;
	}
#line 2213 "yacc_sql.tab.c"
    break;

  case 104: /* join_list: INNER JOIN ID ON condition condition_list join_list  */
#line 679 "yacc_sql.y"
                                                              {
		selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-4].string), CONTEXT->from_level);
	}
#line 2221 "yacc_sql.tab.c"
    break;

  case 111: /* column_ref: ID  */
#line 698 "yacc_sql.y"
                   {
		GroupByDescription group;
		relation_group_init(&group,NULL,(yyvsp[0].string));
		CONTEXT->groups[CONTEXT->group_num++] = group;
		}
#line 2231 "yacc_sql.tab.c"
    break;

  case 112: /* column_ref: ID DOT ID  */
#line 703 "yacc_sql.y"
                         {
		GroupByDescription group;
		relation_group_init(&group,(yyvsp[-2].string),(yyvsp[0].string));
		CONTEXT->groups[CONTEXT->group_num++] = group;

	}
#line 2242 "yacc_sql.tab.c"
    break;

  case 118: /* orderby: ID opt_order_type  */
#line 720 "yacc_sql.y"
                   {
	OrderDescription order;
	relation_order_init(&order, NULL, (yyvsp[-1].string), CONTEXT->order_type);
        CONTEXT->orders[CONTEXT->order_num++] = order;
}
#line 2252 "yacc_sql.tab.c"
    break;

  case 119: /* orderby: ID DOT ID opt_order_type  */
#line 725 "yacc_sql.y"
                         {
	OrderDescription order;
	relation_order_init(&order, (yyvsp[-3].string), (yyvsp[-1].string), CONTEXT->order_type);
        CONTEXT->orders[CONTEXT->order_num++] = order;
}
#line 2262 "yacc_sql.tab.c"
    break;

  case 120: /* opt_order_type: ASC  */
#line 732 "yacc_sql.y"
                     { CONTEXT->order_type = kOrderAsc; }
#line 2268 "yacc_sql.tab.c"
    break;

  case 121: /* opt_order_type: DESC  */
#line 733 "yacc_sql.y"
       { CONTEXT->order_type = kOrderDesc; }
#line 2274 "yacc_sql.tab.c"
    break;

  case 122: /* opt_order_type: %empty  */
#line 734 "yacc_sql.y"
              { CONTEXT->order_type = kOrderAsc; }
#line 2280 "yacc_sql.tab.c"
    break;

  case 125: /* condition: ID comOp value  */
#line 744 "yacc_sql.y"
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
#line 2306 "yacc_sql.tab.c"
    break;

  case 126: /* condition: value comOp value  */
#line 766 "yacc_sql.y"
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
#line 2331 "yacc_sql.tab.c"
    break;

  case 127: /* condition: ID comOp ID  */
#line 787 "yacc_sql.y"
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
#line 2356 "yacc_sql.tab.c"
    break;

  case 128: /* condition: value comOp ID  */
#line 808 "yacc_sql.y"
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
#line 2383 "yacc_sql.tab.c"
    break;

  case 129: /* condition: ID DOT ID comOp value  */
#line 831 "yacc_sql.y"
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
#line 2409 "yacc_sql.tab.c"
    break;

  case 130: /* condition: value comOp ID DOT ID  */
#line 853 "yacc_sql.y"
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
#line 2435 "yacc_sql.tab.c"
    break;

  case 131: /* condition: ID DOT ID comOp ID DOT ID  */
#line 875 "yacc_sql.y"
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
#line 2459 "yacc_sql.tab.c"
    break;

  case 132: /* condition: ID comOp subselect  */
#line 895 "yacc_sql.y"
        {
		RelAttr left_attr;
		relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));

		value_init_subselect(&CONTEXT->values[CONTEXT->value_length++]);
		Condition condition;
		condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 0, NULL, &(CONTEXT->values[CONTEXT->value_length - 1]));
		selects_append_condition(&CONTEXT->ssql->sstr.selection, &condition, CONTEXT->condition_level);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;


	}
#line 2476 "yacc_sql.tab.c"
    break;

  case 133: /* condition: ID DOT ID comOp subselect  */
#line 908 "yacc_sql.y"
        {
		
		RelAttr left_attr;
		relation_attr_init(&left_attr, (yyvsp[-4].string), (yyvsp[-2].string));

		value_init_subselect(&CONTEXT->values[CONTEXT->value_length++]);
		Condition condition;
		condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 0, NULL, &(CONTEXT->values[CONTEXT->value_length - 1]));
		selects_append_condition(&CONTEXT->ssql->sstr.selection, &condition, CONTEXT->condition_level);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
	}
#line 2492 "yacc_sql.tab.c"
    break;

  case 134: /* condition: expression_cluster comOp expression_cluster  */
#line 920 "yacc_sql.y"
        {
		Condition condition;
		condition_init_expr(&condition,(yyvsp[-2].expressions),(yyvsp[0].expressions),CONTEXT->comp);
		selects_append_condition(&CONTEXT->ssql->sstr.selection, &condition, CONTEXT->condition_level);
                CONTEXT->conditions[CONTEXT->condition_length++] = condition;
	}
#line 2503 "yacc_sql.tab.c"
    break;

  case 135: /* expression_cluster: LBRACE expression RBRACE  */
#line 930 "yacc_sql.y"
        {
		(yyval.expressions) = (yyvsp[-1].expressions);
	}
#line 2511 "yacc_sql.tab.c"
    break;

  case 136: /* expression_cluster: expression STAR expression  */
#line 934 "yacc_sql.y"
        {
		Expression *exp = malloc(sizeof(Expression));
		expression_init(exp,3,(yyvsp[-2].expressions),(yyvsp[0].expressions));
		(yyval.expressions) = exp;
	}
#line 2521 "yacc_sql.tab.c"
    break;

  case 137: /* expression_cluster: expression DIV expression  */
#line 940 "yacc_sql.y"
        {
		Expression *exp = malloc(sizeof(Expression));
		expression_init(exp,4,(yyvsp[-2].expressions),(yyvsp[0].expressions));
		(yyval.expressions) = exp;
	}
#line 2531 "yacc_sql.tab.c"
    break;

  case 138: /* expression_cluster: expression ADD expression  */
#line 947 "yacc_sql.y"
        {
		Expression *exp = malloc(sizeof(Expression));
		expression_init(exp,1,(yyvsp[-2].expressions),(yyvsp[0].expressions));
		(yyval.expressions) = exp;
	}
#line 2541 "yacc_sql.tab.c"
    break;

  case 139: /* expression_cluster: expression MINUS expression  */
#line 953 "yacc_sql.y"
        {
		Expression *exp = malloc(sizeof(Expression));
		expression_init(exp,2,(yyvsp[-2].expressions),(yyvsp[0].expressions));
		(yyval.expressions) = exp;
	}
#line 2551 "yacc_sql.tab.c"
    break;

  case 140: /* expression: primary_expression  */
#line 960 "yacc_sql.y"
                          {
		(yyval.expressions) = (yyvsp[0].expressions);
	}
#line 2559 "yacc_sql.tab.c"
    break;

  case 141: /* primary_expression: NUMBER  */
#line 967 "yacc_sql.y"
        {
		Expression *exp = malloc(sizeof(Expression));
		Value value;
		value_init_integer(&value,(yyvsp[0].number));
		expression_init_val(exp, &value);
		(yyval.expressions) = exp;
	}
#line 2571 "yacc_sql.tab.c"
    break;

  case 142: /* primary_expression: FLOAT  */
#line 975 "yacc_sql.y"
        {
		Expression *exp = malloc(sizeof(Expression));
		Value value;
                value_init_float(&value, (yyvsp[0].floats));
		expression_init_val(exp,&value);
		(yyval.expressions) = exp;
	}
#line 2583 "yacc_sql.tab.c"
    break;

  case 143: /* primary_expression: ID  */
#line 983 "yacc_sql.y"
        {
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[0].string));
		Expression *exp = malloc(sizeof(Expression));
		expression_init_attr(exp,&attr);
		(yyval.expressions) = exp;
      	}
#line 2595 "yacc_sql.tab.c"
    break;

  case 144: /* primary_expression: ID DOT ID  */
#line 990 "yacc_sql.y"
                   {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[0].string), (yyvsp[-2].string));
		Expression *exp = malloc(sizeof(Expression));
		expression_init_attr(exp,&attr);
		(yyval.expressions) = exp;
  	}
#line 2607 "yacc_sql.tab.c"
    break;

  case 145: /* comOp: EQ  */
#line 1007 "yacc_sql.y"
         { CONTEXT->comp = EQUAL_TO; }
#line 2613 "yacc_sql.tab.c"
    break;

  case 146: /* comOp: LT  */
#line 1008 "yacc_sql.y"
         { CONTEXT->comp = LESS_THAN; }
#line 2619 "yacc_sql.tab.c"
    break;

  case 147: /* comOp: GT  */
#line 1009 "yacc_sql.y"
         { CONTEXT->comp = GREAT_THAN; }
#line 2625 "yacc_sql.tab.c"
    break;

  case 148: /* comOp: LE  */
#line 1010 "yacc_sql.y"
         { CONTEXT->comp = LESS_EQUAL; }
#line 2631 "yacc_sql.tab.c"
    break;

  case 149: /* comOp: GE  */
#line 1011 "yacc_sql.y"
         { CONTEXT->comp = GREAT_EQUAL; }
#line 2637 "yacc_sql.tab.c"
    break;

  case 150: /* comOp: NE  */
#line 1012 "yacc_sql.y"
         { CONTEXT->comp = NOT_EQUAL; }
#line 2643 "yacc_sql.tab.c"
    break;

  case 151: /* comOp: IS NOT  */
#line 1013 "yacc_sql.y"
             {CONTEXT->comp = OP_IS_NOT; }
#line 2649 "yacc_sql.tab.c"
    break;

  case 152: /* comOp: IS  */
#line 1014 "yacc_sql.y"
         {CONTEXT->comp = OP_IS; }
#line 2655 "yacc_sql.tab.c"
    break;

  case 153: /* comOp: IN  */
#line 1015 "yacc_sql.y"
             { CONTEXT->comp = OP_IN; }
#line 2661 "yacc_sql.tab.c"
    break;

  case 154: /* comOp: NOT IN  */
#line 1016 "yacc_sql.y"
                 {CONTEXT->comp = OP_NOT_IN; }
#line 2667 "yacc_sql.tab.c"
    break;

  case 155: /* load_data: LOAD DATA INFILE SSS INTO TABLE ID SEMICOLON  */
#line 1021 "yacc_sql.y"
                {
		  CONTEXT->ssql->flag = SCF_LOAD_DATA;
			load_data_init(&CONTEXT->ssql->sstr.load_data, (yyvsp[-1].string), (yyvsp[-4].string));
		}
#line 2676 "yacc_sql.tab.c"
    break;


#line 2680 "yacc_sql.tab.c"

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
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (scanner, YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturn;
#endif


/*-------------------------------------------------------.
| yyreturn -- parsing is finished, clean up and return.  |
`-------------------------------------------------------*/
yyreturn:
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

#line 1026 "yacc_sql.y"

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
