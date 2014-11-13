/******************************************
  Definicion TIPOS de mensajes Padre-Hijo
 ******************************************/

#ifndef __DEF_MSJS_H__
#define __DEF_MSJS_H__

#define TIPO_MSJ 	0
#define SUBTIPO 	1

/***************************
 Estas son los tipos de Mensaje que
 hay que utilizar
************************************/

/** Tipos de mensaje compilador-GUI */

enum tiposMsj {
	INS = 0,
	SACAR,
	BSIM,
	BPROC,
	BPARAM,
	DEL,
	VERIF,
	TEMP,
	CADFMT,
	ETIQ,
	BUSQ_ETIQ,
	DEL_CTRL,
	GENCOD
	};

/** Sub-tipos msj para Generacion de codigo */

enum msjGenCod {
	INI_PROG = 0,
	INI_BLQ = 1,
	DVAR = 2,
	FIN_BLOQUE = 3,
	ASIGNACION = 4,
	SALIDA = 5,
	ENTRADA = 6,
	JINCOND = 7,
	JCOND = 8,
	ESC_ETQ = 9,
	DEC_PROC = 10,
	DEC_PARAM = 11,
	FIN_PROTO = 12,
	FIN_DEC = 13,
	CALL_PROC = 14,
	};


#endif
