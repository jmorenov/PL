/** @file
 Definicion entrada TS.
 Entrada TS y funciones adicionales de comunicacion con
 el proceso padre Usado para COMPILADOR
 */

#ifndef __TABSIM_H__
#define __TABSIM_H__


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


#define DECLARA 0
#define LLAMADA 1


#endif
