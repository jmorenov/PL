
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
     MAIN = 258,
     MAS_MENOS = 259,
     ENTERO = 260,
     UNARIO = 261,
     CASE = 262,
     PARIZQ = 263,
     PARDER = 264,
     ASIG = 265,
     IF = 266,
     ELSE = 267,
     WHILE = 268,
     INPUT = 269,
     OUTPUT = 270,
     F_VAR_LOCAL = 271,
     I_VAR_LOCAL = 272,
     FIN_BLOQUE = 273,
     INI_BLOQUE = 274,
     TIPO_DATO = 275,
     RETURN = 276,
     SWITCH = 277,
     BOOL = 278,
     I_CONS_PILA = 279,
     F_CONS_PILA = 280,
     FIN_SENTENC = 281,
     CADENA = 282,
     REAL = 283,
     NOMBRE = 284,
     CHAR = 285,
     BREAK = 286,
     COMA = 287,
     DOS_PUNTOS = 288,
     OR_LOGICO = 289,
     AND_LOGICO = 290,
     OP_IGUALDAD = 291,
     OP_RELACIONAL = 292,
     MULTIPLICAT = 293,
     INCREMENTO = 294,
     OR_BIT = 295,
     REDIRECT_E = 296,
     REDIRECT_S = 297
   };
#endif
/* Tokens.  */
#define MAIN 258
#define MAS_MENOS 259
#define ENTERO 260
#define UNARIO 261
#define CASE 262
#define PARIZQ 263
#define PARDER 264
#define ASIG 265
#define IF 266
#define ELSE 267
#define WHILE 268
#define INPUT 269
#define OUTPUT 270
#define F_VAR_LOCAL 271
#define I_VAR_LOCAL 272
#define FIN_BLOQUE 273
#define INI_BLOQUE 274
#define TIPO_DATO 275
#define RETURN 276
#define SWITCH 277
#define BOOL 278
#define I_CONS_PILA 279
#define F_CONS_PILA 280
#define FIN_SENTENC 281
#define CADENA 282
#define REAL 283
#define NOMBRE 284
#define CHAR 285
#define BREAK 286
#define COMA 287
#define DOS_PUNTOS 288
#define OR_LOGICO 289
#define AND_LOGICO 290
#define OP_IGUALDAD 291
#define OP_RELACIONAL 292
#define MULTIPLICAT 293
#define INCREMENTO 294
#define OR_BIT 295
#define REDIRECT_E 296
#define REDIRECT_S 297




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


