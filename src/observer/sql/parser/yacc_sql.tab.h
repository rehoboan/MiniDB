/* A Bison parser, made by GNU Bison 3.7.1.  */

/* Bison interface for Yacc-like parsers in C

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
    IS = 261,                      /* IS  */
    NOT = 262,                     /* NOT  */
    NULLABLE = 263,                /* NULLABLE  */
    NULL_T = 264,                  /* NULL_T  */
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
    DATE_T = 284,                  /* DATE_T  */
    TEXT_T = 285,                  /* TEXT_T  */
    HELP = 286,                    /* HELP  */
    EXIT = 287,                    /* EXIT  */
    DOT = 288,                     /* DOT  */
    INTO = 289,                    /* INTO  */
    VALUES = 290,                  /* VALUES  */
    FROM = 291,                    /* FROM  */
    WHERE = 292,                   /* WHERE  */
    AND = 293,                     /* AND  */
    SET = 294,                     /* SET  */
    ON = 295,                      /* ON  */
    LOAD = 296,                    /* LOAD  */
    DATA = 297,                    /* DATA  */
    INFILE = 298,                  /* INFILE  */
    EQ = 299,                      /* EQ  */
    LT = 300,                      /* LT  */
    GT = 301,                      /* GT  */
    LE = 302,                      /* LE  */
    GE = 303,                      /* GE  */
    NE = 304,                      /* NE  */
    NUMBER = 305,                  /* NUMBER  */
    FLOAT = 306,                   /* FLOAT  */
    DATE = 307,                    /* DATE  */
    ID = 308,                      /* ID  */
    PATH = 309,                    /* PATH  */
    SSS = 310,                     /* SSS  */
    STAR = 311,                    /* STAR  */
    STRING_V = 312                 /* STRING_V  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 116 "yacc_sql.y"

  struct _Attr *attr;
  struct _Condition *condition1;
  struct _Value *value1;
  char *string;
  int number;
  float floats;
	char *position;

#line 131 "yacc_sql.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif



int yyparse (void *scanner);

#endif /* !YY_YY_YACC_SQL_TAB_H_INCLUDED  */
