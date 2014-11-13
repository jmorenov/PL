%{
#define MAXLONBUFFER 200
char buffer[MAXLONBUFFER];
%}

letter	[a-zA-Z]
ident	[a-zA-Z_]
digit	[0-9]
space	[ \t]
endline [\n]
symbol 	[^\"\""]
other 	.

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
"."	{ return 	POINT;}
"‘"	{ return 	LIMIT_CHAR;}
"("	{ return 	PL;}
")"	{ return 	PR;}
"{"	{ return 	BEGIN;}
"}"	{ return 	END;}
","	{ return 	COMMA;}
";"	{ return 	SEMICOLON;}
"if"	{ return 	CONDITIONAL;}
"else"	{ return 	ELSE;}
"while"	{ return 	CONDITIONAL;}
"do"	{ return 	DO ;}
"until"	{ return 	UNTIL;}
"input"	{ return 	INPUT;}
"output"	{ return 	OUTPUT;}
"true"	{ return 	BOOL;}
"false"	{ return 	BOOL;}
"return"	{ return 	RETURN;}
{digit}+	{ return  TYPE;}
{digit}+\.{digit}+	{ return  TYPE;}
{letter}	{ return  TYPE;}
{ident}+ { return  ID;}
{space}+ {}
{endline} {line++;}

{other} {snprintf(buffer, MAXLONBUFFER, "el(los) caracter(es) '%s' no forma(n) ningun token conocido",yytext);
	yyerror(buffer);}
%%

/*********************************************************
**
** Fichero: MAIN.C
** Función: Pruebas de FLEX para practicas Proc.Leng
**
*********************************************************/
#include <stdio.h>
#include <stdlib.h>
extern FILE *yyin ;
int yyparse(void) ;
FILE *abrir_entrada( int argc, char *argv[] )
{
	FILE *f= NULL ;
	if ( argc > 1 )
	{
		f= fopen(argv[1],"r");
		if (f==NULL)
		{
			fprintf(stderr,"fichero ’%s’ no encontrado\n",argv[1]);
			exit(1);
		}
		else
			printf("leyendo fichero ’%s’.\n",argv[1]);
	}
	else
		printf("leyendo entrada estándar.\n");

	return f ;
}
/************************************************************/
int main( int argc, char *argv[] )
{
	yyin= abrir_entrada(argc,argv) ;
	return yyparse() ;
}

