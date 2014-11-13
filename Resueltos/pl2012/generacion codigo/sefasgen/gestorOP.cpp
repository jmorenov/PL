/**
 @file Implementacion clase gestorOP
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "gestorOP.h"
#include "regTrad.h"
#include "def_msjs.h"


extern Traduccion rgls[MAX_REGLAS];

/**
 Constructor
*/

gestorOP::gestorOP(FXchar *titOP = " Op:", FXchar *nomOP = "<NO_DEF>"
	, FXchar *titDat = " Lexema:", FXchar *nomDat = "<NO_APLICA>")
	{
	datos.cptOP = titOP;
	datos.txtOP = nomOP;
	datos.cptDato = titDat;
	datos.txtDato = nomDat;

	datos.iniSel = -1;
	datos.tamSel = -1;
	}


/**
 Constructor
*/

gestorINS::gestorINS(FXTabSim *t, int in, int out) : gestorOP(" Op:", "Insercion"
	, " Lexema:", "<NO_APL>")
	{
	tabla = t;
	dfIN = in;
	dfOUT = out;
	};

/**
 Pre-insercion.
 Lectura datos necesarios y actualizacion datos para Barra de estado
*/

DatosBarra gestorINS::pre(void) {
	int nbytes, tam;
	char *msj;
	unsigned char tipo;
		
	// Tam y lexema

	read(dfIN, &tam, sizeof(int));
	
	reg.lexema = (char *) malloc((tam+1) * sizeof(char));
	if ( reg.lexema == NULL ) {
		perror("reg.lexema");
		setStatus(-1);
		return getDatos();
		}
	
	read(dfIN, reg.lexema, tam * sizeof(char));
	reg.lexema[tam] = '\0';

	// Leemos el tipo de dato
	read(dfIN, &reg.tipoDato, sizeof(unsigned char));
	
	// Leemos el tipo de entrada
	nbytes = read(dfIN, &reg.tipoTs, sizeof(unsigned char));

	// Si es un DESC_CTRL, leemos campos adicionales

	if ( reg.tipoTs == DESC_CTRL ) {
		// Tam y etiqueta de entrada
		read(dfIN, &tam, sizeof(int));
		reg.etqtEnt = (char *) malloc ((tam+1) * sizeof(char));
		if ( reg.etqtEnt == NULL ) {
			perror("PADRE Mem reg.etqtEnt");
			// Que hacer AHORA ????
			setStatus(-1);
			return getDatos();
			}
		read(dfIN, reg.etqtEnt, tam * sizeof(char));
		reg.etqtEnt[tam] = '\0';

		// Tam y etiqueta de salida
		read(dfIN, &tam, sizeof(int));
		reg.etqtSal = (char *) malloc ((tam+1) * sizeof(char));
		if ( reg.etqtSal == NULL ) {
			perror("PADRE Mem reg.etqtSal");
			// Que hacer AHORA ????
			setStatus(-1);
			return getDatos();
			}

		read(dfIN, reg.etqtSal, tam * sizeof(char));
		reg.etqtSal[tam] = '\0';

		// Tam y etiqueta ELSE
		read(dfIN, &tam, sizeof(int));
		reg.etqtElse = (char *) malloc ((tam+1) * sizeof(char));

		if ( reg.etqtElse == NULL ) {
			perror("PADRE Mem reg.etqtElse");
			// Que hacer AHORA ????
			setStatus(-1);
			return getDatos();
			}

		nbytes = read(dfIN, reg.etqtElse, tam * sizeof(char));
		reg.etqtElse[tam] = '\0';

		// Tam y Variable de Control
		nbytes = read(dfIN, &tam, sizeof(int));
		reg.nomVarCtrl = (char *) malloc ((tam+1) * sizeof(char));

		if ( reg.nomVarCtrl == NULL ) {
			perror("PADRE Mem reg.etqtEnt");
			// Que hacer AHORA ????
			}

		nbytes = read(dfIN, reg.nomVarCtrl, tam*sizeof(char));
		reg.nomVarCtrl[tam] = '\0';
		}


	// Si NO es una MARCA, leemos datos de localizacion

	if ( reg.tipoTs != MARCA ) {
		nbytes = read(dfIN, &reg.linIni, sizeof(int));
		nbytes = read(dfIN, &reg.linFin, sizeof(int));
		nbytes = read(dfIN, &reg.colIni, sizeof(int));
		nbytes = read(dfIN, &reg.colFin, sizeof(int));

		setIni(reg.colIni);
		setTam(reg.colFin + 1 - reg.colIni);
		}

	setTxtDato(reg.lexema);
	setTxtRes("<>");

	// ... y centramos el codigo
	// txtCod->setCenterLine(iniSel);

	setStatus(0);
	return getDatos();
	}

/**
 Post-insercion.
 Ejecucion de la Insercion y actualizacion datos
*/

DatosBarra gestorINS::post(void) {
	FXint nFilas;
	FXbool resOP;
	FXchar msj[4];

	resOP = tabla->intro(reg);
			
	if ( resOP ) {
		setTxtRes("OK");
		setStatus(0);
		strcpy(msj, "ACK");
	} else {
		setTxtRes("ERR DUPLICADO");
		setStatus(1);
		strcpy(msj, "REP");
		}

	// Mandamos resultado al hijo
	write(dfOUT, msj, 4 * sizeof(char));
	
	free(reg.lexema);
	if ( reg.tipoTs == DESC_CTRL ) {
		free(reg.etqtEnt);
		free(reg.etqtSal);
		free(reg.etqtElse);
		free(reg.nomVarCtrl);
		}

	// codOp = OP_POST;

	return getDatos();
	}


///////////   gestorBSIM

/**
 Constructor
*/

gestorBSIM::gestorBSIM(FXTabSim *t, int in, int out) : gestorOP(" Op:", "Busqueda SIM"
	, " Lexema:", "<NO_APL>")
	{
	tabla = t;
	dfIN = in;
	dfOUT = out;
	};


/**
 pre-Busqueda.
 Lectura de datos
*/

DatosBarra gestorBSIM::pre(void) {
	int tam, nbytes;
	char msj[4];
	tDato tipo;
	unsigned char tAux;
	int salida;

	// Tam y lexema del simbolo buscado
	nbytes = read(dfIN, &tam, sizeof(tam));
	
	reg.lexema = (char *) malloc ( (tam+1) * sizeof(char));
	if ( reg.lexema == NULL ) {
		perror("reg.lexema");
		printf("tam: %d\n", tam);
		exit(1);
		}
	
	nbytes = read(dfIN, reg.lexema, tam * sizeof(char));
	reg.lexema[tam] = '\0';

	setTxtDato(reg.lexema);
	
	// Variables de localizacion
	nbytes = read(dfIN, &reg.linIni, sizeof(int));
	nbytes = read(dfIN, &reg.linFin, sizeof(int));
	nbytes = read(dfIN, &reg.colIni, sizeof(int));
	nbytes = read(dfIN, &reg.colFin, sizeof(int));

	// Guardamos la posicion de la seleccion
	setIni(reg.colIni);
	setTam(reg.colFin + 1 - reg.colIni);

	// ... y centramos el codigo
	/** @todo Comprobar que pasa con el centrado de Codigo!!! */
	// txtCod->setCenterLine(iniSel);

	/********
	flagLexema = 1;
	cadDatosOp = reg.lexema;
	flagResultado = 1;
	cadResultado = "";
	cadCaption = "  Lexema:";

	codOp = OP_BUSCAR_SIM;
	***************************/

	setTxtRes("<>");
	
	// Desactivar gestor PIPE
	// getApp()->removeInput(dfIN, INPUT_READ);

	setStatus(0);
	return getDatos();
	}


// Post-busqueda en TS

DatosBarra gestorBSIM::post(void) {
	FXchar msj[4];
	int salida, nbytes, pos;
	unsigned char tAux;

	reg.tipoDato = tabla->buscarSIM(reg.lexema);

	if ( reg.tipoDato == DESC ) {
		strcpy(msj, "ERR");
		// salida = -1;
		// cadResultado = "ERR";
		setTxtRes("ERR");
		setStatus(-1);
	} else {
		strcpy(msj, "ACK");
		// salida = 0;
		// cadResultado = "OK";
		setTxtRes("OK");
		setStatus(0);
		}

	
	nbytes = write(dfOUT, msj, 4 * sizeof(char));
	
	// tAux = reg.tipoDato;
	nbytes = write(dfOUT, &reg.tipoDato, sizeof(unsigned char));

	// flagLexema = 0;
	free(reg.lexema);

	// flagResultado = 1;
	// codOp = OP_POST;

	return getDatos();
	}


/////////////// 	gestor Busqueda Procedimientos

/**
 Constructor
*/

gestorBPROC::gestorBPROC(FXTabSim *t, int in, int out) : gestorOP(" Op:", "Busqueda PROC"
	, " Lexema:", "<NO_APL>")
	{
	tabla = t;
	dfIN = in;
	dfOUT = out;
	};


/**
 Pre-Busqueda de procedimiento.
 Lectura del nombre
*/

DatosBarra gestorBPROC::pre(void) {
	char msj[4];
	int nbytes, tam;
	
	// Tam del nombre y nombre
	nbytes = read(dfIN, &tam, sizeof(tam));
	
	reg.lexema = (char *) malloc ( (tam+1) * sizeof(char));
	if ( reg.lexema == NULL ) {
		perror("id");
		printf("tam: %d\n", tam);
		exit(1);
		}
	
	nbytes = read(dfIN, reg.lexema, tam * sizeof(char));
	reg.lexema[tam] = '\0';

	setTxtDato(reg.lexema);

	// Variables de localizacion
	nbytes = read(dfIN, &reg.linIni, sizeof(int));
	nbytes = read(dfIN, &reg.linFin, sizeof(int));
	nbytes = read(dfIN, &reg.colIni, sizeof(int));
	nbytes = read(dfIN, &reg.colFin, sizeof(int));

	// Guardamos la seleccion donde corresponde
	setIni(reg.colIni);
	setTam(reg.colFin + 1 - reg.colIni);

	// ... y centramos el codigo
	// txtCod->setCenterLine(iniSel);

	
	// Actualizacion barra estado
	/**
	codOp = OP_BUSCAR_PROC;
	flagLexema = 1;
	cadDatosOp = reg.lexema;
	flagResultado = 1;
	cadResultado = "";
	cadCaption = "  Lexema:";
	***/

	setTxtRes("<>");

	// Desactivar gestor PIPE
	// getApp()->removeInput(dfIN, INPUT_READ);

	setStatus(0);

	return getDatos();
	}

/**
 Post-Busqueda de Procedimiento
*/

DatosBarra gestorBPROC::post(void) {
	int npars;
	
	npars = tabla->buscarPROC(reg.lexema);
	
	// Mandamos Num parametros declarados al hijo

	write(dfOUT, &npars, sizeof(int));
	
	// Actualizacion barra de estado y gui

	free(reg.lexema);
	
	if ( npars < 0 ) {
		setTxtRes("ERR");
		setStatus(-1);
	} else {
		setTxtRes("OK");
		setStatus(0);
		}

	return getDatos();
	}

/////////////////   Gestor para Busqueda de Parametros

/**
 Constructor
*/

gestorBPARAM::gestorBPARAM(FXTabSim *t, int in, int out) : gestorOP(" Op:", "Busqueda PARAM"
	, " Tipo dato:", "<NO_APL>")
	{
	tabla = t;
	dfIN = in;
	dfOUT = out;
	};

/**
 Pre-busqueda de Parametro
*/

DatosBarra gestorBPARAM::pre(void) {
	int nbytes;

	nbytes = read(dfIN, &reg.tipoDato, sizeof(unsigned char));
	
	// Variables de localizacion
	nbytes = read(dfIN, &reg.linIni, sizeof(int));
	nbytes = read(dfIN, &reg.linFin, sizeof(int));
	nbytes = read(dfIN, &reg.colIni, sizeof(int));
	nbytes = read(dfIN, &reg.colFin, sizeof(int));

	// Guardamos la posicion del texto a seleccionar
	setIni(reg.colIni);
	setTam(reg.colFin + 1 - reg.colIni);

	// ... y centramos el codigo
	// txtCod->setCenterLine(iniSel);

	// Actualizacion barra de estado
	/***************
	codOp = OP_BUSCAR_PARAM;
	cadDatosOp = "<NO_DISP>";
	reg.lexema = strdup("<NO_DISP>");
	flagLexema = 1;
	cadResultado = "";
	flagResultado = 1;
	cadCaption = "  Lexema:";
	*****************************/

	setTxtRes("<>");
	setTxtDato(tabla->nombreTipo(reg.tipoDato));

	// Desactivar gestor PIPE
	// getApp()->removeInput(dfIN, INPUT_READ);

	setStatus(0);

	return getDatos();
	}

	
/**
 Post-busqueda de Parametro
*/

DatosBarra gestorBPARAM::post(void) {
	int nbytes;
	char msj[4];
	FXint resultado;

	resultado = tabla->buscarPARAM(reg.tipoDato);
	
	switch ( resultado ) {
		case 0:
			// Correcto
			// printf("Correcto\n");
			strcpy(msj, "ACK");
			setTxtRes("OK");
			setStatus(0);
			break;
		case 1:
			// Num parametros incorrecto
			// printf("Num param INCORRECTO\n");
			strcpy(msj, "NUM");
			setTxtRes("ERR NUM PARAM");
			setStatus(-1);
			break;
		case 2:
			// Tipo incorrecto
			strcpy(msj, "ERR");
			setTxtRes("ERR TIPO");
			setStatus(-1);
			break;
		default:
			// NO DEBERIAMOS LLEGAR AQUI !!!!!
			printf("NO DEBERIAMOS ESTAR AQUI!!!!\n");
			strcpy(msj, "UPS");
			setStatus(-1);
			break;
		}
	
	nbytes = write(dfOUT, msj, 4 * sizeof(char));
	

	// Actualizacion barra estado
	// codOp = OP_POST;

	return getDatos();
	}


/////////////	Gestor para Sacar Simbolos

/**
 Constructor
*/

gestorDEL::gestorDEL(FXTabSim *t, int in, int out) : gestorOP(" Op:", "Sacar SIMS"
	, " ", " ")
	{
	tabla = t;
	dfIN = in;
	dfOUT = out;
	};


/**
 Pre-sacar simbolos
*/

DatosBarra gestorDEL::pre(void) {

	tabla->marcar();

	// Desactivar gestor PIPE
	// getApp()->removeInput(dfIN, INPUT_READ);

	setTxtRes("<>");
	setStatus(0);

	return getDatos();
	}


// Post-sacarTS

DatosBarra gestorDEL::post(void) {
	tabla->limpiar();
	tabla->sacar();

	setTxtRes("OK");

	return getDatos();
	}

/////////////	Gestor para Verificar Tipos de Dato

/**
 Constructor
*/

gestorVERIF::gestorVERIF(FXTabSim *t, int in, int out) : gestorOP(" Op:", "Comprobar Tipos"
	, " Tipos:", "<>")
	{
	tabla = t;
	dfIN = in;
	dfOUT = out;
	};


/**
 Pre-verificacion de tipos
*/

DatosBarra gestorVERIF::pre(void) {
	FXint status, nbytes;
	unsigned char foo;

	// 1era entrada
	// Tipo
	nbytes = read(dfIN, &reg.tipoDato, sizeof(unsigned char));

	// Variables de localizacion
	nbytes = read(dfIN, &reg.linIni, sizeof(int));
	nbytes = read(dfIN, &reg.linFin, sizeof(int));
	nbytes = read(dfIN, &reg.colIni, sizeof(int));
	nbytes = read(dfIN, &reg.colFin, sizeof(int));

	// 2a entrada
	// Tipo
	nbytes = read(dfIN, &tDatoAux, sizeof(unsigned char));

	// Variables de localizacion
	nbytes = read(dfIN, &foo, sizeof(int));
	nbytes = read(dfIN, &reg.linFin, sizeof(int));
	nbytes = read(dfIN, &foo, sizeof(int));
	nbytes = read(dfIN, &reg.colFin, sizeof(int));

	// Guardamos la posicion de la seleccion
	setIni(reg.colIni);
	setTam(reg.colFin + 1 - reg.colIni);

	setTxtDato("<>");
	setTxtRes("<>");

	setStatus(0);

	return getDatos();
	}


/**
 Post-Verificacion de tipos
*/

DatosBarra gestorVERIF::post(void) {
	int res, nbytes;
	FXchar tipos[100];

	// Actualizacion de GUI
	if ( tDatoAux == reg.tipoDato ) {
		res = 1;
		setStatus(0);
		setTxtRes("OK");
	} else {
		res = 0;
		setStatus(-1);
		setTxtRes("ERR");
		/**
		cadDatosOp.assign(nomDat[reg.tipoDato]
			, strlen(nomDat[reg.tipoDato]));
		cadDatosOp.append(" y ", 3);
		cadDatosOp.append(nomDat[tDatAux], strlen(nomDat[tDatAux]));
		**/
		}

	nbytes = write(dfOUT, &res, sizeof(int));

	// tipos = tabla->nombreTipo((tDato)reg.tipoDato);
	// tipos += " y ";
	// tipos += tabla->nombreTipo(tDatoAux);

	strcpy(tipos, tabla->nombreTipo((tDato)reg.tipoDato));
	strcat(tipos, " y ");
	strcat(tipos, tabla->nombreTipo((tDato)tDatoAux));

	setTxtDato(tipos);

	return getDatos();
	}



/////////////	Gestor para Creacion nombres temporales

/**
 Constructor
*/

gestorTEMP::gestorTEMP(FXTabSim *t, int in, int out, FXchar *b)
	: gestorOP(" Op:", "Generar Temporal"
	, " Nombre:", "<>")
	{
	tabla = t;
	dfIN = in;
	dfOUT = out;
	base = b;
	};

/**
 Pre-creacion nombre variable temporal
*/

DatosBarra gestorTEMP::pre(void) {
	setTxtDato("<>");
	setTxtRes("<>");

	// La creacion de temporales
	// no altera el Codigo Seleccionado !!!
	setStatus(2);

	return getDatos();
	}


/**
 Post-generacion nombre variable temporal
*/

DatosBarra gestorTEMP::post(void) {
	static FXint cont = 0;
	FXString nom;
	const char *txt;
	int tam;

	nom.assign(base);
	nom.append(FXStringVal(cont).text());

	cont++;

	// Mandamos el nombre temporal al Compilador
	txt = nom.text();
	tam = nom.length();
	write(dfOUT, &tam, sizeof(int));
	write(dfOUT, txt, tam * sizeof(char));
	
	/****
	codOp = OP_POST;
	flagResultado = 1;
	cadResultado = "OK";
	flagLexema = 1;
	cadDatosOp.assign(nom.text());
	************/

	setTxtRes("OK");
	setTxtDato((FXchar *)txt);
	// setStatus(0);
	

	return getDatos();
	}

/////////////	Gestor para Creacion de Cadenas de Formato

/**
 Constructor
*/

gestorCADFMT::gestorCADFMT(FXTabSim *t, int in, int out) : gestorOP(" Op:"
	, "Crear cadena formato"
	, " Cadena:", "<>")
	{
	tabla = t;
	dfIN = in;
	dfOUT = out;
	};

/**
 Pre-creacion de la cadena.
 Lectura de la nueva variable y tipo
*/

DatosBarra gestorCADFMT::pre(void) {
	int tam, ini, fin;
	char tChar;

	// Lectura del tipo de Entrada/Salida
	read(dfIN, &tipoES, sizeof(unsigned char));

	// Lectura de variables de localizacion
	read(dfIN, &ini, sizeof(int));
	read(dfIN, &fin, sizeof(int));

	setIni(ini);
	setTam(fin-ini+1);

	// Tipo del argumento
	// Hay que leerlo como un char !!!!
	// read(dfIN, &tChar, sizeof(char));
	read(dfIN, &tipo, sizeof(tDato));

	// printf("Leido tipo: %d\n", tipo);
	// tipo = (tDato)tChar;

	// Tam y nombre argumento
	read(dfIN, &tam, sizeof(int));
	nombre = (FXchar *) malloc ((tam+1) * sizeof(char));
	if ( nombre == NULL ) {
		perror("ERR genCadFmt nombre");
		// TODO: Msj ERROR al hijo para que ABORTE !!!
		setStatus(-1);
		return getDatos();
		}

	read(dfIN, nombre, tam * sizeof(char));
	nombre[tam] = '\0';

	setTxtRes("<>");
	setStatus(0);

	return getDatos();
	}


/**
 Post-generacion cadena Formato
*/

DatosBarra gestorCADFMT::post(void) {
	int tam;
	FXString strFmt, strVar;
	FXchar espTipo;
	const FXchar *txt;

	strFmt.assign('%');
	switch ( tipo ) {
		case ENTERO:
			espTipo = 'd';
			break;
		case REAL:
			espTipo = 'f';
			break;
		case BOOLEANO:
			espTipo = 'd';
			break;
		case CARACTER:
			espTipo = 'c';
			break;
		case STRING:
			espTipo = 's';
			break;
		default:
			printf("ERROR post_genCadFmt Esp para tipo: %d", tipo);
			// printf("%s", tabla->nombreTipo(tipo));
			printf(" NO DISPONIBLE\n");
			espTipo = '?';
			break;
		}

	strFmt.append(espTipo);

	/** @todo Anadir espacio en blanco al final para ENTRADA?? */

	/********
	printf("PADRE post_genCadFmt tipoTemp: %d TIPO: ", tipoTemp);
	impTipo(tipoTemp);
	printf("\n");
	*********************/


	if ( tipoES == SCAN ) {
		strVar.assign(", &");
	} else if ( tipoES == PRINT ) {
		strVar.assign(", ");
	} else {
		printf("PADRE ERROR post_genCadFmt tipoES = ¿ %d ?\n"
			, tipoES);
		strVar.assign(", ?");
		}

	strVar.append(nombre);

	/**********
	printf("PADRE genCadFmt Formato: %s Variables: %s\n"
		, strFmt.text(), strVar.text());
	*************/

	tam = strFmt.length();
	txt = strFmt.text();
	write(dfOUT, &tam, sizeof(int));
	write(dfOUT, txt, tam * sizeof(char));

	tam = strVar.length();
	txt = strVar.text();
	write(dfOUT, &tam, sizeof(int));
	write(dfOUT, txt, tam * sizeof(char));

	setTxtRes("OK");
	setTxtDato((FXchar *)txt);
	setStatus(0);

	free(nombre);

	return getDatos();
	}



/////////////	Gestor para Creacion de nombres de etiqueta

/**
 Constructor
*/

gestorETIQ::gestorETIQ(FXTabSim *t, int in, int out, FXchar *b) : gestorOP(" Op:"
	, "Crear etiqueta"
	, " Etiqueta:", "<>")
	{
	tabla = t;
	dfIN = in;
	dfOUT = out;
	base = b;
	};


/**
 Pre-generacion de la etiqueta
*/

DatosBarra gestorETIQ::pre(void) {

	// Actualizacion Barra de estado
	/***
	codOp = OP_GEN_ETQ;
	flagResultado = 1;
	cadResultado = "";
	flagLexema = 1;
	cadCaption.assign("  Nom Etiqueta:", 15);
	cadDatosOp = "<NO_DISP>";
	***/

	setTxtRes("<>");
	setTxtDato("<>");
	setStatus(0);

	// Desactivar gestor PIPE
	// getApp()->removeInput(dfIN, INPUT_READ);

	return getDatos();
	}


/**
 Post-generacion nombre etiqueta
 Envio del nombre al COMPILADOR
*/

DatosBarra gestorETIQ::post(void) {
	static FXint cont = 0;
	const FXchar *txt;
	int tam, nbytes;
	FXString nomEtq;

	nomEtq.assign(base);
	nomEtq.append(FXStringVal(cont).text());

	txt = nomEtq.text();

	cont++;

	// Envio de la nueva etiqueta
	tam = nomEtq.length();
	nbytes = write(dfOUT, &tam, sizeof(int));
	nbytes = write(dfOUT, txt, tam * sizeof(char));

	// printf("PADRE genero nueva etiqueta: %s\n", txt);

	// Actualizacion barra de estado
	/**
	codOp = OP_POST;
	flagResultado = 1;
	cadResultado = "OK";
	flagLexema = 1;
	cadDatosOp.assign(txt, tam);
	**/

	setTxtRes("OK");
	setTxtDato((FXchar *)txt);
	setStatus(0);

	return getDatos();
	}


/////////////	Gestor para Busqueda de Etiquetas

/**
 Constructor
*/

gestorBUSQ_ETIQ::gestorBUSQ_ETIQ(FXTabSim *t, int in, int out): gestorOP(" Op:"
	, "Busqueda Etiqueta"
	, " Tipo Etq:", "<>")
	{
	tabla = t;
	dfIN = in;
	dfOUT = out;
	};

/**
 Pre-Busqueda de etiqueta.
 Lectura de datos
*/

DatosBarra gestorBUSQ_ETIQ::pre(void) {
	int nbytes;

	printf("gestorBETIQ->pre()\n");

	// Lectura del tipo de etiqueta
	nbytes = read(dfIN, &tEtiqueta, sizeof(unsigned char));

	setCptDato(" Tipo Etiqueta:");
	switch( tEtiqueta ) {
		case ETQ_ENT:
			setTxtDato("ENTRADA");
			break;
		case ETQ_SAL:
			setTxtDato("SALIDA");
			break;
		case ETQ_ELSE:
			setTxtDato("ELSE");
			break;
		default:
			setTxtDato("<ETQ_ERR>");
			break;
		}

	setTxtRes("<>");
	setStatus(0);

	return getDatos();
	}

/**
 Post-busqueda etiqueta en el ultimo DESC CTRL de la TS.
 La funcion miembro buscarEtqTS de la TS crea una
 cadena de retorno SIGNIFICATIVA en caso de error:
	- No encontrar Descriptor Control ( "EB" )
	- No poder reservar memoria dinamica ( "EM" )
*/

DatosBarra gestorBUSQ_ETIQ::post(void) {
	int nbytes, tam;
	char *nomEtq;

	nomEtq = tabla->buscarETQ(tEtiqueta);

	tam = strlen(nomEtq);
	nbytes = write(dfOUT, &tam, sizeof(int));
	nbytes = write(dfOUT, nomEtq, tam * sizeof(char));

	// Actualizacion Barra de estado
	setCptDato(" Nombre Etiq:");

	if ( strcmp(nomEtq, "EM") == 0 ) {
		setTxtRes("ERR-MEM");
		setTxtDato("<NO_APL>");
		setStatus(-1);
	} else if ( strcmp(nomEtq, "EB") == 0 ) {
		setTxtRes("NO CTRL");
		setTxtDato("<NO_APL>");
		setStatus(-1);
	} else {
		setTxtRes("OK");
		setTxtDato(nomEtq);
		setStatus(0);
		}

	free(nomEtq);

	return getDatos();
	}


/////////////	Gestor para Sacar Descriptor de Control

/**
 Constructor
*/

gestorDEL_CTRL::gestorDEL_CTRL(FXTabSim *t, int in, int out): gestorOP(" Op:"
	, "Sacar Desc Ctrl"
	, " ", " ")
	{
	tabla = t;
	dfIN = in;
	dfOUT = out;
	};


/**
 Pre-sacar
*/

DatosBarra gestorDEL_CTRL::pre(void) {
	int i;
	
	// Actualizacion Barra de estado
	setTxtRes("<>");
	setCptDato(" Num simbolos:");
	setTxtDato("<>");


	/** Resaltamos los items que vamos a eliminar */

	numReg = tabla->marcarCTRL();

	// Deshabilitamos gestor PIPE
	// getApp()->removeInput(dfIN, INPUT_READ);

	setStatus(0);
	return getDatos();
	}

/**
 Post-eliminacion simbolos TS hasta DESC_CTRL
 Ejecucion de la operacion y Actualizacion Barra de estado
 */

DatosBarra gestorDEL_CTRL::post(void) {
	int i;

	tabla->limpiar();
	tabla->sacarCTRL();

	// Actualizacion barra de estado
	if ( numReg > 0 ) {
		setTxtRes("OK");
		setTxtDato((FXchar *)FXStringVal(numReg).text());
		setStatus(0);
	} else {
		setTxtRes("ERR");
		setTxtDato("<DESC>");
		setStatus(-1);
		}

	return getDatos();
	}


/////////////	Gestor para Generacion de Codigo

/**
 Constructor
*/

gestorGENCOD::gestorGENCOD(FXText *t1, FXText *t2, int in, int out)
	: gestorOP(" Op:", "Gen Codigo", " ", " ")
	{
	txtMAIN = t1;
	txtPROCS = t2;
	txtActual = t1;
	dfIN = in;
	dfOUT = out;

	numTabs[0] = 0;
	numTabs[1] = 0;

	destino = 0;
	pos = 0;
	};

/**
 Pre-generacion de codigo.
 Leer mensaje con tipo de Codigo del compilador
*/

DatosBarra gestorGENCOD::pre(void) {
	FXint ini, fin;

	// Leemos el tipo de codigo
	// => Indice de la regla a utilizar !!!!
	read(dfIN, &tipo, sizeof(char));

	if ( tipo == INI_BLQ ) {
		read(dfIN, &ini, sizeof(int));
		read(dfIN, &fin, sizeof(int));
		setIni(ini);
		setTam(fin-ini+1);
		setStatus(0);
	} else {
		setStatus(2);
		}

	setTxtOP("Gen Codigo");
	setCptDato(" TIPO:");
	setTxtDato(rgls[tipo].nombre);
	setTxtRes("<>");
	// setStatus(0);

	return getDatos();
	}

/**
 Recepcion de datos y construccion de la cadena.
*/

void gestorGENCOD::traducir(void) {
	FXint i;
	FXString tabulacion;

	// Añadimos la nueva traduccion

	tabulacion.assign('\t', numTabs[destino]);
	txtActual->appendText(tabulacion.text(), tabulacion.length());

	for ( i = 0; i < rgls[tipo].numCampos; i++ ) {
		leerCampo(i);
		}


	return;
	}

/**
 Lectura de un campo de una regla de traduccion
 y añadirlo al codigo generado
 @param nc Numero de campo
*/

void gestorGENCOD::leerCampo(FXint nc) {
	unsigned char tCampo;
	FXString textoGEN;
	FXint posNL;
	FXint tam;
	FXchar *cadCampo;
	unsigned char tipoDato;
	FXchar *tradTIPOS[] = { "void", "<DESCONOCIDO>"
		, "int", "float", "LISTA_REAL", "LISTA_ENTERO"
		, "unsigned char", "LISTA_BOOLEANO", "char"
		, "LISTA CARACTER", "STRING_CADENA"
		, "TDA_ARRAY", "TDA_CJTO", "TDA_PILA"
		};


	tCampo = rgls[tipo].tipos[nc];

	switch ( tCampo ) {
		case ARG_STRING:
			// Eliminamos las comillas
			// e interpretamos "\n" como CARACTER
			textoGEN = &rgls[tipo].args[nc][1];
			textoGEN.remove(textoGEN.length()-1);

			do {
				posNL = textoGEN.find("\\n");

				if ( posNL != -1 ) {
					textoGEN.remove(posNL, 2);
					textoGEN.insert(posNL, '\n');
					}

			} while ( posNL != -1 );

			do {
				posNL = textoGEN.find("\\\"");

				if ( posNL != -1 )
					textoGEN.remove(posNL, 1);

			} while ( posNL != -1 );

			txtActual->appendText(textoGEN.text()
				, textoGEN.length());

			break;

		case ARG_CAD_OPC:
		case ARG_CAD:
			// Cadenas enviadas por el COMPILADOR

			read(dfIN, &tam, sizeof(int));
			if ( tam > 0 ) {
				cadCampo = (FXchar *) malloc ((tam+1) * sizeof(FXchar));
				if ( cadCampo == NULL ) {
					fprintf(stderr, "Tam campo: %d\n", tam);
					perror("Mem gestorGENCOD.post()");
				} else { 
					read(dfIN, cadCampo, tam * sizeof(char));
					cadCampo[tam] = '\0';
					txtActual->appendText(cadCampo, tam);

					if ( tipo == DEC_PARAM )
						multiParams = true;

					free(cadCampo);
					}
			} else {
				// printf("DEBUG Cadena OPCIONAL no PRESENTE\n");
				}
		
			break;

		case ARG_TIPO:

			if ( multiParams && tipo == DEC_PARAM) {
				/** 
				 @todo En vez de mandar los parametros de 1
					en 1 se pueden mandar todos de una vez !!!
				*/
				txtActual->appendText(", ", 2);
				}


			read(dfIN, &tipoDato, sizeof(char));

			/***
			printf("DEBUG Leido tipo dato: %s\n"
				, tradTIPOS[tipoDato]);
			**/

			txtActual->appendText(tradTIPOS[tipoDato]
				, strlen(tradTIPOS[tipoDato]));
			break;

		default:
			fprintf(stderr, "ERROR gestorGENCOD ");
			fprintf(stderr, "tipoCampo no reconocido %d\n", tipo);
			break;
		}

	return;
	}


/**
 Post-generacion de codigo.
*/

DatosBarra gestorGENCOD::post(void) {

	// REGLA decProc
	if ( strcmp(rgls[tipo].nombre, "decProc") == 0 ) {
		txtActual = txtPROCS;
		destino = 1;
		multiParams = false;
		pos++;
		}

	if ( tipo == FIN_BLOQUE ) {
		numTabs[destino]--;
		if ( numTabs[destino] < 0 )
			numTabs[destino] = 0;
		}


	traducir();

	// txtActual->appendText("\n", 1);

	if ( tipo == INI_BLQ )
		// (*ptrNivTab)++;

	if ( tipo == FIN_DEC ) {
		// ptrNivTab = &nivTabMAIN;
		txtActual = txtMAIN;
		}

	switch ( tipo ) {
		case INI_BLQ:
			numTabs[destino]++;
			break;
		case FIN_DEC:
			pos = (--pos < 0)?0:pos;

			if ( pos == 0 ) {
				destino = 0;
				txtActual = txtMAIN;
			} else {
				destino = 1;
				txtActual = txtPROCS;
				}

			break;
		}


	setTxtRes("OK");
	setStatus(2);

	return getDatos();
	}
