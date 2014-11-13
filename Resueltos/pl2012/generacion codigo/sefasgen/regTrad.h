/**
 @file
 Definicion estructura para regla de Traduccion
*/

#ifndef __REG_TRAD_H__
#define __REG_TRAD_H__

#define MAX_REGLAS 50
#define MAX_CAMPOS 10

enum {
	ARG_CAD,
	ARG_TIPO,
	ARG_CAD_OPC,
	ARG_VAR,
	ARG_STRING
	};



struct reglaTrad {
	char *nombre;
	int numCampos;
	unsigned char tipos[MAX_CAMPOS];
	char *args[MAX_CAMPOS];
	};

typedef struct reglaTrad Traduccion;



#endif
