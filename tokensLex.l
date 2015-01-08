%{
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAXLONBUFFER 200
char buffer[MAXLONBUFFER];
%}

letter	[a-zA-Z]
ident	[a-zA-Z_]
digit	[0-9]
space	[ \t]
endline [\n]
symbol 	[^\"\""]

%option noyywrap

%%

"main"	{ return 	MAIN;}
"int"	{ return 	TYPE;}
"float"	{ return 	TYPE;}
"char"	{ return 	TYPE;}
"bool"	{ return 	TYPE;}
"list of"	{ return 	LIST;}
"["	{ return 	BEGIN_LIST;}
"]"	{ return 	END_LIST;}
"="	{ return 	ASSIGN;}
"-"	{ return 	OP_PM;}
"+"	{ return 	OP_PM;}
"*"	{ return 	OP_BIN;}
"/"	{ return 	OP_BIN;}
"/="	{ return 	OP_BIN;}
"%="	{ return 	OP_BIN;}
"|"	{ return 	OP_BIN;}
"^="	{ return 	OP_BIN;}
"~"	{ return 	OP_BIN;}
"+="	{ return 	OP_BIN;}
"-="	{ return 	OP_BIN;}
"*="	{ return 	OP_BIN;}
"@"	{ return 	OP_BIN;}
"%"	{ return 	OP_BIN;}
">"	{ return 	OP_BIN;}
"<"	{ return 	OP_BIN;}
">="	{ return 	OP_BIN;}
"<="	{ return 	OP_BIN;}
"=="	{ return 	OP_BIN;}
"!="	{ return 	OP_BIN;}
"||"	{ return 	OP_BIN;}
"&&"	{ return 	OP_BIN;}
"^"	{ return 	OP_BIN;}
"**"	{ return 	OP_BIN;}
"!"	{ return 	OP_UNIT;}
"#"	{ return 	OP_UNIT;}
"?"	{ return 	OP_UNIT;}
"++"	{ return 	OP_UNIT;}
"<<"	{ return 	OP_LIST;}
">>"	{ return 	OP_LIST;}
"$"	{ return 	OP_LIST_START_CURSOR;}
"'"	{ return 	LIMIT_CHAR;}
"("	{ return 	PL;}
")"	{ return 	PR;}
"{"	{ return 	BEGIN_P;}
"}"	{ return 	END;}
","	{ return 	COMMA;}
";"	{ return 	SEMICOLON;}
"if"	{ return 	IF;}
"else"	{ return 	ELSE;}
"while"	{ return 	WHILE;}
"do"	{ return 	DO ;}
"until"	{ return 	UNTIL;}
"input"	{ return 	INPUT;}
"output"	{ return 	OUTPUT;}
"true"	{ return 	BOOL;}
"false"	{ return 	BOOL;}
"return"	{ return 	RETURN;}
"START_VAR" { return START_VAR_DEC; }
"END_VAR" { return END_VAR_DEC; }
{digit}+	{ return  INT;}
{digit}+\.{digit}+	{ return  FLOAT;}
"'"{letter}|{digit}|{symbol}"'"	{ return  CHAR;}
"\""({letter}|{digit}|{symbol})+"\""	{ return CAD;}
{ident}+ { return  ID;}
{space}+ {}
{endline} {linea_actual++;printf("\n");}
. {snprintf(buffer, MAXLONBUFFER, "el(los) caracter(es) '%s' no forma(n) ningun token conocido",yytext);
yyerror(buffer);
}

%%
