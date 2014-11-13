/**
 @file
 Funciones para generacion de codigo.
 */

#include <unistd.h>
#include "tabsim.h"
#include "gui.h"
#include "def_msjs.h"

#define PRINT 	0
#define SCAN 	1

#define COND 	0
#define INCOND	1

#define ETQ_ENT		0
#define ETQ_SAL		1
#define ETQ_ELSE	2

/** Funciones externa para TS */

extern char *buscarEtqTS(unsigned char tipo);
extern int sacarCtrlTS(void);
extern void impTipo(tDato);

extern int pipePH[2], pipeHP[2], pipeERR[2];
extern stEntrada regTS;
extern int tope;


tDato tipoTemp;
FXchar *nombre;
FXchar *fmt;
FXchar *vars;
FXchar *etq;
int tamNom;
int numOprnds;
FXString operandos[4];
char tipoES;
unsigned char tipoSalto;
unsigned char tipoEtq;
int numReg;
int contParams;

FXText *txtDestino;
unsigned char flagFin;

int tamLista;
char *listaArgs;


/**
 Gestion Mensaje generacion de CODIGO.
 Se determina la sentencia a generar y se
 llama a la funcion correspondiente
*/

FXint guiWindow::gestMsjGen(void) {
	int nbytes, tam;
	char msj[4];

	nbytes = read(pipeHP[0], msj, sizeof(char));

	switch( msj[0] ) {
		case 'I':
			// Inicio COD GENERADO
			pre_genIni();
			break;
		case 'F':
			// Fin COD GENERADO
			pre_genFin();
			break;
		case 'V':
			// Declaracion VARIABLE
			pre_genDecVar();
			break;
		case '{':
			// Inicio BLOQUE
			pre_genIniBlq();
			break;
		case '}':
			// Fin BLOQUE
			pre_genFinBlq();
			break;
		case 'A':
			// Asignacion
			pre_genAsig();
			break;
		case SENT_ES:
			// Sentencia Entrada/Salida
			pre_genES();
			break;
		case SENT_SALTO:
			pre_genSalto();
			break;
		case ESC_ETIQ:
			pre_genEscEtq();
			break;
		case DEC_PROC:
			pre_genDecProc();
			break;
		case DEC_PARAM:
			pre_genDecParam();
			break;
		case FIN_CAB:
			pre_genFinCabecera();
			break;
		case FIN_DEC_PROC:
			pre_genFinDecProc();
			break;
		case CALL_PROC:
			pre_genLlamada();
			break;
		default:
			// DESCONOCIDO
			fprintf(stderr, "Msj GEN COD DESCONOCIDO: %c\n"
				, msj[0]);
			break;
		}

	/** @todo Refinar un poco mas Hay funciones que NO escriben */
	flagGen = 1;

	// Nos centramos en la ultima linea de codigo generado
	txtDestino->setCenterLine(txtDestino->getBottomLine());

	return 1;
	}

// pre-Generacion Codigo Inicio

long guiWindow::pre_genIni(void) {
	
	// Actualizacion Barra de estado
	codOp = OP_GEN_INI;
	flagResultado = 1;
	cadResultado = "";
	flagLexema = 1;
	cadCaption = "  TIPO COD:";
	cadDatosOp = "INICIO";

	// Marcamos codigo generado como pendiente
	// flagCodGen = 1;

	// Empezamos escribiendo en Codigo generado
	txtDestino = txtGen;

	// Desactivar gestor PIPE

	getApp()->removeInput(pipeHP[0], INPUT_READ);

	return 1;
	}

/**
 Post-generacion codigo INICIO.
 Escritura en Campo de texto de los include's y main
 @todo Solucionar el tema de las comillas !!!
 @todo Flag para indicar si se generaron PROCS Si no
	es asi NO escribir el include.....
	Tambien se podria eliminar a posteriori antes
	de guardar el archivo
*/

FXint guiWindow::post_genIni(void) {
	FXString txt;

	txt = "#include <stdio.h>\n#include \"";
	txt += incDatos + "\"\n#include \"" + incFuncs + "\"\n\nmain()";
	txtDestino->insertText(0, txt.text(), txt.length());

	codOp = OP_POST;
	flagResultado = 1;
	cadResultado = "OK";
	flagLexema = 0;

	return 1;
	}


// Pre-generacion codigo FINAL
// El return ya no hace falta !!!!
// Cierre del programa = Cierre del bloque

long guiWindow::pre_genFin(void) {
	// Actualizacion Barra de estado
	codOp = OP_GEN_FIN;
	flagResultado = 1;
	cadResultado = "";
	flagLexema = 1;
	cadCaption.assign("  TIPO COD:", 11);
	cadDatosOp = "FINAL";

	// Marcamos codigo generado como pendiente
	// flagCodGen = 1;

	// Desactivar gestor PIPE

	txtDestino = txtGen;

	getApp()->removeInput(pipeHP[0], INPUT_READ);

	return 1;
	}

	
// Post-generacion codigo FINAL
// Escritura en Campo de texto

FXint guiWindow::post_genFin(void) {
	
	txtDestino->appendText("\nreturn 0;\n}\n", 13);

	codOp = OP_POST;
	flagResultado = 1;
	cadResultado = "OK";
	flagLexema = 0;

	return 1;
	}


// Pre-generacion codigo Declaracion de Variable

long guiWindow::pre_genDecVar(void) {
	int nbytes;

	// Lectura tipo Dato
	nbytes = read(pipeHP[0], &tipoTemp, sizeof(char));
	// Lecura tamaÃ±o y nombre variable
	nbytes = read(pipeHP[0], &tamNom, sizeof(int));
	nombre = (FXchar *) malloc ((tamNom+1) * sizeof(char));
	if ( nombre == NULL ) {
		perror("PADRE genDecVar MEM nombre");
		// TODO: Msj ERROR al HIJO
		return 0;
		}
	nbytes = read(pipeHP[0], nombre, tamNom * sizeof(char));
	nombre[tamNom] = '\0';
	
	printf("PADRE Generar DEC VARIABLE %d %s\n", tipoTemp, nombre);

	// Actualizacion Barra de estado
	codOp = OP_GEN_DEC_VAR;
	flagResultado = 1;
	cadResultado = "";
	flagLexema = 1;
	cadCaption.assign("  TIPO COD:", 11);
	cadDatosOp = "DEC VAR";

	// Marcamos codigo generado como pendiente
	// flagCodGen = 1;

	// Desactivar gestor PIPE

	getApp()->removeInput(pipeHP[0], INPUT_READ);

	return 1;
	}

// Post-generacion codigo DECLARACION VARIABLE
// Escritura en Campo de texto

FXint guiWindow::post_genDecVar(void) {
	FXString strAux;

	strAux.assign('\t', nivTab);
	txtDestino->appendText(strAux.text(), strAux.length());

	switch( tipoTemp ) {
		case ENTERO:
			strAux.assign("int ", 4);
			break;
		case REAL:
			strAux.assign("float ", 6);
			break;
		case BOOLEANO:
			strAux.assign("unsigned char ", 14);
			break;
		case CARACTER:
			strAux.assign("char ", 5);
			break;
		case LISTA_BOOLEANO:
		case LISTA_ENTERO:
		case LISTA_REAL:
		case LISTA_CARACTER:
			fprintf(stderr, "DEC VAR Tipo LISTA NO IMPLEM\n");
			strAux.assign("tLista<TIPO> ", 13);
			break;
		default:
			fprintf(stderr, "Tipo DESCONOCIDO: %d\n", tipoTemp);
			strAux.assign("TIPO_ERR", 9);
			break;
		}

	txtDestino->appendText(strAux.text(), strAux.length());
	txtDestino->appendText(nombre, tamNom);
	txtDestino->appendText(";\n", 2);

	free(nombre);


	codOp = OP_POST;
	flagResultado = 1;
	cadResultado = "OK";
	flagLexema = 0;

	return 1;
	}



// Pre-generacion codigo INICIO BLOQUE
// Escribir comentario, "{" y Aumentar nivel Tabulacion

long guiWindow::pre_genIniBlq(void) {
	int nbytes;
	int ini, fin;

	// Lectura variables de localizacion
	nbytes = read(pipeHP[0], &ini, sizeof(int));
	nbytes = read(pipeHP[0], &fin, sizeof(int));

	// Lectura del tam y comentario
	nbytes = read(pipeHP[0], &tamNom, sizeof(int));

	if ( tamNom > 0 ) {
		nombre = (FXchar *) malloc ((tamNom+1) * sizeof(char));
		if ( nombre == NULL ) {
			perror("PADRE genIniBlq MEM nombre");
			// TODO: Msj ERROR al HIJO
			return 0;
			}
		nbytes = read(pipeHP[0], nombre, tamNom * sizeof(char));
		nombre[tamNom] = '\0';
		}

	// Actualizacion Barra de estado
	codOp = OP_GEN_INIBLQ;
	flagResultado = 1;
	cadResultado = "";
	flagLexema = 1;
	cadCaption.assign("  TIPO COD:", 11);
	cadDatosOp = "INI BLQ";

	// Codigo seleccionado
	dtsGUI.iniSel = ini;
	dtsGUI.tamSel = fin + 1 - ini;
	// flagTexto = 1;

	// Marcamos codigo generado como pendiente
	// flagCodGen = 1;

	// Desactivar gestor PIPE

	getApp()->removeInput(pipeHP[0], INPUT_READ);

	/** Variables de localizacion
	fprintf(stderr, "PADRE Ini: %d Fin: %d Com: %s\n"
		, ini, fin, nombre);
	***/

	return 1;
	}


// Post-generacion codigo INICIO BLOQUE

FXint guiWindow::post_genIniBlq(void) {
	FXString strAux;

	// Los comentarios quedan de la forma
	// <nivTab>{\t<Comentario>\n
	strAux.assign('\n');
	strAux.append('\t', nivTab);
	strAux.append("{\t");

	if ( tamNom > 0 ) {
		strAux.append(nombre, tamNom);
		free(nombre);
		}

	strAux.append('\n');

	// Aumentamos nivel Tabulacion
	nivTab++;
	
	txtDestino->appendText(strAux.text(), strAux.length());

	codOp = OP_POST;
	flagResultado = 1;
	cadResultado = "OK";
	flagLexema = 0;

	return 1;
	}


// Pre-generacion codigo FIN BLOQUE

long guiWindow::pre_genFinBlq(void) {

	// Actualizacion Barra de estado
	codOp = OP_GEN_FINBLQ;
	flagResultado = 1;
	cadResultado = "";
	flagLexema = 1;
	cadCaption.assign("  TIPO COD:", 11);
	cadDatosOp = "FIN BLQ";

	// Marcamos codigo generado como pendiente
	// flagCodGen = 1;

	// Desactivar gestor PIPE

	getApp()->removeInput(pipeHP[0], INPUT_READ);

	return 1;
	}


// Post-generacion codigo FIN BLOQUE

FXint guiWindow::post_genFinBlq(void) {
	FXString strAux;

	// Disminuimos nivel de Tabulacion
	nivTab--;
	strAux.assign('\t', nivTab);
	strAux.append("}\n");	

	txtDestino->appendText(strAux.text(), strAux.length());

	codOp = OP_POST;
	flagResultado = 1;
	cadResultado = "OK";
	flagLexema = 0;

	return 1;
	}


// Generacion del codigo correspondiente a una asignacion

long guiWindow::pre_genAsig(void) {
	int tam, nbytes, i;
	FXchar *opr;

	// Lectura del Num de operandos
	read(pipeHP[0], &numOprnds, sizeof(int));

	printf("PADRE GEN ASIG num Operandos: %d\n", numOprnds);

	// Lectura operandos

	for(i = 0; i < numOprnds; i++) {
		nbytes = read(pipeHP[0], &tam, sizeof(int));
		opr = (FXchar *) malloc ((tam+1) * sizeof(FXchar));
		if ( opr == NULL ) {
			perror("PADRE GenAsig Mem opr");
			// TODO: Msj ERROR al HIJO
			return 0;
			}
		nbytes = read(pipeHP[0], opr, tam * sizeof(char));
		opr[tam] = '\0';

		printf("PADRE GEN ASIG op[%d]: %s\n", i, opr);
		operandos[i].assign(opr);
		free(opr);
		}


	// Actualizacion Barra de estado
	codOp = OP_GEN_ASIG;
	flagResultado = 1;
	cadResultado = "";
	flagLexema = 1;
	cadCaption.assign("  TIPO COD:", 11);
	cadDatosOp = "ASIGNACION";

	// Marcamos codigo generado como pendiente
	// flagCodGen = 1;

	// Desactivar gestor PIPE

	getApp()->removeInput(pipeHP[0], INPUT_READ);

	return 1;
	}

// Post-generacion ASIGNACION

FXint guiWindow::post_genAsig(void) {
	FXString strAux;
	int i;

	strAux.assign('\t', nivTab);
	txtDestino->appendText(strAux.text(), strAux.length());
	txtDestino->appendText(operandos[0].text(), operandos[0].length());
	txtDestino->appendText(" = ", 3);
	txtDestino->appendText(operandos[1].text(), operandos[1].length());

	for ( i = 2; i < numOprnds; i++ ) {
		txtDestino->appendText(" ", 1);
		txtDestino->appendText(operandos[i].text()
			, operandos[i].length());
		}

	txtDestino->appendText(";\n", 2);

	codOp = OP_POST;
	flagResultado = 1;
	cadResultado = "OK";
	flagLexema = 0;

	return 1;
	}


/**
 * Generacion codigo intermedio para sentencia de E/S.
 * Lectura de datos del Compilador
 */

long guiWindow::pre_genES(void) {
	int tam, nbytes;

	// Tipo de Sentencia
	nbytes = read(pipeHP[0], &tipoTemp, sizeof(char));

	// Tam y cadena de formato
	nbytes = read(pipeHP[0], &tam, sizeof(int));
	fmt = (FXchar *) malloc ((tam+1) * sizeof(char));
	if ( fmt == NULL ) {
		perror("PADRE pre_genES Mem fmt");
		/** @todo Enviar msj error al HIJO */
		return 0;
		}
	nbytes = read(pipeHP[0], fmt, tam * sizeof(char));
	fmt[tam] = '\0';

	// Tam y cadena de variables
	nbytes = read(pipeHP[0], &tam, sizeof(int));
	vars = (FXchar *) malloc ((tam+1) * sizeof(char));
	if ( vars == NULL ) {
		perror("PADRE pre_genES Mem vars");
		/** @todo Enviar msj error al HIJO */
		return 0;
		}
	nbytes = read(pipeHP[0], vars, tam * sizeof(char));
	vars[tam] = '\0';

	// Actualizacion Barra de estado
	codOp = OP_GEN_ES;
	flagResultado = 1;
	cadResultado = "";
	flagLexema = 1;
	cadCaption.assign("  Tipo COD:", 11);
	cadDatosOp.assign("Ent/Sal");

	// Marcamos codigo generado como pendiente
	// flagCodGen = 1;

	// Desactivar gestor PIPE

	getApp()->removeInput(pipeHP[0], INPUT_READ);

	return 1;
	}

/**
 * Generacion codigo para sentencia E/S.
 * Actualizacion de la GUI codigo generado
 */

FXint guiWindow::post_genES(void) {
	FXString op;
	
	op.assign('\t', nivTab);

	if ( tipoTemp == PRINT )
		op.append("printf(\"");
	else if ( tipoTemp == SCAN ) 
		op.append("scanf(\"");
	else {
		fprintf(stderr, "PADRE Tipo E/S No reconocido: %d\n"
			, tipoTemp);

		codOp = OP_POST;
		flagLexema = 0;
		flagResultado = 1;
		cadResultado = "ERR";
		free(fmt);
		free(vars);

		return 1;
		}

	op.append(fmt);
	op.append('"');
	op.append(vars);
	op.append(");\n");

	txtDestino->appendText(op.text(), op.length());

	free(fmt);
	free(vars);


	// Actualizacion barra de estado
	codOp = OP_POST;
	flagResultado = 1;
	cadResultado = "OK";
	flagLexema = 0;

	return 1;
	}
 
/**
 Pre-Generacion codigo Sentencia salto.
 Lectura de los datos necesarios para generar el codigo
 */

long guiWindow::pre_genSalto(void) {
	int nbytes, tam;

	// Actualizacion Barra de estado
	codOp = OP_GEN_SALTO;
	flagResultado = 1;
	cadResultado = "";
	flagLexema = 1;
	cadCaption.assign("  Tipo COD:", 11);
	cadDatosOp.assign("Salto");

	
	// Tipo de salto
	nbytes = read(pipeHP[0], &tipoSalto, sizeof(unsigned char));

	// Tam y nombre variable
	nbytes = read(pipeHP[0], &tam, sizeof(int));
	nombre = (FXchar *) malloc ((tam+1) * sizeof(char));
	if ( nombre == NULL ) {
		/** @todo Msj de ABORTAR/ERROR al HIJO  */
		perror("pre_genSalto Mem nombre");
		cadResultado = "ERR-MEM";
		return 1;
		}
	nbytes = read(pipeHP[0], nombre, tam * sizeof(char));
	nombre[tam] = '\0';

	// Tam y nombre etiqueta
	nbytes = read(pipeHP[0], &tam, sizeof(int));
	etq = (FXchar *) malloc ((tam+1) * sizeof(char));
	if ( etq == NULL ) {
		/** @todo Msj de ABORTAR/ERROR al HIJO  */
		perror("pre_genSalto Mem etq");
		cadResultado = "ERR-MEM";
		return 1;
		}
	nbytes = read(pipeHP[0], etq, tam * sizeof(char));
	etq[tam] = '\0';

	// Actualizacion barra de estado YA ESTA HECHA

	// Desactivar gestor PIPE

	getApp()->removeInput(pipeHP[0], INPUT_READ);

	return 1;
	}

/**
  Post-generacion codigo Salto.
  Actualizacion de la GUI
 */

FXint guiWindow::post_genSalto(void) {
	FXString salto;

	/************************
	  TODO: Donde esta el error ???
	  Se supone que era para comprobar si habian
	  habido problemas de Mem dinamica en pre_genSalto() !!!

	if ( strcmp(cadResultado, "ERR-MEM") == 0 ) {
		codOp = OP_POST;
		cadDatosOp.assign("<NO GENERADA>");
		flagLexema = 1;
		return 1;
		}
	 **********************************************/


	salto.assign('\n');
	salto.append('\t', nivTab);

	if ( tipoSalto == COND ) { 
  		salto.append("if ( !");
		salto.append(nombre);
		salto.append(" ) goto ");
		salto.append(etq);
		salto.append(";\n");
	} else {
		salto.append("goto ");
		salto.append(etq);
		salto.append(";\n");
		}

	txtDestino->appendText(salto.text(),salto.length());

	printf("PADRE escribio sentencia de salto\n");

	free(nombre);
	free(etq);

	// Actualizacion barra de estado
	codOp = OP_POST;
	flagResultado = 1;
	cadResultado = "OK";
	flagLexema = 0;

	return 1;
	}


/**
 Pre-generacion escritura etiqueta
 Lectura de la etiqueta y actualizacion Barra de estado
 */

long guiWindow::pre_genEscEtq(void) {
	int nbytes, tam;

	// Lectura de la etiqueta y su tamaÃ±o
	nbytes = read(pipeHP[0], &tam, sizeof(int));
	etq = (FXchar *) malloc ((tam+1) * sizeof(char));
	if ( nombre == NULL ) {
		perror("PADRE genDecVar MEM nombre");
		// TODO: Msj ERROR al HIJO
		return 0;
		}
	nbytes = read(pipeHP[0], etq, tam * sizeof(char));
	etq[tam] = '\0';


	// Actualizacion Barra de estado
	codOp = OP_GEN_ESCETQ;
	flagResultado = 1;
	cadResultado = "";
	flagLexema = 1;
	cadCaption.assign("  TIPO COD:", 11);
	cadDatosOp = "ESC ETIQUETA";

	// Marcamos codigo generado como pendiente
	// flagCodGen = 1;

	// Desactivar gestor PIPE

	getApp()->removeInput(pipeHP[0], INPUT_READ);

	return 1;
	}


// Post-generacion codigo INICIO BLOQUE

FXint guiWindow::post_genEscEtq(void) {
	FXString strAux;

	strAux.assign('\n');
	strAux.append('\t', nivTab);
	strAux.append(etq, strlen(etq));
	strAux.append(":\n", 2);

	txtDestino->appendText(strAux.text(), strAux.length());

	codOp = OP_POST;
	flagResultado = 1;
	cadResultado = "OK";
	flagLexema = 0;

	free(etq);

	return 1;
	}


/**
 Pre-generar declaracion de proc
*/

long guiWindow::pre_genDecProc(void) {
	int tam;

	// Tamaño y nombre
	read(pipeHP[0], &tam, sizeof(int));
	nombre = (FXchar *) malloc ((tam+1) * sizeof(char));
	if ( nombre == NULL ) {
		perror("Mem pre_decProc");
		exit(1);
		}
	read(pipeHP[0], nombre, tam * sizeof(char));
	nombre[tam] = '\0';

	// Tipo de dato devuelto
	read(pipeHP[0], &tipoTemp, sizeof(char));

	// Inicializamos el numero de Parametros
	contParams = 0;

	// Actualizacion Barra de estado
	codOp = OP_GEN_DEC_PROC;
	cadResultado = "";
	flagResultado = 1;
	flagLexema = 1;
	cadCaption.assign("  TIPO COD:", 11);
	cadDatosOp = "DEC PROC";

	// Cambiamos al fichero de funciones
	txtDestino = txtProcs;

	// Desactivar gestor PIPE

	getApp()->removeInput(pipeHP[0], INPUT_READ);

	return 1;
	}

	
/**
 Post-generar declaracion de proc
*/

FXint guiWindow::post_genDecProc(void) {
	FXString strDec;

	strDec.assign('\n');
	strDec.append('\t', nivTab2);

	if ( tipoTemp != NO_ASIG )
		fprintf(stderr, "UPS! Todavia no generamos FUNCIONES\n");

	strDec.append("void ");
	strDec.append(nombre, strlen(nombre));
	strDec.append("( ", 2);

	txtProcs->appendText(strDec.text(), strDec.length());

	codOp = OP_POST;
	flagResultado = 1;
	cadResultado = "OK";
	flagLexema = 0;

	free(nombre);

	return 1;
	}


/**
 Pre-generar parametro en Declaracion de proc
*/

long guiWindow::pre_genDecParam(void) {
	int tam;

	// Tamaño y nombre
	read(pipeHP[0], &tamNom, sizeof(int));
	if ( tamNom != 0 ) {
		nombre = (FXchar *) malloc ((tamNom+1) * sizeof(char));
		if ( nombre == NULL ) {
			perror("Mem pre_decProc");
			exit(1);
			}
		read(pipeHP[0], nombre, tamNom * sizeof(char));
		nombre[tamNom] = '\0';
		}

	// Tipo de dato devuelto
	read(pipeHP[0], &tipoTemp, sizeof(char));


	// Actualizacion Barra de estado
	codOp = OP_GEN_PARAM;
	cadResultado = "";
	flagResultado = 1;
	flagLexema = 1;
	cadCaption.assign("  TIPO COD:", 11);
	cadDatosOp = "DEC PARAM";

	// Desactivar gestor PIPE

	getApp()->removeInput(pipeHP[0], INPUT_READ);

	return 1;
	}

	
/**
 Post-generar parametro en Declaracion de proc
*/

FXint guiWindow::post_genDecParam(void) {
	FXString strPar;
	FXchar *nomTiposDato[] = { "void", "DESCONOCIDO"
				, "int", "real"
				, "LISTA_REAL", "LISTA_ENTERO"
				, "unsigned char", "LISTA_BOOLEANO"
				, "char", "LISTA_CARACTER"
				, "STRING", "ARRAY", "CJTO", "PILA"
				};

	if ( contParams > 0 )
		strPar.append(", ", 2);

	contParams++;

	strPar.append(nomTiposDato[tipoTemp], strlen(nomTiposDato[tipoTemp]));
	strPar.append(' ');

	if ( tamNom != 0 ) {
		strPar.append(nombre, strlen(nombre));
		free(nombre);
		}

	txtProcs->appendText(strPar.text(), strPar.length());

	codOp = OP_POST;
	flagResultado = 1;
	cadResultado = "OK";
	flagLexema = 0;

	return 1;
	}


/**
 Pre Fin Cabecera de PROC.
*/

long guiWindow::pre_genFinCabecera(void) {

	// Actualizacion Barra de estado
	codOp = OP_GEN_FIN_CAB;
	cadResultado = "";
	flagResultado = 1;
	flagLexema = 1;
	cadCaption.assign("  TIPO COD:", 11);
	cadDatosOp = "Fin Cabecera PROC";

	// Desactivar gestor PIPE

	getApp()->removeInput(pipeHP[0], INPUT_READ);

	return 1;
	}

/**
 Post Fin Declaracion PROC
*/

FXint guiWindow::post_genFinCabecera(void) {

	txtProcs->appendText(" )", 2);

	contParams = 0;
	codOp = OP_POST;
	flagResultado = 1;
	cadResultado = "OK";
	flagLexema = 0;

	return 1;
	}


/**
 Pre Fin Cuerpo del PROC.
*/

long guiWindow::pre_genFinDecProc(void) {

	// Actualizacion Barra de estado
	codOp = OP_GEN_FIN_DEC_PROC;
	cadResultado = "";
	flagResultado = 1;
	flagLexema = 1;
	cadCaption.assign("  TIPO COD:", 11);
	cadDatosOp = "Fin Dec PROC";

	// Desactivar gestor PIPE

	getApp()->removeInput(pipeHP[0], INPUT_READ);

	return 1;
	}

/**
 Post Fin Declaracion PROC
*/

FXint guiWindow::post_genFinDecProc(void) {

	txtDestino = txtGen;

	// Esto no va AQUI !!!!
	// Se cambia cuando termine la declaracion del PROC
	// txtDestino = txtGen;

	contParams = 0;
	codOp = OP_POST;
	flagResultado = 1;
	cadResultado = "OK";
	flagLexema = 0;

	return 1;
	}

	
/**
 Pre-Llamada a procedimiento
*/

long guiWindow::pre_genLlamada(void) {
	
	// Tam y nombre del proc
	read(pipeHP[0], &tamNom, sizeof(int));
	nombre = (FXchar *) malloc ((tamNom+1) * sizeof(char));
	if ( nombre == NULL ) {
		perror("pre_genLlamada");
		// Y ahora que ??
		return 0;
		}

	read(pipeHP[0], nombre, tamNom * sizeof(char));
	nombre[tamNom] = '\0';

	// Tam y lista de argumentos
	read(pipeHP[0], &tamLista, sizeof(int));
	if ( tamLista > 0 ) {
		listaArgs = (char *) malloc ((tamLista+1)*sizeof(char));
		if ( listaArgs == NULL ) {
			perror("pre_genLLamada");
			// Y ahora que ???
			return 0;
			}
		read(pipeHP[0], listaArgs, tamLista * sizeof(char));
		listaArgs[tamLista] = '\0';
		}

	// Actualizacion Barra de estado
	codOp = OP_GEN_CALL_PROC;
	cadResultado = "";
	flagResultado = 1;
	flagLexema = 1;
	cadCaption.assign("  TIPO COD:", 11);
	cadDatosOp = "Llamada a PROC";

	// Desactivar gestor PIPE

	getApp()->removeInput(pipeHP[0], INPUT_READ);

	return 1;
	}


/**
 Post-llamada a PROC
*/

FXint guiWindow::post_genLlamada(void) {
	FXString strAux;

	strAux.assign('\t', nivTab);
	strAux.append(nombre);
	strAux.append("( ");

	if ( tamLista > 0 ) {
		strAux.append(listaArgs);
		free(listaArgs);
		}

	strAux.append(" );\n");

	/*******	
	txtDestino->appendText(nombre, tamNom);
	txtDestino->appendText("( ", 2);
	**********************************/
	
	txtDestino->appendText(strAux.text(), strAux.length());

	free(nombre);

	codOp = OP_POST;
	flagResultado = 1;
	cadResultado = "OK";
	flagLexema = 0;

	return 1;
	}


