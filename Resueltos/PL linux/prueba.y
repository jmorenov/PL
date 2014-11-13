%{
/*********************************************************
**
** Fichero: PRUEBA.Y
** Función: Pruebas de YACC para practicas de PL
**
********************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
/**
***
	La siguiente declaracion permite que ’yyerror’ se pueda invocar desde el
	fuente de lex (prueba.l)
**/
void yyerror( char * msg ) ;
/**
	La siguiente variable se usará para conocer el numero de la línea
	que se esta leyendo en cada momento. También es posible usar la variable
	’yylineno’ que también nos muestra la línea actual. Para ello es necesario
	invocar a flex con la opción ’-l’ (compatibilidad con lex).
**/

int linea_actual = 1 ;
%}
/**
Para uso de mensajes de error sintáctico con BISON.
La siguiente declaración provoca que ’bison’, ante un error sintáctico,
visualice mensajes de error con indicación de los tokens que se esperaban
en el lugar en el que produjo el error (SÓLO FUNCIONA CON BISON=2.1).
Para Bison2.1 es mediante
 YYERROR_VERBOSE
En caso de usar mensajes de error mediante ’mes’ y ’mes2’ (ver apéndice D)
nada de lo anterior debe tenerse en cuenta.
%error-verbose
**/

/**
A continuación declaramos los nombres simbólicos de los tokens.
byacc se encarga de asociar a cada uno un código
**/


%token PRINCIPAL
%token PROCEDIMIENTO
%token TIPO	
%token PILA	
%token CONST	
%token CONSTCADENA	
%token ASIG	
%token MASMAS	
%token MASMENOS
%token OPBIN	
%token OPUNARIO
%token PARIZQ
%token PARDER
%token INIBLQ
%token FINBLQ
%token DELIMITADOR
%token COMA
%token PYC
%token SI
%token SINO	
%token MIENTRAS
%token HACER
%token HASTA
%token ENTRADA
%token SALIDA
%token CORCHETEIZQ
%token CORCHETEDER
%token IDENT
%token OTRO

%left MASMAS
%right OPUNARIO
%left OPBIN
%left MASMENOS

%%
/**
Sección de producciones que definen la gramática.
**/

Programa : Cabecera_programa bloque;
Cabecera_programa : PRINCIPAL PARIZQ PARDER;
bloque : 	INIBLQ Declar_de_variables_locales Declar_de_subprogs Sentencias FINBLQ | 
			INIBLQ Declar_de_variables_locales Sentencias	FINBLQ
			| INIBLQ Declar_de_subprogs	Sentencias FINBLQ
			| INIBLQ Sentencias	FINBLQ;

Declar_de_subprogs : Cabecera_subprog bloque;
Cabecera_subprog : 	PROCEDIMIENTO IDENT PARIZQ parametros PARDER |
					PROCEDIMIENTO IDENT PARIZQ PARDER;
parametros: parametros COMA tipo IDENT | tipo IDENT;

Declar_de_variables_locales : DELIMITADOR Variables_locales DELIMITADOR;
Variables_locales : Variables_locales Cuerpo_declar_variables | Cuerpo_declar_variables;

Cuerpo_declar_variables : tipo lista_nombres PYC;
lista_nombres: lista_nombres COMA IDENT	| IDENT;
tipo : TIPO | PILA TIPO;
Sentencias : Sentencias Sentencia | Sentencia;
Sentencia : bloque
			| sentencia_asignacion
			| sentencia_if
			| sentencia_while
			| sentencia_entrada
			| sentencia_salida
			| sentencia_hacer_hasta
			| llamada_procedimiento;
sentencia_asignacion : IDENT ASIG expresion PYC;
sentencia_if : SI PARIZQ expresion PARDER Sentencia | SI PARIZQ expresion PARDER Sentencia sentencia_else;
sentencia_else : SINO Sentencia;
sentencia_while : MIENTRAS PARIZQ expresion PARDER Sentencia;
sentencia_entrada : ENTRADA lista_nombres PYC;
sentencia_salida : SALIDA expresiones PYC;
sentencia_hacer_hasta : HACER Sentencia HASTA expresion PYC;
llamada_procedimiento : IDENT PARIZQ expresiones PARDER PYC | IDENT PARIZQ PARDER PYC;
expresiones : expresiones COMA expresion | expresion;
expresion :   PARIZQ expresion PARDER 
			| OPUNARIO expresion
			| expresion OPBIN expresion
			| MASMENOS expresion
			| expresion MASMENOS expresion
			| expresion MASMAS expresion
			| IDENT
			| CONST
			| CONSTCADENA
			| constante_pila;
constante_pila : CORCHETEIZQ lista_constantes CORCHETEDER;
lista_constantes : lista_constantes COMA CONST | CONST;


/** esto representa la cadena vacía **/ ;

%%
/** aqui incluimos el fichero generado por el ’lex’
*** que implementa la función ’yylex’
**/
#ifdef DOSWINDOWS
#include "lexyy.c"
#else
#include "lex.yy.c"
#endif
/**
Variable de entorno que indica la plataforma
se debe implementar la función yyerror. En este caso
simplemente escribimos el mensaje de error en pantalla
**/

void yyerror( char *msg )
{
	fprintf(stderr,"[Linea %d]: %s\n", linea_actual, msg) ;
}


