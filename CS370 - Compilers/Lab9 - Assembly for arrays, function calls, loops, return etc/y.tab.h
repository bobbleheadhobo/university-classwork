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

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    T_NUM = 258,
    T_INT = 259,
    T_VOID = 260,
    T_READ = 261,
    T_WRITE = 262,
    T_RETURN = 263,
    T_IF = 264,
    T_THEN = 265,
    T_ELSE = 266,
    T_WHILE = 267,
    T_DO = 268,
    T_EQ = 269,
    T_LE = 270,
    T_GE = 271,
    T_NE = 272,
    T_ID = 273,
    T_STRING = 274,
    T_BOOLEAN = 275,
    T_END = 276,
    T_BEGIN = 277,
    T_OF = 278,
    T_AND = 279,
    T_OR = 280,
    T_TRUE = 281,
    T_FALSE = 282,
    T_NOT = 283
  };
#endif
/* Tokens.  */
#define T_NUM 258
#define T_INT 259
#define T_VOID 260
#define T_READ 261
#define T_WRITE 262
#define T_RETURN 263
#define T_IF 264
#define T_THEN 265
#define T_ELSE 266
#define T_WHILE 267
#define T_DO 268
#define T_EQ 269
#define T_LE 270
#define T_GE 271
#define T_NE 272
#define T_ID 273
#define T_STRING 274
#define T_BOOLEAN 275
#define T_END 276
#define T_BEGIN 277
#define T_OF 278
#define T_AND 279
#define T_OR 280
#define T_TRUE 281
#define T_FALSE 282
#define T_NOT 283

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 55 "lab9.y" /* yacc.c:1909  */

	int value;
	char *ID;
	struct ASTnode *astnode;
	enum AST_Declared_Type DeclType;
	enum AST_Operator_Type operator;
       

#line 119 "y.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
