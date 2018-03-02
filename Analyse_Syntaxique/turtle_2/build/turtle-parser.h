/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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

#ifndef YY_YY_HOME_NEAR_L3_LICENCE3_ANALYSE_SYNTAXIQUE_TURTLE_2_BUILD_TURTLE_PARSER_H_INCLUDED
# define YY_YY_HOME_NEAR_L3_LICENCE3_ANALYSE_SYNTAXIQUE_TURTLE_2_BUILD_TURTLE_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    VALUE = 258,
    COLOUR_NAME_VALUE = 259,
    NAME = 260,
    TURTLE_VAR = 261,
    COS = 262,
    SIN = 263,
    TAN = 264,
    SQRT = 265,
    POW = 266,
    RANDOM = 267,
    KW_RIGHT = 268,
    KW_LEFT = 269,
    KW_HEADING = 270,
    KW_UP = 271,
    KW_DOWN = 272,
    KW_PRINT = 273,
    KW_FORWARD = 274,
    KW_BACKWARD = 275,
    KW_POSITION = 276,
    KW_COLOUR = 277,
    KW_REPEAT = 278,
    KW_SET = 279,
    KW_PROC = 280,
    KW_CALL = 281
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 18 "turtle-parser.y" /* yacc.c:1909  */

  double value;
  const char *name;
  const char *turtle_var;
  const char *colour_name_value;

  struct ast_node *node;

#line 90 "/home/near/L3/Licence3/Analyse_Syntaxique/turtle_2/build/turtle-parser.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (struct ast *ret);

#endif /* !YY_YY_HOME_NEAR_L3_LICENCE3_ANALYSE_SYNTAXIQUE_TURTLE_2_BUILD_TURTLE_PARSER_H_INCLUDED  */
