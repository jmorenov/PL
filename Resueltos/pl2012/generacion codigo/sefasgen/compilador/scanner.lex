/*******************************************************
 Analizador Lexico para la gramatica de ejemplo
 *******************************************************/


%option noyywrap
%option yylineno

%{

/* Definiciones de los codigos de token */
/* Usamos el fichero generado con yacc -d */

#include <string.h>
#include <stdio.h>
#include "y.tab.h"
// #include "tabsim.h"

#include "sefasgen.h"

#define COL_TABULADOR 4

extern void yyerror(char *s);

int num_linea = 0;
char errlex[255];
tEntrada tipoTS;

/* Variables de localizacion */

static int linI = 0;
static int linF = 0;
static int colI = 0;
static int colF = 0;

extern stEntrada yylval;

void actualizarLoc(stEntrada *reg, int tamToken);

%}

%%

[ \t]+		{ 
		/* Quitamos los espacios en blanco */
		colI += yyleng;
		// fprintf(stderr, "BLANCO -> colI: %d\n", colI);
		}

\n+		{ 
		num_linea++;
		// Los retornos de carro son 1 CARACTER !!!
		colI += yyleng;

		// linI += yyleng;
		// linF = linI;
		// fprintf(stderr, "NewLine -> linI: %d\n", linI);
		}

procedimiento	{
		if ( yylval.lexema != NULL )
			free(yylval.lexema);

		// yylval.lexema = strdup("{");

		colF = colI + yyleng - 1;

		// fprintf(stderr, "Actualizado colF: %d\n", colF);
		yylval.linIni = linI;
		yylval.linFin = linF;
		yylval.colIni = colI;
		yylval.colFin = colF;

		// Actualizamos para el siguiente
		colI = colF+1;
		colF = colI;

		return(PROCEDIMIENTO);
		}

principal	{
		/*******************
		if ( yylval.lexema != NULL )
			free(yylval.lexema);
		 *********************************/

		yylval.lexema = strdup(yytext);

		colF = colI + yyleng - 1;

		// fprintf(stderr, "Actualizado colF: %d\n", colF);

		yylval.linIni = linI;
		yylval.linFin = linF;
		yylval.colIni = colI;
		yylval.colFin = colF;

		// Actualizamos para el siguiente
		colI = colF+1;
		colF = colI;

		return(PRINCIPAL);
		}

ini_variables	{ 
		colI += yyleng;
		return(DELIM_VAR1);
		}

fin_variables	{
		colI += yyleng; 
		return(DELIM_VAR2);
		}

leer		{
		/** Si queremos que se seleccione, debemos localizar */

		colF = colI + yyleng - 1;
		// yylval.linIni = linI;
		// yylval.linFin = linF;
		yylval.colIni = colI;
		yylval.colFin = colF;

		// Actualizamos para el siguiente
		colI = colF+1;
		colF = colI;

		return(LEER);
		}

escribir	{
		actualizarLoc(&yylval, yyleng);

		return(ESCRIBIR);
		}

si		{
		colF = colI + yyleng - 1;

		// fprintf(stderr, "Actualizado colF: %d\n", colF);

		yylval.linIni = linI;
		yylval.linFin = linF;
		yylval.colIni = colI;
		yylval.colFin = colF;

		// Actualizamos para el siguiente
		colI = colF+1;
		colF = colI;

		return(SI);
		}

sino		{
		colF = colI + yyleng - 1;

		// fprintf(stderr, "Actualizado colF: %d\n", colF);

		yylval.linIni = linI;
		yylval.linFin = linF;
		yylval.colIni = colI;
		yylval.colFin = colF;

		// Actualizamos para el siguiente
		colI = colF+1;
		colF = colI;

		return(SINO);
		}

mientras	{ colI += yyleng; return(MIENTRAS); }

en_caso_de_que	{ colI += yyleng; return(SWITCH); }

caso		{ colI += yyleng; return(CASO); }

saltar		{ colI += yyleng; return(SALTAR); }

defecto		{ colI += yyleng; return(DEFECTO); }

"{"		{
		colF = colI + yyleng - 1;

		yylval.colIni = colI;
		yylval.colFin = colF;
		yylval.linIni = linI;
		yylval.linFin = linF; 

		// Actualizamos para el siguiente
		colI = colF+1;
		colF = colI;

		return(LLAVE_ABRE);
		}

"}"		{
		colF = colI + yyleng - 1;

		yylval.colIni = colI;
		yylval.colFin = colF;
		yylval.linIni = linI;
		yylval.linFin = linF; 

		// Actualizamos para el siguiente
		colI = colF+1;
		colF = colI;

		return(LLAVE_CIERRA);
		}

"("		{
		colF = colI + yyleng - 1;

		yylval.colIni = colI;
		yylval.colFin = colF;
		yylval.linIni = linI;
		yylval.linFin = linF; 
		// Daba problemas el strdup ????
		// yylval.lexema = strdup(yytext);

		// Actualizamos para el siguiente
		colI = colF+1;
		colF = colI;

		return(PARENT_ABRE);
		}

")"		{
		colF = colI + yyleng - 1;

		yylval.colIni = colI;
		yylval.colFin = colF;
		yylval.linIni = linI;
		yylval.linFin = linF; 
		// Daba problemas el strdup ???
		// yylval.lexema = strdup(yytext);

		// Actualizamos para el siguiente
		colI = colF+1;
		colF = colI;

		return(PARENT_CIERRA);
		}

"["		{ colI += yyleng; return(CORCHETE_ABRE); }

"]"		{ colI += yyleng; return(CORCHETE_CIERRA); }

";"		{ colI += yyleng; return(PUNTO_COMA); }

","		{ colI += yyleng; return(COMA); }

":"		{ colI += yyleng; return(DOSPUNTOS); }

"real"		{
		colI += yyleng; 
		yylval.tipoDato = REAL;
		return(TIPO);
		}

"entero"	{
		colI += yyleng; 
		yylval.tipoDato = ENTERO;
		return(TIPO);
		}

"caracter"	{
		colI += yyleng; 
		yylval.tipoDato = CARACTER;
		return(TIPO);
		}

"booleano"	{
		colI += yyleng; 
		yylval.tipoDato = BOOLEANO;
		return(TIPO);
		}

"lista_real"		{
			colI += yyleng; 
			yylval.tipoDato = LISTA_REAL;
			return(TIPO);
			}

"lista_entero"		{
			colI += yyleng; 
			yylval.tipoDato = LISTA_ENTERO;
			return(TIPO);
			}

"lista_caracter"	{
			colI += yyleng; 
			yylval.tipoDato = LISTA_CARACTER;
			return(TIPO);
			}

"lista_booleano"	{
			colI += yyleng; 
			yylval.tipoDato = LISTA_BOOLEANO;
			return(TIPO);
			}
			

"+"|"-"			{
			colF = colI + yyleng - 1;

			yylval.colIni = colI;
			yylval.colFin = colF;
			yylval.linIni = linI;
			yylval.linFin = linF;
			/***********************************
			  TODO: Arreglar esto de una vez
			  TODO: SIEMPRE DA PROBLEMAS ¿¿ ???
			 ************************************/

			yylval.lexema = strdup(yytext);

			// Actualizamos para el siguiente
			colI = colF+1;
			colF = colI;

			if ( !strcmp(yytext, "+") )
				yylval.nParam = 1; 
			else
				yylval.nParam = 2;
	
			return(OP_ARIT12);
			}

"*"|"/"|"^"|"&"|"|"	{
			colF = colI + yyleng - 1;

			yylval.colIni = colI;
			yylval.colFin = colF;
			yylval.linIni = linI;
			yylval.linFin = linF; 

			// Actualizamos para el siguiente
			colI = colF+1;
			colF = colI;


			if ( !strcmp(yytext, "*") )
				yylval.nParam = 1;
			else if ( !strcmp(yytext, "/") )
				yylval.nParam = 2;
			else if ( !strcmp(yytext, "^") )
				yylval.nParam = 3;
			else if ( !strcmp(yytext, "&") )
				yylval.nParam = 4;
			else
				yylval.nParam = 5;
 
			yylval.lexema = strdup(yytext);
			return(OP_ARIT2);
			}

"="		{ colI += yyleng; return(IGUAL); }

"!"		{
		colF = colI + yyleng - 1;

		yylval.colIni = colI;
		yylval.colFin = colF;
		yylval.linIni = linI;
		yylval.linFin = linF; 
		yylval.lexema = strdup(yytext);

		// Actualizamos para el siguiente
		colI = colF+1;
		colF = colI;

		return(OP_LOGICO1);
		}

"&&"|"||"	{
		if ( !strcmp(yytext, "&&") )
			yylval.nParam = 1;
		else
			yylval.nParam = 2;

		colF = colI + yyleng - 1;

		yylval.colIni = colI;
		yylval.colFin = colF;
		yylval.linIni = linI;
		yylval.linFin = linF; 
		yylval.lexema = strdup(yytext);

		// Actualizamos para el siguiente
		colI = colF+1;
		colF = colI;

		return(OP_LOGICO2);
		}

"<"|"<="|">"|">="|==|!=		{
				if ( !strcmp(yytext, "<") )
					yylval.nParam = 1;
				else if ( !strcmp(yytext, "<=") )
					yylval.nParam = 2;
				else if ( !strcmp(yytext, ">") )
					yylval.nParam = 3;
				else if ( !strcmp(yytext, ">=") )
					yylval.nParam = 4;
				else if ( !strcmp(yytext, "==") )
					yylval.nParam = 5;
				else 
					yylval.nParam = 6;


				colF = colI + yyleng - 1;
	
				yylval.colIni = colI;
				yylval.colFin = colF;
				yylval.linIni = linI;
				yylval.linFin = linF; 
				yylval.lexema = strdup(yytext);

				// Actualizamos para el siguiente
				colI = colF + 1;
				colF = colI;

				return(OP_LOGICO3);
				}

[0-9]+			{
			actualizarLoc(&yylval, yyleng);

			yylval.tipoDato = ENTERO;
			yylval.valor.entero = atoi(yytext);
			return(VALOR);
			}

[0-9]+"."[0-9]+		{
			colF = colI + yyleng - 1;

			yylval.colIni = colI;
			yylval.colFin = colF;
			yylval.linIni = linI;
			yylval.linFin = linF; 
			// yylval.lexema = strdup(yytext);

			// Actualizamos para el siguiente
			colI = colF+1;
			colF = colI;

			yylval.tipoDato = REAL;
			yylval.valor.real = atof(yytext);
			return(VALOR);
			}


VERDADERO|FALSO		{
			colF = colI + yyleng - 1;

			yylval.colIni = colI;
			yylval.colFin = colF;
			yylval.linIni = linI;
			yylval.linFin = linF; 
			yylval.lexema = strdup(yytext);

			// Actualizamos para el siguiente
			colI = colF+1;
			colF = colI;


			yylval.tipoDato = BOOLEANO;
			if ( !strcmp(yytext, "VERDADERO") )
				yylval.valor.booleano = 1;
			else
				yylval.valor.booleano = 0;

			return(VALOR);
			}

[a-zA-Z][a-zA-Z_0-9]*	{
			colF = colI + yyleng - 1;

			yylval.colIni = colI;
			yylval.colFin = colF;
			yylval.linIni = linI;
			yylval.linFin = linF; 
			yylval.lexema = strdup(yytext);

			// Actualizamos para el siguiente
			colI = colF+1;
			colF = colI;

			return(IDENTIFICADOR);
			}


"#"|"->"|"<<"|">>"	{
			colI += yyleng;

			if ( !strcmp(yytext, "#") )
				yylval.nParam = 1;
			else if ( !strcmp(yytext, "->") )
				yylval.nParam = 2;
			else if ( !strcmp(yytext, "<<") )
				yylval.nParam = 3;
			else 
				yylval.nParam = 4;

			return(OP_LISTAS1);
			}

"@"|"++"|"%"		{
			colI += yyleng;

			if ( !strcmp(yytext, "@") )
				yylval.nParam = 1;
			else if ( !strcmp(yytext, "++") )
				yylval.nParam = 2;
			else
				yylval.nParam = 3;

			return(OP_LISTAS2);
			}

"."			{ colI += yyleng; return(OP_LISTAS3); }

\\			{ colI += yyleng; return(OP_LISTAS4); } 

\"[^"]+\"		{
			// Cuidado con las cadenas !!!! 
			// No se deberian permitir cadenas MULTI-linea

			colF = colI + yyleng - 1;

			yylval.colIni = colI;
			yylval.colFin = colF;
			yylval.linIni = linI;
			yylval.linFin = linF; 

			// Actualizamos para el siguiente
			colI = colF+1;
			colF = colI;

			// TODO: CUIDADO con ESTO
			yylval.lexema = strdup(yytext);
			return(CADENA);
			}

.		{
		colI += yyleng;

		strcpy(errlex, "Error LEXICO: ");
		strcat(errlex, yytext);  
		yyerror(errlex);

	/**********************
		fprintf(stderr, "HIJO LEX-> (Linea %d) %s y aparece %s\n"
			, yylineno, errlex, yytext);
	 ****************************************************/
		}
		


%%

void actualizarLoc(stEntrada *reg, int tamToken) {
	colF = colI + tamToken - 1;

	reg->colIni = colI;
	reg->colFin = colF;
	reg->linIni = linI;
	reg->linFin = linF; 

	// Actualizamos contadores globales
	colI = colF+1;
	colF = colI;
	}

