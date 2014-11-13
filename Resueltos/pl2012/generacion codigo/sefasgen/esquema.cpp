/**
 @file
 Funciones para implementar Esquema de Traduccion
*/

#include <stdio.h>
#include <fx.h>
#include "gui.h"
#include "parser.h"
#include "regTrad.h"

Traduccion rgls[MAX_REGLAS];
int nRgls;

/**
 Lectura del esquema de Traduccion de fichero.
 @todo Recordar liberar la memoria al terminar !!!
 @todo Hacer algo con los errores !!!!!!
*/

void guiWindow::leerEsquema(FXString nom) {
	FXint i, j;
	unsigned char tipoCampo;
	FXchar *nombres[5] = { "CAD", "TIPO", "CAD_OPC"
		, "VAR", "STRING" };

	printf("Leyendo esquema: %s\n", nom.text());

	yyin = fopen(nom.text(), "r");

	if ( yyin == NULL ) {
		perror("No se pudo abrir Esquema");
		return;
		}

	nRgls = 0;

	yyparse();

	printf("Total reglas de traduccion: %d\n", nRgls);

	for ( i = 0; i < nRgls; i++ ) {
		printf("\nRegla %d\n", i);
		printf("\tNombre %s\n", rgls[i].nombre);
		// printf("\tCadena Formato %s\n", rgls[i].fmt);
		printf("\tNum campos %d\n", rgls[i].numCampos);

		for ( j = 0; j < rgls[i].numCampos; j++ ) {
			tipoCampo = rgls[i].tipos[j];
			printf("\tTipo del Campo[%d]: %s\n", j
				, nombres[tipoCampo]);
			if ( tipoCampo == ARG_STRING )
				printf("\t\tValor cadena %s\n"
					, rgls[i].args[j]);
			}
		}



	
	return;
	}
