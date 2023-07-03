
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
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


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     ID = 258,
     STRING = 259,
     WHILE = 260,
     FOR = 261,
     IF = 262,
     ELSE = 263,
     FUNCTION = 264,
     RETURN = 265,
     BREAK = 266,
     CONT = 267,
     LOCAL = 268,
     TRUE = 269,
     FALSE = 270,
     NIL = 271,
     AND = 272,
     OR = 273,
     NOT = 274,
     PLUS = 275,
     MINUS = 276,
     ASSIGN = 277,
     MULTIPLY = 278,
     MODULE = 279,
     DIVIDE = 280,
     DECREASE = 281,
     INCREASE = 282,
     GREAT_EQUAL = 283,
     LESS_EQUAL = 284,
     GREATER = 285,
     LESS = 286,
     EQUAL = 287,
     NOTEQUAL = 288,
     L_C_BRACKET = 289,
     R_C_BRACKET = 290,
     L_S_BRACKET = 291,
     R_S_BRACKET = 292,
     L_PARENTH = 293,
     R_PARENTH = 294,
     COMA = 295,
     SEMICOLON = 296,
     COLON = 297,
     D_COLON = 298,
     DOT = 299,
     D_DOT = 300,
     OTHER = 301,
     INTCONST = 302,
     RCONST = 303
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1676 of yacc.c  */
#line 103 "syntax_anal.y"

char* stringValue;
int intValue;
float realValue;
struct expr* expressValue;



/* Line 1676 of yacc.c  */
#line 109 "syntax_anal.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


