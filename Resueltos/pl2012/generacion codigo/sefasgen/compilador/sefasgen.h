#ifndef __SEFASGEN_H__
#define __SEFASGEN_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*****************************************
  Definicion de la estructura asociada
  a un simbolo de la gramatica
 *****************************************/
 
 
/** @enum
 * Tipo de entrada en la TS
 */

typedef enum { MARCA = 0	/**< Inicio/Fin de bloque */
	, PROC			/**< Procedimiento	  */
	, VARIABLE
	, PAR_FORMAL		/**< Parametro Formal */
	, DESC_CTRL		/**< Descriptor de Control para Saltos */
	, FUNCION		/**< Funcion */
	, RANGO			/**< Rangos para indices ARRAYS	*/
	} tEntrada;

/** @enum
 * Tipos de dato admitidos por el lenguaje
 */

typedef enum { NO_ASIG = 0 	/**< No Asignado */
	, DESC			/**< Desconocido / Erroneo */
	, ENTERO, REAL, LISTA_REAL, LISTA_ENTERO
	, BOOLEANO, LISTA_BOOLEANO, CARACTER, LISTA_CARACTER
	, STRING		/**< Cadena */
	, ARRAY
	, CJTO
	, PILA
	} tDato;

/**
 Valor asociado a entrada de la TS
 */


typedef union valor {
	int entero;
	float real;
	unsigned char booleano;
	char caracter;
	} tValor;

/**
 Entrada de la TS.
 */

typedef struct entrada_ts {
	char *lexema;		/**< Lexema del token */
	tEntrada tipoTs;	/**< Tipo de entrada */
	tDato tipoDato;		/**< Tipo del dato */
	int nParam;		/**< Num parametros formales, si es proc */
	tValor valor;		/**< Valor del token */

	/*** Localizacion en Cod Fuente **/
	int linIni;		/**< Localizacion: linea Inicio */
	int linFin;		/**< Localizacion: linea Fin */
	int colIni;		/**< Localizacion: columna Inicio */
	int colFin;		/**< Localizacion: columna Fin */

	/** NUEVOS CAMPOS */
	int nDim;		/**< Num de dimensiones (ARRAY) */
	tValor minRango;	/**< Valor minimo (CJTO) */
	tValor maxRango;	/**< Valor maximo (CJTO) */
	int minIndx;		/**< Indice minimo (ARRAY) */
	int maxIndx;		/**< Indice maximo (ARRAY) */

	/***  Campos para la GENERACION de CODIGO   *****/

	char *nomTemp;		/**< Nombre de la variable temporal */
	char *etqtEnt;		/**< Nombre etiqueta de entrada */
	char *etqtSal;		/**< Nombre etiqueta de salida */
	char *etqtElse;		/**< Nombre etiqueta else */
	char *nomVarCtrl;	/**< Variable de control en EXP Condicion */
	char *formato;		/**< Cadena de formato para E/S */
	char *variables;	/**< Cadena de variables usadas en E/S */
	} stEntrada;



#define YYSTYPE stEntrada



/************************************
  Funciones disponibles para la
  ejecucion de acciones semánticas
 ************************************/


#define PRINT 	0
#define SCAN 	1

#define COND	0
#define INCOND	1

/** Tipos de etiqueta */

#define ETQ_ENT		0
#define ETQ_SAL		1
#define ETQ_ELSE	2


/***
 Peticiones de operacion
 de la Tabla de Simbolos
***/

int pet_introTS(stEntrada reg, tEntrada tipoTS);
tDato pet_BuscarTS(stEntrada reg);
void pet_SacarTS(void);
int pet_BuscarPROC(stEntrada reg);
unsigned char pet_BuscarPARAM(stEntrada reg);
int pet_VerifTIPO(stEntrada reg1, stEntrada reg2);

/*** Peticiones de GENERACION de CODIGO   ***/

void pet_GenIni(void);

// void pet_GenFin(void);

void pet_GenDecVar(tDato tipo, char *nom);
void pet_GenIniBlq(char *comentario, int ini, int fin);
void pet_GenFinBlq(void);
void pet_GenAsig(int nOp, char *op1, char *op2, char *, char *);
char *pet_GenTemp(void);
void pet_GenCadFormato(int ini, int fin
	, char **formato, char **vars, tDato tipo
	, char *nuevoArg, unsigned char tipoSent);

void pet_GenENTRADA(char *fmt, char *vars);
void pet_GenSALIDA(char *fmt, char *vars);

void pet_GenSaltoCond(char *nomVar, char *etq);
/** @todo Repasar si hace falta el nombre de la VARIABLE ¿??¿ */
void pet_GenSaltoInCond(char *etq);


char *pet_GenEtiq(void);
void pet_EscEtq(char *etq);
char *pet_BuscarEtq(unsigned char tipoEtq);
void pet_SacarCTRL(void);
void pet_Rango(char *lex, int *min, int *max);

void pet_GenDecProc(char *lex, tDato tipo);
void pet_GenParam(tDato tipo, char *lex);
void pet_GenFinCabecera(void);
void pet_GenFinDecProc(void);
void pet_GenLlamada(char *proc, char *args);


/*** Funciones auxiliares ***/

void check(void);
void reiniciar(void);
void informar(int pos, int tam);
char *convCadena(tDato tipo, tValor valor);


/**
 Variables definidas por FLEX
 */


unsigned char flagREI;

extern int yylineno;
extern FILE *yyin;
extern char *yytext;


#endif
