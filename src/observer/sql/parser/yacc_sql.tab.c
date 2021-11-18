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
  size_t select_length;
  size_t condition_length;
  size_t from_length;

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
  context->from_length = 0;
  context->select_length = 0;
  context->value_length = 0;
  context->ssql->sstr.insertion.value_num = 0;
  printf("parse sql failed. error=%s", str);
}

ParserContext *get_context(yyscan_t scanner)
{
  return (ParserContext *)yyget_extra(scanner);
}

#define CONTEXT get_context(scanner)


#line 146 "yacc_sql.tab.c"

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
  YYSYMBOL_NUMBER = 61,                    /* NUMBER  */
  YYSYMBOL_FLOAT = 62,                     /* FLOAT  */
  YYSYMBOL_DATE = 63,                      /* DATE  */
  YYSYMBOL_ID = 64,                        /* ID  */
  YYSYMBOL_PATH = 65,                      /* PATH  */
  YYSYMBOL_SSS = 66,                       /* SSS  */
  YYSYMBOL_STAR = 67,                      /* STAR  */
  YYSYMBOL_STRING_V = 68,                  /* STRING_V  */
  YYSYMBOL_YYACCEPT = 69,                  /* $accept  */
  YYSYMBOL_commands = 70,                  /* commands  */
  YYSYMBOL_command = 71,                   /* command  */
  YYSYMBOL_exit = 72,                      /* exit  */
  YYSYMBOL_help = 73,                      /* help  */
  YYSYMBOL_sync = 74,                      /* sync  */
  YYSYMBOL_begin = 75,                     /* begin  */
  YYSYMBOL_commit = 76,                    /* commit  */
  YYSYMBOL_rollback = 77,                  /* rollback  */
  YYSYMBOL_drop_table = 78,                /* drop_table  */
  YYSYMBOL_show_tables = 79,               /* show_tables  */
  YYSYMBOL_desc_table = 80,                /* desc_table  */
  YYSYMBOL_create_index = 81,              /* create_index  */
  YYSYMBOL_field_list = 82,                /* field_list  */
  YYSYMBOL_field = 83,                     /* field  */
  YYSYMBOL_drop_index = 84,                /* drop_index  */
  YYSYMBOL_create_table = 85,              /* create_table  */
  YYSYMBOL_attr_def_list = 86,             /* attr_def_list  */
  YYSYMBOL_attr_def = 87,                  /* attr_def  */
  YYSYMBOL_null_value = 88,                /* null_value  */
  YYSYMBOL_number = 89,                    /* number  */
  YYSYMBOL_type = 90,                      /* type  */
  YYSYMBOL_ID_get = 91,                    /* ID_get  */
  YYSYMBOL_insert = 92,                    /* insert  */
  YYSYMBOL_row_list = 93,                  /* row_list  */
  YYSYMBOL_row = 94,                       /* row  */
  YYSYMBOL_value_list = 95,                /* value_list  */
  YYSYMBOL_value = 96,                     /* value  */
  YYSYMBOL_delete = 97,                    /* delete  */
  YYSYMBOL_update = 98,                    /* update  */
  YYSYMBOL_select = 99,                    /* select  */
  YYSYMBOL_select_attr = 100,              /* select_attr  */
  YYSYMBOL_attr_list = 101,                /* attr_list  */
  YYSYMBOL_rel_list = 102,                 /* rel_list  */
  YYSYMBOL_join_list = 103,                /* join_list  */
  YYSYMBOL_where = 104,                    /* where  */
  YYSYMBOL_opt_group = 105,                /* opt_group  */
  YYSYMBOL_column_ref_commalist = 106,     /* column_ref_commalist  */
  YYSYMBOL_column_ref = 107,               /* column_ref  */
  YYSYMBOL_opt_order = 108,                /* opt_order  */
  YYSYMBOL_order_list = 109,               /* order_list  */
  YYSYMBOL_orderby = 110,                  /* orderby  */
  YYSYMBOL_opt_order_type = 111,           /* opt_order_type  */
  YYSYMBOL_condition_list = 112,           /* condition_list  */
  YYSYMBOL_condition = 113,                /* condition  */
  YYSYMBOL_comOp = 114,                    /* comOp  */
  YYSYMBOL_load_data = 115                 /* load_data  */
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
#define YYLAST   295

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  69
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  47
/* YYNRULES -- Number of rules.  */
#define YYNRULES  129
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  308

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   323


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
      65,    66,    67,    68
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   178,   178,   180,   184,   185,   186,   187,   188,   189,
     190,   191,   192,   193,   194,   195,   196,   197,   198,   199,
     200,   204,   209,   214,   220,   226,   232,   238,   244,   250,
     258,   263,   269,   271,   276,   282,   289,   298,   300,   304,
     316,   329,   330,   333,   338,   341,   342,   343,   344,   345,
     348,   357,   374,   375,   380,   385,   387,   392,   395,   398,
     401,   405,   412,   422,   432,   452,   472,   477,   482,   488,
     493,   498,   503,   508,   513,   518,   523,   528,   535,   537,
     544,   551,   556,   561,   566,   571,   576,   581,   586,   591,
     598,   600,   604,   606,   610,   612,   615,   616,   620,   621,
     625,   630,   638,   640,   643,   644,   646,   647,   652,   659,
     660,   661,   664,   666,   670,   691,   711,   731,   753,   774,
     795,   817,   818,   819,   820,   821,   822,   823,   824,   828
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
  "NULLABLE", "NULL_T", "EQ", "LT", "GT", "LE", "GE", "NE", "NUMBER",
  "FLOAT", "DATE", "ID", "PATH", "SSS", "STAR", "STRING_V", "$accept",
  "commands", "command", "exit", "help", "sync", "begin", "commit",
  "rollback", "drop_table", "show_tables", "desc_table", "create_index",
  "field_list", "field", "drop_index", "create_table", "attr_def_list",
  "attr_def", "null_value", "number", "type", "ID_get", "insert",
  "row_list", "row", "value_list", "value", "delete", "update", "select",
  "select_attr", "attr_list", "rel_list", "join_list", "where",
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
     315,   316,   317,   318,   319,   320,   321,   322,   323
};
#endif

#define YYPACT_NINF (-220)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -220,   114,  -220,    16,    26,     0,   -23,    53,    69,    34,
      37,    19,    92,    96,    97,   103,   106,    62,  -220,  -220,
    -220,  -220,  -220,  -220,  -220,  -220,  -220,  -220,  -220,  -220,
    -220,  -220,  -220,  -220,  -220,  -220,    51,    52,   110,    63,
      64,    91,   100,   105,   108,    48,  -220,    87,   137,   138,
    -220,    78,    82,   102,  -220,  -220,  -220,  -220,  -220,    99,
     124,   113,   111,   148,   158,   -32,   116,   118,   130,    15,
     131,  -220,   132,  -220,  -220,   121,   120,   133,   134,   135,
     139,   151,  -220,  -220,     2,   174,     4,     6,     7,   176,
     178,   179,   180,    49,   181,     9,   182,    30,   204,   155,
     170,  -220,   184,   157,   187,   150,   181,   152,   181,   181,
     153,   181,   154,   181,   156,   -28,   159,   160,   161,   162,
    -220,  -220,   208,   163,   120,   120,   115,   193,  -220,  -220,
    -220,  -220,     3,  -220,   128,   177,  -220,   115,   203,   135,
     201,  -220,  -220,  -220,  -220,  -220,    -1,   165,   205,  -220,
     206,  -220,  -220,   207,  -220,   209,  -220,   210,    28,   211,
      38,    46,    47,   181,   166,   212,   215,   215,   213,   182,
     229,   175,   190,  -220,  -220,  -220,  -220,  -220,  -220,    59,
      93,    30,  -220,   120,   183,   184,   240,   185,   191,  -220,
    -220,  -220,   216,   165,   181,   181,   181,   181,   181,   186,
     181,   181,   188,   181,   189,   181,   192,  -220,   202,  -220,
     231,   235,   235,   115,   227,   193,  -220,   128,  -220,  -220,
    -220,   217,  -220,   177,   252,   255,  -220,  -220,  -220,   232,
    -220,   165,   233,   216,  -220,  -220,  -220,  -220,  -220,   234,
    -220,  -220,   236,  -220,   237,  -220,   238,    30,   198,   249,
     264,   265,   213,  -220,  -220,   104,   214,  -220,  -220,  -220,
      29,   216,   266,   243,   181,   181,   181,   181,   177,   239,
     244,  -220,   218,  -220,  -220,  -220,   241,  -220,  -220,  -220,
    -220,  -220,   268,  -220,  -220,  -220,  -220,   263,   219,   198,
       8,   246,   220,  -220,  -220,  -220,  -220,  -220,  -220,   221,
    -220,   218,  -220,  -220,    79,   246,  -220,  -220
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
       0,     0,     0,     0,     0,    78,    66,     0,     0,     0,
      23,     0,     0,     0,    24,    25,    26,    22,    21,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    67,     0,    29,    28,     0,    94,     0,     0,     0,
       0,     0,    27,    35,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    78,    78,    90,     0,     0,     0,     0,
       0,    50,    37,     0,     0,     0,    78,     0,    78,    78,
       0,    78,     0,    78,     0,     0,     0,     0,     0,     0,
      79,    68,     0,     0,    94,    94,     0,    52,    57,    58,
      59,    60,     0,    61,     0,   112,    62,     0,     0,     0,
       0,    45,    46,    47,    48,    49,    41,     0,     0,    70,
       0,    69,    72,     0,    74,     0,    76,     0,     0,     0,
       0,     0,     0,    78,     0,    90,    96,    96,    55,     0,
       0,     0,   128,   121,   122,   123,   124,   125,   126,     0,
       0,     0,    95,    94,     0,    37,     0,     0,     0,    42,
      40,    34,    32,     0,    78,    78,    78,    78,    78,     0,
      78,    78,     0,    78,     0,    78,     0,    80,     0,    91,
       0,   102,   102,     0,     0,    52,    51,     0,   127,   116,
     114,   117,   115,   112,     0,     0,    38,    36,    44,     0,
      43,     0,     0,    32,    71,    73,    75,    77,    82,     0,
      81,    84,     0,    86,     0,    88,     0,     0,     0,     0,
       0,     0,    55,    54,    53,     0,     0,   113,    63,   129,
      41,    32,     0,     0,    78,    78,    78,    78,   112,   100,
      97,    98,   106,    64,    65,    56,     0,   118,   119,    39,
      33,    30,     0,    83,    85,    87,    89,    92,     0,     0,
     111,   104,     0,    31,    93,   101,    99,   109,   110,     0,
     107,   106,   103,   120,   111,   104,   108,   105
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -220,  -220,  -220,  -220,  -220,  -220,  -220,  -220,  -220,  -220,
    -220,  -220,  -220,  -216,  -181,  -220,  -220,    90,   141,    17,
    -220,  -220,  -220,  -220,    61,   117,    35,  -123,  -220,  -220,
    -220,  -220,   -93,   123,     5,  -114,   122,  -220,     1,    81,
     -14,    -7,    -9,  -219,  -176,  -132,  -220
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,   232,   192,    29,    30,   140,   102,   190,
     229,   146,   103,    31,   170,   127,   214,   134,    32,    33,
      34,    47,    71,   124,   125,    98,   211,   270,   271,   250,
     302,   291,   300,   182,   135,   179,    35
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     120,   121,   180,   168,   257,   223,    41,    42,    43,    44,
     166,   167,   233,   149,   183,   151,   152,   263,   154,   122,
     156,    89,    90,    91,    92,   187,   297,   298,    36,   106,
      37,   109,    84,   111,   113,    85,   158,   123,    39,   159,
      40,    48,   107,   171,   110,   280,   112,   114,   299,   287,
     261,   188,   189,    38,   172,   198,   220,   222,   173,   174,
     175,   176,   177,   178,    45,   201,    49,    46,   199,   224,
     207,   268,    50,   203,   205,    51,    69,    69,   202,    93,
      52,   188,   189,    53,   128,   255,   204,   206,    70,   119,
     252,   129,   130,   131,   132,    54,   133,   297,   298,    55,
      56,   234,   235,   236,   237,   238,    57,   240,   241,    58,
     243,    59,   245,   128,     2,    60,    61,    65,     3,     4,
     129,   130,   131,   219,    62,   133,    66,    63,    64,     5,
      72,    67,   277,     6,    68,     7,     8,     9,    10,    11,
      73,    74,    75,    12,    13,    14,    76,   128,    77,    78,
      79,    82,    15,    16,   129,   130,   131,   221,   128,   133,
      80,    83,    17,    96,    97,   129,   130,   131,   276,   128,
     133,   283,   284,   285,   286,    81,   129,   130,   131,   172,
      86,   133,    87,   173,   174,   175,   176,   177,   178,   141,
     142,   143,   144,   145,    88,    94,    95,    99,   105,   101,
     100,   108,   115,   104,   116,   117,   118,   136,   126,    69,
     137,   138,   139,   147,   148,   184,   150,   153,   155,   164,
     157,   169,   181,   160,   161,   162,   163,   165,   186,   191,
     208,   193,   216,   194,   195,   210,   196,   197,   200,   217,
     123,   213,   218,   227,   231,   230,   228,   225,   248,   247,
     239,   249,   242,   244,   253,   258,   246,   256,   259,   260,
     262,   264,   269,   265,   266,   267,   272,   273,   274,   281,
     282,   293,   289,   122,   301,   226,   254,   279,   278,   288,
     185,   292,   290,   295,   303,   304,   215,   275,   209,   212,
     296,   307,   294,   251,   305,   306
};

static const yytype_int16 yycheck[] =
{
      93,    94,   134,   126,   223,   181,     6,     7,     8,     9,
     124,   125,   193,   106,   137,   108,   109,   233,   111,    10,
     113,     6,     7,     8,     9,    26,    18,    19,    12,    27,
      14,    27,    64,    27,    27,    67,    64,    28,    12,    67,
      14,    64,    40,    40,    40,   261,    40,    40,    40,   268,
     231,    52,    53,    37,    51,    27,   179,   180,    55,    56,
      57,    58,    59,    60,    64,    27,    13,    67,    40,   183,
     163,   247,     3,    27,    27,    41,    28,    28,    40,    64,
      43,    52,    53,    64,    54,   217,    40,    40,    40,    40,
     213,    61,    62,    63,    64,     3,    66,    18,    19,     3,
       3,   194,   195,   196,   197,   198,     3,   200,   201,     3,
     203,    49,   205,    54,     0,    64,    64,    26,     4,     5,
      61,    62,    63,    64,    14,    66,    26,    64,    64,    15,
      43,    26,   255,    19,    26,    21,    22,    23,    24,    25,
       3,     3,    64,    29,    30,    31,    64,    54,    46,    50,
      26,     3,    38,    39,    61,    62,    63,    64,    54,    66,
      47,     3,    48,    42,    44,    61,    62,    63,    64,    54,
      66,   264,   265,   266,   267,    64,    61,    62,    63,    51,
      64,    66,    64,    55,    56,    57,    58,    59,    60,    32,
      33,    34,    35,    36,    64,    64,    64,    64,    47,    64,
      66,    27,    26,    64,    26,    26,    26,     3,    26,    28,
      55,    41,    28,    26,    64,    12,    64,    64,    64,    11,
      64,    28,    45,    64,    64,    64,    64,    64,    27,    64,
      64,    26,     3,    27,    27,    20,    27,    27,    27,    64,
      28,    28,    52,     3,    28,    54,    61,    64,    17,    47,
      64,    16,    64,    64,    27,     3,    64,    40,     3,    27,
      27,    27,    64,    27,    27,    27,    17,     3,     3,     3,
      27,     3,    28,    10,    28,   185,   215,   260,    64,    40,
     139,    40,    64,    64,    64,    64,   169,   252,   165,   167,
     289,   305,   287,   212,   301,   304
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    70,     0,     4,     5,    15,    19,    21,    22,    23,
      24,    25,    29,    30,    31,    38,    39,    48,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    84,
      85,    92,    97,    98,    99,   115,    12,    14,    37,    12,
      14,     6,     7,     8,     9,    64,    67,   100,    64,    13,
       3,    41,    43,    64,     3,     3,     3,     3,     3,    49,
      64,    64,    14,    64,    64,    26,    26,    26,    26,    28,
      40,   101,    43,     3,     3,    64,    64,    46,    50,    26,
      47,    64,     3,     3,    64,    67,    64,    64,    64,     6,
       7,     8,     9,    64,    64,    64,    42,    44,   104,    64,
      66,    64,    87,    91,    64,    47,    27,    40,    27,    27,
      40,    27,    40,    27,    40,    26,    26,    26,    26,    40,
     101,   101,    10,    28,   102,   103,    26,    94,    54,    61,
      62,    63,    64,    66,    96,   113,     3,    55,    41,    28,
      86,    32,    33,    34,    35,    36,    90,    26,    64,   101,
      64,   101,   101,    64,   101,    64,   101,    64,    64,    67,
      64,    64,    64,    64,    11,    64,   104,   104,    96,    28,
      93,    40,    51,    55,    56,    57,    58,    59,    60,   114,
     114,    45,   112,    96,    12,    87,    27,    26,    52,    53,
      88,    64,    83,    26,    27,    27,    27,    27,    27,    40,
      27,    27,    40,    27,    40,    27,    40,   101,    64,   102,
      20,   105,   105,    28,    95,    94,     3,    64,    52,    64,
      96,    64,    96,   113,   104,    64,    86,     3,    61,    89,
      54,    28,    82,    83,   101,   101,   101,   101,   101,    64,
     101,   101,    64,   101,    64,   101,    64,    47,    17,    16,
     108,   108,    96,    27,    93,   114,    40,   112,     3,     3,
      27,    83,    27,    82,    27,    27,    27,    27,   113,    64,
     106,   107,    17,     3,     3,    95,    64,    96,    64,    88,
      82,     3,    27,   101,   101,   101,   101,   112,    40,    28,
      64,   110,    40,     3,   103,    64,   107,    18,    19,    40,
     111,    28,   109,    64,    64,   110,   111,   109
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    69,    70,    70,    71,    71,    71,    71,    71,    71,
      71,    71,    71,    71,    71,    71,    71,    71,    71,    71,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    81,    82,    82,    83,    84,    85,    86,    86,    87,
      87,    88,    88,    88,    89,    90,    90,    90,    90,    90,
      91,    92,    93,    93,    94,    95,    95,    96,    96,    96,
      96,    96,    97,    98,    99,    99,   100,   100,   100,   100,
     100,   100,   100,   100,   100,   100,   100,   100,   101,   101,
     101,   101,   101,   101,   101,   101,   101,   101,   101,   101,
     102,   102,   103,   103,   104,   104,   105,   105,   106,   106,
     107,   107,   108,   108,   109,   109,   110,   110,   110,   111,
     111,   111,   112,   112,   113,   113,   113,   113,   113,   113,
     113,   114,   114,   114,   114,   114,   114,   114,   114,   115
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
       1,     1,     5,     8,     9,     9,     1,     2,     4,     5,
       5,     7,     5,     7,     5,     7,     5,     7,     0,     3,
       5,     6,     6,     8,     6,     8,     6,     8,     6,     8,
       0,     3,     0,     7,     0,     3,     0,     3,     1,     3,
       1,     3,     0,     4,     0,     3,     0,     2,     4,     1,
       1,     0,     0,     3,     3,     3,     3,     3,     5,     5,
       7,     1,     1,     1,     1,     1,     1,     2,     1,     8
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
#line 204 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_EXIT;//"exit";
    }
#line 1460 "yacc_sql.tab.c"
    break;

  case 22: /* help: HELP SEMICOLON  */
#line 209 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_HELP;//"help";
    }
#line 1468 "yacc_sql.tab.c"
    break;

  case 23: /* sync: SYNC SEMICOLON  */
#line 214 "yacc_sql.y"
                   {
      CONTEXT->ssql->flag = SCF_SYNC;
    }
#line 1476 "yacc_sql.tab.c"
    break;

  case 24: /* begin: TRX_BEGIN SEMICOLON  */
#line 220 "yacc_sql.y"
                        {
      CONTEXT->ssql->flag = SCF_BEGIN;
    }
#line 1484 "yacc_sql.tab.c"
    break;

  case 25: /* commit: TRX_COMMIT SEMICOLON  */
#line 226 "yacc_sql.y"
                         {
      CONTEXT->ssql->flag = SCF_COMMIT;
    }
#line 1492 "yacc_sql.tab.c"
    break;

  case 26: /* rollback: TRX_ROLLBACK SEMICOLON  */
#line 232 "yacc_sql.y"
                           {
      CONTEXT->ssql->flag = SCF_ROLLBACK;
    }
#line 1500 "yacc_sql.tab.c"
    break;

  case 27: /* drop_table: DROP TABLE ID SEMICOLON  */
#line 238 "yacc_sql.y"
                            {
        CONTEXT->ssql->flag = SCF_DROP_TABLE;//"drop_table";
        drop_table_init(&CONTEXT->ssql->sstr.drop_table, (yyvsp[-1].string));
    }
#line 1509 "yacc_sql.tab.c"
    break;

  case 28: /* show_tables: SHOW TABLES SEMICOLON  */
#line 244 "yacc_sql.y"
                          {
      CONTEXT->ssql->flag = SCF_SHOW_TABLES;
    }
#line 1517 "yacc_sql.tab.c"
    break;

  case 29: /* desc_table: DESC ID SEMICOLON  */
#line 250 "yacc_sql.y"
                      {
      CONTEXT->ssql->flag = SCF_DESC_TABLE;
      desc_table_init(&CONTEXT->ssql->sstr.desc_table, (yyvsp[-1].string));
    }
#line 1526 "yacc_sql.tab.c"
    break;

  case 30: /* create_index: CREATE INDEX ID ON ID LBRACE field field_list RBRACE SEMICOLON  */
#line 259 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-7].string), (yyvsp[-5].string), CONTEXT->field_names, CONTEXT->index_field_num, 0);
		}
#line 1535 "yacc_sql.tab.c"
    break;

  case 31: /* create_index: CREATE UNIQUE INDEX ID ON ID LBRACE field field_list RBRACE SEMICOLON  */
#line 264 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-7].string), (yyvsp[-5].string), CONTEXT->field_names, CONTEXT->index_field_num, 1);
                }
#line 1544 "yacc_sql.tab.c"
    break;

  case 33: /* field_list: COMMA field field_list  */
#line 271 "yacc_sql.y"
                               {

    	}
#line 1552 "yacc_sql.tab.c"
    break;

  case 34: /* field: ID  */
#line 276 "yacc_sql.y"
          {
    		CONTEXT->field_names[CONTEXT->index_field_num++]=(yyvsp[0].string);
    	}
#line 1560 "yacc_sql.tab.c"
    break;

  case 35: /* drop_index: DROP INDEX ID SEMICOLON  */
#line 283 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_DROP_INDEX;//"drop_index";
			drop_index_init(&CONTEXT->ssql->sstr.drop_index, (yyvsp[-1].string));
		}
#line 1569 "yacc_sql.tab.c"
    break;

  case 36: /* create_table: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE SEMICOLON  */
#line 290 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_CREATE_TABLE;//"create_table";
			// CONTEXT->ssql->sstr.create_table.attribute_count = CONTEXT->value_length;
			create_table_init_name(&CONTEXT->ssql->sstr.create_table, (yyvsp[-5].string));
			//临时变量清零
			CONTEXT->value_length = 0;
		}
#line 1581 "yacc_sql.tab.c"
    break;

  case 38: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 300 "yacc_sql.y"
                                   {    }
#line 1587 "yacc_sql.tab.c"
    break;

  case 39: /* attr_def: ID_get type LBRACE number RBRACE null_value  */
#line 305 "yacc_sql.y"
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
#line 1603 "yacc_sql.tab.c"
    break;

  case 40: /* attr_def: ID_get type null_value  */
#line 317 "yacc_sql.y"
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
#line 1619 "yacc_sql.tab.c"
    break;

  case 42: /* null_value: NULLABLE  */
#line 330 "yacc_sql.y"
                 {
		CONTEXT->nullable = true;
	}
#line 1627 "yacc_sql.tab.c"
    break;

  case 43: /* null_value: NOT NULL_T  */
#line 333 "yacc_sql.y"
                   {

	}
#line 1635 "yacc_sql.tab.c"
    break;

  case 44: /* number: NUMBER  */
#line 338 "yacc_sql.y"
                       {(yyval.number) = (yyvsp[0].number);}
#line 1641 "yacc_sql.tab.c"
    break;

  case 45: /* type: INT_T  */
#line 341 "yacc_sql.y"
              { (yyval.number)=INTS; }
#line 1647 "yacc_sql.tab.c"
    break;

  case 46: /* type: STRING_T  */
#line 342 "yacc_sql.y"
                  { (yyval.number)=CHARS; }
#line 1653 "yacc_sql.tab.c"
    break;

  case 47: /* type: FLOAT_T  */
#line 343 "yacc_sql.y"
                 { (yyval.number)=FLOATS; }
#line 1659 "yacc_sql.tab.c"
    break;

  case 48: /* type: DATE_T  */
#line 344 "yacc_sql.y"
                { (yyval.number)=DATES; }
#line 1665 "yacc_sql.tab.c"
    break;

  case 49: /* type: TEXT_T  */
#line 345 "yacc_sql.y"
                { (yyval.number)=TEXTS; }
#line 1671 "yacc_sql.tab.c"
    break;

  case 50: /* ID_get: ID  */
#line 349 "yacc_sql.y"
        {
		char *temp=(yyvsp[0].string);
		snprintf(CONTEXT->id, sizeof(CONTEXT->id), "%s", temp);
	}
#line 1680 "yacc_sql.tab.c"
    break;

  case 51: /* insert: INSERT INTO ID VALUES row row_list SEMICOLON  */
#line 358 "yacc_sql.y"
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
#line 1700 "yacc_sql.tab.c"
    break;

  case 53: /* row_list: COMMA row row_list  */
#line 375 "yacc_sql.y"
                                {
	}
#line 1707 "yacc_sql.tab.c"
    break;

  case 54: /* row: LBRACE value value_list RBRACE  */
#line 380 "yacc_sql.y"
                                        {
		CONTEXT->row_end[CONTEXT->row_num++]=CONTEXT->value_length;
	}
#line 1715 "yacc_sql.tab.c"
    break;

  case 56: /* value_list: COMMA value value_list  */
#line 387 "yacc_sql.y"
                              {
  		// CONTEXT->values[CONTEXT->value_length++] = *$2;
	  }
#line 1723 "yacc_sql.tab.c"
    break;

  case 57: /* value: NULL_T  */
#line 392 "yacc_sql.y"
          {
		value_init_null(&CONTEXT->values[CONTEXT->value_length++]);
	}
#line 1731 "yacc_sql.tab.c"
    break;

  case 58: /* value: NUMBER  */
#line 395 "yacc_sql.y"
           {
  		value_init_integer(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].number));
		}
#line 1739 "yacc_sql.tab.c"
    break;

  case 59: /* value: FLOAT  */
#line 398 "yacc_sql.y"
          {
  		value_init_float(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].floats));
		}
#line 1747 "yacc_sql.tab.c"
    break;

  case 60: /* value: DATE  */
#line 401 "yacc_sql.y"
          {
    			(yyvsp[0].string) = substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      		value_init_date(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].string));
    		}
#line 1756 "yacc_sql.tab.c"
    break;

  case 61: /* value: SSS  */
#line 405 "yacc_sql.y"
         {
			(yyvsp[0].string) = substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
  		value_init_string(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].string));
		}
#line 1765 "yacc_sql.tab.c"
    break;

  case 62: /* delete: DELETE FROM ID where SEMICOLON  */
#line 413 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_DELETE;//"delete";
			deletes_init_relation(&CONTEXT->ssql->sstr.deletion, (yyvsp[-2].string));
			deletes_set_conditions(&CONTEXT->ssql->sstr.deletion,
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;
    }
#line 1777 "yacc_sql.tab.c"
    break;

  case 63: /* update: UPDATE ID SET ID EQ value where SEMICOLON  */
#line 423 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_UPDATE;//"update";
			Value *value = &CONTEXT->values[0];
			updates_init(&CONTEXT->ssql->sstr.update, (yyvsp[-6].string), (yyvsp[-4].string), value,
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;
		}
#line 1789 "yacc_sql.tab.c"
    break;

  case 64: /* select: SELECT select_attr FROM ID rel_list where opt_group opt_order SEMICOLON  */
#line 433 "yacc_sql.y"
        {
			// CONTEXT->ssql->sstr.selection.relations[CONTEXT->from_length++]=$4;
			selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-5].string));
			selects_append_conditions(&CONTEXT->ssql->sstr.selection, CONTEXT->conditions, CONTEXT->condition_length);
			selects_append_orders(&CONTEXT->ssql->sstr.selection, CONTEXT->orders, CONTEXT->order_num);
			selects_append_groups(&CONTEXT->ssql->sstr.selection, CONTEXT->groups, CONTEXT->group_num);

			CONTEXT->ssql->flag=SCF_SELECT;//"select";
			// CONTEXT->ssql->sstr.selection.attr_num = CONTEXT->select_length;

			//临时变量清零
			CONTEXT->condition_length=0;
			CONTEXT->from_length=0;
			CONTEXT->select_length=0;
			CONTEXT->value_length = 0;
			CONTEXT->order_num = 0;
			CONTEXT->group_num = 0;

	}
#line 1813 "yacc_sql.tab.c"
    break;

  case 65: /* select: SELECT select_attr FROM ID join_list where opt_group opt_order SEMICOLON  */
#line 453 "yacc_sql.y"
        {
		selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-5].string));
		selects_append_conditions(&CONTEXT->ssql->sstr.selection, CONTEXT->conditions, CONTEXT->condition_length);
		selects_append_orders(&CONTEXT->ssql->sstr.selection, CONTEXT->orders, CONTEXT->order_num);
		selects_append_groups(&CONTEXT->ssql->sstr.selection, CONTEXT->groups, CONTEXT->group_num);
		CONTEXT->ssql->flag = SCF_SELECT;

		//临时变量清0
		CONTEXT->condition_length = 0;
		CONTEXT->from_length = 0;
		CONTEXT->select_length = 0;
		CONTEXT->value_length = 0;
		CONTEXT->order_num = 0;
		CONTEXT->group_num = 0;
	}
#line 1833 "yacc_sql.tab.c"
    break;

  case 66: /* select_attr: STAR  */
#line 472 "yacc_sql.y"
         {
			RelAttr attr;
			relation_attr_init(&attr, NULL, "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 1843 "yacc_sql.tab.c"
    break;

  case 67: /* select_attr: ID attr_list  */
#line 477 "yacc_sql.y"
                   {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 1853 "yacc_sql.tab.c"
    break;

  case 68: /* select_attr: ID DOT ID attr_list  */
#line 482 "yacc_sql.y"
                              {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 1863 "yacc_sql.tab.c"
    break;

  case 69: /* select_attr: COUNT LBRACE STAR RBRACE attr_list  */
#line 488 "yacc_sql.y"
                                             {
			RelAttr attr;
			relation_attr_with_agg_init(&attr, "COUNT", NULL, "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 1873 "yacc_sql.tab.c"
    break;

  case 70: /* select_attr: COUNT LBRACE ID RBRACE attr_list  */
#line 493 "yacc_sql.y"
                                           {
			RelAttr attr;
			relation_attr_with_agg_init(&attr, "COUNT", NULL, (yyvsp[-2].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 1883 "yacc_sql.tab.c"
    break;

  case 71: /* select_attr: COUNT LBRACE ID DOT ID RBRACE attr_list  */
#line 498 "yacc_sql.y"
                                                  {
			RelAttr attr;
			relation_attr_with_agg_init(&attr, "COUNT", (yyvsp[-4].string), (yyvsp[-2].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 1893 "yacc_sql.tab.c"
    break;

  case 72: /* select_attr: MAX LBRACE ID RBRACE attr_list  */
#line 503 "yacc_sql.y"
                                         {
			RelAttr attr;
			relation_attr_with_agg_init(&attr, "MAX", NULL, (yyvsp[-2].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 1903 "yacc_sql.tab.c"
    break;

  case 73: /* select_attr: MAX LBRACE ID DOT ID RBRACE attr_list  */
#line 508 "yacc_sql.y"
                                                {
			RelAttr attr;
			relation_attr_with_agg_init(&attr, "MAX", (yyvsp[-4].string), (yyvsp[-2].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 1913 "yacc_sql.tab.c"
    break;

  case 74: /* select_attr: MIN LBRACE ID RBRACE attr_list  */
#line 513 "yacc_sql.y"
                                         {
			RelAttr attr;
			relation_attr_with_agg_init(&attr, "MIN", NULL, (yyvsp[-2].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 1923 "yacc_sql.tab.c"
    break;

  case 75: /* select_attr: MIN LBRACE ID DOT ID RBRACE attr_list  */
#line 518 "yacc_sql.y"
                                                {
			RelAttr attr;
			relation_attr_with_agg_init(&attr, "MIN", (yyvsp[-4].string), (yyvsp[-2].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 1933 "yacc_sql.tab.c"
    break;

  case 76: /* select_attr: AVG LBRACE ID RBRACE attr_list  */
#line 523 "yacc_sql.y"
                                         {
			RelAttr attr;
			relation_attr_with_agg_init(&attr, "AVG", NULL, (yyvsp[-2].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 1943 "yacc_sql.tab.c"
    break;

  case 77: /* select_attr: AVG LBRACE ID DOT ID RBRACE attr_list  */
#line 528 "yacc_sql.y"
                                                {
			RelAttr attr;
			relation_attr_with_agg_init(&attr, "MIN", (yyvsp[-4].string), (yyvsp[-2].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 1953 "yacc_sql.tab.c"
    break;

  case 79: /* attr_list: COMMA ID attr_list  */
#line 537 "yacc_sql.y"
                         {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
     	  // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length].relation_name = NULL;
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length++].attribute_name=$2;
      }
#line 1965 "yacc_sql.tab.c"
    break;

  case 80: /* attr_list: COMMA ID DOT ID attr_list  */
#line 544 "yacc_sql.y"
                                {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length].attribute_name=$4;
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length++].relation_name=$2;
  	  }
#line 1977 "yacc_sql.tab.c"
    break;

  case 81: /* attr_list: COMMA COUNT LBRACE STAR RBRACE attr_list  */
#line 551 "yacc_sql.y"
                                                   {
			RelAttr attr;
			relation_attr_with_agg_init(&attr, "COUNT", NULL, "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	  }
#line 1987 "yacc_sql.tab.c"
    break;

  case 82: /* attr_list: COMMA COUNT LBRACE ID RBRACE attr_list  */
#line 556 "yacc_sql.y"
                                                 {
			RelAttr attr;
			relation_attr_with_agg_init(&attr, "COUNT", NULL, (yyvsp[-2].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 1997 "yacc_sql.tab.c"
    break;

  case 83: /* attr_list: COMMA COUNT LBRACE ID DOT ID RBRACE attr_list  */
#line 561 "yacc_sql.y"
                                                        {
			RelAttr attr;
			relation_attr_with_agg_init(&attr, "COUNT", (yyvsp[-4].string), (yyvsp[-2].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2007 "yacc_sql.tab.c"
    break;

  case 84: /* attr_list: COMMA MAX LBRACE ID RBRACE attr_list  */
#line 566 "yacc_sql.y"
                                               {
			RelAttr attr;
			relation_attr_with_agg_init(&attr, "MAX", NULL, (yyvsp[-2].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2017 "yacc_sql.tab.c"
    break;

  case 85: /* attr_list: COMMA MAX LBRACE ID DOT ID RBRACE attr_list  */
#line 571 "yacc_sql.y"
                                                      {
			RelAttr attr;
			relation_attr_with_agg_init(&attr, "MAX", (yyvsp[-4].string), (yyvsp[-2].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2027 "yacc_sql.tab.c"
    break;

  case 86: /* attr_list: COMMA MIN LBRACE ID RBRACE attr_list  */
#line 576 "yacc_sql.y"
                                               {
			RelAttr attr;
			relation_attr_with_agg_init(&attr, "MIN", NULL, (yyvsp[-2].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2037 "yacc_sql.tab.c"
    break;

  case 87: /* attr_list: COMMA MIN LBRACE ID DOT ID RBRACE attr_list  */
#line 581 "yacc_sql.y"
                                                      {
			RelAttr attr;
			relation_attr_with_agg_init(&attr, "MIN", (yyvsp[-4].string), (yyvsp[-2].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2047 "yacc_sql.tab.c"
    break;

  case 88: /* attr_list: COMMA AVG LBRACE ID RBRACE attr_list  */
#line 586 "yacc_sql.y"
                                               {
			RelAttr attr;
			relation_attr_with_agg_init(&attr, "AVG", NULL, (yyvsp[-2].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2057 "yacc_sql.tab.c"
    break;

  case 89: /* attr_list: COMMA AVG LBRACE ID DOT ID RBRACE attr_list  */
#line 591 "yacc_sql.y"
                                                      {
			RelAttr attr;
			relation_attr_with_agg_init(&attr, "AVG", (yyvsp[-4].string), (yyvsp[-2].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2067 "yacc_sql.tab.c"
    break;

  case 91: /* rel_list: COMMA ID rel_list  */
#line 600 "yacc_sql.y"
                        {
				selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-1].string));
		  }
#line 2075 "yacc_sql.tab.c"
    break;

  case 93: /* join_list: INNER JOIN ID ON condition condition_list join_list  */
#line 606 "yacc_sql.y"
                                                              {
		selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-4].string));
	}
#line 2083 "yacc_sql.tab.c"
    break;

  case 100: /* column_ref: ID  */
#line 625 "yacc_sql.y"
                   {
		GroupByDescription group;
		relation_group_init(&group,NULL,(yyvsp[0].string));
		CONTEXT->groups[CONTEXT->group_num++] = group;
		}
#line 2093 "yacc_sql.tab.c"
    break;

  case 101: /* column_ref: ID DOT ID  */
#line 630 "yacc_sql.y"
                         {
		GroupByDescription group;
		relation_group_init(&group,(yyvsp[-2].string),(yyvsp[0].string));
		CONTEXT->groups[CONTEXT->group_num++] = group;

	}
#line 2104 "yacc_sql.tab.c"
    break;

  case 107: /* orderby: ID opt_order_type  */
#line 647 "yacc_sql.y"
                   {
	OrderDescription order;
	relation_order_init(&order, NULL, (yyvsp[-1].string), CONTEXT->order_type);
        CONTEXT->orders[CONTEXT->order_num++] = order;
}
#line 2114 "yacc_sql.tab.c"
    break;

  case 108: /* orderby: ID DOT ID opt_order_type  */
#line 652 "yacc_sql.y"
                         {
	OrderDescription order;
	relation_order_init(&order, (yyvsp[-3].string), (yyvsp[-1].string), CONTEXT->order_type);
        CONTEXT->orders[CONTEXT->order_num++] = order;
}
#line 2124 "yacc_sql.tab.c"
    break;

  case 109: /* opt_order_type: ASC  */
#line 659 "yacc_sql.y"
                     { CONTEXT->order_type = kOrderAsc; }
#line 2130 "yacc_sql.tab.c"
    break;

  case 110: /* opt_order_type: DESC  */
#line 660 "yacc_sql.y"
       { CONTEXT->order_type = kOrderDesc; }
#line 2136 "yacc_sql.tab.c"
    break;

  case 111: /* opt_order_type: %empty  */
#line 661 "yacc_sql.y"
              { CONTEXT->order_type = kOrderAsc; }
#line 2142 "yacc_sql.tab.c"
    break;

  case 114: /* condition: ID comOp value  */
#line 671 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));

			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 0, NULL, right_value);
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
#line 2167 "yacc_sql.tab.c"
    break;

  case 115: /* condition: value comOp value  */
#line 692 "yacc_sql.y"
                {
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 2];
			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 0, NULL, left_value, 0, NULL, right_value);
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
#line 2191 "yacc_sql.tab.c"
    break;

  case 116: /* condition: ID comOp ID  */
#line 712 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));
			RelAttr right_attr;
			relation_attr_init(&right_attr, NULL, (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 1, &right_attr, NULL);
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
#line 2215 "yacc_sql.tab.c"
    break;

  case 117: /* condition: value comOp ID  */
#line 732 "yacc_sql.y"
                {
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];
			RelAttr right_attr;
			relation_attr_init(&right_attr, NULL, (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 0, NULL, left_value, 1, &right_attr, NULL);
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
#line 2241 "yacc_sql.tab.c"
    break;

  case 118: /* condition: ID DOT ID comOp value  */
#line 754 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, (yyvsp[-4].string), (yyvsp[-2].string));
			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 0, NULL, right_value);
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
#line 2266 "yacc_sql.tab.c"
    break;

  case 119: /* condition: value comOp ID DOT ID  */
#line 775 "yacc_sql.y"
                {
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];

			RelAttr right_attr;
			relation_attr_init(&right_attr, (yyvsp[-2].string), (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 0, NULL, left_value, 1, &right_attr, NULL);
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
#line 2291 "yacc_sql.tab.c"
    break;

  case 120: /* condition: ID DOT ID comOp ID DOT ID  */
#line 796 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, (yyvsp[-6].string), (yyvsp[-4].string));
			RelAttr right_attr;
			relation_attr_init(&right_attr, (yyvsp[-2].string), (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 1, &right_attr, NULL);
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
#line 2314 "yacc_sql.tab.c"
    break;

  case 121: /* comOp: EQ  */
#line 817 "yacc_sql.y"
         { CONTEXT->comp = EQUAL_TO; }
#line 2320 "yacc_sql.tab.c"
    break;

  case 122: /* comOp: LT  */
#line 818 "yacc_sql.y"
         { CONTEXT->comp = LESS_THAN; }
#line 2326 "yacc_sql.tab.c"
    break;

  case 123: /* comOp: GT  */
#line 819 "yacc_sql.y"
         { CONTEXT->comp = GREAT_THAN; }
#line 2332 "yacc_sql.tab.c"
    break;

  case 124: /* comOp: LE  */
#line 820 "yacc_sql.y"
         { CONTEXT->comp = LESS_EQUAL; }
#line 2338 "yacc_sql.tab.c"
    break;

  case 125: /* comOp: GE  */
#line 821 "yacc_sql.y"
         { CONTEXT->comp = GREAT_EQUAL; }
#line 2344 "yacc_sql.tab.c"
    break;

  case 126: /* comOp: NE  */
#line 822 "yacc_sql.y"
         { CONTEXT->comp = NOT_EQUAL; }
#line 2350 "yacc_sql.tab.c"
    break;

  case 127: /* comOp: IS NOT  */
#line 823 "yacc_sql.y"
             {CONTEXT->comp = OP_IS_NOT; }
#line 2356 "yacc_sql.tab.c"
    break;

  case 128: /* comOp: IS  */
#line 824 "yacc_sql.y"
         {CONTEXT->comp = OP_IS; }
#line 2362 "yacc_sql.tab.c"
    break;

  case 129: /* load_data: LOAD DATA INFILE SSS INTO TABLE ID SEMICOLON  */
#line 829 "yacc_sql.y"
                {
		  CONTEXT->ssql->flag = SCF_LOAD_DATA;
			load_data_init(&CONTEXT->ssql->sstr.load_data, (yyvsp[-1].string), (yyvsp[-4].string));
		}
#line 2371 "yacc_sql.tab.c"
    break;


#line 2375 "yacc_sql.tab.c"

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

#line 834 "yacc_sql.y"

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
