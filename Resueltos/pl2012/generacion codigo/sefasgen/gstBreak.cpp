/**
 @file
 Gestion de puntos de ruptura.
 @todo Ejecucion hasta BREAK desde el principio ( sin Pulsar INICIAR )
 @todo Eliminar break alcanzado de la lista de breakpoints...
 @test Comprobar si se pierden mensajes de STDERR del HIJO !!!
 */

#include <stdio.h>
#include <unistd.h>
#include "gui.h"
#include "def_msjs.h"

// DIFF
#include "tabsim.h"

extern int pipePH[2], pipeHP[2], pipeERR[2];


/**
 Establecer nuevo breakpoint
*/

long guiWindow::onCmdSetBreak(FXObject *sender, FXSelector sel, void *) {
	FXchar *brk = "[B]";
	FXint i;

	// printf("DEBUG onCmdSetBreak Añadiendo Break\n");

	if ( nuevoBreak(txtCod->getCursorPos()) ) {
		// Añadimos un marcador
		txtCod->insertStyledText(txtCod->getCursorPos(), brk, 3, 1);
		}

	return 1;
	}

/**
 Actualizar estado boton "SetBreakpoint".
 Si estamos en modo AUTO se deshabilita el boton
*/

long guiWindow::onUpdSetBreak(FXObject *sender, FXSelector sel, void *) {
	if ( flagAuto || status == COMPILADOR_OK || status == PENDIENTE )
		sender->handle(this, FXSEL(SEL_COMMAND, ID_DISABLE), NULL);
	else
		sender->handle(this, FXSEL(SEL_COMMAND, ID_ENABLE), NULL);
	return 1;
	}


FXbool guiWindow::nuevoBreak(FXint pos) {
	FXint i;

	// Si queda sitio...
	if ( numBreaks < 10 ) {
		breaks[numBreaks] = pos;
		numBreaks++;

		printf("NUEVO breaks[%d]: %d\n", numBreaks-1, pos);
		printf("Total breaks: %d\n", numBreaks);
		return true;
		}

	return false;
	}


/**
 Actualizacion estado boton "Sig breakpoint"
*/

long guiWindow::onUpdNxtBreak(FXObject *sender, FXSelector, void *) {
	if ( numBreaks > 0 
		&& (status == LISTO_INICIAR || status == LISTO_PASO) )
		sender->handle(this,FXSEL(SEL_COMMAND,ID_ENABLE),NULL);
	else
		sender->handle(this,FXSEL(SEL_COMMAND,ID_DISABLE),NULL);

	return 1;
	}




/**
 Envio del nombre del compilador y codigo fuente
 al proceso compilador.
 @todo Usar esta funcion tambien para onCmdIniciar
*/

void guiWindow::iniciar(void) {
	char msjIni[6] = "START";
	int nbytes, tam;
	
	/********************
	 La clase FXTabSim se ocupa de si misma
	tope = -1;
	bloque = -1;
	blqAnt = -1;
	********************************************/
		
	// Limpiamos el Codigo Generado si hace falta

	if ( flagGen )
		txtGen->removeText(0, txtGen->getLength());

	// Establecemos gestor de Entrada para pipe
	/** @todo El gestor de entrada para pipeHP[0]
	 debe establecerlo la funcion llamadora.
	 Si estamos en AUTO NO se activa.

	(this->getApp())->addInput(pipeHP[0], INPUT_READ, this, ID_PIPE);
	********************************************************************/

	// Gestor de Datos pendientes en STDERR del hijo
	// Esta parte SI es comun
	getApp()->addInput(pipeERR[0], INPUT_READ, this, ID_ERR);

	// Mandamos nombre ficheros al Hijo

	// tam y rutaCompilador
	tam = strlen(rutaCompilador);
	nbytes = write(pipePH[1], &tam, sizeof(int));
	nbytes = write(pipePH[1], rutaCompilador, tam * sizeof(FXchar));

	// tam y fCompilador
	tam = strlen(fCompilador);
	nbytes = write(pipePH[1], &tam, sizeof(int));
	nbytes = write(pipePH[1], fCompilador, tam * sizeof(FXchar));

	// tam y fCodigo
	tam = strlen(fCodigo);
	nbytes = write(pipePH[1], &tam, sizeof(int));
	nbytes = write(pipePH[1], fCodigo, tam * sizeof(FXchar));


	// Mensaje de inicio al hijo para SINCRONIZAR
	nbytes = write(pipePH[1], msjIni, 6 * sizeof(char));
		
	// Deshabilitamos boton Inicio
	/** @todo 
	 Habilitar el boton "Paso" depende de la funcion llamadora
	 Si estamos en AUTO no se deberia habilitar para evitar
	 problemas con el usuario
	*********************************************/

	// status = LISTO_PASO;
	codOp = OP_ESPERA;

	return;
	}

/**
 Comprueba si hemos llegado al pto de ruptura.
*/

long guiWindow::chkBreak(FXObject *sender, FXSelector sel, void *) {
	char msj[4];
	FXint i,acum;


	/** @todo Comprobar PORQUE se va de loooooco al terminar la compilacion */

	if ( iniSelCod < breaks[sigBreak] && codOp != FIN_COMPILACION ) {

		if ( codOp == OP_POST ) {
			// Indicamos al hijo que continue
			// fprintf(stderr, "DEBUG chkBreak: Continuar al COMPILADOR\n");
			strcpy(msj, "ACK");
			write(pipePH[1], msj, 4 * sizeof(char));
			codOp = OP_ESPERA;
			this->handle(this, FXSEL(SEL_COMMAND, ID_FIN_AUTOPASO), NULL);
		} else if ( codOp == OP_ESPERA ) {
			// Lectura nueva peticion del compilador
			read(pipeHP[0], msj, sizeof(char));
			/****
			fprintf(stderr, "DEBUG chkBreak: Leida nueva peticion %d\n"
				, msj[0]);
			****/
			// fprintf(stderr, "DEBUG AUTO Nueva peticion: %c\n", msj[0]);
			this->handle(this, FXSEL(SEL_COMMAND, ID_EXEC_PRE), &msj[0]);
		} else {
			// Ejecutar post-OP
			// fprintf(stderr, "DEBUG AUTO Hay que ejecutar POST\n");
			// fprintf(stderr, "DEBUG chkBreak: Ejecutar POST\n");
			this->handle(this, FXSEL(SEL_COMMAND, ID_EXEC_POST), NULL);
			}

	} else if ( codOp == FIN_COMPILACION ) {

		// Hemos terminado
		fprintf(stderr, "DEBUG AUTO Fin COMPILACION\n");

		// Eliminamos las marcas en el Codigo Fuente
		acum = 0;
		for ( i = sigBreak; i < numBreaks; i++ ) {
			txtCod->removeText(breaks[i]-acum, 3);
			breaks[i] = 0;
			acum += 3;
			}

		numBreaks = 0;
		sigBreak = 0;

		dtsGUI.iniSel = 0;
		dtsGUI.tamSel = 1;
		// dtsGUI.status = 0;

		flagAuto = false;
		status = LISTO_INICIAR;

	} else if ( iniSelCod >= breaks[sigBreak] ) {

		fprintf(stderr, "DEBUG AUTO Se alcanzo pto de ruptura %d\n", sigBreak);
		fprintf(stderr, "DEBUG dtsGUI.iniSel: %d Break: %d\n"
			, dtsGUI.iniSel, breaks[sigBreak] );

		// Actualizamos posicion en codigo fuente
		txtCod->setCenterLine(dtsGUI.iniSel);

		// Hemos alcanzado pto de Ruptura
		txtCod->removeText(breaks[sigBreak], 3);
		breaks[sigBreak] = 0;
		sigBreak++;

		if ( sigBreak > numBreaks-1 ) {
			// Ya no quedan breakpoints...
			// Deshabilitamos el boton
			numBreaks = 0;
			sigBreak = 0;
		} else {
			// Actualizamos posiciones...
			/*****************
			for ( i = sigBreak; i < numBreaks; i++ )
				breaks[i] -= 3;
			 ***************************/

			breaks[sigBreak] -= 3 * sigBreak;
			}

		/** @todo Activar boton Paso y dejar todo limpio */
		status = LISTO_PASO;
		flagAuto = false;
		}

	return 1;
	}


/**
 Ejecucion pre-OPERACION.
 @param ptr Puntero a caracter que selecciona la operacion
 @todo Se podria utilizar el ID del mensaje para ejecutar PRE o POST
*/

long guiWindow::ejecutarPRE(FXObject *sender, FXSelector sel, void *ptr) {
	FXchar *ptrOp;
	char msj[4];
	int nbytes, tam;

	ptrOp = (FXchar *)ptr;

	switch ( *ptrOp ) {
		case 'L':
			calcPosGram();
			break;
		case 'F':
			// Fin Compilacion
			// Actualizacion de GUI
			dtsGUI.txtOP = "<FIN_COMPILACION>";
			dtsGUI.cptDato = "";
			dtsGUI.txtDato = "";
			dtsGUI.txtRes = "OK";

			dtsGUI.iniSel = 0;
			dtsGUI.tamSel = 1;

			// Informamos al usuario
			FXMessageBox::information(this, MBOX_OK, "Fin"
				, "Termino la compilacion");

			miTabla->reiniciar();
			strcpy(msj, "REI");
			nbytes = write(pipePH[1], msj, 4 * sizeof(char));

			// Desactivar la recepcion del pipe
			/********
			(this->getApp())->removeInput(pipeHP[0], INPUT_READ);
			***************/
			// Desactivamos el boton de paso
			codOp = FIN_COMPILACION;
			status = LISTO_INICIAR;

			break;
		default:
			/*********
			fprintf(stderr, "DEBUG gstActual->pre()codOp: %d %c\n"
				, *ptrOp, *ptrOp);
			**************/

			gstActual = gestores[*ptrOp];
			dtsGUI = gstActual->pre();

			if ( dtsGUI.status != 2 ) {
				iniSelCod = dtsGUI.iniSel;
				tamSelCod = dtsGUI.tamSel;

				// Actualizamos posicion en codigo fuente
				if ( !flagAuto )
					txtCod->setCenterLine(dtsGUI.iniSel);
				}

			codOp = OP_PRUEBAS;

			// Desactivar gestor PIPE
			getApp()->removeInput(pipeHP[0], INPUT_READ);
			break;
		}

	if ( flagAuto )
		this->handle(this
			, FXSEL(SEL_COMMAND, ID_FIN_AUTOPASO)
			, NULL);



	return 1;
	}

/**
 Ejecucion post-OPERACION.
*/

long guiWindow::ejecutarPOST(FXObject *sender, FXSelector, void *ptr) {

	if ( codOp == OP_PRUEBAS ) {
		dtsGUI = gstActual->post();
		codOp = OP_POST;

		// Marcamos que se ha generado codigo
		if ( gstActual == gestores[GENCOD] )
			flagGen = 1;

		if ( flagAuto )
			this->handle(this
				, FXSEL(SEL_COMMAND, ID_FIN_AUTOPASO)
				, NULL);

		if ( dtsGUI.status != 2 && !flagAuto ) {
			// Actualizamos posicion en codigo fuente
			txtCod->setCenterLine(dtsGUI.iniSel);
			}

		return 1;
	} else {
		fprintf(stderr, "\nDEBUG ejecutarPOST codOp ERRONEO!!!\n");
		}


	return 1;
	}

		
	
/**
 Gestion de 1 paso durante compilacion hasta pto de ruptura.
*/

long guiWindow::onCmdNxtBreak(FXObject *sender, FXSelector sel, void *) {
	int i, nbytes;
	char msj[4];

	fprintf(stderr, "\nPulsaste NxtBREAK\n");

	// Deshabilitamos el boton "SetBreak"
	flagAuto = true;

	// Comprobamos el estado
	// Si estamos en LISTO_INICIAR tendriamos que
	// mandar los nombres de los archivos

	if ( status == LISTO_INICIAR ) {
		iniciar();
		dtsGUI.iniSel = 0;
		dtsGUI.tamSel = 1;
		}

	// Hay que ejecutar pre/post operacion
	this->handle(this, FXSEL(SEL_COMMAND, ID_FIN_AUTOPASO), NULL);

	return 1;
	}

