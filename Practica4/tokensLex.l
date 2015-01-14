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
"int"	{ yylval.type = integer; return 	TYPE;}
"float"	{ yylval.type = real; return 	TYPE;}
"char"	{ yylval.type = character; return 	TYPE;}
"bool"	{ yylval.type = boolean; return 	TYPE;}
"list of"	{ yylval.type = list; return 	LIST;}
"["	{ return 	BEGIN_LIST;}
"]"	{ return 	END_LIST;}
"="	{ return 	ASSIGN;}	
"-"	{ yylval.attrib = OP_PM; yylval.type = integer; return 	OP_PM;}
"+"	{ yylval.attrib = OP_PM; yylval.type = integer; return 	OP_PM;}
"*"	{ yylval.attrib = OP_BIN; yylval.type = integer; return 	OP_BIN;}
"/"	{ yylval.attrib = OP_BIN; yylval.type = integer; return 	OP_BIN;}
"/="	{ yylval.attrib = OP_BIN; yylval.type = integer; return 	OP_BIN;}
"%="	{ yylval.attrib = OP_BIN; yylval.type = integer; return 	OP_BIN;}
"|"	{ yylval.attrib = OP_BIN; yylval.type = integer; return 	OP_BIN;}
"^="	{ yylval.attrib = OP_BIN; yylval.type = integer; return 	OP_BIN;}
"~"	{ yylval.attrib = OP_BIN; yylval.type = integer; return 	OP_BIN;}
"+="	{ yylval.attrib = OP_BIN; yylval.type = integer; return 	OP_BIN;}
"-="	{ yylval.attrib = OP_BIN; yylval.type = integer; return 	OP_BIN;}
"*="	{ yylval.attrib = OP_BIN; yylval.type = integer; return 	OP_BIN;}
">"	{ yylval.attrib = OP_BIN; yylval.type = boolean; return 	OP_BIN;}
"<"	{ yylval.attrib = OP_BIN; yylval.type = boolean; return 	OP_BIN;}
">="	{ yylval.attrib = OP_BIN; yylval.type = boolean; return 	OP_BIN;}
"<="	{ yylval.attrib = OP_BIN; yylval.type = boolean; return 	OP_BIN;}
"=="	{ yylval.attrib = OP_BIN; yylval.type = boolean; return 	OP_BIN;}
"!="	{ yylval.attrib = OP_BIN; yylval.type = boolean; return 	OP_BIN;}
"||"	{ yylval.attrib = OP_BIN; yylval.type = boolean; return 	OP_BIN;}
"&&"	{ yylval.attrib = OP_BIN; yylval.type = boolean; return 	OP_BIN;}
"^"	{ yylval.attrib = OP_BIN; yylval.type = integer; return 	OP_BIN;}
"!"	{ yylval.attrib = OP_UNIT; yylval.type = boolean; return 	OP_UNIT;}


"@"	{ yylval.attrib = OP_BIN; return 	OP_BIN;}
"%"	{ yylval.attrib = OP_BIN; return 	OP_BIN;}
"**"	{ yylval.attrib = OP_BIN; return 	OP_BIN;}

"#"	{ yylval.attrib = OP_UNIT; return 	OP_UNIT;}
"?"	{ yylval.attrib = OP_UNIT; 	OP_UNIT;}
"--" { yylval.attrib = OP_BIN; return OP_BIN;}
"++"	{ yylval.attrib = OP_BIN; return 	OP_BIN;}
"<<"	{ yylval.attrib = OP_LIST; yylval.type = list;  return 	OP_LIST;}
">>"	{ yylval.attrib = OP_LIST;  yylval.type = list; return 	OP_LIST;}
"$"	{ yylval.attrib = OP_LIST_START_CURSOR;  yylval.type = list;  return 	OP_LIST_START_CURSOR;}

"return"	{ return 	RETURN;}


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
"START_VAR" { return START_VAR_DEC; }
"END_VAR" { return END_VAR_DEC; }

"true"	{ yylval.lexem = strdup (yytext); yylval.attrib = BOOL;
				yylval.type = boolean; return 	BOOL;}
"false"	{ yylval.lexem = strdup (yytext); yylval.attrib = BOOL;
				yylval.type = boolean; return 	BOOL;}

{digit}+	{ yylval.lexem = strdup (yytext); yylval.attrib = INT;
					yylval.type = integer; return  INT;}
{digit}+\.{digit}+	{ yylval.lexem = strdup (yytext); yylval.attrib = FLOAT;
					yylval.type = real; return  FLOAT;}
"\'"{symbol_char}"\'"	{ yylval.lexem = strdup (yytext); yylval.attrib = CHAR;
					yylval.type = character; return  CHAR;}
"\""{symbol_cad}+"\""	{ yylval.lexem = strdup (yytext); yylval.attrib = CAD;
					return CAD;}
{letter}{alphanum}* { yylval.attrib = ID; yylval.lexem = strdup (yytext); return  ID;}
{space}+ {}
{endline} {linea_actual++;}
. {snprintf(buffer, MAXLONBUFFER, "el(los) caracter(es) '%s' no forma(n) ningun token conocido",yytext);
yyerror(buffer);
}

%%