/* A Bison parser, made by GNU Bison 2.7.  */

/* Bison interface for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2012 Free Software Foundation, Inc.
   
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

#ifndef YY_YY_PARSER_HPP_INCLUDED
# define YY_YY_PARSER_HPP_INCLUDED
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     T_RETURN = 258,
     T_IF = 259,
     T_WHILE = 260,
     T_EXTENDS = 261,
     T_ELSE = 262,
     T_REPEAT = 263,
     T_UNTIL = 264,
     T_PRINT = 265,
     T_TRUE = 266,
     T_FALSE = 267,
     T_AND = 268,
     T_OR = 269,
     T_NOT = 270,
     T_NEW = 271,
     T_INTEGER = 272,
     T_BOOLEAN = 273,
     T_NONE = 274,
     T_DOT = 275,
     T_SEMICOLON = 276,
     T_COLON = 277,
     T_COMMA = 278,
     T_OPENPAREN = 279,
     T_CLOSEPAREN = 280,
     T_OPENCURLYBRACKET = 281,
     T_CLOSECURLYBRACKET = 282,
     T_POINTTO = 283,
     T_EQUAL = 284,
     T_ASSIGN = 285,
     T_PLUS = 286,
     T_MINUS = 287,
     T_MULTIPLY = 288,
     T_DIVIDE = 289,
     T_MODULO = 290,
     T_LESSEQUAL = 291,
     T_LESS = 292,
     T_NUMBER = 293,
     T_ID = 294,
     T_GREATEQUAL = 295,
     T_GREAT = 296,
     T_EXP = 297,
     UMINUS = 298
   };
#endif


#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */

#endif /* !YY_YY_PARSER_HPP_INCLUDED  */
