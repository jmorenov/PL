/********************
 Funcion main
**********************/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <signal.h>
#include "gui.h"
#include "tabsim.h"
#include "opTS.h"
#include "iconos.h"
#include "prefs.h"
#include "fuentes.h"
#include "reglas.h"
#include "dlgIncludes.h"
#include "def_msjs.h"
#include "regTrad.h"
#include "sefasgen.h"

////////////////////////////////////////
//
// 	Inicio de la aplicacion
//
////////////////////////////////////////

/** 
 @name Variables globales
 @todo Ver si se pueden eliminar...
*/
//@{
extern int pipePH[2];
extern int pipeHP[2];
extern int pipeERR[2];
extern pid_t pid;
extern FILE *strERR;
//@}

/**
 Funcion de espera para el proceso compilador.
 El proceso hijo espera que se le envie el nombre
 del ejecutable del compilador y el del codigo fuente
*/

void espera(void) {
	int nbytes, tam;
	char msj[4];
	FXchar *rutaComp, *fComp, *fCod;

	// Debemos recibir del padre ...
	// tam y rutaCompilador
	nbytes = read(0, &tam, sizeof(int));
	rutaComp = (FXchar *) malloc((tam+1) * sizeof(FXchar));
	if ( rutaComp == NULL ) {
		perror("rutaCompilador");
		exit(1);
		}

	nbytes = read(0, rutaComp, tam * sizeof(FXchar));
	rutaComp[tam] = '\0';

	// tam y fCompilador
	nbytes = read(0, &tam, sizeof(int));
	fComp = (FXchar *) malloc((tam+1) * sizeof(FXchar));
	if ( fComp == NULL ) {
		perror("fComp");
		exit(1);
		}

	nbytes = read(0, fComp, tam * sizeof(FXchar));
	fComp[tam] = '\0';

	// tam y fCodigo
	nbytes = read(0, &tam, sizeof(int));
	fCod = (FXchar *) malloc((tam+1) * sizeof(FXchar));
	if ( fCod == NULL ) {
		perror("COMP fCod");
		exit(1);
		}

	nbytes = read(0, fCod, tam * sizeof(FXchar));
	fCod[tam] = '\0';

	fprintf(stderr, "COMPILADOR: %s\n", rutaComp);

	// Ya podemos arrancar el compilador...
	execl(rutaComp, fComp, fCod, NULL);

	// TODO: No debemos llegar aqui !!!
	// TODO: y si lo hacemos el padre deberia SABERLO
	perror("Ejecucion compilador");

	exit(1);
	}
	

int main(int argc, char *argv[]) {

	guiWindow *wdwPpal = NULL;

	/****************************************************** 
	  Creacion del proceso hijo, encargado del compilador
	  y los pipes de comunicacion con el 
	 ******************************************************/

	pipe(pipePH);
	pipe(pipeHP);
	pipe(pipeERR);

	if ( (pid=fork()) == -1 ) {
		perror("FORK");
		exit(-1);
		}

	if ( pid == 0 ) {
		// Hijo

		close(pipeHP[0]);
		dup2(pipeHP[1], 1);
		close(pipePH[1]);
		dup2(pipePH[0],0);
		close(pipeERR[0]);
		dup2(pipeERR[1], 2);

		// Espera hasta que el usuario haya cargado en el entorno
		// los ficheros del compilador y codigo fuente

		espera();
	
	} else {
		// Padre
		close(pipeHP[1]);
		close(pipePH[0]);
		close(pipeERR[1]);

		strERR = fdopen(pipeERR[0], "r");
		}


	// Construir aplicacion
	// FXApp *application = new FXApp("SEFASGEN","Infinity Inc.");
	Sefasgen application("SEFASGEN", "SFGSoft");	

	// Arrancar
	application.init(argc, argv);

	application.create();

	// guiWindow
	wdwPpal = new guiWindow(&application);
	wdwPpal->create();

	return application.run();
	}

