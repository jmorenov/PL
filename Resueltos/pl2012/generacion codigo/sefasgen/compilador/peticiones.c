/**
 @file
 Funciones de peticion de operacion con TS
 del compilador al GUI.
*/
 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "sefasgen.h"
#include "def_msjs.h"

extern unsigned char flagREI;

/**
 Peticion Insertar nueva entrada en TS
 @param reg Nueva entrada a insertar
 @param tipoTS Tipo de entrada ( MARCAR, PROC, ... )
 @return 1 si la insercion fue correcta, 0 en otro caso
 */

int pet_introTS(stEntrada reg, tEntrada tipoTS) {
	char msj[4];
	int tam, nbytes;
	unsigned char tipo;
	
	// Mandamos peticion al padre

	// Tipo de mensaje: Insercion
	// strcpy(msj, "I");
	/** @todo Utilizar enumeracion como en gestorOP!!! */
	msj[0] = INS;
	nbytes = write(1, &msj, sizeof(char));

	// Tam y Lexema

	tam = strlen(reg.lexema);
	nbytes = write(1, &tam, sizeof(int));
	nbytes = write(1, reg.lexema, tam * sizeof(char));

	// Tipo de dato
	
	tipo = reg.tipoDato;
	nbytes = write(1, &tipo, sizeof(unsigned char));
	
	// Tipo de entrada
	
	tipo = tipoTS;
	nbytes = write(1, &tipo, sizeof(unsigned char));
	
	// Si se trata de un descriptor de control
	// Mandar campos adicionales

	if ( tipoTS == DESC_CTRL ) {
		// Tam y etiqueta de entrada
		tam = strlen(reg.etqtEnt);
		nbytes = write(1, &tam, sizeof(int));
		nbytes = write(1, reg.etqtEnt, tam * sizeof(char));
		tam = strlen(reg.etqtSal);
		nbytes = write(1, &tam, sizeof(int));
		nbytes = write(1, reg.etqtSal, tam * sizeof(char));
		tam = strlen(reg.etqtElse);
		nbytes = write(1, &tam, sizeof(int));
		nbytes = write(1, reg.etqtElse, tam * sizeof(char));
		tam = strlen(reg.nomVarCtrl);
		nbytes = write(1, &tam, sizeof(int));
		nbytes = write(1, reg.nomVarCtrl, tam * sizeof(char));
		}


	// Localizacion del lexema
	// Si NO es MARCA ( "{" o "}" )
	/** @todo Verificar si haria falta LOCALIZACION para DESC CONTROL */
	if ( tipoTS != MARCA ) {
		// Linea inicio
		nbytes = write(1, &reg.linIni, sizeof(int));
		// Linea fin
		nbytes = write(1, &reg.linFin, sizeof(int));
		// Columna inicio
		nbytes = write(1, &reg.colIni, sizeof(int));
		// Columna fin
		nbytes = write(1, &reg.colFin, sizeof(int));
		}

	// Esperamos Respuesta del PADRE
	// Tipo de respuesta:
	//	ACK 
	//	REP (simbolo presente en TS)


	// fprintf(stderr, "Mandado mensaje INTRO\n");

	nbytes = read(0, msj, 4 * sizeof(char));
	printf("Recibido resultado: %s\n", msj);

	// Comprobamos si debemos REINICIAR
	check();
	
	if ( strcmp(msj, "ACK") == 0 ) {
		printf("Simbolo introducido...\n");
		return 1;
	} else {
		printf("Simbolo REPETIDO!!!!\n");
		return 0;
		}

	// fprintf(stderr, "COMP recibio continuacion: %s\n", msj);
	}

/**
 Busqueda del tipo de un simbolo en el ambito actual.
 @param reg Se debe haber establecido en la estructura
 el lexema del simbolo y las variables de localizacion
 @return Tipo de dato del simbolo DESC si no se encuentra
*/
 
tDato pet_BuscarTS(stEntrada reg) {
	int tam, nbytes;
	char msj[4];
	unsigned char tipo;
		
	fprintf(stderr, "[INF] Buscando %s\n", reg.lexema);
	
	// Peticion al padre
	// strcpy(msj, "B");
	msj[0] = BSIM;
	nbytes = write(1, &msj, sizeof(char));
	
	// Tam e Identificador
	
	tam = strlen(reg.lexema);
	nbytes = write(1, &tam, sizeof(int));
	nbytes = write(1, reg.lexema, tam * sizeof(char));

	// Variables de localizacion
	nbytes = write(1, &reg.linIni, sizeof(int));
	nbytes = write(1, &reg.linFin, sizeof(int));
	nbytes = write(1, &reg.colIni, sizeof(int));
	nbytes = write(1, &reg.colFin, sizeof(int));

	// Esperamos Respuesta del PADRE
	// Tipo de respuesta:
	//	ACK 
	//	ERR (simbolo no encontrado)

	nbytes = read(0, msj, 4 * sizeof(char));
	
	// Tipo de dato

	nbytes = read(0, &tipo, sizeof(unsigned char));
	
	fprintf(stderr, "[INF] Recibido Tipo de %s\n", reg.lexema);
	
	// Espera de señal de continuacion
	// nbytes = read(0, msj, 4 * sizeof(char));

	// Comprobamos si debemos REINICIAR
	check();

	return (tDato)tipo;
	}

/**
  Sacar todos los simbolos pertenecientes
  al ultimo bloque.
*/
 
void pet_SacarTS(void) {
	char msj[4];
	int nbytes;
	
	fprintf(stderr, "COMP Sacando simbolos...\n");
	
	// Peticion al padre
	// strcpy(msj, "S");
	msj[0] = DEL;
	nbytes = write(1, msj, sizeof(char));
	
	// Esperamos respuesta del padre
	// ACK o ERR
	// nbytes = read(0, msj, 4 * sizeof(char));
	// fprintf(stderr, "COMP Fin sacar simbolos\n");

	// Comprobamos si debemos REINICIAR
	check();
	
	return;
	}
	
/**
 Peticion de busqueda PROCEDIMIENTO para
  comprobar numero y tipo de argumentos
  correcto en llamada.
 @return Numero de parametros declarados
	-1 si hubo algun error
*/

int pet_BuscarPROC(stEntrada reg) {
	char msj[4];
	int nbytes, tam;
	
	fprintf(stderr, "COMP Buscando PROC: %s\n", reg.lexema);
	
	// Peticion al padre
	// strcpy(msj, "P");
	msj[0] = BPROC;
	nbytes = write(1, msj, sizeof(char));
	
	// Tamaño y lexema del identificar de PROC
	
	tam = strlen(reg.lexema);
	nbytes = write(1, &tam, sizeof(int));
	nbytes = write(1, reg.lexema, tam * sizeof(char));
	
	// Variables de localizacion
	nbytes = write(1, &reg.linIni, sizeof(int));
	nbytes = write(1, &reg.linFin, sizeof(int));
	nbytes = write(1, &reg.colIni, sizeof(int));
	nbytes = write(1, &reg.colFin, sizeof(int));


	// Esperamos respuesta del padre
	nbytes = read(0, &tam, sizeof(int));

	// Comprobamos si debemos REINICIAR
	check();
	
	return tam;
	}

 
/**
 Peticion para comprobar tipo de Dato 
 de un argumento en una llamada a PROCEDIMIENTO.
 @return 1 si el tipo es correcto
	 0 en otro caso
 *************************************************/
 
unsigned char pet_BuscarPARAM(stEntrada reg) {
	char msj[4];
	int nbytes, tam;
	unsigned char resultado;

	fprintf(stderr, "COMP Buscando tipo PARAM...\n");
	
	// Peticion al padre
	// strcpy(msj, "A");
	msj[0] = BPARAM;
	nbytes = write(1, msj, sizeof(char));
	
	// Tipo de dato
	
	nbytes = write(1, &reg.tipoDato, sizeof(unsigned char));
	
	// Variables de localizacion
	nbytes = write(1, &reg.linIni, sizeof(int));
	nbytes = write(1, &reg.linFin, sizeof(int));
	nbytes = write(1, &reg.colIni, sizeof(int));
	nbytes = write(1, &reg.colFin, sizeof(int));


	// Esperamos respuesta del padre
	// ACK -> Tipo correcto
	// NUM -> Num de parametros incorrecto
	// ERR -> Tipo de dato INCORRECTO
	
	nbytes = read(0, msj, 4 * sizeof(char));
	if ( strcmp(msj, "ACK") == 0 )
		resultado = 1;
	else
		resultado = 0;
	
	
	// Espera de la señal de continuar
	// nbytes = read(0, msj, 4 * sizeof(char));

	// Comprobamos si debemos REINICIAR
	check();


	return resultado;
	}

/**
 Peticion de comprobacion de tipos.
 Aunque podria realizarse en el propio
 compilador esta disponible para que
 para poder ser reflejada en Sefasgen

 @param reg1 1era entrada a comparar
 @param reg2 2a entrada
 @return 1 -> OK 0 -> ERROR
*/

int pet_VerifTIPO(stEntrada reg1, stEntrada reg2) {
	int nbytes, res;
	char msj[4];

	// Peticion de comprobacion al padre
	// strcpy(msj, "V");
	msj[0] = VERIF;
	nbytes = write(1, msj, sizeof(char));

	// 1era entrada
	// Tipo de dato

	nbytes = write(1, &reg1.tipoDato, sizeof(unsigned char));

	// Variables de localizacion
	nbytes = write(1, &reg1.linIni, sizeof(int));
	nbytes = write(1, &reg1.linIni, sizeof(int));
	nbytes = write(1, &reg1.colIni, sizeof(int));
	nbytes = write(1, &reg1.colFin, sizeof(int));

	// 2a entrada
	// Tipo de dato
	nbytes = write(1, &reg2.tipoDato, sizeof(unsigned char));
	
	// Variables de localizacion
	nbytes = write(1, &reg2.linIni, sizeof(int));
	nbytes = write(1, &reg2.linIni, sizeof(int));
	nbytes = write(1, &reg2.colIni, sizeof(int));
	nbytes = write(1, &reg2.colFin, sizeof(int));

	// Esperamos contestacion
	nbytes = read(0, &res, sizeof(int));

	// Esperamos señal de continuar
	// nbytes = read(0, msj, 4 * sizeof(char));

	// Comprobamos si debemos REINICIAR
	check();

	return res;
	}

/**
  Peticion generar Inicio de Programa.
  Inclusion de archivos de cabecera
  y MAIN
*/

void pet_GenIni(void) {
	int nbytes;
	char msj[4];

	msj[TIPO_MSJ] = GENCOD;
	msj[SUBTIPO] = 0;
	nbytes = write(1, msj, 2 * sizeof(char));

	// Comprobamos si debemos reiniciar
	check();

	return;
	}


/**
 Peticion generacion Codigo para DECLARACION de VARIABLE.
 @param tipo Tipo de dato de la variable
 @param nom Nombre de la variable
*/

void pet_GenDecVar(tDato tipo, char *nom) {
	int nbytes, tam;
	char msj[4];

	// strcpy(msj, "GV");
	msj[0] = GENCOD;
	msj[1] = DVAR;
	nbytes = write(1, msj, 2 * sizeof(char));

	// Tipo de dato
	nbytes = write(1, &tipo, sizeof(char));
	// Tam y nombre variable
	tam = strlen(nom);
	nbytes = write(1, &tam, sizeof(int));
	nbytes = write(1, nom, tam * sizeof(char));

	// Comprobamos si debemos reiniciar
	check();

	return;
	}


/**
  Peticion generacion de codigo para INICIO BLOQUE.
  Escribir "{" y Aumentar nivel de Tabulacion
  Incluye comentario para facilitar trazabilidad
  @todo Permitir NO incluir comentario
*/

void pet_GenIniBlq(char *comentario, int ini, int fin) {
	char msj[4];
	int nbytes, tam;

	// strcpy(msj, "G{");
	msj[0] = GENCOD;
	msj[1] = 1;
	nbytes = write(1, msj, 2 * sizeof(char));
	
	// Enviamos las variables de localizacion
	nbytes = write(1, &ini, sizeof(int));
	nbytes = write(1, &fin, sizeof(int));


	// Enviamos comentario y su tamaño
	// si es que lo hay...

	if ( comentario != NULL ) {
		tam = strlen(comentario);
		nbytes = write(1, &tam, sizeof(int));
		nbytes = write(1, comentario, tam * sizeof(char));
	} else {
		tam = 0;
		write(1, &tam, sizeof(int));
		}
	
	// Comprobamos si debemos reiniciar
	check();

	return;
	}

/**
  Peticion generacion de codigo para FIN BLOQUE.
  Disminuir nivel Tabulacion y Escribir "}"
*/

void pet_GenFinBlq(void) {
	char msj[4];
	int nbytes, tam;

	// strcpy(msj, "G}");
	msj[0] = GENCOD;
	msj[1] = FIN_BLOQUE;
	nbytes = write(1, msj, 2 * sizeof(char));
	

	// Comprobamos si debemos reiniciar
	check();

	return;
	}


/**
  Peticion generacion de codigo para ASIGNACION.
  Se pueden utilizar un minimo de 2 operandos y
  un maximo de 4.
  @param numOp Numero de operadores/operandos
  @param op1,op2,op3,op4 operandos/operadores
*/


void pet_GenAsig(int numOp, char *op1, char *op2, char *op3, char *op4) {
	char msj[4];
	int nbytes, tam;

	// strcpy(msj, "GA");
	msj[0] = GENCOD;
	msj[1] = ASIGNACION;
	nbytes = write(1, msj, 2 * sizeof(char));

	// Numero de operandos
	/*** Ya no hace falta
	nbytes = write(1, &numOp, sizeof(int));
	****************************************/

	// Minimo de 2 Operandos
	tam = strlen(op1);
	nbytes = write(1, &tam, sizeof(int));
	nbytes = write(1, op1, tam * sizeof(char));
	tam = strlen(op2);
	nbytes = write(1, &tam, sizeof(int));
	nbytes = write(1, op2, tam * sizeof(char));

	switch ( numOp ) {
		case 2:
			tam = 0;
			nbytes = write(1, &tam, sizeof(int));
			nbytes = write(1, &tam, sizeof(int));
			break;
		case 3:
			tam = strlen(op3);
			nbytes = write(1, &tam, sizeof(int));
			nbytes = write(1, op3, tam * sizeof(char));
			tam = 0;
			nbytes = write(1, &tam, sizeof(int));
			break;
		case 4:
			tam = strlen(op3);
			nbytes = write(1, &tam, sizeof(int));
			nbytes = write(1, op3, tam * sizeof(char));

			tam = strlen(op4);
			nbytes = write(1, &tam, sizeof(int));
			nbytes = write(1, op4, tam * sizeof(char));
			break;
		}


			

			
	// Comprobamos si debemos reiniciar
	check();

	return;
	}

/**
  Peticion de un nuevo Nombre de VAR TEMPORAL.
 */

char *pet_GenTemp(void) {
	int tam, nbytes;
	char *nom;
	char msj[4];

	//strcpy(msj, "GT");
	msj[0] = TEMP;
	write(1, msj, sizeof(char));

	// Esperamos respuesta del PADRE
	// TODO: MSJ ACK Previo al nuevo nombre ??
	// Tam y nuevo nombre
	read(0, &tam, sizeof(int));
	nom = (char *) malloc ((tam+1) * sizeof(char));
	if ( nom == NULL ) {
		// Cuidado que va a STDERR
		perror("ERR: NomTemp Memoria nom");
		return NULL;
		}
	read(0, nom, tam * sizeof(char));
	nom[tam] = '\0';

	fprintf(stderr, "COMP pet_GenTemp recibio: %s\n", nom);

	// Comprobamos si debemos reiniciar
	check();

	return nom;
	}

/**
 Peticion generacion cadena formato para Entrada/Salida.
 Post:
	- Formato contiene la nueva cadena Ej: "La suma 2 + 4 = %d\n"
	- Vars contiene los nombres de las nuevas variables ", temp"

 @param colIni columna de inicio de la expresion
 @param colFin columna final de la expresion
 @param tipo Tipo de dato del argumento a añadir
 @param nuevoArg nombre del nuevo argumento a añadir
 @param tipoSent Tipo de Sentencia 0 - SALIDA 1 - ENTRADA
*/

void pet_GenCadFormato(int colIni, int colFin
	, char **formato, char **vars, tDato tipo
	, char *nuevoArg, unsigned char tipoSent)
	{
	char msj[4];
	int tam, nbytes;
	char *nuevoFmt;
	char *nuevaVar;
	char tipoChar;

	// Peticion al padre
	// msj[TIPO_MSJ] = GEN;
	// msj[SUBTIPO] = CAD_FORMATO;
	// msj[2] = '\0';
	msj[0] = CADFMT;
	nbytes = write(1, msj, sizeof(char));

	// Tipo de E/S
	nbytes = write(1, &tipoSent, sizeof(unsigned char));

	// Localizacion de la cadena de formato
	nbytes = write(1, &colIni, sizeof(int));
	nbytes = write(1, &colFin, sizeof(int));


	// Tipo del nuevo argumento
	// Si se usa char, leer en un char
	// y convertir a tDato !!!!
	// nbytes = write(1, &tipo, sizeof(char));
	nbytes = write(1, &tipo, sizeof(tDato));

	// Tam y nombre nuevo argumento
	tam = strlen(nuevoArg);
	nbytes = write(1, &tam, sizeof(int));
	nbytes = write(1, nuevoArg, tam * sizeof(char));

	// Recepcion datos del PADRE
	// Nueva porcion cadena formato
	nbytes = read(0, &tam, sizeof(int));
	nuevoFmt = (char *) malloc ((tam+1) * sizeof(char));

	if ( nuevoFmt == NULL ) {
		perror("ERR GenCadFormato nuevoFmt");
		// QUE HACER ???
		// En teoria TERMINAR !!!!
		return;
		}

	read(0, nuevoFmt, tam * sizeof(char));
	nuevoFmt[tam] = '\0';

	// Nueva porcion cadena variables
	nbytes = read(0, &tam, sizeof(int));
	nuevaVar = (char *) malloc ((tam+1) * sizeof(char));

	if ( nuevoFmt == NULL ) {
		perror("ERR GenCadFormato nuevaVar");
		// TODO: Gestion de ERRORES en HIJO
		return;
		}

	read(0, nuevaVar, tam * sizeof(char));
	nuevaVar[tam] = '\0';


	fprintf(stderr, "COMP genCadFormato NUEVOS Fmt: %s Var: %s\n"
		, nuevoFmt, nuevaVar);

	// COPIA de las NUEVAS CADENAS
	// TODO: Revisar punteros NULL !!!!

	if ( *formato == NULL ) {
		fprintf(stderr, "COMP Crear NUEVO *formato\n");
		// Nueva cadena
		// En teoria strlen(nuevoFmt) = 3 => %<tipo>\0
		(*formato) = (char *) malloc((strlen(nuevoFmt)+1)
			* sizeof(char));
		if ( (*formato) == NULL ) {
			perror("ERR GenCadFormato *formato");
			return;
			}

		strcpy(*formato, nuevoFmt);
		free(nuevoFmt);
	} else {
		// Ampliar la cadena
		(*formato) = (char *) realloc(*formato
			, (strlen(*formato)+ strlen(nuevoFmt) + 1)
			* sizeof(char));
		if ( *formato == NULL ) {
			perror("ERR GenCadFormato realloc *formato");
			return;
			}

		*formato = strcat(*formato, nuevoFmt);
		free(nuevoFmt);
		}

	if ( *vars == NULL ) {
		// Nueva cadena
		fprintf(stderr, "COMP Crear NUEVO *vars\n");
		(*vars) = (char *) malloc((strlen(nuevaVar)+1)
			* sizeof(char));
		if ( (*vars) == NULL ) {
			perror("ERR GenCadFormato *vars");
			return;
			}

		strcpy(*vars, nuevaVar);
		free(nuevaVar);
	} else {
		// Ampliar la cadena
		(*vars) = (char *) realloc(*vars
			, (strlen(*vars)+ strlen(nuevaVar) + 1)
			* sizeof(char));
		if ( *vars == NULL ) {
			perror("ERR GenCadFormato realloc *vars");
			return;
			}

		*vars = strcat(*vars, nuevaVar);
		free(nuevaVar);
		}
	
	fprintf(stderr, "COMP genCadFormato TOTALES Fmt: %s Var: %s\n"
		, *formato, *vars);


	// Comprobamos si debemos reiniciar
	check();

	return;
	}


/**
 Peticion generar codigo para Entrada/Salida.
 @param fmt Cadena que describe el formato
 @param vars Cadena que describe las variables usadas
 @param tipoSent Tipo de sentencia ENTRADA o SALIDA
 */

void pet_GenENTRADA(char *fmt, char *vars) {
	char msj[4];
	int tam, nbytes;

	msj[TIPO_MSJ] = GENCOD;
	msj[SUBTIPO] = ENTRADA;

	nbytes = write(1, msj, 2 * sizeof(char));

	// Tipo de Sentencia
	/**
	Ya no lo necesitamos..
	Tenemos funciones separadas
	nbytes = write(1, &tipoSent, sizeof(char));
	***/

	// Tamaño y cadena de formato
	tam = strlen(fmt);
	nbytes = write(1, &tam, sizeof(int));
	nbytes = write(1, fmt, tam * sizeof(char));

	// Tamaño y cadena de variables
	tam = strlen(vars);
	nbytes = write(1, &tam, sizeof(int));
	nbytes = write(1, vars, tam * sizeof(char));

	// Comprobamos si debemos reiniciar
	check();

	return;
	}

/**
 Peticion generar codigo para Entrada/Salida.
 @param fmt Cadena que describe el formato
 @param vars Cadena que describe las variables usadas
 @param tipoSent Tipo de sentencia ENTRADA o SALIDA
 */

void pet_GenSALIDA(char *fmt, char *vars) {
	char msj[4];
	int tam, nbytes;

	msj[TIPO_MSJ] = GENCOD;
	msj[SUBTIPO] = SALIDA;

	nbytes = write(1, msj, 2 * sizeof(char));

	// Tipo de Sentencia
	/**
	Ya no lo necesitamos..
	Tenemos funciones separadas
	nbytes = write(1, &tipoSent, sizeof(char));
	***/

	// Tamaño y cadena de formato
	tam = strlen(fmt);
	nbytes = write(1, &tam, sizeof(int));
	nbytes = write(1, fmt, tam * sizeof(char));

	// Tamaño y cadena de variables
	tam = strlen(vars);
	nbytes = write(1, &tam, sizeof(int));
	nbytes = write(1, vars, tam * sizeof(char));

	// Comprobamos si debemos reiniciar
	check();

	return;
	}


/**
 Peticion generar sentencia de salto CONDICIONAL
 @param nomVar Variable de la expresion en salto condicional
 @param etq Etiqueta destino del salto
 */

void pet_GenSaltoCond(char *nomVar, char *etq) {
	int nbytes, tam;
	char msj[2];

	msj[TIPO_MSJ] = GENCOD;
	msj[SUBTIPO] = JCOND;
	nbytes = write(1, msj, 2 * sizeof(char));

	// Enviamos tipo de salto
	/** Ya no...
	nbytes = write(1, &tipo, sizeof(unsigned char));
	***/

	// Tam y nombre variable
	tam = strlen(nomVar);
	nbytes = write(1, &tam, sizeof(int));
	nbytes = write(1, nomVar, tam * sizeof(char));

	// Tam y nombre etiqueta
	tam = strlen(etq);
	nbytes = write(1, &tam, sizeof(int));
	nbytes = write(1, etq, tam * sizeof(char));

	// Comprobamos si debemos reiniciar
	check();

	return;
	}

/**
 Peticion generar sentencia de salto INCONDICIONAL
 @param etq Etiqueta destino del salto
 */

void pet_GenSaltoInCond(char *etq) {
	int nbytes, tam;
	char msj[2];

	msj[TIPO_MSJ] = GENCOD;
	msj[SUBTIPO] = JINCOND;
	nbytes = write(1, msj, 2 * sizeof(char));

	// Enviamos tipo de salto
	/** Ya no...
	nbytes = write(1, &tipo, sizeof(unsigned char));
	***/

	// Tam y nombre etiqueta
	tam = strlen(etq);
	nbytes = write(1, &tam, sizeof(int));
	nbytes = write(1, etq, tam * sizeof(char));

	// Comprobamos si debemos reiniciar
	check();

	return;
	}

/**
 Peticion de un nuevo Nombre de ETIQUETA
 @todo pet_GenEtiq y pet_GenTemp son IDENTICAS !!!
 @todo Convertirlas en una sola funcion
 */

char *pet_GenEtiq(void) {
	int tam, nbytes;
	char *etq;
	char msj[2];

	/****  strcpy(msj, "GT");	********/

	// Mandamos peticion al padre
	// msj[TIPO_MSJ] = GEN;
	// msj[SUBTIPO] = ETIQUETA;
	msj[0] = ETIQ;
	write(1, msj, sizeof(char));


	// Esperamos respuesta del PADRE
	// Tam y nuevo nombre
	read(0, &tam, sizeof(int));
	etq = (char *) malloc ((tam+1) * sizeof(char));
	if ( etq == NULL ) {
		// Cuidado que va a STDERR
		perror("ERR: NomTemp Memoria nom");
		return NULL;
		}
	read(0, etq, tam * sizeof(char));
	etq[tam] = '\0';

	fprintf(stderr, "COMP pet_GenEtiqueta recibio: %s\n", etq);

	// Comprobamos si debemos reiniciar
	check();

	return etq;
	}
	
/**
 Peticion escribir etiqueta.
 @param etq Cadena con la etiqueta a escribir
 */

void pet_EscEtq(char *etq) {
	int tam, nbytes;
	char msj[2];

	msj[TIPO_MSJ] = GENCOD;
	msj[SUBTIPO] = ESC_ETQ;
	nbytes = write(1, msj, 2 * sizeof(char));

	tam = strlen(etq);
	nbytes = write(1, &tam, sizeof(int));
	nbytes = write(1, etq, tam * sizeof(char));

	// Comprobamos si debemos reiniciar
	check();

	return;
	}

/**
 Peticion busqueda Etiqueta en ultimo DESCRIPTOR de CONTROL en la TS
 @param tipoEtq Tipo de etiqueta necesaria
 */

char *pet_BuscarEtq(unsigned char tipoEtq) {
	int nbytes,tam;
	char msj[2];
	char *etq;

	// msj[TIPO_MSJ] = GEN;
	// msj[SUBTIPO] = BUSQ_ETQ;

	fprintf(stderr, "DEBUG COMPILADOR Enviando Tipo Etiqueta: %d\n"
		, tipoEtq);

	msj[0] = BUSQ_ETIQ;
	nbytes = write(1, msj, sizeof(char));

	// Enviamos Tipo de etiqueta buscado
	nbytes = write(1, &tipoEtq, sizeof(unsigned char));

	fprintf(stderr, "DEBUG COMPILADOR Enviado Tipo Etiqueta\n");

	// Recepcion de la etiqueta y tamaño
	nbytes = read(0, &tam, sizeof(int));
	etq = (char *) malloc ((tam+1) * sizeof(char));
	if ( etq == NULL ) {
		fprintf(stderr, "[ERR] No hay MEM para BuscarEtq");
		return NULL;
		}

	nbytes = read(0, etq, tam * sizeof(char));
	etq[tam] = '\0';

	// Comprobamos si debemos reiniciar
	check();

	return etq;
	}

/**
 Peticion de sacar simbolos de la TS
 hasta el ultimo descriptor de control
 */

void pet_SacarCTRL(void) {
	int nbytes;
	char msj[2];

	// msj[TIPO_MSJ] = GEN;
	// msj[SUBTIPO] = SACAR_CTRL;
	msj[0] = DEL_CTRL;

	nbytes = write(1, msj, sizeof(char));

	// Comprobamos si debemos reiniciar
	check();

	return;
	}



/***********************************************
  Funcion para comprobar respuesta
  ACK -> Continuar
  REI -> Reiniciar Nuevo compilador y/o Codigo
 ***********************************************/

void check(void) {
	int nbytes;
	char msj[4];

	nbytes = read(0, msj, 4 * sizeof(char));

	if ( strcmp(msj, "REI") == 0 ) {
		fprintf(stderr, "[INF] COMPILADOR recibio REI\n");
		// Funcionara ???
		flagREI = 1;
		strcpy(msj, "ACK");
		write(1, msj, 4 * sizeof(char));
		reiniciar();

	} else if ( strcmp(msj, "FIN") == 0 ) {
		fprintf(stderr, "[INF] COMPILADOR recibio FIN\n");
		// Despedida y cierre
		strcpy(msj, "ACK");
		nbytes = write(1, msj, 4 * sizeof(char));
		fprintf(stderr, "COMP aborto compilacion\n");
		exit(0);
		}

	// fprintf(stderr, "COMP check() = %s\n", msj);

	return;
	}

/******************************************
  REINICIO
  Lectura NUEVO compilador y NUEVO CODIGO
 ******************************************/

void reiniciar(void) {
	int nbytes, tam;
	char msj[4];
	char *ruta, *fComp, *fCod;

	fprintf(stderr, "[INF] Esperando NUEVOS archivos\n");

	// Tam y ruta al compilador
	nbytes = read(0, &tam, sizeof(int));
	ruta = (char *) malloc ((tam+1) * sizeof(char));
	if ( ruta == NULL ) {
		perror("[ERR] Reiniciar() Mem ruta");
		// TODO: msj ERROR al PADRE
		exit(1);
		}
	nbytes = read(0, ruta, tam * sizeof(char));
	ruta[tam] = '\0';

	// Tam y fichero ejecutable compilador
	nbytes = read(0, &tam, sizeof(int));
	fComp = (char *) malloc ((tam+1) * sizeof(char));
	if ( fComp == NULL ) {
		perror("[ERR] Reiniciar() Mem fComp");
		// TODO: msj ERROR al PADRE
		exit(1);
		}
	nbytes = read(0, fComp, tam * sizeof(char));
	fComp[tam] = '\0';

	// Tam y fichero codigo fuente
	nbytes = read(0, &tam, sizeof(int));
	fCod = (char *) malloc ((tam+1) * sizeof(char));
	if ( fCod == NULL ) {
		perror("[ERR] reiniciar() Mem fCod");
		// TODO: msj ERROR al PADRE
		exit(1);
		}
	nbytes = read(0, fCod, tam * sizeof(char));
	fCod[tam] = '\0';

	// LISTOS para ejecutar nuevo compilador

	fprintf(stderr, "[INF] NUEVA ruta: %s\n", ruta);
	fprintf(stderr, "[INF] NUEVO compilador: %s\n", fComp);
	fprintf(stderr, "[INF] NUEVO codigo fuente: %s\n", fCod);

	// NO HACE FALTA EJECUTAR DE NUEVO SOLO SI ES OTRO FICHERO DE DATOS
	// Basta CERRAR-ABRIR yyin ???
	execl(ruta, fComp, fCod, NULL);

	// NO deberiamos llegar aqui !!!
	perror("[ERR] Fallo de execl()");
	exit(1);
	}


/************************************
  Funcion encargada de informar al
  padre de la posicion del analisis
  en el fichero de GRAMATICA YACC
 ************************************/

void informar(int pos, int tam) {
	int nbytes;
	char msj[4];

	strcpy(msj, "L");
	nbytes = write(1, msj, sizeof(char));
	nbytes = write(1, &pos, sizeof(int));
	nbytes = write(1, &tam, sizeof(int));

	// Esperamos respuesta
	// NO HAY PASO !!!!!!!!!

	nbytes = read(0, msj, 4 * sizeof(char));

	return;
	}


/***********************************************
 convCadena
 
 Convierte el valor que se pasa como argumento
 a una cadena
 ***********************************************/
 
char *convCadena(tDato tipo, tValor valor) 
{
	char *cadValor;
	int num = -1;
	int tam = 25;
		
	
	if ( tipo == CARACTER )
		tam = 4;

	cadValor = (char *) malloc ( tam * sizeof(char) );
	if ( cadValor == NULL ) {
		perror("convCadena >> cadValor");
		exit(-1);
		}
	
	switch ( tipo ) {
		case ENTERO:
					
			while ( !(num > -1 && num < tam) ) {
				
				num = snprintf(cadValor, tam, "%d"
					, valor.entero);
				
				if ( num > -1 ) 
					/* glibc 2.1 */
					tam++;
				else
					/* glibc 2.0 */
					tam *= 2;
					
				cadValor = realloc(cadValor
					, tam*sizeof(char));

				if ( cadValor == NULL ) {
					perror("convCadena >> cadValor");
					exit(-1);
					}
				}
			
			#ifdef __DEBUG__
				fprintf(stderr, "Snprintf: %s\n", cadValor);
			#endif
			
			break;

		case REAL:
		
			while ( !(num > -1 && num < tam) ) {
				
				num = snprintf(cadValor, tam, "%f", valor.real);
				
				if ( num > -1 ) 
					/* glibc 2.1 */
					tam++;
				else
					/* glibc 2.0 */
					tam *= 2;
					
				cadValor = realloc(cadValor
					, tam*sizeof(char));

				if ( cadValor == NULL ) {
					perror("convCadena >> cadValor");
					exit(-1);
					}
				}
			
			#ifdef __DEBUG__
				fprintf(stderr, "Snprintf: %s\n", cadValor);
			#endif
			
			break;

		case BOOLEANO:
		
			while ( !(num > -1 && num < tam) ) {
				
				num = snprintf(cadValor, tam, "%d"
					, valor.booleano);
				
				if ( num > -1 ) 
					/* glibc 2.1 */
					tam++;
				else
					/* glibc 2.0 */
					tam *= 2;
					
				if ( (cadValor = realloc(cadValor, tam*sizeof(char))) == NULL ) {
					perror("convCadena >> cadValor");
					exit(-1);
					}
				}
			
			#ifdef __DEBUG__
				fprintf(stderr, "Snprintf: %s\n", cadValor);
			#endif
			
			break;
		
		case CARACTER:
		
			while ( !(num > -1 && num < tam) ) {
				
				/* Necesitamos las comillas simples */
				
				cadValor[0] = '\'';
				num = snprintf(&cadValor[1], tam, "%c", valor.caracter);

				if ( num > -1 && num < tam ) 
					/* glibc 2.1 */
					tam++;
				else if ( num == -1 )
					/* glibc 2.0 */
					tam *= 2;
					
				if ( (cadValor = realloc(cadValor, tam*sizeof(char))) == NULL ) {
					perror("convCadena >> cadValor");
					exit(-1);
					}
				}
			
			cadValor[0] = '\'';
			cadValor[2] = '\'';
			cadValor[3] = '\0';
			
			#ifdef __DEBUG__
				fprintf(stderr, "Snprintf: %s\n", cadValor);
			#endif
			
			break;

		default:
		
			fprintf(stderr, "COMP Tipo %d NO CONV a cadena\n"
				, tipo);
			break;
		}
	
	return cadValor;
	}


/**
 Peticion para generar declaracion de procedimiento/funcion
*/

void pet_GenDecProc(char *nom, tDato tipo) {
	int tam;
	char msj[2];

	// Tipo de mensaje
	msj[TIPO_MSJ] = GENCOD;
	msj[SUBTIPO] = DEC_PROC;
	write(1, msj, 2 * sizeof(char));

	// Tipo de valor devuelto
	// De momento solo PROCS
	write(1, &tipo, sizeof(char));

	tam = strlen(nom);
	write(1, &tam, sizeof(int));
	write(1, nom, tam * sizeof(char));

	// Comprobamos si debemos reiniciar
	check();
	}

/**
 Peticion de generar parametro en declaracion de PROC
*/

void pet_GenParam(tDato tipo, char *nom) {
	int tam;
	char msj[2];


	//Tipo de mensaje
	msj[TIPO_MSJ] = GENCOD;
	msj[SUBTIPO] = DEC_PARAM;
	write(1, msj, 2 * sizeof(char));

	write(1, &tipo, sizeof(char));

	if ( nom != NULL ) {
		tam = strlen(nom);
		write(1, &tam, sizeof(int));
		write(1, nom, tam * sizeof(char));
	} else {
		tam = 0;
		write(1, &tam, sizeof(int));
		}



	// Comprobamos si debemos reiniciar
	check();
	}

/**
 Generar fin Cabecera del PROC => " )"
*/

void pet_GenFinCabecera(void) {
	char msj[2];

	msj[TIPO_MSJ] = GENCOD;
	msj[SUBTIPO] = FIN_PROTO;
	write(1, msj, 2 * sizeof(char));

	// Comprobamos...
	check();
	}

/**
 Fin Procedimiento = Fin Bloque que lo defin
*/

void pet_GenFinDecProc(void) {
	char msj[2];

	msj[TIPO_MSJ] = GENCOD;
	msj[SUBTIPO] = FIN_DEC;
	write(1, msj, 2 * sizeof(char));

	// Comprobamos...
	check();
	}

/**
 Llamada a Procedimiento
*/

void pet_GenLlamada(char *id, char *listaParams) {
	char msj[2];
	int tam;

	msj[TIPO_MSJ] = GENCOD;
	msj[SUBTIPO] = CALL_PROC;
	write(1, msj, 2 * sizeof(char));

	tam = strlen(id);
	write(1, &tam, sizeof(int));
	write(1, id, tam * sizeof(char));

	if ( strcmp(listaParams, "<< SIN_ARGUMENTOS >>") == 0 ) {
		tam = 0;
		write(1, &tam, sizeof(int));
	} else {
		tam = strlen(listaParams);
		write(1, &tam, sizeof(int));
		write(1, listaParams, tam * sizeof(char));
		}

	// Comprobamos...
	check();
	}

