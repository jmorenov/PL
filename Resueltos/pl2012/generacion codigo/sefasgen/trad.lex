%{

#include <stdio.h>
#include <string.h>

#include "y.tab.h"

extern char *yylval;
extern void yyerror(char *);

char msj[25];

/*********************
  Ya no usamos esto

"FMT"		{ return FORMATO; }

*****************************************/
%}

%option noyywrap
%option yylineno

id 		[a-zA-Z_]+
string		\"(\\\"|[^"])+\"

%%

[ \t\n]+	{}

^#.*		{}

{string}	{
		yylval = strdup(yytext);
		return STRING;
		}

"CAD"		{
		return CAD;
		}

"CAD_OPC"	{
		return CAD_OPC;
		}

"TIPO"		{
		return TIPO;
		}

"VAR"		{
		return VAR;
		}

"REGLA"		{
		return REGLA;
		}

"FIN_REGLA"	{
		return FIN_REGLA;
		}


{id}		{
		yylval = strdup(yytext);
		return ID;
		}


.		{
		strcpy(msj, "Error LEXICO: ");
		strcat(msj, yytext);
		yyerror(msj);
		}

%%
