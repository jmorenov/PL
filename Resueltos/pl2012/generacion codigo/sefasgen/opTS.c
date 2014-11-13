/************************************
  Funciones que operan directamente
  con la Tabla de Simbolos
  Utilizadas por el padre
 ************************************/
 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "tabsim.h"
#include "opTS.h"

extern int yylineno;

/******************************
  Variables globales
 ******************************/

stEntrada tSimbolos[MAX_TS];
tDato tipoAux;


int pos;

int tope;	/* Indice de la tabla de simbolos */
int bloque;	/* Indice del bloque actual ( = indice ID proc ) */
int blqAnt;
tValor valor;
char *lexTemp;


int contador;
int iniProc;
int numPar;
int posTope;
int posParam;

int nbytes;
char msj[4];
int tam;

/*******************************************************
  Imprime el tipo de dato que se pasa como argumento
  funcion auxiliar
 *******************************************************/

void impTipo(tDato tipo)
{
	switch(tipo) {
		case ENTERO:
			printf("entero");
			break;
		case REAL:
			printf("real");
			break;
		case BOOLEANO:
			printf("booleano");
			break;
		case CARACTER:
			printf("caracter");
			break;
		case LISTA_ENTERO:
			printf("lista de enteros");
			break;
		case LISTA_REAL:
			printf("lista de reales");
			break;
		case LISTA_BOOLEANO:
			printf("lista de booleanos");
			break;
		case LISTA_CARACTER:
			printf("lista de caracteres");
			break;
		case STRING:
			printf("<STRING>");
			break;
		default:
			printf("¿¿??");
			break;
		}

	return;
}

/*******************************************************
  Realiza la suma/resta de tipos de datos
  Supone que los tipos de dato coinciden
 *******************************************************/

void operar(stEntrada *destino, stEntrada op1, stEntrada op2, int operacion)
{
	switch(op1.tipoDato) {
		case ENTERO:
			if ( operacion == 1 )
				destino->valor.entero = op1.valor.entero
					+ op2.valor.entero;
			else
				destino->valor.entero = op1.valor.entero
					- op2.valor.entero;

			break;

		case REAL:
			if ( operacion == 1 )
				destino->valor.real = op1.valor.real
					+ op2.valor.real;
			else
				destino->valor.real = op1.valor.real
					- op2.valor.real;

			break;


		case CARACTER:
			if ( operacion == 1 )
				destino->valor.caracter = op1.valor.caracter
					+ op2.valor.caracter;
			else
				destino->valor.caracter = op1.valor.caracter
					- op2.valor.caracter;

			break;

		default:
			printf("\nSuma / resta de listas NO implementada\n");
			break;
		}
}




/*******************************************************
  Actualizar el valor de un simbolo almacenado
  en la tabla de Simbolos

  Supone que el nuevo valor es adecuado para el
  tipo de dato almacenado
 *******************************************************/

void actualizaTS(char *lexema, tValor valor)
{
	int i = 0;
	int e = 0;

	/* Buscamos la variable en el ultimo ambito */
	
	i = tope;

	while ( i >= 0 && e == 0 ) {

		if ( !strcmp(tSimbolos[i].lexema, lexema) ) {

			printf("\n %s ", tSimbolos[i].lexema);

			switch(tSimbolos[i].tipoDato) {
				case ENTERO:
					tSimbolos[i].valor.entero =
						valor.entero;
					printf("Nuevo valor: %d\n"
						, tSimbolos[i].valor.entero);
					break;
				case REAL:
					tSimbolos[i].valor.real =
						valor.real;
					printf("Nuevo valor: %f\n"
						, tSimbolos[i].valor.real);

					break;
				case CARACTER:
					tSimbolos[i].valor.caracter =
						valor.caracter;
					printf("Nuevo valor: %c\n"
						, tSimbolos[i].valor.caracter);

					break;
				case BOOLEANO:
					tSimbolos[i].valor.booleano =
						valor.booleano;
					printf("Nuevo valor: %d\n"
						, tSimbolos[i].valor.booleano);

					break;
				default:
					printf("\nActualizacion de tipo ");
					impTipo(tSimbolos[i].tipoDato);
					printf(" no implementada\n");
					break;
				}

			e = 1;
		} else
			i--;
		}
}


/*******************************************************
  Introducir identificador en la TS
  con tipo NO_ASIG
  Verifica si el identificador ya se encuentra en la TS
 *******************************************************/

void introTS(stEntrada entrada, tEntrada tipoTS) 
{
	int j = 0;
	int e = 0;


	if ( tipoTS == MARCA ) {

		tope++;
		tSimbolos[tope].lexema = strdup(entrada.lexema);
		tSimbolos[tope].tipoTs = MARCA;
		tSimbolos[tope].tipoDato = NO_ASIG;
		tSimbolos[tope].nParam = -1;

		return;
		}

	if ( tipoTS == DESC_CTRL ) {
		tope++;
		tSimbolos[tope].lexema = strdup(entrada.lexema);
		tSimbolos[tope].tipoTs = DESC_CTRL;
		tSimbolos[tope].tipoDato = NO_ASIG;
		tSimbolos[tope].etqtEnt = strdup(entrada.etqtEnt);
		tSimbolos[tope].etqtSal = strdup(entrada.etqtSal);
		tSimbolos[tope].etqtElse = strdup(entrada.etqtElse);
		tSimbolos[tope].nomVarCtrl = strdup(entrada.nomVarCtrl);

		return;
		}

		
	/*******************************************
	  Busqueda en el ambito de la variable
	  Dentro de su bloque
	 *******************************************/

	j = (bloque>0)?bloque:0;

	while ( (j <= tope) && (tope != -1) ) {

		if ( (!strcmp(tSimbolos[j].lexema, entrada.lexema)) ) {

			e = 1;
			printf("\nError en la linea <NO_APLICABLE> ");
			printf("Identificador duplicado: %s\n"
				, entrada.lexema);
			break;

		} else if ( (!strcmp(tSimbolos[j].lexema, "{"))
			&& (tSimbolos[j].nParam > -1) ) {

				/****************************************
				  Nos saltamos los parametros formales
				  que ya no podemos referenciar
				  +2 por las 2 marcas "{" y "}"
				 ****************************************/

				j += 2+tSimbolos[j].nParam;

		} else {
			j++;
			}
		}

	/****************************************
	  Si no la hemos encontrado, podemos
	  insertarla en la tabla de simbolos
	 ****************************************/

	if ( e == 0 ) {

		printf("Procedemos a la insercion...\n");
		
		tope++;
		tSimbolos[tope].lexema = strdup(entrada.lexema);
		tSimbolos[tope].tipoTs = tipoTS;
		tSimbolos[tope].tipoDato = entrada.tipoDato;
		tSimbolos[tope].nParam = -1;

		/****************************************************
		  Si es un PROCedimiento, inicializamos el nº de
		  parametros a 0
		 ****************************************************/
		
		if ( tipoTS == PROC ) {
			tSimbolos[tope].nParam = 0;
			blqAnt = (bloque == -1)?0:bloque;
			bloque = tope;
			printf("\n>> Ini_bloque: %d\n", bloque);
			
			// Debemos almacenar pos para los parametros
			
			iniProc = tope;
			numPar = 0;
			}

		/****************************************************
		  Si es un parametro formal, actualizamos
		  el nº de parametros en la entrada de la
		  tabla de simbolos corespondiente al procedimiento
		 ****************************************************/

		if ( tipoTS == PAR_FORMAL ) {
			// DEBUG
			
			tSimbolos[iniProc].nParam++;
			numPar = tSimbolos[iniProc].nParam;
			printf(">> Actualizado num parametros: %d\n"
				, tSimbolos[pos].nParam);
			}
			


		printf(">> Lexema: %s tope: %d bloque: %d ", tSimbolos[tope].lexema
			, tope, bloque);
		printf("tipoTS: ");

		switch ( tipoTS ) {
			case VARIABLE:
					printf("variable");
					break;

			case PROC:
					printf("procedimiento");
					break;

			case PAR_FORMAL:
					printf("parametro formal");
					break;
			case MARCA:
					printf("marca");
					break;
			default:
					printf("Incorrecto ???");
					break;
			}

		printf(" Tipo Dato: ");
		impTipo(tSimbolos[tope].tipoDato);
		printf("\n");
		}
	}

/*****************************************************
  Al llegar al fin de bloque sacar simbolos de la TS
 *****************************************************/

void sacarTS() 
{
	int i = 0, aux;
	int finPar, iniPar;

	printf("\n<< Fin bloque: %d\n", bloque);

	while ( i == 0 ) {
	
		printf("<< Desechando TS[%d] = %s\n", tope, tSimbolos[tope].lexema);

		if ( !strcmp(tSimbolos[tope].lexema, "}") ) {

			if ( tSimbolos[tope].nParam < 0 ) {
				i = 1;
				finPar = tope;
			} else {
				tope -= 2 + tSimbolos[tope].nParam;
				}
		} else {
			tope--;
			}
		}


	i = 0;
	aux = finPar - 1;


	/* Buscamos la pareja de "}" que hemos encontrado */

	while ( i == 0 && aux != -1 ) {

		if ( !strcmp(tSimbolos[aux].lexema, "{") ) {
			i = 1;
			iniPar = aux;
			}
		
		aux--;
		}

	/* Actualizamos el inicio y cierre 
	para saltar los parametros formales */

	tSimbolos[iniPar].nParam = tSimbolos[bloque].nParam;
	tSimbolos[finPar].nParam = tSimbolos[bloque].nParam;

	tope = finPar;
	
	aux = iniPar -1;
	i = 0;


	printf("<< Buscando bloque anterior\n");

	/***********************************
	  Buscamos el bloque en el que
	  estamos
	 ***********************************/

	while ( i == 0 && aux != -1 ) {

		printf("<< TS[%d] = %s\n", aux, tSimbolos[aux].lexema);

		if ( (!strcmp(tSimbolos[aux].lexema, "{"))
			&& ( tSimbolos[aux].nParam < 0 ) )
			i = 1;
		else
			aux--;
		}

	if ( i == 1 )
		bloque = aux - 1;
	else
		bloque = 0;

	printf("<< Tras sacar, bloque: %d tope: %d\n"
		, bloque, tope);
}

/*********************************************

  Busca un ID en la TS y nos devuelve el tipo

 ********************************************************/


tDato buscaTS(char *identif, int *pos)
{
	int j = 0;
	int e = 0;
	tDato tipo;

	j = tope;

	printf("\n?? Busqueda en TS de %s\n", identif);

	while ( (j >= 0) && (j >= bloque)) {


		if ( !strcmp(tSimbolos[j].lexema, identif) ) {

			tipo = tSimbolos[j].tipoDato;
			e = 1;
			*pos = j;
			printf("?? Encontrado %s en %d\n", identif, j);

			break;

		} else if ( (!strcmp(tSimbolos[j].lexema, "}"))
			&& ( tSimbolos[j].nParam > -1 ) ) {
			
			printf("?? Saltamos de %d ", j);
			j -= (2 + tSimbolos[j].nParam);
			printf("a %d\n", j);

		} else {
			j--;
			}
		}

	if ( e == 0 ) {
		printf("\nPADRE: Error en la linea <NO_AP> ");
		printf("Identificador no declarado %s\n", identif);
		tipo = DESC;
		j = -1;
		}

	return tipo;
}


/******************************************************
  Funcion encargada de buscar en la TS los datos
  necesarios para comprobar la llamada a un PROC

  - Posicion en la tabla de simbolos 
	del ID del procedimiento
  - Nº de argumentos

 ******************************************************/

void buscarPROC(char *identif, int *posIni, int *numParam) {
	int j = 0;
	int e = 0;
	tDato tipo;

	j = tope;

	printf("\nPP Busqueda de procedimiento %s ", identif);

	while ( j >= 0 && j >= bloque) {

		if ( !strcmp(tSimbolos[j].lexema, identif) ) {
			tipo = tSimbolos[j].tipoDato;
			e = 1;
			break;
		} else {
			j--;
			}
		}

	if ( e == 0 ) {
		printf("\nError en la linea <NO_AP> ");
		printf("Identificador no declarado %s\n", identif);
		tipo = DESC;
		*posIni = -1;
		*numParam = -1;
	} else {
		*posIni = j;
		*numParam = tSimbolos[j].nParam;

		printf("pos: %d num parametros: %d\n"
			, *posIni, *numParam);
		}
	}


/********************************************************************
  Busqueda del tipo de dato de un argumento de PROCEDIMIENTO
  posParam indica la posicion en la TS del argumento actual
  posTope indica posicion tope para argumentos del PROC actual
  
  TODO: Ampliar funcionalidad a FUNCIONES Con estas, se pueden
  	anidar las llamadas restar(suma(4,multiplicar(2,4)),4) !!!!
  	
  Devuelve:
  	0 -> Correcto
  	1 -> Numero de argumentos incorrecto
  	2 -> Tipo incorrecto
 ********************************************************************/
 
unsigned char buscarPARAM(tDato tipo) {
	
	if ( posParam == posTope )
		return 1;
	
	if ( tipo != tSimbolos[posParam].tipoDato )
		return 2;
	
	posParam++;

	return 0;
	}


/**
 Busqueda de una de las etiquetas del ULTIMO descriptor de control
 @param tipo Tipo de etiqueta buscada
 */

char *buscarEtqTS(unsigned char tipo) {
	int j = 0, i;
	int e = 0, tam;
	char *etq;
	char *etqAux;

	j = tope;

	while ( (j >= 0) && (j >= bloque) && e == 0 ) {

		if ( tSimbolos[j].tipoTs == DESC_CTRL ) {

			i = j;
			e = 1;
			}
		j++;
		}

	if ( e == 0 ) {
		etq = (char *) malloc (3 * sizeof(char));
		strcpy(etq, "EB");
		return etq;
		}

	switch(tipo) {
		case ETQ_ENT:
			etqAux = tSimbolos[i].etqtEnt;
			break;
		case ETQ_SAL:
			etqAux = tSimbolos[i].etqtSal;
			break;
		case ETQ_ELSE:
			etqAux = tSimbolos[i].etqtElse;
			break;
		}

	tam = strlen(etqAux);
	etq = (char *) malloc ((tam+1) * sizeof(char));
	if ( etq == NULL ) {
		etq = (char *) malloc (3 * sizeof(char));
		strcpy(etq, "EM");
		return etq;
		}

	strcpy(etq, etqAux);
	
	return etq;
	}
	 	
/**
 Eliminar de la TS todos los simbolos hasta el ultimo
 descriptor de instruccion de control
 @return Numero de registros eliminados
 ********************************************************/

int sacarCtrlTS(void) {
	int num = 0;

	while( tSimbolos[tope].tipoTs != DESC_CTRL ) {

		if ( tSimbolos[tope].lexema != NULL ) {
			free(tSimbolos[tope].lexema);
			num++;
			}

		tope--;
		}


	free(tSimbolos[tope].nomVarCtrl);
	free(tSimbolos[tope].etqtSal);
	free(tSimbolos[tope].etqtElse);
	free(tSimbolos[tope].etqtEnt);

	num++;
	tope--;

	return num;
}



