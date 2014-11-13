%token ID STRING VAR CAD TIPO CAD_OPC
%token REGLA FIN_REGLA

%start ESQUEMA

%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "msj.err"
#include "regTrad.h"

#define CAMPO_NULO 255

#define YYSTYPE char *

extern int yylineno;
extern char *yytext;

extern Traduccion rgls[MAX_REGLAS];
extern int nRgls;

int indxRegla = 0;
int indxCampo = 0;
int i;

/******************
int tipoTemp;
char *argTemp;

int tipos[MAX_CAMPOS];
char *args[MAX_CAMPOS];
*************************/
%}

%%

ESQUEMA : ESQUEMA DEC_REGLA
	| DEC_REGLA
	;

DEC_REGLA : REGLA ID
	{
	/**********
	printf("Regla: %d id: %s\n", indxRegla, $2);
	printf("\tFormato: %s\n", $4);
	***************/

	rgls[indxRegla].nombre = strdup($2);
	free($2);	

	rgls[indxRegla].numCampos = 0;
	indxCampo = 0;
	}
	LISTA_CAMPOS FIN_REGLA
	{
	/*********
	printf("Fin regla: %d\n", indxRegla);
	*************/

	indxRegla++;
	nRgls++;
	}
	;

LISTA_CAMPOS : LISTA_CAMPOS TIPO_CAMPO
	| TIPO_CAMPO
	;

TIPO_CAMPO : CAD
	{
	rgls[indxRegla].numCampos++;
	rgls[indxRegla].tipos[indxCampo] = ARG_CAD;
	indxCampo++;
	}
	| TIPO
	{
	rgls[indxRegla].numCampos++;
	rgls[indxRegla].tipos[indxCampo] = ARG_TIPO;
	indxCampo++;
	}
	| VAR
	{
	rgls[indxRegla].numCampos++;
	rgls[indxRegla].tipos[indxCampo] = ARG_VAR;
	indxCampo++;
	}
	| CAD_OPC
	{
	rgls[indxRegla].numCampos++;
	rgls[indxRegla].tipos[indxCampo] = ARG_CAD_OPC;
	indxCampo++;
	}
	| STRING
	{
	rgls[indxRegla].numCampos++;
	rgls[indxRegla].tipos[indxCampo] = ARG_STRING;
	rgls[indxRegla].args[indxCampo] = strdup($1);
	free($1);
	indxCampo++;
	}
	|
	;

%%

void yyerror(char *s)
{
	fprintf(stderr, "ERROR (Linea %d) %s y aparece %s\n"
		, yylineno, s, yytext);
}

/********
int main() {
	yyparse();
	return 0;
	}
 *******************/



