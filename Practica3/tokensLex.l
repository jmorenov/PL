%{
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAXLONBUFFER 200
char buffer[MAXLONBUFFER];
%}

letter	[a-zA-Z]
alphanum [a-zA-Z0-9_]
digit	[0-9]
space	[ \t]
endline [\n]
symbol_char 	[^\']
symbol_cad		[^\"]

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
"--" { return OP_BIN;}
"++"	{ return 	OP_BIN;}
"<<"	{ return 	OP_LIST;}
">>"	{ return 	OP_LIST;}
"$"	{ return 	OP_LIST_START_CURSOR;}
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
"\'"{symbol_char}"\'"	{ return  CHAR;}
"\""{symbol_cad}+"\""	{ return CAD;}
{letter}{alphanum}* { return  ID;}
{space}+ {}
{endline} {linea_actual++;}
. {snprintf(buffer, MAXLONBUFFER, "el(los) caracter(es) '%s' no forma(n) ningun token conocido",yytext);
yyerror(buffer);
}

%%
