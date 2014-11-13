%{

/**
 @todo Revisar gestion memoria dinamica...
*/

// Basta incluir este archivo...

#include "sefasgen.h"


tDato tempTipoDato, tipoTemp, tipoAux;
int estado;
unsigned int flag = 0;

char *etqTemp;

int nParam = 0;
int contParam;
int totalParam;
unsigned char tipoOK;
int tamCadena;

//-----------------------------------


%}

%token PROCEDIMIENTO DELIM_VAR1 DELIM_VAR2 LEER ESCRIBIR SI SINO MIENTRAS
%token SWITCH CASO SALTAR DEFECTO LLAVE_ABRE LLAVE_CIERRA PARENT_ABRE
%token PARENT_CIERRA CORCHETE_ABRE CORCHETE_CIERRA PUNTO_COMA COMA TIPO
%token OP_ARIT12 OP_ARIT2 OP_LOGICO1 OP_LOGICO2 OP_LOGICO3 CADENA
%token IDENTIFICADOR VALOR OP_LISTAS1 OP_LISTAS2 OP_LISTAS3 DOSPUNTOS 
%token PRINCIPAL IGUAL OP_LISTAS4

%left OP_ARIT12 
%left OP_ARIT2
%left OP_LOGICO1 OP_LOGICO2
%left OP_LISTAS1 
%left OP_LISTAS2
%left OP_LISTAS4
%left OP_LISTAS3

%right UNARIO
%nonassoc OP_LOGICO3

%start PROGRAMA


%%

PROGRAMA : CABECERA_PROGRAMA 
	{ pet_GenIni(); }
	BLOQUE
	;

CABECERA_PROGRAMA : PROCEDIMIENTO PRINCIPAL PARENT_ABRE PARENT_CIERRA
	{
	$2.tipoDato = NO_ASIG;
	pet_introTS($2, PROC);

	/*************************
	 MARCA
	 TODO: La MARCA se debe introducir al empezar el BLOQUE


	yylval.lexema = strdup("FIN_PARS");
	yylval.tipoDato = NO_ASIG;
	pet_introTS(yylval, MARCA);
	********************************************************/
	}
	| error
	;

BLOQUE : LLAVE_ABRE
	{
	/*******  Aqui deberia INSERTARSE la MARCA !!!  ******/
	/*************************
	 MARCA
	 TODO: La MARCA se debe introducir al empezar el BLOQUE
	********************************************************/

	yylval.lexema = strdup("FIN_PARS");
	yylval.tipoDato = NO_ASIG;
	pet_introTS(yylval, MARCA);

	pet_GenIniBlq(NULL, $1.colIni, $1.colFin);
	}
	CUERPO_BLOQUE LLAVE_CIERRA 
	{
	pet_SacarTS();

	pet_GenFinBlq();
	}
	;

CUERPO_BLOQUE : DEC_VAR DEC_PROCEDIMIENTOS BLQ_SENTENCIAS
	| DEC_VAR DEC_PROCEDIMIENTOS SENTENCIA
	| DEC_VAR BLQ_SENTENCIAS
	| DEC_VAR SENTENCIA
	;

DEC_VAR : DELIM_VAR1 CUERPO_DECLA_VARS DELIM_VAR2
	|
	;

CUERPO_DECLA_VARS : CUERPO_DECLA_VARS DEC_TIPO
	| DEC_TIPO
	;

DEC_TIPO : TIPO
	{ 
	// Esta SI HACE FALTA que este ENMEDIO
	// Si NO, Tenemos que esperar a reconocer TODO !!!
	tempTipoDato = $1.tipoDato;
	}
	CONJ_PALABRAS
	;

CONJ_PALABRAS :  IDENTIFICADOR PUNTO_COMA
	{
	// Modificado para permitir Localizacion de tokens 
	// ORIGINAL: yylval.tipoDato tempTipoDato
	$1.tipoDato = tempTipoDato;
	estado = pet_introTS($1, VARIABLE);


	// TODO: Solo generar la Declaracion de Variables
	// si la peticion de Introduccion ha sido correcta !!!!!

	if ( estado ) {
		pet_GenDecVar($1.tipoDato, $1.lexema);
		}
	}
	| LISTA_PALS IDENTIFICADOR PUNTO_COMA
	{
	// Modificado para permitir Localizacion de tokens  
	$2.tipoDato = tempTipoDato;
	estado = pet_introTS($2, VARIABLE);

	// if ( flagREI ) YYABORT;

	if ( estado ) {
		pet_GenDecVar($2.tipoDato, $2.lexema);
		}
	}
	;

LISTA_PALS : LISTA_PALS IDENTIFICADOR 
	{
	// MOD 
	$2.tipoDato = tempTipoDato;
	estado = pet_introTS($2, VARIABLE);

	// if ( flagREI ) YYABORT;

	if ( estado ) {
		pet_GenDecVar($2.tipoDato, $2.lexema);
		}
	}
	COMA
	| IDENTIFICADOR
	{
	// MOD 
	$1.tipoDato = tempTipoDato;
	estado = pet_introTS($1, VARIABLE);

	// if ( flagREI ) YYABORT;

	if ( estado ) {
		pet_GenDecVar($1.tipoDato, $1.lexema);
		}
	}
	COMA
	| error
	;

DEC_PROCEDIMIENTOS : DEC_PROCEDIMIENTOS DEC_PROC 
	| DEC_PROC
	;

DEC_PROC : CABECERA BLOQUE
	{
	pet_GenFinDecProc();
	}
	;

CABECERA : PROCEDIMIENTO IDENTIFICADOR 
	{
	// MOD 
	$2.tipoDato = NO_ASIG;

	// TODO: Hay que verificar que el PROC no esta declarado
	// Si es asi NO generar CODIGO
	estado = pet_introTS($2, PROC);

	if ( estado ) 
		pet_GenDecProc($2.lexema, NO_ASIG);
	} 
	PARENT_ABRE PARAMETROS PARENT_CIERRA
	{
	pet_GenFinCabecera();

	/***********************************************
	 Ahora metemos otra marca de bloque "}"
	 Nos servira para conservar los parametros
	 cuando acabe el bloque

	 NOOO !!!!  Solo 1 Marca por Bloque!!!
	yylval.tipoDato = NO_ASIG;
	yylval.nParam = -1;
	yylval.lexema = strdup("FIN_PARS");
	pet_introTS(yylval, MARCA);
	************************************************/
	}
	;

PARAMETROS : LISTA_PARAMS
	|
	{
	pet_GenParam(NO_ASIG, NULL);
	}
	| error
	;

LISTA_PARAMS : LISTA_PARAMS COMA TIPO IDENTIFICADOR
	{
	$4.tipoDato = $3.tipoDato;
	estado = pet_introTS($4, PAR_FORMAL);

	if ( estado )
		pet_GenParam($3.tipoDato, $4.lexema);
	}
	| TIPO IDENTIFICADOR
	{
	// MOD3
	$2.tipoDato = $1.tipoDato;
	estado = pet_introTS($2, PAR_FORMAL);

	if ( estado )
		pet_GenParam($1.tipoDato, $2.lexema);
	}
	;

EXPRESION : EXPRESION OP_ARIT12 EXPRESION 
	{
	/**********************************************
	  COMPROBACION DE TIPOS

	  NO SE PIDE LA ASIGNACION DE VALORES !!!!!!!
	  OP_ARIT12 = "+", "-"
	 **********************************************/

	if ( $1.tipoDato == $3.tipoDato ) {
		/************************************************** 
		  La suma/resta se puede hacer para cualquier tipo
		  EXCEPTO para booleanos
		 **************************************************/

		if ( ($1.tipoDato != BOOLEANO) 
			&& ($1.tipoDato != LISTA_BOOLEANO) ) {

			$$.tipoDato = $1.tipoDato;

			/* Hay que definir las operaciones para listas 	*/
			/* $2.nParam define la operacion		*/
			/* 1 = Suma, 2 = Resta				*/

			//  operar(&($$), $1, $3, $2.nParam);
 
		} else {

			fprintf(stderr, "ERROR linea: %d ", yylineno);
			fprintf(stderr, "Op +/- con tipo de dato");
			fprintf(stderr, "incorrecto");

			$$.tipoDato = DESC;
			}
	} else {

		fprintf(stderr, "ERROR linea: %d OP_A12 ", yylineno);
		fprintf(stderr, "Tipos no coinciden ");
		$$.tipoDato = DESC;
		}

	/******************************************
	  Asignacion variables de localizacion
	  TODO: Verificacion TIPO por OPERADOR !!!
	 ******************************************/

	estado = pet_VerifTIPO($1, $3);

	$$.linIni = $1.linIni;
	$$.colIni = $1.colIni;
	$$.linFin = $3.linFin;
	$$.colFin = $3.colFin;

	$$.nomTemp = pet_GenTemp();

	if ( estado ) {
		$$.tipoDato = $1.tipoDato;
		pet_GenDecVar($$.tipoDato, $$.nomTemp);

		fprintf(stderr, "ASIG %s = %s %s %s\n"
			, $$.nomTemp, $1.nomTemp
			, $2.lexema, $3.nomTemp);

		pet_GenAsig(4, $$.nomTemp, $1.nomTemp
			, $2.lexema, $3.nomTemp);
	} else {
		$$.tipoDato = DESC;
		}
	}
	| EXPRESION OP_ARIT2 EXPRESION 
	{
	/***********************************
	  Comprobacion de tipos
	 ***********************************/

	if ( $1.tipoDato == $3.tipoDato ) {
		
		if ( ($1.tipoDato == BOOLEANO) 
			|| ($1.tipoDato == LISTA_BOOLEANO) ) {

			fprintf(stderr, "Error linea %d", yylineno);
			fprintf(stderr, " OP_A2 no definida para ");
			fprintf(stderr, "BOOLEANO o LISTA_BOOLEANO\n");

			$$.tipoDato = DESC;
		
		} else {
			$$.tipoDato = $1.tipoDato;
			}

	} else {
		fprintf(stderr, "Error linea: %d ", yylineno);
		fprintf(stderr, "OP_A2 Tipos no coinciden\n");
		$$.tipoDato = DESC;
		}

	/***************************************
	  Asignacion variables de localizacion
	 ***************************************/

	// TODO: Verificacion TIPO correcto para OPERADOR
	estado = pet_VerifTIPO($1, $3);

	$$.linIni = $1.linIni;
	$$.colIni = $1.colIni;
	$$.linFin = $3.linFin;
	$$.colFin = $3.colFin;

	$$.nomTemp = pet_GenTemp();

	if ( estado ) {
		$$.tipoDato = $1.tipoDato;
		pet_GenDecVar($$.tipoDato, $$.nomTemp);

		fprintf(stderr, "ASIG %s = %s %s %s\n"
			, $$.nomTemp, $1.nomTemp
			, $2.lexema, $3.nomTemp);

		pet_GenAsig(4, $$.nomTemp, $1.nomTemp
			, $2.lexema, $3.nomTemp);

	} else {
		$$.tipoDato = DESC;
		}

	}
	| EXPRESION OP_LOGICO2 EXPRESION
	{
	/***********************************************
	  Como en C o solo se puede con BOOLEANOS ???
	  OP_LOGICO2 = "&&" o "||"
	 ***********************************************/

	/***************************************
	  Asignacion variables de localizacion
	 ***************************************/

	estado = pet_VerifTIPO($1, $3);

	$$.linIni = $1.linIni;
	$$.colIni = $1.colIni;
	$$.linFin = $3.linFin;
	$$.colFin = $3.colFin;

	if ( estado ) {
		if ( ($1.tipoDato == BOOLEANO) 
			|| ($1.tipoDato == LISTA_BOOLEANO) ) {

			$$.nomTemp = pet_GenTemp();
			$$.tipoDato = $1.tipoDato;

			pet_GenDecVar($$.tipoDato, $$.nomTemp);

			fprintf(stderr, "ASIG %s = %s %s %s\n"
				, $$.nomTemp, $1.nomTemp
				, $2.lexema, $3.nomTemp);

			pet_GenAsig(4, $$.nomTemp, $1.nomTemp
				, $2.lexema, $3.nomTemp);

		} else {
			$$.nomTemp = strdup("tempNO_BOOL\n");
			$$.tipoDato = DESC;

			fprintf(stderr, "ERROR Linea: %d Tipos no booleanos\n"
				, yylineno);
			}

	} else {
		fprintf(stderr, "Error Linea: %d ", yylineno);
		fprintf(stderr, "Tipos no coinciden\n");

		$$.tipoDato = DESC;
		$$.nomTemp = strdup("tempERRTipo");
		}
 	}
	| EXPRESION OP_LOGICO3 EXPRESION
	{
	/***************************************
	  OP_LOGICO3 = "<", "<=", ... , "!="
	 ***************************************/

	estado = pet_VerifTIPO($1, $3);

	$$.linIni = $1.linIni;
	$$.colIni = $1.colIni;
	$$.linFin = $3.linFin;
	$$.colFin = $3.colFin;

	if ( estado ) {

		$$.nomTemp = pet_GenTemp();
		$$.tipoDato = BOOLEANO;

		pet_GenDecVar($$.tipoDato, $$.nomTemp);

		fprintf(stderr, "ASIG %s = %s %s %s\n"
			, $$.nomTemp, $1.nomTemp
			, $2.lexema, $3.nomTemp);

		pet_GenAsig(4, $$.nomTemp, $1.nomTemp
				, $2.lexema, $3.nomTemp);

	} else {
		fprintf(stderr, "Error Linea: %d ", yylineno);
		fprintf(stderr, "Tipos no coinciden\n");

		$$.tipoDato = DESC;
		$$.nomTemp = strdup("tempERRTipo");
		}
 	}
	| OP_ARIT12 EXPRESION %prec UNARIO
	{
	if ( ($2.tipoDato == ENTERO) || ($2.tipoDato == LISTA_ENTERO)
		|| ($2.tipoDato == REAL ) || ($2.tipoDato == LISTA_REAL) )

		$$.tipoDato = $2.tipoDato;

	else {
		fprintf(stderr, "\nError linea %d", yylineno);
		fprintf(stderr, " Op con tipo de dato incorrecto\n");

		$$.tipoDato = DESC;
		}

	/***************************************
	  Asignacion variables de localizacion
	 ***************************************/

	// TODO: Check TIPO para OPERADOR...

	$$.linIni = $1.linIni;
	$$.colIni = $1.colIni;
	$$.linFin = $2.linFin;
	$$.colFin = $2.colFin;

	$$.nomTemp = pet_GenTemp();

	// Falta Declaracion de TEMP
	// Conversion en cadena
	// Asignacion
	$$.tipoDato = $2.tipoDato;
	pet_GenDecVar($$.tipoDato, $$.nomTemp);
	pet_GenAsig(3, $$.nomTemp, $1.lexema, $2.nomTemp, NULL);
 	}
	| VALOR 
	{
	$$.tipoDato = $1.tipoDato;

	// CONVERSION de un VALOR en una CADENA

	$$.nomTemp = convCadena($$.tipoDato, $1.valor);
	fprintf(stderr, "[COMP] convCadena $$.nomTemp: %s\n", $$.nomTemp);


	/***************************************
	  Asignacion variables de localizacion
	 ***************************************/

	$$.linIni = $1.linIni;
	$$.colIni = $1.colIni;
	$$.linFin = $1.linFin;
	$$.colFin = $1.colFin;
	}
	| PARENT_ABRE EXPRESION PARENT_CIERRA
	{
	$$.tipoDato = $2.tipoDato;

	/***************************************
	  Asignacion variables de localizacion
	  CHECK-TODO: Asignar localizacion a los parentesis
	 ***************************************/

	$$.linIni = $1.linIni;
	$$.colIni = $1.colIni;
	$$.linFin = $3.linFin;
	$$.colFin = $3.colFin;

	$$.nomTemp = strdup($2.nomTemp);

	// DEBUG
	fprintf(stderr, "nombre Temp: %s\n", $$.nomTemp);
	}
	| OP_LOGICO1 EXPRESION
	{
	/******************************************
	  OP_LOGICO1 = "!"
	  Solo para BOOLEANOS
	  CHECK: Asignar localizacion al OP_LOGICO1
	 ******************************************/

	if ( ($2.tipoDato == BOOLEANO) || ($2.tipoDato == LISTA_BOOLEANO) )
		$$.tipoDato = $2.tipoDato;
	else {
		fprintf(stderr, "\nError linea: %d ", yylineno);
		fprintf(stderr, "Tipo de dato incorrecto\n");
	
		$$.tipoDato = DESC;
		}

	/***************************************
	  Asignacion variables de localizacion
	 ***************************************/

	// TODO: Check TIPO para OPERADOR...

	$$.linIni = $1.linIni;
	$$.colIni = $1.colIni;
	$$.linFin = $2.linFin;
	$$.colFin = $2.colFin;
	}
	| OPERAR_LISTA
	| IDENTIFICADOR 
	{ 
	$$.tipoDato = pet_BuscarTS(yylval);

	// if ( flagREI ) YYABORT;


	/***************************************
	  Asignacion variables de localizacion
	 ***************************************/

	$$.linIni = $1.linIni;
	$$.colIni = $1.colIni;
	$$.linFin = $1.linFin;
	$$.colFin = $1.colFin;

	// De nuevo copiamos...

	$$.nomTemp = strdup($1.lexema);
	}
	| error
	;

OPERAR_LISTA : EXPRESION OP_LISTAS1
	{
	/************************************
	  OP_LISTAS1 = "#", "->", "<<", ">>"
	 ************************************/

	if ( ($1.tipoDato != LISTA_ENTERO) && ($1.tipoDato != LISTA_REAL)
		&& ($1.tipoDato != LISTA_CARACTER)
		&& ($1.tipoDato != LISTA_BOOLEANO) ) {

		fprintf(stderr, "Error linea: %d ", yylineno);
		fprintf(stderr, "OP_LISTAS1 con tipo incorrecto: ");
		// impTipo($1.tipoDato);
		// printf("\n");

		$$.tipoDato = DESC;
	} else {

		if ( $2.nParam == 1 )

			/* # es cardinalidad de la lista */
			$$.tipoDato = ENTERO;

		else

			/**********************************************
			  En otro caso, devolvemos LISTA_TIPO o TIPO ??
			  Hay que decidirlo...
			 **********************************************/
			
			$$.tipoDato = $1.tipoDato;
		}
	}
	| OP_LISTAS1 EXPRESION
	{
	/*************************************
	  Se debe BORRAR esta Regla !!!!
	**************************************/
	}
	| EXPRESION OP_LISTAS2 EXPRESION
	{
	/********************************************
	  OP_LISTAS2 = 
		"@"  nParam = 1
		"++" nParam = 2
		"%"  nParam = 3

	  La posicion de una lista debe ser un entero

	  ++ es para Meter en la lista ??  <LISTA> ++ <VALOR>
	  Valor de POS: <LISTA> @ <POS>
	  Borrar:  <LISTA> % <POS>
	  Insertar en pos: <LISTA> . <POS> \ <VALOR>
	 ***********************************************/

	if ( ($1.tipoDato != LISTA_ENTERO) && ($1.tipoDato != LISTA_REAL)
		&& ($1.tipoDato != LISTA_CARACTER)
		&& ($1.tipoDato != LISTA_BOOLEANO) ) {

		fprintf(stderr, "Error linea: %d ", yylineno);
		fprintf(stderr, "OP_LISTAS2 con tipo incorrecto: \n");
		// impTipo($1.tipoDato);
		// printf("\n");

		$$.tipoDato = DESC;

	} else if ( $2.nParam == 1 || $2.nParam == 3 ) {

		if ( $3.tipoDato != ENTERO ) {
			fprintf(stderr, "\nError linea %d ", yylineno);
			fprintf(stderr, "Posicion no entera: ");
			// impTipo($3.tipoDato);
			fprintf(stderr, "\n");

			$$.tipoDato = DESC;
		} else {

			switch( $1.tipoDato ) {
				case LISTA_ENTERO:
						$$.tipoDato = ENTERO;
						break;
				case LISTA_REAL:
						$$.tipoDato = REAL;
						break;
				case LISTA_CARACTER:
						$$.tipoDato = CARACTER;
						break;
				case LISTA_BOOLEANO:
						$$.tipoDato = BOOLEANO;
						break;
				default:
						fprintf(stderr, "\nFallo !LISTA\n");
						$$.tipoDato = DESC;
						break;
				}
			}
	} else {

		/* Insercion en la lista */

		switch( $1.tipoDato ) {
			case LISTA_ENTERO:
					if ( $3.tipoDato != ENTERO )
						flag = 1;
					else
						$$.tipoDato = ENTERO;
					break;
			case LISTA_REAL:
					if ( $3.tipoDato != REAL )
						flag = 1;
					else
						$$.tipoDato = REAL;
					break;
			case LISTA_CARACTER:
					if ( $3.tipoDato != CARACTER )
						flag = 1;
					else
						$$.tipoDato = CARACTER;
					break;
			case LISTA_BOOLEANO:
					if ( $3.tipoDato != BOOLEANO )
						flag = 1;
					else
						$$.tipoDato = BOOLEANO;
					break;
			default:
					fprintf(stderr, "\nTIPO != LISTA!!!\n");
					flag = 1;
			}

		if ( flag == 1 ) {
			fprintf(stderr, "\nError linea %d ", yylineno);
			fprintf(stderr, "OP_LISTAS2 el tipo del valor (");
			// impTipo($3.tipoDato);
			fprintf(stderr, ") no coincide con el de la lista (");
			// impTipo($1.tipoDato);
			fprintf(stderr, ")\n");

			$$.tipoDato = DESC;
			flag = 0;
			}
		}
	}
	| EXPRESION OP_LISTAS3 EXPRESION OP_LISTAS4 EXPRESION
	{
	/**************************************************
	  TODO: Comprobacion de tipos para OP_LISTAS...
	  TODO: No deberia ser muy dificil...con PETBUSCAR
	
	OP_LISTAS3 = .
	OP_LISTAS4 = \

	Insertar en POS: <LISTA> . <POS> . <VALOR>


	if ( ($1.tipoDato != LISTA_ENTERO) && ($1.tipoDato != LISTA_REAL)
		&& ($1.tipoDato != LISTA_CARACTER)
		&& ($1.tipoDato != LISTA_BOOLEANO) ) {

		fprintf(stderr, "ERR Error linea: %d ", yylineno);
		fprintf(stderr, "ERR OP_LISTAS2 con tipo incorrecto\n");

		$$.tipoDato = DESC;

	} else if ( $3.tipoDato != ENTERO ) {
		fprintf(stderr, "\nError linea %d ", yylineno);
		fprintf(stderr, "Posicion no entera\n");

		$$.tipoDato = DESC;

	} else {

		switch( $1.tipoDato ) {
			case LISTA_ENTERO:
					if ( $5.tipoDato != ENTERO )
						flag = 1;
					else
						$$.tipoDato = ENTERO;
					break;
			case LISTA_REAL:
					if ( $5.tipoDato != REAL )
						flag = 1;
					else
						$$.tipoDato = REAL;
					break;
			case LISTA_CARACTER:
					if ( $5.tipoDato != CARACTER )
						flag = 1;
					else
						$$.tipoDato = CARACTER;
					break;
			case LISTA_BOOLEANO:
					if ( $5.tipoDato != BOOLEANO )
						flag = 1;
					else
						$$.tipoDato = BOOLEANO;
					break;
			default:
					printf("\nTIPO != LISTA!!!\n");
					flag = 1;
			}

		if ( flag == 1 ) {
			fprintf(stderr, "\nError linea %d ", yylineno);
			fprintf(stderr, "OP_LISTAS2 el tipo del valor (");
			fprintf(stderr, ") no coincide tipo lista (");
			fprintf(stderr, ")\n");

			$$.tipoDato = DESC;
			flag = 0;
			}
		}

	***************************************************/
	}
	;

SENTENCIAS : LLAVE_ABRE BLQ_SENTENCIAS LLAVE_CIERRA
	| SENTENCIA
	| LLAVE_ABRE SENTENCIA LLAVE_CIERRA
	;

BLQ_SENTENCIAS : BLQ_SENTENCIAS SENTENCIA
	| SENTENCIA SENTENCIA
	;

SENTENCIA : OP_SIMPLE PUNTO_COMA
	| OP_COMPUESTA
	;


OP_SIMPLE : ASIG  
	| ENTRADA 
	| SALIDA
	| LLAMADA_PROCEDIMIENTO
	| error
	;

OP_COMPUESTA : SENTENCIA_SI
	| SENTENCIA_MIENTRAS
	| SENTENCIA_EN_CASO 
	;

ASIG : IDENTIFICADOR IGUAL EXPRESION
	{
	/** 
	 @todo TODO: No hay porque hacerlo en 2 partes...
	 Para eso estan $1, $2.... 
	 */

	tipoTemp = pet_BuscarTS($1);
	$1.tipoDato = tipoTemp;
	estado = pet_VerifTIPO($1, $3);

	/*************************************************************
	  Comprobacion de tipos MANUAL en el HIJO
	  NO deberia hacer falta porque se lo hemos pedido al PADRE
	 *************************************************************/

	if ( tipoTemp != $3.tipoDato ) {
		fprintf(stderr, "[ERR] Error linea: %d ASIGNACION "
			, yylineno);
		fprintf(stderr, "tipos no coinciden\n");
		// impTipo(tipoTemp);
		// printf(" y ");
		// impTipo($4.tipoDato);
		// printf("\n");
		}


	fprintf(stderr, "[COMP] Misma comprobacion tipo ");
	fprintf(stderr, "segun PADRE: %s\n", (estado == 1)?"OK":"ERR");

	pet_GenIniBlq("/** Asignacion **/\n", $1.colIni, $3.colFin);

	// Peticion de ASIGNACION

	pet_GenAsig(2, $1.lexema, $3.nomTemp, NULL, NULL);

	pet_GenFinBlq();
	}
	;

LISTA_EXP : LISTA_EXP COMA EXPRESION 
	{
	fprintf(stderr, "[COMP] Argumentos R1\n");
	tipoOK = pet_BuscarPARAM($3);
	contParam++;

	if ( tipoOK && $1.tipoDato == NO_ASIG ) {
		$$.tipoDato = NO_ASIG;
		tamCadena = strlen($1.variables)
			+ 2 + strlen($3.nomTemp) + 1;

		$$.variables = (char *) malloc(tamCadena * sizeof(char));
		if ( $$.variables == NULL ) {
			perror("LISTA_EXP");
			$$.tipoDato = DESC;
		} else {
			strcpy($$.variables, $1.variables);
			strcat($$.variables, ", ");
			strcat($$.variables, $3.nomTemp);
			fprintf(stderr, "DEBUG ListaEXP %s\n"
				, $$.variables);

			// Deberiamos poder liberar memoria !!!
			free($3.nomTemp);
			free($1.variables);
			}
	} else {
		$$.tipoDato = DESC;
		}
	}
	| EXPRESION
	{
	fprintf(stderr, "[COMP] Argumentos R2\n");
	tipoOK = pet_BuscarPARAM($1);
	contParam++;
	if ( tipoOK ) {
		$$.tipoDato = NO_ASIG;
		// Crear la lista de expresiones...
		$$.variables = strdup($1.nomTemp);
		fprintf(stderr, "DEBUG ListaExp %s\n", $1.nomTemp);
		// Deberiamos poder liberar la memoria
		// de nomTemp ???? y toda la demas...
		free($1.nomTemp);
	} else
		$$.tipoDato = DESC;
	}
	|
	{
	/****************
	  Cuidado AQUI !!!
	  Se admiten listas de expresiones
	  que empiezan por COMA !!!!
	 ************************************/
	
	$$.tipoDato = NO_ASIG;
	$$.variables = strdup("<< SIN_ARGUMENTOS >>");
	}
	;

ENTRADA : LEER
	{
	pet_GenIniBlq("/** Sent ENTRADA **/\n", $1.colIni, $1.colFin);
	}
	LISTA_IDS
	{
	pet_GenENTRADA($3.formato, $3.variables);

	pet_GenFinBlq();
	}
	;

LISTA_IDS : LISTA_IDS COMA IDENTIFICADOR 
	{ 
	tipoAux = pet_BuscarTS(yylval);

	pet_GenCadFormato($1.colIni, $3.colFin
		, &($$.formato), &($$.variables), tipoAux
		, $3.lexema, SCAN);

	// Asignamos variables de localizacion
	$$.colIni = $1.colIni;
	$$.colFin = $3.colFin;	
	}
	| IDENTIFICADOR
	{
	tipoAux = pet_BuscarTS(yylval);

	pet_GenCadFormato($1.colIni, $1.colFin
		, &($$.formato), &($$.variables), tipoAux
		, $1.lexema, SCAN);

	// Asignamos variables de localizacion
	$$.colIni = $1.colIni;
	$$.colFin = $1.colFin;
	}
	;

SALIDA : ESCRIBIR
	{
	pet_GenIniBlq("/** Sent SALIDA **/\n", $1.colIni, $1.colFin);
	}
	LISTA_ARG
	{
	pet_GenSALIDA($3.formato, $3.variables);

	pet_GenFinBlq();
	}
	;

LISTA_ARG : LISTA_ARG COMA EXPRESION
	{
	pet_GenCadFormato($1.colIni, $3.colFin
		, &($$.formato), &($$.variables), $3.tipoDato
		, $3.nomTemp, PRINT);

	// Asignamos variables de localizacion
	$$.colIni = $1.colIni;
	$$.colFin = $3.colFin;
	}
	| LISTA_ARG COMA CADENA
	{
	pet_GenCadFormato($1.colIni, $3.colFin
		, &($$.formato), &($$.variables), STRING
		, $3.lexema, PRINT);

	// Asignamos variables de localizacion
	$$.colIni = $1.colIni;
	$$.colFin = $3.colFin;
	}
	| EXPRESION
	{
	pet_GenCadFormato($1.colIni, $1.colFin
		, &($$.formato), &($$.variables), $1.tipoDato
		, $1.nomTemp, PRINT);

	// Asignamos variables de localizacion
	$$.colIni = $1.colIni;
	$$.colFin = $1.colFin;
	}
	| CADENA
	{
	pet_GenCadFormato($1.colIni, $1.colFin
		, &($$.formato), &($$.variables), STRING
		, $1.lexema, PRINT);

	// Asignamos variables de localizacion
	$$.colIni = $1.colIni;
	$$.colFin = $1.colFin;
	}
	;

SENTENCIA_SI : PARTE_IF PARTE_ELSE

PARTE_IF : SI
	{
	// Bloque SENTENCIA if
	pet_GenIniBlq("/**  Sentencia IF   **/\n", $1.colIni, $1.colFin);

	$1.etqtElse = pet_GenEtiq();
	$1.etqtSal = pet_GenEtiq();
	$1.etqtEnt = pet_GenEtiq();
	$1.nomVarCtrl = strdup("<NO_APL>");
	$1.tipoTs = DESC_CTRL;
	$1.tipoDato = NO_ASIG;
	$1.lexema = strdup("<CTRL_SI>");

	// Veamos que pasa....
	pet_introTS($1, DESC_CTRL);
	}
	PARENT_ABRE EXPRESION PARENT_CIERRA 
	{
	/************************************************
	  La comprobacion $4.tipoDato == BOOLEANO
	  debe hacerse ya que POSIBLEMENTE la Expresion
	  NO se encuentre en la TS

	  DEBUG Aunque haya ERROR SEMANTICO nuevo Bloque 
	 ************************************************/

	// Pequeña chapuza para que se vea todo...

	$5.tipoDato = BOOLEANO;
	estado = pet_VerifTIPO($4, $5);
	
	if ( $4.tipoDato != BOOLEANO ) {
		/** @todo Gestion de msj por pipeERR en PADRE */
		fprintf(stderr, "ERR SEMANTICO Linea %d: ", yylineno);
		fprintf(stderr, "Expresion NO booleana en Condicion\n");
		pet_GenIniBlq("/**  Parte if EXP no BOOL  **/"
			, $4.colIni, $4.colFin);
	} else {
		// pet_GenSalto($4.nomTemp, $1.etqtElse, COND);
		pet_GenSaltoCond($4.nomTemp, $1.etqtElse);
		pet_GenIniBlq("/**  Parte if   **/\n"
			, $4.colIni, $4.colFin);
		}

	}
	SENTENCIAS
	{
	// Salto incondicional a la etiqueta de salida
	// pet_GenSalto($4.nomTemp, $1.etqtSal, INCOND);
	pet_GenSaltoInCond($1.etqtSal);

	// fin del bloque PARTE_IF

	pet_GenFinBlq();

	// Paso 7 -> Se emite la etiqueta parte ELSE
	pet_EscEtq($1.etqtElse);
	}
	;

PARTE_ELSE : SINO 
	{ 
	pet_GenIniBlq("/**  Parte else  **/\n", $1.colIni, $1.colFin);
	}
	SENTENCIAS
	{
	// Fin Bloque Else

	pet_GenFinBlq();

	// Fin bloque sentencia IF

	pet_GenFinBlq();

	// Escribir etiqueta SALIDA
	// indexCtrl = buscaCtrl();
	etqTemp = pet_BuscarEtq(ETQ_SAL);

	// escEtqta(tSimbolos[indexCtrl].etqtSalida);
	pet_EscEtq(etqTemp);
	free(etqTemp);
	// Eliminar simbolos de la TS
	// TODO: Implementar sacaCtrl();

	pet_SacarCTRL();
	}
	|
	{
	// Fin bloque sentencia IF
	pet_GenFinBlq();

	// Buscar y escribir etiqueta de SALIDA
	etqTemp = pet_BuscarEtq(ETQ_SAL);
	pet_EscEtq(etqTemp);
	free(etqTemp);

	// Eliminar simbolos de la TS
	pet_SacarCTRL();
	}
	;



SENTENCIA_MIENTRAS : MIENTRAS PARENT_ABRE EXPRESION PARENT_CIERRA SENTENCIAS
	;

SENTENCIA_EN_CASO : SWITCH IDENTIFICADOR LLAVE_ABRE 
        LISTA_CASOS LLAVE_CIERRA
	;

LISTA_CASOS : LISTA_CASOS CASO VALOR DOSPUNTOS SENTENCIAS
	| LISTA_CASOS CASO VALOR DOSPUNTOS SENTENCIAS SALTAR
	| LISTA_CASOS DEFECTO DOSPUNTOS SENTENCIAS SALTAR
	| CASO VALOR DOSPUNTOS SENTENCIAS
	| CASO VALOR DOSPUNTOS SENTENCIAS SALTAR
	;

LLAMADA_PROCEDIMIENTO : IDENTIFICADOR 
	{
	/**********************
	  La peticion deberia devolver el numero
	  de argumentos

	  De momento vale porque no se puede llamar
	  a un proc dentro de la llamada a otro
	  pero CUIDADO con las Funciones SI y la
	  liamos !!!!!!!!!!!!
	  Para solucionarlo tenemos el campo de 
	  numero de Parametros COOOOÑO !!!!
	 ******************************************/
	$1.nParam = pet_BuscarPROC($1);
	contParam = 0;
	if ( $1.nParam < 0 )
		fprintf(stderr, "[ERR] Proc no declarado: %s\n", $1.lexema);
	else {
		// Usamos 
		$1.tipoDato = NO_ASIG;
		pet_GenIniBlq("/** Llamada a PROC **/\n"
			, $1.colIni, $1.colFin);
		/*****************************
		  Aqui NO !!!
		  Primero hay que generar los temporales
		  para la Lista de Expresiones

		pet_GenLlamada($1.lexema);
		******************************************/
		}
	}
	PARENT_ABRE LISTA_EXP PARENT_CIERRA
	{
	/******************************
	  Deberiamos comprobar si el 
	  numero de parametros leidos coincide
	  con el declarado y si la lista de
	  argumentos es correcta en su TOTALIDAD
	  Muuuuuuuuuuucho cuidado que con las
	  funciones se puede liar la grande !!!
	*******************************************/

	if ( contParam != $1.nParam && $1.nParam >= 0 ) {
		fprintf(stderr, "[ERR] Linea %d Num parametros no concuerda\n", yylineno);
		fprintf(stderr, "[ERR] Declarados: %d  Usados: %d\n"
			, $1.nParam, contParam);
	} else if ( $4.tipoDato != NO_ASIG ) {
		fprintf(stderr, "[ERR] Linea %d Llamada a PROC incorrecta\n", yylineno);
	} else {
		// Llamada CORRECTA
		pet_GenLlamada($1.lexema, $4.variables);
		// TODO: Liberar MEMORIA
		free($4.variables);
		}

	pet_GenFinBlq();
	}
	;


%%


#include "plantilla.c"
