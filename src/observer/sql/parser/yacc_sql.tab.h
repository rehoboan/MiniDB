/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_YACC_SQL_TAB_H_INCLUDED
# define YY_YY_YACC_SQL_TAB_H_INCLUDED
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
    TABLE = 265,                   /* TABLE  */
    TABLES = 266,                  /* TABLES  */
    INDEX = 267,                   /* INDEX  */
    SELECT = 268,                  /* SELECT  */
    DESC = 269,                    /* DESC  */
    SHOW = 270,                    /* SHOW  */
    SYNC = 271,                    /* SYNC  */
    INSERT = 272,                  /* INSERT  */
    DELETE = 273,                  /* DELETE  */
    UPDATE = 274,                  /* UPDATE  */
    LBRACE = 275,                  /* LBRACE  */
    RBRACE = 276,                  /* RBRACE  */
    COMMA = 277,                   /* COMMA  */
    TRX_BEGIN = 278,               /* TRX_BEGIN  */
    TRX_COMMIT = 279,              /* TRX_COMMIT  */
    TRX_ROLLBACK = 280,            /* TRX_ROLLBACK  */
    INT_T = 281,                   /* INT_T  */
    STRING_T = 282,                /* STRING_T  */
    FLOAT_T = 283,                 /* FLOAT_T  */
    HELP = 284,                    /* HELP  */
    EXIT = 285,                    /* EXIT  */
    DOT = 286,                     /* DOT  */
    INTO = 287,                    /* INTO  */
    VALUES = 288,                  /* VALUES  */
    FROM = 289,                    /* FROM  */
    WHERE = 290,                   /* WHERE  */
    AND = 291,                     /* AND  */
    SET = 292,                     /* SET  */
    ON = 293,                      /* ON  */
    LOAD = 294,                    /* LOAD  */
    DATA = 295,                    /* DATA  */
    INFILE = 296,                  /* INFILE  */
    EQ = 297,                      /* EQ  */
    LT = 298,                      /* LT  */
    GT = 299,                      /* GT  */
    LE = 300,                      /* LE  */
    GE = 301,                      /* GE  */
    NE = 302,                      /* NE  */
    NUMBER = 303,                  /* NUMBER  */
    FLOAT = 304,                   /* FLOAT  */
    ID = 305,                      /* ID  */
    PATH = 306,                    /* PATH  */
    SSS = 307,                     /* SSS  */
    STAR = 308,                    /* STAR  */
    STRING_V = 309                 /* STRING_V  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 110 "yacc_sql.y"

  struct _Attr *attr;
  struct _Condition *condition1;
  struct _Value *value1;
  char *string;
  int number;
  float floats;
	char *position;

#line 128 "yacc_sql.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif




int yyparse (void *scanner);


#endif /* !YY_YY_YACC_SQL_TAB_H_INCLUDED  */
