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

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 139 "yacc_sql.y"

  struct _Attr *attr;
  struct _Condition *condition1;
  struct _Value *value1;
  char *string;
  int number;
  float floats;

#line 138 "yacc_sql.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif




int yyparse (void *scanner);


#endif /* !YY_YY_YACC_SQL_TAB_H_INCLUDED  */
