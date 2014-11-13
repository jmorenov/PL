/**
 @file
 Implementacion de la GUI.
 Interfaz grafico y gestion de la comunicacion
 GUI-Compilador
 */

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

/** @name Variables globales */
//@{

// Pipes de comunicacion con proceso COMPILADOR
int pipePH[2], pipeHP[2], pipeERR[2];
FILE *strERR;
pid_t pid;

//@}

extern Traduccion rgls[MAX_REGLAS];
extern int nRgls;

// @todo Leer el compilador y codigo de linea de comando / GUI

FXDEFMAP(guiWindow) guiWindowMap[] = {

// ________Tipo Mensaje________________ID______Manejador Mensaje
FXMAPFUNC(SEL_COMMAND, guiWindow::ID_INICIAR, guiWindow::onCmdIniciar),
FXMAPFUNC(SEL_UPDATE, guiWindow::ID_INICIAR, guiWindow::onUpdIniciar),
FXMAPFUNC(SEL_COMMAND, guiWindow::ID_PASO,guiWindow::onCmdPaso),
FXMAPFUNC(SEL_UPDATE, guiWindow::ID_PASO,guiWindow::onUpdPaso),
FXMAPFUNC(SEL_IO_READ, guiWindow::ID_PIPE, guiWindow::onRcvPipe),
FXMAPFUNC(SEL_COMMAND, guiWindow::ID_ABRIR_COMP
	, guiWindow::onCmdAbrirCompilador),
FXMAPFUNC(SEL_COMMAND, guiWindow::ID_ABRIR_COD
	, guiWindow::onCmdAbrirCodigo),
FXMAPFUNC(SEL_COMMAND, guiWindow::ID_ABRIR_GRAM
	, guiWindow::onCmdAbrirGramatica),
FXMAPFUNC(SEL_UPDATE, guiWindow::ID_OPERACION, guiWindow::onUpdOperacion),
FXMAPFUNC(SEL_UPDATE, guiWindow::ID_LEXEMA, guiWindow::onUpdLexema),
FXMAPFUNC(SEL_UPDATE, guiWindow::ID_RESULTADO, guiWindow::onUpdResultado),

FXMAPFUNC(SEL_UPDATE, guiWindow::ID_TXTCOD, guiWindow::onUpdCodigo),

FXMAPFUNC(SEL_COMMAND, guiWindow::ID_REINICIAR, guiWindow::onCmdReiniciar),
FXMAPFUNC(SEL_COMMAND, guiWindow::ID_TERMINAR, guiWindow::onCmdTerminar),

FXMAPFUNC(SEL_UPDATE, guiWindow::ID_TXTGRAM, guiWindow::onUpdGramatica),

FXMAPFUNC(SEL_UPDATE, guiWindow::ID_CAPLEX, guiWindow::onUpdCaption),
FXMAPFUNC(SEL_COMMAND, guiWindow::ID_GUARDAR_GEN, guiWindow::onCmdGuardar),
FXMAPFUNC(SEL_UPDATE, guiWindow::ID_GUARDAR_GEN, guiWindow::onCmdGuardar),
FXMAPFUNC(SEL_IO_READ, guiWindow::ID_ERR, guiWindow::onRcvErr),

FXMAPFUNC(SEL_COMMAND, guiWindow::ID_SET_BREAK, guiWindow::onCmdSetBreak),
FXMAPFUNC(SEL_UPDATE, guiWindow::ID_SET_BREAK, guiWindow::onUpdSetBreak),

FXMAPFUNC(SEL_UPDATE, guiWindow::ID_NXT_BREAK, guiWindow::onUpdNxtBreak),
FXMAPFUNC(SEL_COMMAND, guiWindow::ID_NXT_BREAK, guiWindow::onCmdNxtBreak),

FXMAPFUNC(SEL_COMMAND, guiWindow::ID_FIN_AUTOPASO, guiWindow::chkBreak),
FXMAPFUNC(SEL_COMMAND, guiWindow::ID_EXEC_PRE, guiWindow::ejecutarPRE),
FXMAPFUNC(SEL_COMMAND, guiWindow::ID_EXEC_POST, guiWindow::ejecutarPOST),

FXMAPFUNC(SEL_COMMAND, guiWindow::ID_PREFS, guiWindow::onCmdPrefs),
FXMAPFUNC(SEL_COMMAND, guiWindow::ID_GUARDAR_PREFS, guiWindow::onCmdGuardarPrefs),

FXMAPFUNC(SEL_COMMAND, guiWindow::ID_TAB_FG, guiWindow::onCmdColorTab),
FXMAPFUNC(SEL_CHANGED, guiWindow::ID_TAB_FG, guiWindow::onCmdColorTab),
FXMAPFUNC(SEL_UPDATE, guiWindow::ID_TAB_FG, guiWindow::onUpdColorTab),
FXMAPFUNC(SEL_COMMAND, guiWindow::ID_TAB_BG, guiWindow::onCmdColorTab),
FXMAPFUNC(SEL_CHANGED, guiWindow::ID_TAB_BG, guiWindow::onCmdColorTab),
FXMAPFUNC(SEL_UPDATE, guiWindow::ID_TAB_BG, guiWindow::onUpdColorTab),
FXMAPFUNC(SEL_COMMAND, guiWindow::ID_TAB_NEW_FG, guiWindow::onCmdColorTab),
FXMAPFUNC(SEL_CHANGED, guiWindow::ID_TAB_NEW_FG, guiWindow::onCmdColorTab),
FXMAPFUNC(SEL_UPDATE, guiWindow::ID_TAB_NEW_FG, guiWindow::onUpdColorTab),
FXMAPFUNC(SEL_COMMAND, guiWindow::ID_TAB_NEW_BG, guiWindow::onCmdColorTab),
FXMAPFUNC(SEL_CHANGED, guiWindow::ID_TAB_NEW_BG, guiWindow::onCmdColorTab),
FXMAPFUNC(SEL_UPDATE, guiWindow::ID_TAB_NEW_BG, guiWindow::onUpdColorTab),
FXMAPFUNC(SEL_COMMAND, guiWindow::ID_TAB_SIM_FG, guiWindow::onCmdColorTab),
FXMAPFUNC(SEL_CHANGED, guiWindow::ID_TAB_SIM_FG, guiWindow::onCmdColorTab),
FXMAPFUNC(SEL_UPDATE, guiWindow::ID_TAB_SIM_FG, guiWindow::onUpdColorTab),
FXMAPFUNC(SEL_COMMAND, guiWindow::ID_TAB_SIM_BG, guiWindow::onCmdColorTab),
FXMAPFUNC(SEL_CHANGED, guiWindow::ID_TAB_SIM_BG, guiWindow::onCmdColorTab),
FXMAPFUNC(SEL_UPDATE, guiWindow::ID_TAB_SIM_BG, guiWindow::onUpdColorTab),
FXMAPFUNC(SEL_COMMAND, guiWindow::ID_TAB_DUP_FG, guiWindow::onCmdColorTab),
FXMAPFUNC(SEL_CHANGED, guiWindow::ID_TAB_DUP_FG, guiWindow::onCmdColorTab),
FXMAPFUNC(SEL_UPDATE, guiWindow::ID_TAB_DUP_FG, guiWindow::onUpdColorTab),
FXMAPFUNC(SEL_COMMAND, guiWindow::ID_TAB_DUP_BG, guiWindow::onCmdColorTab),
FXMAPFUNC(SEL_CHANGED, guiWindow::ID_TAB_DUP_BG, guiWindow::onCmdColorTab),
FXMAPFUNC(SEL_UPDATE, guiWindow::ID_TAB_DUP_BG, guiWindow::onUpdColorTab),
FXMAPFUNC(SEL_COMMAND, guiWindow::ID_TAB_DEL_FG, guiWindow::onCmdColorTab),
FXMAPFUNC(SEL_CHANGED, guiWindow::ID_TAB_DEL_FG, guiWindow::onCmdColorTab),
FXMAPFUNC(SEL_UPDATE, guiWindow::ID_TAB_DEL_FG, guiWindow::onUpdColorTab),
FXMAPFUNC(SEL_COMMAND, guiWindow::ID_TAB_DEL_BG, guiWindow::onCmdColorTab),
FXMAPFUNC(SEL_CHANGED, guiWindow::ID_TAB_DEL_BG, guiWindow::onCmdColorTab),
FXMAPFUNC(SEL_UPDATE, guiWindow::ID_TAB_DEL_BG, guiWindow::onUpdColorTab),
FXMAPFUNC(SEL_COMMAND, guiWindow::ID_TAB_PROC_FG, guiWindow::onCmdColorTab),
FXMAPFUNC(SEL_CHANGED, guiWindow::ID_TAB_PROC_FG, guiWindow::onCmdColorTab),
FXMAPFUNC(SEL_UPDATE, guiWindow::ID_TAB_PROC_FG, guiWindow::onUpdColorTab),
FXMAPFUNC(SEL_COMMAND, guiWindow::ID_TAB_PROC_BG, guiWindow::onCmdColorTab),
FXMAPFUNC(SEL_CHANGED, guiWindow::ID_TAB_PROC_BG, guiWindow::onCmdColorTab),
FXMAPFUNC(SEL_UPDATE, guiWindow::ID_TAB_PROC_BG, guiWindow::onUpdColorTab),
FXMAPFUNC(SEL_COMMAND, guiWindow::ID_TAB_PARAM_FG, guiWindow::onCmdColorTab),
FXMAPFUNC(SEL_CHANGED, guiWindow::ID_TAB_PARAM_FG, guiWindow::onCmdColorTab),
FXMAPFUNC(SEL_UPDATE, guiWindow::ID_TAB_PARAM_FG, guiWindow::onUpdColorTab),
FXMAPFUNC(SEL_COMMAND, guiWindow::ID_TAB_PARAM_BG, guiWindow::onCmdColorTab),
FXMAPFUNC(SEL_CHANGED, guiWindow::ID_TAB_PARAM_BG, guiWindow::onCmdColorTab),
FXMAPFUNC(SEL_UPDATE, guiWindow::ID_TAB_PARAM_BG, guiWindow::onUpdColorTab),

FXMAPFUNC(SEL_COMMAND, guiWindow::ID_COD_FG, guiWindow::onCmdCodFG),
FXMAPFUNC(SEL_CHANGED, guiWindow::ID_COD_FG, guiWindow::onCmdCodFG),
FXMAPFUNC(SEL_UPDATE, guiWindow::ID_COD_FG, guiWindow::onUpdCodFG),
FXMAPFUNC(SEL_COMMAND, guiWindow::ID_COD_BG, guiWindow::onCmdCodBG),
FXMAPFUNC(SEL_CHANGED, guiWindow::ID_COD_BG, guiWindow::onCmdCodBG),
FXMAPFUNC(SEL_UPDATE, guiWindow::ID_COD_BG, guiWindow::onUpdCodBG),
FXMAPFUNC(SEL_COMMAND, guiWindow::ID_COD_SEL_FG, guiWindow::onCmdCodSelFG),
FXMAPFUNC(SEL_CHANGED, guiWindow::ID_COD_SEL_FG, guiWindow::onCmdCodSelFG),
FXMAPFUNC(SEL_UPDATE, guiWindow::ID_COD_SEL_FG, guiWindow::onUpdCodSelFG),
FXMAPFUNC(SEL_COMMAND, guiWindow::ID_COD_SEL_BG, guiWindow::onCmdCodSelBG),
FXMAPFUNC(SEL_CHANGED, guiWindow::ID_COD_SEL_BG, guiWindow::onCmdCodSelBG),
FXMAPFUNC(SEL_UPDATE, guiWindow::ID_COD_SEL_BG, guiWindow::onUpdCodSelBG),

FXMAPFUNC(SEL_COMMAND, guiWindow::ID_COD_ERR_FG, guiWindow::onCmdCodErrFG),
FXMAPFUNC(SEL_CHANGED, guiWindow::ID_COD_ERR_FG, guiWindow::onCmdCodErrFG),
FXMAPFUNC(SEL_UPDATE, guiWindow::ID_COD_ERR_FG, guiWindow::onUpdCodErrFG),
FXMAPFUNC(SEL_COMMAND, guiWindow::ID_COD_ERR_BG, guiWindow::onCmdCodErrBG),
FXMAPFUNC(SEL_CHANGED, guiWindow::ID_COD_ERR_BG, guiWindow::onCmdCodErrBG),
FXMAPFUNC(SEL_UPDATE, guiWindow::ID_COD_ERR_BG, guiWindow::onUpdCodErrBG),

FXMAPFUNC(SEL_COMMAND, guiWindow::ID_COD_NLIN_FG, guiWindow::onCmdCodNLinFG),
FXMAPFUNC(SEL_CHANGED, guiWindow::ID_COD_NLIN_FG, guiWindow::onCmdCodNLinFG),
FXMAPFUNC(SEL_UPDATE, guiWindow::ID_COD_NLIN_FG, guiWindow::onUpdCodNLinFG),
FXMAPFUNC(SEL_COMMAND, guiWindow::ID_COD_NLIN_BG, guiWindow::onCmdCodNLinBG),
FXMAPFUNC(SEL_CHANGED, guiWindow::ID_COD_NLIN_BG, guiWindow::onCmdCodNLinBG),
FXMAPFUNC(SEL_UPDATE, guiWindow::ID_COD_NLIN_BG, guiWindow::onUpdCodNLinBG),


FXMAPFUNC(SEL_COMMAND, guiWindow::ID_GRAM_FG, guiWindow::onCmdColorGram),
FXMAPFUNC(SEL_CHANGED, guiWindow::ID_GRAM_FG, guiWindow::onCmdColorGram),
FXMAPFUNC(SEL_UPDATE, guiWindow::ID_GRAM_FG, guiWindow::onUpdColorGram),

FXMAPFUNC(SEL_COMMAND, guiWindow::ID_GRAM_BG, guiWindow::onCmdColorGram),
FXMAPFUNC(SEL_CHANGED, guiWindow::ID_GRAM_BG, guiWindow::onCmdColorGram),
FXMAPFUNC(SEL_UPDATE, guiWindow::ID_GRAM_BG, guiWindow::onUpdColorGram),

FXMAPFUNC(SEL_COMMAND, guiWindow::ID_GRAM_ACT_FG, guiWindow::onCmdColorGram),
FXMAPFUNC(SEL_CHANGED, guiWindow::ID_GRAM_ACT_FG, guiWindow::onCmdColorGram),
FXMAPFUNC(SEL_UPDATE, guiWindow::ID_GRAM_ACT_FG, guiWindow::onUpdColorGram),

FXMAPFUNC(SEL_COMMAND, guiWindow::ID_GRAM_ACT_BG, guiWindow::onCmdColorGram),
FXMAPFUNC(SEL_CHANGED, guiWindow::ID_GRAM_ACT_BG, guiWindow::onCmdColorGram),
FXMAPFUNC(SEL_UPDATE, guiWindow::ID_GRAM_ACT_BG, guiWindow::onUpdColorGram),

FXMAPFUNC(SEL_COMMAND, guiWindow::ID_GEN_FG, guiWindow::onCmdColorGen),
FXMAPFUNC(SEL_CHANGED, guiWindow::ID_GEN_FG, guiWindow::onCmdColorGen),
FXMAPFUNC(SEL_UPDATE, guiWindow::ID_GEN_FG, guiWindow::onUpdColorGen),
FXMAPFUNC(SEL_COMMAND, guiWindow::ID_GEN_BG, guiWindow::onCmdColorGen),
FXMAPFUNC(SEL_CHANGED, guiWindow::ID_GEN_BG, guiWindow::onCmdColorGen),
FXMAPFUNC(SEL_UPDATE, guiWindow::ID_GEN_BG, guiWindow::onUpdColorGen),

FXMAPFUNC(SEL_COMMAND, guiWindow::ID_FUENTES, guiWindow::onCmdFuentes),

FXMAPFUNC(SEL_COMMAND, guiWindow::ID_NEW_FNT_TAB, guiWindow::onCmdCambiarFnt),
FXMAPFUNC(SEL_UPDATE, guiWindow::ID_FNT_TAB, guiWindow::onUpdLeerFuentes),
FXMAPFUNC(SEL_COMMAND, guiWindow::ID_NEW_FNT_COD, guiWindow::onCmdCambiarFnt),
FXMAPFUNC(SEL_UPDATE, guiWindow::ID_FNT_COD, guiWindow::onUpdLeerFuentes),
FXMAPFUNC(SEL_COMMAND, guiWindow::ID_NEW_FNT_GRAM, guiWindow::onCmdCambiarFnt),
FXMAPFUNC(SEL_UPDATE, guiWindow::ID_FNT_GRAM, guiWindow::onUpdLeerFuentes),
FXMAPFUNC(SEL_COMMAND, guiWindow::ID_NEW_FNT_GEN, guiWindow::onCmdCambiarFnt),
FXMAPFUNC(SEL_UPDATE, guiWindow::ID_FNT_GEN, guiWindow::onUpdLeerFuentes),
FXMAPFUNC(SEL_COMMAND, guiWindow::ID_NEW_FNT_LOG, guiWindow::onCmdCambiarFnt),
FXMAPFUNC(SEL_UPDATE, guiWindow::ID_FNT_LOG, guiWindow::onUpdLeerFuentes),

FXMAPFUNC(SEL_COMMAND, guiWindow::ID_REGLAS, guiWindow::onCmdReglas),

FXMAPFUNC(SEL_COMMAND, guiWindow::ID_INC_NUM, guiWindow::onCmdNLinea),
FXMAPFUNC(SEL_COMMAND, guiWindow::ID_DEC_NUM, guiWindow::onCmdNLinea),

FXMAPFUNC(SEL_COMMAND, guiWindow::ID_INCLUDES, guiWindow::onCmdIncludes),
};

// Implementacion

FXIMPLEMENT(guiWindow, FXMainWindow, guiWindowMap, ARRAYNUMBER(guiWindowMap))

/** 
 Constructor.
*/

guiWindow::guiWindow(FXApp *a):FXMainWindow(a, "SEFASGEN", NULL,NULL
	, DECOR_ALL, 0, 0, 800, 600) {

	FXint f, c, i;

	// Menu

	menubar = new FXMenuBar(this,LAYOUT_SIDE_TOP|LAYOUT_FILL_X|FRAME_RAISED);

	// File Menu
	filemenu=new FXMenuPane(this);

	new FXMenuCommand(filemenu, "Cargar &compilador", NULL
		, this, ID_ABRIR_COMP);
	new FXMenuCommand(filemenu, "Cargar codigo &fuente", NULL
		, this, ID_ABRIR_COD);
	new FXMenuCommand(filemenu, "Cargar &gramatica", NULL
		, this, ID_ABRIR_GRAM);
	new FXMenuCommand(filemenu, "&Guardar Cod generado", NULL
		, this, ID_GUARDAR_GEN);
	new FXMenuCommand(filemenu,"&Quit\tCtl-Q", NULL, this, ID_TERMINAR);

	new FXMenuTitle(menubar,"&Archivo",NULL,filemenu);

	// Menu de preferencias

	prefsmenu = new FXMenuPane(this);
	new FXMenuCommand(prefsmenu, "Colores", NULL, this, ID_PREFS);
	new FXMenuCommand(prefsmenu, "Fuentes", NULL, this, ID_FUENTES);
	new FXMenuCommand(prefsmenu, "Reglas coloreado LOG", NULL, this, ID_REGLAS);
	new FXMenuCommand(prefsmenu, "Guardar Preferencias", NULL, this, ID_GUARDAR_PREFS);

	new FXMenuTitle(menubar, "&Preferencias", NULL, prefsmenu);

	// Menu para codigo generado
	genmenu = new FXMenuPane(this);
	new FXMenuCommand(genmenu, "Archivos...",  NULL, this, ID_INCLUDES);

	new FXMenuTitle(menubar, "Generacion de codigo", NULL, genmenu);

	////////////////////////////
	// Barra de herramientas
	////////////////////////////

	barraOp = new FXToolBar(this,LAYOUT_SIDE_TOP|LAYOUT_FILL_X
		|FRAME_RAISED);

	// Creacion de los iconos y botones

	icoIni = new FXGIFIcon(getApp(), iniciar_gif);

	new FXButton(barraOp,"\tIniciar\tIniciar Paso a paso.",icoIni,this
		,ID_INICIAR
		,BUTTON_TOOLBAR|FRAME_RAISED|LAYOUT_TOP|LAYOUT_LEFT);

	// icoPaso = new FXGIFIcon(getApp(), paso_gif);
	icoPaso = new FXPNGIcon(getApp(), pies_png);

	new FXButton(barraOp,"\tPaso\tEjecutar paso de compilacion."
		,icoPaso,this,ID_PASO
		,BUTTON_TOOLBAR|FRAME_RAISED|LAYOUT_TOP|LAYOUT_LEFT);

	icoFin = new FXGIFIcon(getApp(), fin_gif);

	new FXButton(barraOp, "\tTerminar\tTerminar el programa."
		, icoFin, this, ID_TERMINAR
		, BUTTON_TOOLBAR|FRAME_RAISED|LAYOUT_TOP|LAYOUT_RIGHT);

	icoNxtBreak = new FXGIFIcon(getApp(), nxtBreak_gif);

	new FXButton(barraOp, "\tHasta sig break\tCompilar hasta siguiente break."
		, icoNxtBreak, this, ID_NXT_BREAK
		, BUTTON_TOOLBAR|FRAME_RAISED|LAYOUT_TOP|LAYOUT_LEFT);

	icoIncNum = new FXPNGIcon(getApp(), incNL_png);
	icoDecNum = new FXPNGIcon(getApp(), decNL_png);

	icoNewBreak = new FXPNGIcon(getApp(), newBreak_png);


	/////////////	 Barra de estado	////////////////

	statusbar=new FXStatusBar(this,LAYOUT_SIDE_BOTTOM|LAYOUT_FILL_X
		|STATUSBAR_WITH_DRAGCORNER|FRAME_RAISED);

	// Mensaje de inicio

	lineaEstado = statusbar->getStatusLine();
	lineaEstado->setNormalText("Debe elegir compilador y codigo fuente");

	// Resultado OP
	FXLabel *lblRes = new FXLabel(statusbar, NULL, NULL
		, FRAME_SUNKEN|JUSTIFY_RIGHT|LAYOUT_RIGHT|LAYOUT_CENTER_Y
		, 0, 0, 0, 0, 1, 1, 1, 1);

	lblRes->setTarget(this);
	lblRes->setSelector(ID_RESULTADO);
	
	// Titulo para resultado
	FXLabel *capRes = new FXLabel(statusbar, "  Resultado:", NULL
		, LAYOUT_RIGHT|LAYOUT_CENTER_Y);

	// Lexema
	FXLabel *estadoOp = new FXLabel(statusbar, NULL, NULL
		, FRAME_SUNKEN|JUSTIFY_RIGHT|LAYOUT_RIGHT|LAYOUT_CENTER_Y
		, 0, 0, 0, 0, 1, 1, 1, 1);
	estadoOp->setTarget(this);
	estadoOp->setSelector(ID_LEXEMA);

	// Caption lexema
	FXLabel *lblEstado = new FXLabel(statusbar, "  Datos OP:", NULL
		, LAYOUT_RIGHT|LAYOUT_CENTER_Y);

	lblEstado->setTarget(this);
	lblEstado->setSelector(ID_CAPLEX);

	// Op a realizar/realizada
	FXLabel *opCurso = new FXLabel(statusbar, NULL, NULL
		, FRAME_SUNKEN|JUSTIFY_RIGHT|LAYOUT_RIGHT|LAYOUT_CENTER_Y
		, 0, 0, 0, 0, 1, 1, 1, 1);
	opCurso->setTarget(this);
	opCurso->setSelector(ID_OPERACION);

	// Caption para la operacion
	FXLabel *lblOp = new FXLabel(statusbar, " OP:", NULL
		, LAYOUT_RIGHT|LAYOUT_CENTER_Y);

	/////////////////	Parte central de la ventana

	// Splitter A

	splitA=new FXSplitter(this
		,LAYOUT_SIDE_TOP|LAYOUT_FILL_X
		|LAYOUT_FILL_Y|SPLITTER_REVERSED|SPLITTER_VERTICAL);

	// Splitter

	/******	ORIGINAL
	splitter=new FXSplitter(splitA
		,LAYOUT_SIDE_TOP|LAYOUT_FILL_X
		|LAYOUT_FILL_Y|SPLITTER_REVERSED|SPLITTER_HORIZONTAL);
	 **************/

	splitter=new FXSplitter(splitA
		,LAYOUT_SIDE_TOP|LAYOUT_FILL_X
		|SPLITTER_REVERSED|SPLITTER_HORIZONTAL);


	// Panel izquierdo para la Tabla

	tablaFrame = new FXVerticalFrame(splitter
		, FRAME_SUNKEN|FRAME_THICK|LAYOUT_FILL_X|LAYOUT_FILL_Y
		, 0, 0, 0, 0, 5, 5, 5, 5);


	// Libro para CODIGO y GRAMATICA

	libro = new FXTabBook(splitter,this,ID_PANEL
		,PACK_UNIFORM_WIDTH|PACK_UNIFORM_HEIGHT
		|LAYOUT_FILL_X|LAYOUT_FILL_Y|LAYOUT_RIGHT);


	// Etiqueta sobre la TABLA

	new FXLabel(tablaFrame, "TABLA DE SIMBOLOS", NULL
		, JUSTIFY_CENTER_X|LAYOUT_FILL_X);

	// Linea horizontal de division

	new FXHorizontalSeparator(tablaFrame, SEPARATOR_GROOVE
		|LAYOUT_FILL_X);

	// Creacion de la tabla
	miTabla = new FXTabSim(tablaFrame, NULL, 0, TABLE_COL_SIZABLE|TABLE_ROW_SIZABLE
		|LAYOUT_FILL_X|LAYOUT_FILL_Y);


	/////////////////  CODIGO FUENTE   //////////////////////

	// Pestaña
	tabCod=new FXTabItem(libro,"&Codigo",NULL);


	// Panel
	codFrame = new FXVerticalFrame(libro
		, FRAME_THICK|FRAME_RAISED|LAYOUT_FILL_X|LAYOUT_FILL_Y
		, 0, 0, 0, 0, 5, 5, 5, 5);

	/** Barra de herramientas para breakpoints */
	barraCod = new FXToolBar(codFrame,LAYOUT_SIDE_TOP|LAYOUT_FILL_X
		|FRAME_RAISED);

	new FXButton(barraCod,"\tNuevo break\tEstablecer punto de ruptura.",icoNewBreak,this
		,ID_SET_BREAK
		,BUTTON_TOOLBAR|FRAME_RAISED|LAYOUT_TOP|LAYOUT_LEFT);

	new FXButton(barraCod, "\tInc digitos\tInc numero digitos para num linea."
		, icoIncNum, this, ID_INC_NUM
		, BUTTON_TOOLBAR|FRAME_RAISED|LAYOUT_TOP|LAYOUT_RIGHT);

	new FXButton(barraCod, "\tDec digitos\tDec numero digitos para num linea."
		, icoDecNum, this, ID_DEC_NUM
		, BUTTON_TOOLBAR|FRAME_RAISED|LAYOUT_TOP|LAYOUT_RIGHT);


	// Ventana de texto
	txtCod = new FXText(codFrame, this, ID_TXTCOD
		, LAYOUT_FILL_X|LAYOUT_FILL_Y);
	txtCod->setEditable(FALSE);

	// printf("col/tab por defecto: %d\n", txtCod->getTabColumns());
	txtCod->setTabColumns(COL_TABULADOR);

	// Mostramos los numeros de linea
	// El numero de digitos se almacena en el Registro
	txtCod->setBarColumns(numDig);
	txtCod->setNumberColor(colorCodNLinFG);
	txtCod->setBarColor(colorCodNLinBG);

	/** @todo Permitir elegir color del Break ??? */

	estiloBreak.normalForeColor=FXRGB(25, 225, 25);
	estiloBreak.normalBackColor=FXRGB(255, 255, 255);
	estiloBreak.selectForeColor=FXRGB(255, 255, 255);
	estiloBreak.selectBackColor=FXRGB(25, 225, 25);
	estiloBreak.hiliteForeColor=FXRGB(25, 255, 25);
	estiloBreak.hiliteBackColor=FXRGB(255, 255, 255);
	estiloBreak.activeBackColor=FXRGB(255, 255, 255);
	estiloBreak.style= FXText::STYLE_BOLD;

	txtCod->setStyled();
	txtCod->setHiliteStyles(&estiloBreak);


	////////////////     GRAMATICA        /////////////////////


	// Pestaña
	tabGram = new FXTabItem(libro,"&Gramatica",NULL);

	// Panel para la GRAMATICA
	gramFrame = new FXVerticalFrame(libro
		, FRAME_THICK|FRAME_RAISED|LAYOUT_FILL_X|LAYOUT_FILL_Y
		, 0, 0, 0, 0, 5, 5, 5, 5);

	// Ventana de texto

	txtGram = new FXText(gramFrame, this, ID_TXTGRAM
		, LAYOUT_FILL_X|LAYOUT_FILL_Y);
	txtGram->setEditable(FALSE);

	// printf("col/tab por defecto: %d\n", txtCod->getTabColumns());
	txtGram->setTabColumns(COL_TABULADOR);
	txtGram->setStyled();


	////////////////     COD GENERADO        /////////////////////


	// Pestaña
	tabGen = new FXTabItem(libro,"Cod &Generado",NULL);

	// Panel

	genFrame = new FXVerticalFrame(libro
		, FRAME_THICK|FRAME_RAISED|LAYOUT_FILL_X|LAYOUT_FILL_Y
		, 0, 0, 0, 0, 5, 5, 5, 5);

	// Ventana de texto

	/** @todo Repasar si es necesario ( casi que NO )
		que los FXText manden mensajes	*/

	txtGen = new FXText(genFrame, this, ID_TXTGEN
		, LAYOUT_FILL_X|LAYOUT_FILL_Y);
	txtGen->setEditable(FALSE);

	txtGen->setTabColumns(COL_TABULADOR);
	txtGen->setStyled();

	/////////////   Cod generado para PROCS / FUNCIONES

	// Pestaña
	tabProc = new FXTabItem(libro,"Procs",NULL);

	// Panel

	procFrame = new FXVerticalFrame(libro
		, FRAME_THICK|FRAME_RAISED|LAYOUT_FILL_X|LAYOUT_FILL_Y
		, 0, 0, 0, 0, 5, 5, 5, 5);

	// Ventana de texto

	/** @todo Repasar si es necesario ( casi que NO )
		que los FXText manden mensajes	*/

	txtProcs = new FXText(procFrame, NULL, 0
		, LAYOUT_FILL_X|LAYOUT_FILL_Y);
	txtProcs->setEditable(FALSE);

	txtProcs->setTabColumns(COL_TABULADOR);
	txtProcs->setStyled();
	

	////////	Mensajes del COMPILADOR 	////////

	logFrame = new FXVerticalFrame(splitA, LAYOUT_SIDE_TOP|LAYOUT_FILL_X
		|LAYOUT_FILL_Y);

	new FXLabel(logFrame, "Mensajes COMPILADOR", NULL
		, JUSTIFY_LEFT|LAYOUT_FILL_X|LAYOUT_MIN_HEIGHT
		| LAYOUT_TOP
		);

	txtLogFrame = new FXVerticalFrame(logFrame, LAYOUT_FILL_X|LAYOUT_FILL_Y
		|FRAME_THICK, 0,0,0,0, 0,0,0,0);

	txtLog = new FXText(txtLogFrame, NULL, 0
		, LAYOUT_FILL_X|LAYOUT_FILL_Y);

	txtLog->setEditable(FALSE);
	txtLog->setStyled();

	/////////	Inicializacion de variables	////////////

	status = PENDIENTE;
	codOp = OP_ESPERA;

	flagLexema = 0;
	flagResultado = 0;
	cadResultado = "<NO_AP>";

	// No deseleccionamos texto
	// flagTexto = 0;
	cadCaption = "  Lexema:";
	cadDatosOp = "<NO_APL>";
	nivTab = 0;
	nivTab2 = 0;

	// Valores iniciales Barra de estado
	// flagGUI = true;
	dtsGUI.cptOP = " OP:";
	dtsGUI.txtOP = "<ESPERA>";
	dtsGUI.cptDato = " Argumento:";
	dtsGUI.txtDato = "<NULL>";
	dtsGUI.txtRes = "<>";
	dtsGUI.iniSel = -1;
	dtsGUI.tamSel = -1;
	dtsGUI.status = 0;

	iniSelCod = -1;
	tamSelCod = -1;

	/***   Indicadores de carga/generacion de archivos */
	flagGram = 0;
	flagGen = 0;
	flagFunc = 0;

	/***** Posicion Coloreado de texto en el CODIGO FUENTE */
	/** @todo Borrar iniSel y tamSel */
	/**
	iniSel = -1;
	tamSel = -1;
	**/

	/***** Numero de breakpoints */
	/** @todo Recordar vaciar la lista de breaks al REINICIAR */

	numBreaks = 0;
	sigBreak = 0;
	flagAuto = false;


	/***********  Fuentes del Interfaz *************/

	fntTab = NULL;
	fntCod = NULL;
	fntGram = NULL;
	fntGen = NULL;
	fntLog = NULL;

	// Inicializacion de reglas

	numReglas = 0;

	// Colores predefinidos

	coloresTab.size(14);

	crearGestores();

}

/**
 Creacion del Array de gestores
*/

void guiWindow::crearGestores(void) {

	gestores[INS] = new gestorINS(miTabla, pipeHP[0], pipePH[1]);
	gestores[BSIM] = new gestorBSIM(miTabla, pipeHP[0], pipePH[1]);
	gestores[BPROC] = new gestorBPROC(miTabla, pipeHP[0], pipePH[1]);
	gestores[BPARAM] = new gestorBPARAM(miTabla, pipeHP[0], pipePH[1]);
	gestores[DEL] = new gestorDEL(miTabla, pipeHP[0], pipePH[1]);
	gestores[VERIF] = new gestorVERIF(miTabla, pipeHP[0], pipePH[1]);
	gestores[TEMP] = new gestorTEMP(miTabla, pipeHP[0], pipePH[1], "temp");
	gestores[CADFMT] = new gestorCADFMT(miTabla, pipeHP[0], pipePH[1]);
	gestores[ETIQ] = new gestorETIQ(miTabla, pipeHP[0], pipePH[1], "etiq");
	gestores[BUSQ_ETIQ] = new gestorBUSQ_ETIQ(miTabla, pipeHP[0], pipePH[1]);
	gestores[DEL_CTRL] = new gestorDEL_CTRL(miTabla, pipeHP[0], pipePH[1]);

	gestores[GENCOD] = new gestorGENCOD(txtGen, txtProcs, pipeHP[0], pipePH[1]);

	return;
	}

	

/**
 Crear e inicializar ventana principal.
 @todo Añadir todas las llamadas a create AQUI Ejemplo: MENUS
*/

void guiWindow::create(){

	// Leemos las preferencias del REGISTRO FOX
	leerRegistro();

	// Procesamos Esquema de Traduccion
	leerEsquema(nomEsquema);

	// Crear las ventanas
	FXMainWindow::create();
	filemenu->create();
	prefsmenu->create();
	genmenu->create();

	// Hacemos aparecer la ventana ppal
	show();
	}


// Limpieza

guiWindow::~guiWindow() {
	FXint i, j;

	delete txtGram;
	delete gramFrame;
	delete tabGram;
	delete txtCod;
	delete codFrame;
	delete tabCod;

	// delete tabla;
	delete miTabla;

	delete libro;
	delete tablaFrame;
	delete splitter;
	delete statusbar;
	delete icoFin;
	delete icoPaso;
	delete icoIni;
	delete barraOp;
	delete filemenu;
	delete menubar;

	delete txtLog;
	delete logFrame;

	delete fntTab;
	delete fntCod;
	delete fntGram;
	delete fntGen;
	delete fntLog;

	for ( i = 0; i < GENCOD; i++ )
		delete gestores[i];

	// Destruccion del esquema de traduccion

	printf("Liberacion memoria Esquema de Traduccion\n");

	for ( i = 0; i < nRgls; i++ )
		for ( j = 0; j < rgls[i].numCampos; j++ )
			if ( rgls[i].tipos[j] == ARG_STRING )
				free(rgls[i].args[j]);

	}

/**
 Lectura de las PREFERENCIAS desde el registro.
*/

void guiWindow::leerRegistro(void) {
	FXint i, j, nFilas, nCols;
	FXColor cTabFG, cTabBG, cNewFG, cSimFG, cProcFG, cParamFG, cDelFG;
	FXColor cCodFG, cCodBG, cCodSelFG, cCodSelBG;
	FXColor cGramFG, cGramBG, cGramActFG, cGramActBG;
	FXColor cGenFG, cGenBG;
	FXString fontspec;
	FXString campo;
	FXchar *camposTabla[] = { "tablaFG", "tablaBG", "nuevoFG", "nuevoBG"
		, "simboloFG", "simboloBG", "eliminarFG", "eliminarBG" 
		, "dupFG", "dupBG", "procFG", "procBG", "paramFG", "paramBG" };


	// Colores de la Tabla de Simbolos

	for ( i = 0; i < 14; i++ ) {
		coloresTab[i] = getApp()->reg().readColorEntry("COLORES"
			, camposTabla[i], FXRGB(0,0,0));
		miTabla->setColor(i, coloresTab[i]);
		}


	// Colores del Codigo Fuente
	colorCodFG = getApp()->reg().readColorEntry("COLORES","codigoFG"
			, FXRGB(0, 0, 0));
	colorCodBG = getApp()->reg().readColorEntry("COLORES","codigoBG"
			, FXRGB(255,255,255));
	colorCodSelFG = getApp()->reg().readColorEntry("COLORES","codigoSelFG"
			, FXRGB(255, 255, 255));
	colorCodSelBG = getApp()->reg().readColorEntry("COLORES","codigoSelBG"
			, FXRGB(25,25,255));

	colorCodErrFG = getApp()->reg().readColorEntry("COLORES","codigoErrFG"
			, FXRGB(255, 255, 255));
	colorCodErrBG = getApp()->reg().readColorEntry("COLORES","codigoErrBG"
			, FXRGB(255,25,25));

	colorCodNLinFG = getApp()->reg().readColorEntry("COLORES","codigoNLinFG"
			, FXRGB(0, 0, 0));
	colorCodNLinBG = getApp()->reg().readColorEntry("COLORES","codigoNLinBG"
			, FXRGB(200,200,200));
	

	// Colores de la Gramatica
	colorGramFG = getApp()->reg().readColorEntry("COLORES","gramaticaFG"
			, FXRGB(0,0,0));
	colorGramBG = getApp()->reg().readColorEntry("COLORES","gramaticaBG"
			, FXRGB(255,255,255));
	colorGramActFG = getApp()->reg().readColorEntry("COLORES","gramaticaActFG"
			, FXRGB(255,25,25));
	colorGramActBG = getApp()->reg().readColorEntry("COLORES","gramaticaActBG"
			, FXRGB(255,255,255));

	// Colores para Codigo Generado
	colorGenFG = getApp()->reg().readColorEntry("COLORES","generadoFG"
			, FXRGB(0,0,0));
	colorGenBG = getApp()->reg().readColorEntry("COLORES","generadoBG"
			, FXRGB(255,255,255));


	///////   Fuentes

	fontspec=getApp()->reg().readStringEntry("FUENTES","fuenteTabla","");

	if( !fontspec.empty() ) {
		fntTab = new FXFont(getApp(),fontspec);
		miTabla->setFont(fntTab);
		}

	fontspec=getApp()->reg().readStringEntry("FUENTES","fuenteCodigo","");

	if( !fontspec.empty() ) {
		fntCod = new FXFont(getApp(),fontspec);
		txtCod->setFont(fntCod);
		}

	fontspec=getApp()->reg().readStringEntry("FUENTES","fuenteGramatica","");

	if( !fontspec.empty() ) {
		fntGram = new FXFont(getApp(),fontspec);
		txtGram->setFont(fntGram);
		}

	fontspec=getApp()->reg().readStringEntry("FUENTES","fuenteGenerado","");

	if( !fontspec.empty() ) {
		fntGen = new FXFont(getApp(),fontspec);
		txtGen->setFont(fntGen);
		}

	fontspec=getApp()->reg().readStringEntry("FUENTES","fuenteLog","");

	if( !fontspec.empty() ) {
		fntLog = new FXFont(getApp(),fontspec);
		txtLog->setFont(fntLog);
		}

	// Lectura de reglas de coloreado para LOG
	/** @todo Creacion dinamica del array de reglas !!!  */

	numReglas = getApp()->reg().readIntEntry("REGLAS","nReglas", 0);

	for ( i = 0; i < numReglas; i++ ) {
		campo = "regla" + FXStringVal(i);
		reglasLog[i].nombre = getApp()->reg().readStringEntry("REGLAS"
			, campo.text(), "<NULA>");

		campo = "patron" + FXStringVal(i);
		reglasLog[i].patron = getApp()->reg().readStringEntry("REGLAS"
			, campo.text(), "<NULO>");

		campo = "colorFG" + FXStringVal(i);
		estilosLog[i].normalForeColor = getApp()->reg().readColorEntry("REGLAS"
			, campo.text(), FXRGB(0,0,0));

		campo = "colorBG" + FXStringVal(i);
		estilosLog[i].normalBackColor = getApp()->reg().readColorEntry("REGLAS"
			, campo.text(), FXRGB(255,255,255));
		}

	// Lectura del numero de digitos para Numeros de linea del Cod Fuente

	numDig = getApp()->reg().readIntEntry("NUMSLINEA", "ndigitos", 3);

	// Lectura de los nombres de ficheros include
	incDatos = getApp()->reg().readStringEntry("INCLUDES", "tda", "dec_dat.c");
	incFuncs = getApp()->reg().readStringEntry("INCLUDES", "funciones", "dec_func.c");

	// Nombre del fichero que contiene esquema de traduccion
	nomEsquema = getApp()->reg().readStringEntry("GEN_CODIGO", "esquema", "esquema.ets");

	return;
	}


/**
 Guardar las preferencias en el REGISTRO.

 Se almacenan colores, fuentes y reglas de coloreado de log
*/

void guiWindow::escribirRegistro(void) {
	FXString fontspec;
	FXint i;
	FXString campo;
	FXchar *camposTabla[] = { "tablaFG", "tablaBG", "nuevoFG", "nuevoBG"
		, "simboloFG", "simboloBG", "eliminarFG", "eliminarBG" 
		, "dupFG", "dupBG", "procFG", "procBG", "paramFG", "paramBG" };


	// Colores de la Tabla de Simbolos

	for ( i = 0; i < 14; i++ )
		getApp()->reg().writeColorEntry("COLORES"
			, camposTabla[i], coloresTab[i]);



	// Colores del Codigo Fuente
	getApp()->reg().writeColorEntry("COLORES","codigoFG", colorCodFG);
	getApp()->reg().writeColorEntry("COLORES","codigoBG", colorCodBG);
	getApp()->reg().writeColorEntry("COLORES","codigoSelFG", colorCodSelFG);
	getApp()->reg().writeColorEntry("COLORES","codigoSelBG", colorCodSelBG);
	getApp()->reg().writeColorEntry("COLORES","codigoErrFG", colorCodErrFG);
	getApp()->reg().writeColorEntry("COLORES","codigoErrBG", colorCodErrBG);

	getApp()->reg().writeColorEntry("COLORES","codigoNLinFG", colorCodNLinFG);
	getApp()->reg().writeColorEntry("COLORES","codigoNLinBG", colorCodNLinBG);


	// Colores de la Gramatica
	getApp()->reg().writeColorEntry("COLORES","gramaticaFG", colorGramFG);
	getApp()->reg().writeColorEntry("COLORES","gramaticaBG", colorGramBG);
	getApp()->reg().writeColorEntry("COLORES","gramaticaActFG", colorGramActFG);
	getApp()->reg().writeColorEntry("COLORES","gramaticaActBG", colorGramActBG);

	// Colores para Codigo Generado
	getApp()->reg().writeColorEntry("COLORES","generadoFG", colorGenFG);
	getApp()->reg().writeColorEntry("COLORES","generadoBG", colorGenBG);

	////  Fuentes

	fontspec = miTabla->getFont()->getFont();
	getApp()->reg().writeStringEntry("FUENTES","fuenteTabla",fontspec.text());

	fontspec = txtCod->getFont()->getFont();
	getApp()->reg().writeStringEntry("FUENTES","fuenteCodigo",fontspec.text());

	fontspec = txtGram->getFont()->getFont();
	getApp()->reg().writeStringEntry("FUENTES","fuenteGramatica",fontspec.text());

	fontspec = txtGen->getFont()->getFont();
	getApp()->reg().writeStringEntry("FUENTES","fuenteGenerado",fontspec.text());

	fontspec = txtLog->getFont()->getFont();
	getApp()->reg().writeStringEntry("FUENTES","fuenteLog",fontspec.text());


	// Reglas de coloreado para LOG

	getApp()->reg().writeIntEntry("REGLAS","nReglas", numReglas);

	for ( i = 0; i < numReglas; i++ ) {
		campo = "regla" + FXStringVal(i);
		getApp()->reg().writeStringEntry("REGLAS"
			, campo.text(), reglasLog[i].nombre.text());

		campo = "patron" + FXStringVal(i);
		getApp()->reg().writeStringEntry("REGLAS"
			,campo.text(), reglasLog[i].patron.text());

		campo = "colorFG" + FXStringVal(i);
		getApp()->reg().writeColorEntry("REGLAS"
			, campo.text(), estilosLog[i].normalForeColor);

		campo = "colorBG" + FXStringVal(i);
		getApp()->reg().writeColorEntry("REGLAS"
			, campo.text(), estilosLog[i].normalBackColor);
		}

	// Campos para numeros de linea del Cod. Fuente

	getApp()->reg().writeIntEntry("NUMSLINEA", "ndigitos", numDig);

	// Nombre de los includes
	getApp()->reg().writeStringEntry("INCLUDES", "tda", incDatos.text());
	getApp()->reg().writeStringEntry("INCLUDES", "funciones", incFuncs.text());

	// Nombre del fichero con el esquema de traduccion
	getApp()->reg().writeStringEntry("GEN_CODIGO", "esquema", nomEsquema.text());

	return;
	}




/**
 Gestion del boton "Iniciar".
 Envio del nombre de los ficheros COMPILADOR y COD FUENTE
 al proceso hijo compilador
 */

long guiWindow::onCmdIniciar(FXObject *, FXSelector, void *) {

	// Mandamos nombres ficheros al compilador

	iniciar();
		
	// Establecemos gestor de Entrada para pipe

	getApp()->addInput(pipeHP[0], INPUT_READ, this, ID_PIPE);

	// Deshabilitamos boton "Iniciar" y habilitamos "Paso"

	status = LISTO_PASO;
	codOp = OP_ESPERA;

	// Limpiar Campos de texto para codigo generado
	// si hace falta...

	if ( txtGen->getLength() > 0 )
		txtGen->removeText(0, txtGen->getLength());

	if ( txtProcs->getLength() > 0 )
		txtProcs->removeText(0, txtProcs->getLength());

	// Reiniciamos la lista de breaks
	numBreaks = 0;
	sigBreak = 0;

	fprintf(stderr, "DEBUG Pulsado boton INICIAR...\n");

	return 1;
	}

/**
 Actualizacion del boton "Iniciar"
*/

long guiWindow::onUpdIniciar(FXObject* sender,FXSelector,void*){
	if( status == LISTO_INICIAR )
		sender->handle(this,FXSEL(SEL_COMMAND,ID_ENABLE),NULL);
	else
		sender->handle(this,FXSEL(SEL_COMMAND,ID_DISABLE),NULL);

	return 1;
	}

/**
 Gestion del boton "Paso".
*/

long guiWindow::onCmdPaso(FXObject *, FXSelector,void *) {
	char msj[] = "ACK";
	int nbytes, i;

	if ( codOp == OP_POST ) {

		fprintf(stderr, "DEBUG Estamos en OP_POST\n");

		// Limpieza items seleccionados
		miTabla->limpiar();

		// De-seleccionamos el texto de la GRAMATICA
		/** todo Comprobar si basta con txtGram->killHighlight() */
		// flagGram = 0;
		txtGram->killHighlight();

		// Re-activamos gestor de entrada para el PIPE
		getApp()->addInput(pipeHP[0], INPUT_READ, this, ID_PIPE);

		// ACK al hijo...
		nbytes = write(pipePH[1], msj, 4 * sizeof(char));
		
		// Espera de una nueva peticion
		codOp = OP_ESPERA;

		return 1;
		}

	this->handle(this, FXSEL(SEL_COMMAND, ID_EXEC_POST), NULL);

	return 1;
	}

/**
 Actualizacion del estado boton "Paso".
*/

long guiWindow::onUpdPaso(FXObject* sender,FXSelector,void*){
	if(status == LISTO_PASO) {
		sender->handle(this,FXSEL(SEL_COMMAND,ID_ENABLE),NULL);
		lineaEstado->setNormalText("Iniciada compilacion...");
	} else {
		sender->handle(this,FXSEL(SEL_COMMAND,ID_DISABLE),NULL);
		}

	return 1;
	}

/**
 Gestion del pipe de comunicacion con el Compilador.
 Lee del pipe el tipo de Mensaje y llama a la funcion
 encargada de gestionar dicho mensaje
*/

long guiWindow::onRcvPipe(FXObject *sender, FXSelector, void *) {
	int nbytes, i, res;
	char buffer[4];

	// printf("Leyendo del pipe...\n");

	nbytes = read(pipeHP[0], buffer, 1);
			
	this->handle(this, FXSEL(SEL_COMMAND, ID_EXEC_PRE), &buffer[0]);

	return 1;
	}


/**
 Gestion del pipe para los mensajes del compilador.
*/

long guiWindow::onRcvErr(FXObject *sender, FXSelector, void *) {
	char *buffer;
	char tipo[6];
	FXint ll, i, j;
	FXint tamAnt, posCuerpo, tamMsj;
	FXRex *expReg;
	FXbool encaja;
	FXint ini, fin;
	FXint desde, hasta;
	FXchar *copia;


	buffer = (char *) malloc ( 200 * sizeof(char));
	if ( buffer == NULL ) {
		perror("onRcvErr Mem buffer");
		return 0;
		}

	buffer = fgets(buffer, 200, strERR);

	if ( buffer == NULL ) {
		perror("PADRE fgets en pipeERR!!!!");
		// Que hacer ???
		return 0;
		}

	// Mostramos mensaje por LOG

	strncpy(tipo, buffer, 5);
	tipo[5] = '\0';

	tamAnt = txtLog->getLength();
	tamMsj = strlen(buffer);
	txtLog->appendText(buffer, tamMsj);
	ll = txtLog->getBottomLine();
	txtLog->setCenterLine(ll);

	txtLog->setHiliteStyles(estilosLog);

	copia = (FXchar *) malloc ((tamMsj+1) * sizeof(FXchar));
	if ( copia == NULL ) {
		perror("Mem dinamica copia");
		exit(1);
		}

	strncpy(copia, buffer, tamMsj+1);

	// Por defecto SIN estilo

	for ( i = 0; i < tamMsj; i++ )
		buffer[i] = 0;

	// Comparamos con todas las reglas

	for ( i = 0; i < numReglas; i++ ) {
		// printf("Usando patron: %s\n", reglasLog[i].patron.text());

		expReg = new FXRex(reglasLog[i].patron, REX_NORMAL, NULL);

		encaja = expReg->match(copia, tamMsj, &ini, &fin);

		if ( encaja ) {
			// Coloreamos
			// printf("Encaja PATRON[%d] = %s ", i, reglasLog[i].patron.text());
			// printf("Ini: %d Fin: %d\n", ini, fin);

			memset(&buffer[ini], i+1, fin-ini);

			/*********
			for ( j = ini; j < fin; j++ )
				buffer[j] = i+1;
			*************/
			}


		delete expReg;
		}

	txtLog->changeStyle(tamAnt, tamMsj, buffer);


	free(buffer);
	free(copia);

	return 0;
	}


///////////////////	Gestion de MENUS	//////////////////////

/**
 Gestion de la entrada de menu "Abrir compilador".
 Se comprueba si la compilacion esta en marcha y, si es asi,
 se pregunta al usuario si desea reiniciar la compilacion
*/

long guiWindow::onCmdAbrirCompilador(FXObject *sender, FXSelector, void *) {
	FXFileDialog opendialog(this,"Elegir Compilador");
	FXString archivo, msj;
	FXuint resp;

	opendialog.setSelectMode(SELECTFILE_EXISTING);
	resp = FX::MBOX_CLICKED_NO;

	if ( status == LISTO_PASO ) {
		resp = FXMessageBox::question(this, MBOX_YES_NO
			, "Nuevo compilador"
			, "Desea cargar otro compilador y reiniciar?");

		if ( resp == FX::MBOX_CLICKED_NO )
			return 0;
		}

	if ( opendialog.execute() ) {
		archivo = opendialog.getFilename();

		if ( !FXFile::isExecutable(archivo) ) {
			FXMessageBox::error(this, MBOX_OK
			, "Error cargando archivo"
			, "Archivo no ejecutable!!!");
			return 0;
			}

		if ( status == LISTO_PASO ) {
			free(rutaCompilador);
			free(fCompilador);
			}


		printf("Usuario eligio:\n%s\n", archivo.text());
		
		rutaCompilador = strdup(archivo.text());
		fCompilador = strdup((FXFile::name(archivo)).text());

		printf("NUEVA Ruta: %s.\n", rutaCompilador);
		printf("NUEVO fCompilador: %s.\n", fCompilador);


		if ( resp == FX::MBOX_CLICKED_YES ) {
			// Hay que reiniciar el entorno
			status = REINI_COMP;
			handle(this, FXSEL(SEL_COMMAND,ID_REINICIAR), NULL);

			return 1;
			}

		if ( status == CODIGO_OK || status == LISTO_INICIAR ) {
			status = LISTO_INICIAR;
			msj = "Listo para compilar";
		} else {
			status = COMPILADOR_OK;
			msj = "Compilador cargado. Elija codigo fuente";
			}

		lineaEstado->setNormalText(msj);
		}

	return 1;
	}


/**
 Gestion de la entrada de menu "Cargar codigo fuente".
 Se comprueba si la compilacion esta en marcha y, si es asi,
 se pregunta al usuario si desea reiniciar la compilacion
*/

long guiWindow::onCmdAbrirCodigo(FXObject *sender, FXSelector, void *) {
	FXFileDialog opendialog(this,"Cargar Codigo Fuente");
	FXString sel, msj;
	FXuint resp;

	opendialog.setSelectMode(SELECTFILE_EXISTING);
	resp = FX::MBOX_CLICKED_NO;

	if ( status == LISTO_PASO ) {
		resp = FXMessageBox::question(this, MBOX_YES_NO
			, "Nuevo codigo"
			, "Desea cargar otro codigo fuente y reiniciar?");

		if ( resp == FX::MBOX_CLICKED_NO )
			return 0;
		}

	if ( opendialog.execute() ) {
		sel = opendialog.getFilename();

		if ( status == LISTO_PASO ) {
			free(fCodigo);
			}

		printf("Usuario eligio:\n%s\n", sel.text());
		fCodigo = strdup(sel.text());

		if ( resp == FX::MBOX_CLICKED_YES ) {
			// Hay que reiniciar el entorno
			status = REINI_COD;
			handle(this, FXSEL(SEL_COMMAND,ID_REINICIAR), NULL);

			return 1;
			}

		if ( status == COMPILADOR_OK || status == LISTO_INICIAR ) {
			status = LISTO_INICIAR;
			msj = "Listo para compilar";
		} else {
			status = CODIGO_OK;
			msj = "Codigo fuente cargado. Elija compilador";
			}

		// TODO: AÃ±adir comprobaciones sobre el archivo ???
		// TODO: La carga se debe hacer ANTES de establecer STATUS !!
		// y si falla ?? => Estado INCONSISTENTE !!!!

		cargarArchivo(sel, txtCod);

		lineaEstado->setNormalText(msj);

		txtCod->setBarColumns(numDig);
		txtCod->setNumberColor(colorCodNLinFG);
		txtCod->setBarColor(colorCodNLinBG);
		}

	return 1;
	}

/**
 Gestion de la entrada de menu "Cargar gramatica".
 La carga de una nueva gramatica NO es imprescindible para lanzar
 la compilacion aunque si recomendable para seguir el proceso.
 Cargar una gramatica nueva durante la compilacion NO reinicia
 el proceso
*/

long guiWindow::onCmdAbrirGramatica(FXObject *sender, FXSelector, void *) {
	FXFileDialog opendialog(this,"Elegir gramatica");
	FXString archivo, msj;

	opendialog.setSelectMode(SELECTFILE_EXISTING);

	if ( opendialog.execute() ) {
		archivo = opendialog.getFilename();

		printf("Usuario eligio:\n%s\n", archivo.text());
		
		fGramatica = strdup(archivo.text());

		printf("NUEVO fGramatica: %s.\n", fCompilador);

		// TODO: AÃ±adir comprobaciones sobre el archivo ???
		cargarArchivo(archivo, txtGram);
		}

	return 1;
	}



/**
 Gestion de la entrada de menu "Terminar".
 Se pregunta al usuario si esta seguro. Ante una respuesta
 afirmativa se sincroniza el proceso hijo
*/

long guiWindow::onCmdTerminar(FXObject *sender, FXSelector, void *) {
	FXuint resp;
	int res, nbytes, tam;
	char msj[4], msjFin[6];

	resp = FXMessageBox::question(this, MBOX_YES_NO
		, "Terminar"
		, "Desea abortar compilacion y salir ?");

	if ( resp == FX::MBOX_CLICKED_NO )
		return 0;

	// Si terminamos, hay que avisar al hijo...
	// Completamos la op que estuvieramos haciendo
	// para sincronizarnos...

	if ( status == PENDIENTE || status == CODIGO_OK 
		|| status == COMPILADOR_OK ) {
		// Todavia no habiamos empezado
		res = kill(pid, SIGKILL);
		if ( res == -1 )
			perror("PADRE matando a HIJO");

		getApp()->exit();

		return 0;
		}


	if ( status == LISTO_INICIAR ) {
		// Debemos mantener el orden...
		tam = strlen(rutaCompilador);
		nbytes = write(pipePH[1], &tam, sizeof(int));
		nbytes = write(pipePH[1], rutaCompilador,tam * sizeof(char));
		tam = strlen(fCompilador);
		nbytes = write(pipePH[1], &tam, sizeof(int));
		nbytes = write(pipePH[1], fCompilador, tam*sizeof(char));
		tam = strlen(fCodigo);
		nbytes = write(pipePH[1], &tam, sizeof(int));
		nbytes = write(pipePH[1], fCodigo, tam * sizeof(char));

		strcpy(msjFin, "FINAL");
		nbytes = write(pipePH[1], msjFin, 6 * sizeof(char));
		// Esperamos respuesta
		nbytes = read(pipeHP[0], msj, 4 * sizeof(char));
		printf("HIJO se despidio con: %s\n", msj);

		getApp()->exit();

		return 0;
		}

	// TODO: status == CODIGO_OK || status == COMPILADOR_OK

	// Ejecucion POST operacion pendiente

	if ( codOp == OP_PRUEBAS ) {
		/** @todo Comprobar que SIEMPRE estamos en OP_PRUEBAS */
		gstActual->post();
	} else {
		fprintf(stderr, "\nDEBUG onCmdTerminar codOp != OP_PRUEBAS\n");
		}

	// Estamos en OP_POST o FIN_COMPILACION

	strcpy(msj, "FIN");
	nbytes = write(pipePH[1], msj, 4 * sizeof(char));

	// Esperamos su respuesta y terminamos

	nbytes = read(pipeHP[0], msj, 4 * sizeof(char));
	printf("HIJO se despidio con: %s\n", msj);

	getApp()->exit();

	return 0;
	}

/**
 Gestion de la entrada de menu "Guardar cod generado".
 Se puede guardar el codigo en cualquier momento de la compilacion
 Tambien ¿ se pregunta ? al usuario si desea guardar el
 Codigo correspondiente a las funciones
 */

long guiWindow::onCmdGuardar(FXObject *sender, FXSelector sel, void *) {
	FXFileDialog opendialog(this,"Guardar codigo generado");
	FXString archivo, msj;
	FXuint resp;
	FXbool guardado;


	if ( FXSELTYPE(sel) == SEL_UPDATE ) {
		if ( flagGen )
			sender->handle(this, FXSEL(SEL_COMMAND,ID_ENABLE)
				,NULL);
		else
			sender->handle(this, FXSEL(SEL_COMMAND,ID_DISABLE)
				,NULL);

		return 1;
		}

	// Si no es un mensaje de Update es un COMANDO

	opendialog.setSelectMode(SELECTFILE_ANY);

	if ( opendialog.execute() ) {
		archivo = opendialog.getFilename();

		printf("Usuario eligio:\n%s\n", archivo.text());
		
		if ( FXFile::exists(archivo) ) {
		
			resp = FXMessageBox::question(this, MBOX_YES_NO
				, "Archivo existente"
				, "El archivo existe. Desea modificarlo?");

			if ( resp == FX::MBOX_CLICKED_NO )
				printf("No quiere modificar\n");
			else
				guardado = guardarArchivo(archivo, txtGen);
		} else {
			/** @todo Si el archivo existe, guardamos SIEMPRE !!! */
			guardado = guardarArchivo(archivo, txtGen);
			}

		// Informamos al usuario de que se guardan los PROCS
		/** @todo Flag que indique si se generaron procs */
		resp = FXMessageBox::question(this, MBOX_YES_NO
				, "Guardar procedimientos"
				, "Desea guardar los procedimientos declarados?");

		if ( resp == FX::MBOX_CLICKED_YES  ) {
			/** @todo Comprobar de nuevo si el archivo existe */
			guardado = guardarArchivo(incFuncs, txtProcs);
			}

	
		return 1;
		}

	return 0;
	}


/**
 Funcion auxiliar para cargar un archivo.
 El contenido de un archivo se vuelva en un campo de texto
 @param file Cadena con la ruta completa al archivo
 @param txtDestino Campo de texto donde se carga el contenido
 */

FXbool guiWindow::cargarArchivo(FXString file, FXText *txtDestino) {
	FXuint size, n;
	FXchar *texto;
	FILE *fp;

	// Open file
	fp = fopen(file.text(),"r");
	if( !fp ) {
		FXMessageBox::error(this, MBOX_OK, "Error cargando archivo"
			, "No se pudo abrir: %s", file.text());
		return FALSE;
		}

	// Tamaño del fichero
	size=FXFile::size(file);

	// Make buffer to load file
	if( !FXMALLOC(&texto,FXchar,size) ) {
		FXMessageBox::error(this,MBOX_OK, "Error cargando archivo"
			,"Archivo demasiado grande: %s (%d bytes)"
			,file.text(),size);
		fclose(fp);
		return FALSE;
		}

	// Set wait cursor
	getApp()->beginWaitCursor();

	// Read the file
	n=fread(texto,1,size,fp);

	// Close file
	fclose(fp);

	// Cargamos el texto en el widget seleccionado
	txtDestino->setText(texto,n);
	FXFREE(&texto);

	// Kill wait cursor
	getApp()->endWaitCursor();

	return TRUE;
	}
	

/**
 Funcion auxiliar para guardar un archivo.
 El contenido del campo de texto para el Codigo Generado se vuelca
 en un archivo
 @param file Cadena con la ruta completa al archivo
 @return Devuelve booleano que indica si se pudo efectuar la operacion
 */

FXbool guiWindow::guardarArchivo(FXString file, FXText *txtDest) {
	FXuint size, n;
	FXchar *texto;
	FILE *fp;

	// Open file
	fp = fopen(file.text(),"w");
	if( !fp ) {
		FXMessageBox::error(this, MBOX_OK, "Error guardando archivo"
			, "No se pudo abrir: %s", file.text());
		return FALSE;
		}

	// Tamaño del fichero
	size=txtDest->getLength();

	/** @todo Hacer esto un poco mas limpio... */
	if ( size == 0 ) {
		fprintf(stderr, "guardarArchivo: %s VACIO\n", file.text());
		return true;
		}

	// Reserva de memoria para buffer
	if( !FXMALLOC(&texto,FXchar,size+1) ) {
		FXMessageBox::error(this,MBOX_OK, "Error guardando archivo"
			,"Archivo demasiado grande: %s",file.text());
		fclose(fp);
		return FALSE;
		}

	// Set wait cursor
	getApp()->beginWaitCursor();

	// Leemos el contenido del campo de texto
	txtDest->getText(texto, size);

	// AÃ±adimos una nueva linea si es necesario

	if ( (0 < size) && (texto[size-1]!='\n') )
		texto[size++] = '\n';

	// Escribimos en el archivo

	n = fwrite(texto,1,size,fp);

	// Despedida y cierre
	FXFREE(&texto);
	getApp()->endWaitCursor();
	fclose(fp);

	return TRUE;
	}
	
	
/**
 Gestion de la entrada "Colores" del menu Preferencias.
 */

long guiWindow::onCmdPrefs(FXObject *sender, FXSelector, void *) {
	dlgPrefs preferencias(this);

	/** @todo
	 Tendriamos que hacerlo con una copia tal y como
	 se hace para los patrones... Si el usuario acepta
	 se cambian los colores
	*/
		
	preferencias.execute();

	return 1;
	}


/**
 Entrada "Guardar preferencias" del menu Preferencias.
 Se guardan los colores seleccionados en el Registro FOX
*/

long guiWindow::onCmdGuardarPrefs(FXObject *sender, FXSelector, void *) {
	escribirRegistro();
	getApp()->reg().write();
	return 1;
	}

/**
 Entrada "Fuentes" del menu Preferencias.
*/

long guiWindow::onCmdFuentes(FXObject *sender, FXSelector, void *) {
	dlgFuentes fuentes(this);
	fuentes.execute();
	}


/**
 Lectura de las fuentes establecidas para la GUI.
 Utilizada para Actualizar el nombre de la fuente en campos de texto
 del dialogo de Cambiar Fuente
*/

long guiWindow::onUpdLeerFuentes(FXObject *sender, FXSelector sel, void *) {
	FXFont *fuente;
	FXFontDesc descFuente;
	FXString strDesc;

	switch( FXSELID(sel) ) {

		case ID_FNT_TAB:
			fuente = fntTab;
			break;
		case ID_FNT_COD:
			fuente = fntCod;
			break;
		case ID_FNT_GRAM:
			fuente = fntGram;
			break;
		case ID_FNT_GEN:
			fuente = fntGen;
			break;
		case ID_FNT_LOG:
			fuente = fntLog;
			break;
		}


	strDesc = fuente->getFont();

	sender->handle(this, FXSEL(SEL_COMMAND, ID_SETSTRINGVALUE), (void *)&strDesc);

	return 1;
	}

/**
 Lectura de la fuente ACTUAL de un elemento de la GUI.
 NO se utilizan mensajes/targets !!!!
 FUNCION No utilizada !!!!!!!!
*/

FXString guiWindow::leerFuente(FXuint id) {
	FXFont *fuente;
	FXFontDesc descFuente;
	FXString strDesc;

	switch( id ) {

		case ID_FNT_TAB:
			fuente = miTabla->getFont();
			break;
		}

	/***************
	printf("Recibido mensaje ID_FNT_TAB en guiWindow...\n");
	printf("Face fuente: %s\n", descFuente.face);
	 ***********************************************************/

	strDesc = fuente->getName();
	strDesc.append('-');
	strDesc.append(FXStringVal(fuente->getWeight()));
	strDesc.append('-');
	strDesc.append(FXStringVal(fuente->getSlant()));
	strDesc.append('-');
	strDesc.append(FXStringVal(fuente->getSize()));


	return strDesc;
	}


/**
 Cambio de la fuente asignada a un elemento de la GUI.
*/

long guiWindow::onCmdCambiarFnt(FXObject *sender, FXSelector sel, void *ptr) {
	FXFontDialog fontdlg(this,"Nueva fuente",DECOR_BORDER|DECOR_TITLE);
	FXFontDesc fontdesc;
	FXFont *fuente;

	switch ( FXSELID(sel) ) {
		case ID_NEW_FNT_TAB:
			// miTabla->getFont()->getFontDesc(fontdesc);
			fuente = fntTab;
			break;
		case ID_NEW_FNT_COD:
			fuente = fntCod;
			break;
		case ID_NEW_FNT_GRAM:
			fuente = fntGram;
			break;
		case ID_NEW_FNT_GEN:
			fuente = fntGen;
			break;
		case ID_NEW_FNT_LOG:
			fuente = fntLog;
			break;
		default:
			fprintf(stderr, "Mensaje de fuente INCORRECTO!!!!\n");
			return 0;
		}

	fuente->getFontDesc(fontdesc);
	printf("Fuente actual: %s\n", fontdesc.face);
	fontdlg.setFontSelection(fontdesc);

	if ( fontdlg.execute() ) {
		FXFont *oldfont = fuente;
		fontdlg.getFontSelection(fontdesc);
		printf("Seleccionada fuente: %s\n", fontdesc.face);
		fuente = new FXFont(getApp(),fontdesc);
		fuente->create();

		if ( fuente == NULL ) {
			printf("Fuente == NULL !!!!\n");
			delete fuente;
			return 0;
			}

		switch ( FXSELID(sel) ) {
			case ID_NEW_FNT_TAB:
				fntTab = fuente;
				miTabla->setFont(fuente);
				break;
			case ID_NEW_FNT_COD:
				fntCod = fuente;
				txtCod->setFont(fuente);
				break;
			case ID_NEW_FNT_GRAM:
				fntGram = fuente;
				txtGram->setFont(fuente);
				break;
			case ID_NEW_FNT_GEN:
				fntGen = fuente;
				txtGen->setFont(fuente);
				break;
			case ID_NEW_FNT_LOG:
				fntLog = fuente;
				txtLog->setFont(fuente);
				break;
			}


		delete oldfont;
		}

	return 1;
	}

/**
 Entrada de menu "Reglas de coloreado".
*/

long guiWindow::onCmdReglas(FXObject *sender, FXSelector sel, void *) {
	dlgReglas dlg(this);
	FXint i;

	// Operamos sobre una copia
	for ( i = 0; i < numReglas; i++ ) {
		dlg.reglas[i].nombre = reglasLog[i].nombre;
		dlg.reglas[i].patron = reglasLog[i].patron;

		dlg.reglas[i].colorFG = estilosLog[i].normalForeColor;
		dlg.reglas[i].colorBG = estilosLog[i].normalBackColor;

		dlg.numReglas = numReglas;
		}

	if ( numReglas == 0 ) {
		// No hay reglas definidas => Regla por defecto
		dlg.reglas[0].nombre = "<Nueva>";
		dlg.reglas[0].patron = "<Patron>";
		dlg.reglas[0].colorFG = FXRGB(0,0,0);
		dlg.reglas[0].colorBG = FXRGB(255,255,255);
		
		dlg.numReglas = 1;
		}


	if ( dlg.execute() ) {
		// Actualizamos las reglas
		for ( i = 0; i < dlg.numReglas; i++ ) {
			reglasLog[i].nombre = dlg.reglas[i].nombre;
			reglasLog[i].patron = dlg.reglas[i].patron;

			// Los ESTILOS de colores deben ir por otro lado
			// reglasLog[i].colorFG = dlg.reglas[i].colorFG;
			// reglasLog[i].colorBG = dlg.reglas[i].colorBG;

			estilosLog[i].normalForeColor = dlg.reglas[i].colorFG;
			estilosLog[i].normalBackColor = dlg.reglas[i].colorBG;
			}

		numReglas = dlg.numReglas;
		}

	
	return 1;
	}


/**
 Entrada de menu "Archivos include" y esquema de Traduccion
*/

long guiWindow::onCmdIncludes(FXObject *sender, FXSelector sel, void *ptr) {
	dlgIncludes dlg(this);

	dlg.nomDatos = incDatos;
	dlg.nomFuncs = incFuncs;
	dlg.nomEsquema = nomEsquema;

	if ( dlg.execute() ) {
		incDatos = dlg.nomDatos;
		incFuncs = dlg.nomFuncs;
		nomEsquema = dlg.nomEsquema;
		}

	return 1;
	}


//////////////////	Funciones actualizacion COLORES		////////////////

/**
 Cambio color Tabla.
 @see Ver el TODO de onUpdColorTab
*/

long guiWindow::onCmdColorTab(FXObject *sender, FXSelector sel, void *ptr) {
	FXint id;

	// Nuevo modo para ahorrar trabajo
	id = FXSELID(sel);
	coloresTab[id - ID_TAB_FG] = (FXColor)(FXuval)ptr;
	miTabla->setColor(id - ID_TAB_FG, (FXColor)(FXuval)ptr);

	return 1;
	}

/**
 Actualizacion color TABLA
*/


long guiWindow::onUpdColorTab(FXObject *sender, FXSelector sel, void *ptr) {
	FXColor clr;
	FXint id;

	id = FXSELID(sel);
	clr = coloresTab[id - ID_TAB_FG];

	sender->handle(this, FXSEL(SEL_COMMAND, ID_SETINTVALUE), (void *)&clr);

	return 1;
	}


/**
 Cambio del color del TEXTO del CODIGO FUENTE.
*/

long guiWindow::onCmdCodFG(FXObject *sender, FXSelector, void *ptr) {
	txtCod->setTextColor((FXColor)(FXuval)ptr);
	return 1;
	}

/**
 Actualizacion del color del TEXTO del CODIGO FUENTE.
*/

long guiWindow::onUpdCodFG(FXObject *sender, FXSelector sel, void *ptr) {
	FXColor color;
	color = txtCod->getTextColor();
	sender->handle(this, FXSEL(SEL_COMMAND, ID_SETINTVALUE)
		,(void*)&color);

	return 1;
	}



/**
 Cambio del color de FONDO para CODIGO FUENTE.
*/

long guiWindow::onCmdCodBG(FXObject *sender, FXSelector, void *ptr) {
	txtCod->setBackColor((FXColor)(FXuval)ptr);
	return 1;
	}

/**
 Actualizacion color FONDO para CODIGO FUENTE.
*/

long guiWindow::onUpdCodBG(FXObject *sender, FXSelector, void *ptr) {
	FXColor color = txtCod->getBackColor();
	sender->handle(this, FXSEL(SEL_COMMAND, ID_SETINTVALUE), (void *)&color);
	return 1;
	}

/**
 Cambio del color para CODIGO FUENTE ACTIVO.
*/

long guiWindow::onCmdCodSelFG(FXObject *sender, FXSelector, void *ptr) {
	// txtCod->setHiliteTextColor((FXColor)(FXuval)ptr);
	// printf("Cambiado color FG FUENTE ACTIVO\n");
	colorCodSelFG = (FXColor)(FXuval)ptr;
	return 1;
	}

/**
 Actualizacion del color para CODIGO FUENTE ACTIVO.
*/

long guiWindow::onUpdCodSelFG(FXObject *sender, FXSelector, void *ptr) {
	// FXColor color = txtCod->getHiliteBackColor();
	sender->handle(this, FXSEL(SEL_COMMAND, ID_SETINTVALUE)
		, (void *)&colorCodSelFG);
	return 1;
	}

/**
 Cambio del color de FONDO para CODIGO FUENTE ACTIVO.
*/

long guiWindow::onCmdCodSelBG(FXObject *sender, FXSelector, void *ptr) {
	// txtCod->setHiliteBackColor((FXColor)(FXuval)ptr);
	// printf("Cambiado color BACK FUENTE ACTIVO\n");
	colorCodSelBG = (FXColor)(FXuval)ptr;
	return 1;
	}

/**
 Actualizacion del color de FONDO para CODIGO FUENTE ACTIVO.
*/

long guiWindow::onUpdCodSelBG(FXObject *sender, FXSelector, void *ptr) {
	sender->handle(this, FXSEL(SEL_COMMAND, ID_SETINTVALUE)
		, (void *)&colorCodSelBG);
	return 1;
	}


/**
 Cambio del color para Cod Fuente Erroneo
*/

long guiWindow::onCmdCodErrFG(FXObject *sender, FXSelector, void *ptr) {
	colorCodErrFG = (FXColor)(FXuval)ptr;
	return 1;
	}

/**
 Actualizacion del color para Cod Fuente Erroneo
*/

long guiWindow::onUpdCodErrFG(FXObject *sender, FXSelector, void *ptr) {
	sender->handle(this, FXSEL(SEL_COMMAND, ID_SETINTVALUE)
		, (void *)&colorCodErrFG);
	return 1;
	}

/**
 Cambio del color de FONDO para Cod Fuente Erroneo
*/

long guiWindow::onCmdCodErrBG(FXObject *sender, FXSelector, void *ptr) {
	colorCodErrBG = (FXColor)(FXuval)ptr;
	return 1;
	}

/**
 Actualizacion del color de FONDO para Cod Fuente Erroneo
*/

long guiWindow::onUpdCodErrBG(FXObject *sender, FXSelector, void *ptr) {
	sender->handle(this, FXSEL(SEL_COMMAND, ID_SETINTVALUE)
		, (void *)&colorCodErrBG);
	return 1;
	}

/**
 Cambio del color FRENTE para Numeros de linea.
*/

long guiWindow::onCmdCodNLinFG(FXObject *sender, FXSelector, void *ptr) {
	colorCodNLinFG = (FXColor)(FXuval)ptr;
	txtCod->setNumberColor(colorCodNLinFG);
	return 1;
	}

/**
 Actualizacion del color FRENTE para Numeros de linea.
*/

long guiWindow::onUpdCodNLinFG(FXObject *sender, FXSelector, void *ptr) {
	sender->handle(this, FXSEL(SEL_COMMAND, ID_SETINTVALUE)
		, (void *)&colorCodNLinFG);
	return 1;
	}

/**
 Cambio del color FONDO para Numeros de linea.
*/

long guiWindow::onCmdCodNLinBG(FXObject *sender, FXSelector, void *ptr) {
	colorCodNLinBG = (FXColor)(FXuval)ptr;
	txtCod->setBarColor(colorCodNLinBG);
	return 1;
	}

/**
 Actualizacion del color FONDO para Numeros de linea.
*/

long guiWindow::onUpdCodNLinBG(FXObject *sender, FXSelector, void *ptr) {
	sender->handle(this, FXSEL(SEL_COMMAND, ID_SETINTVALUE)
		, (void *)&colorCodNLinBG);
	return 1;
	}



/////////////	Colores de la GRAMATICA


/**
 Cambio del color para GRAMATICA.
*/

long guiWindow::onCmdColorGram(FXObject *sender, FXSelector sel, void *ptr) {

	switch( FXSELID(sel) ) {
		case ID_GRAM_FG:
			colorGramFG = (FXColor)(FXuval)ptr;
			txtGram->setTextColor(colorGramFG);
			break;
		case ID_GRAM_BG:
			colorGramBG = (FXColor)(FXuval)ptr;
			txtGram->setBackColor(colorGramBG);
			break;
		case ID_GRAM_ACT_FG:
			colorGramActFG = (FXColor)(FXuval)ptr;
			break;
		case ID_GRAM_ACT_BG:
			colorGramActBG = (FXColor)(FXuval)ptr;
			break;
		}

	return 1;
	}

/**
 Actualizacion del color para GRAMATICA.
*/

long guiWindow::onUpdColorGram(FXObject *sender, FXSelector sel, void *ptr) {
	FXColor color;

	switch( FXSELID(sel) ) {
		case ID_GRAM_FG:
			color = colorGramFG;
			break;
		case ID_GRAM_BG:
			color = colorGramBG;
			break;
		case ID_GRAM_ACT_FG:
			color = colorGramActFG;
			break;
		case ID_GRAM_ACT_BG:
			color = colorGramActBG;
			break;
		}

	sender->handle(this, FXSEL(SEL_COMMAND, ID_SETINTVALUE), (void *)&color);

	return 1;
	}


/**
 Cambio del color del CODIGO GENERADO.
*/

long guiWindow::onCmdColorGen(FXObject *sender, FXSelector sel, void *ptr) {
	
	switch( FXSELID(sel) ) {
		case ID_GEN_FG:
			colorGenFG = (FXColor)(FXuval)ptr;
			txtGen->setTextColor(colorGenFG);
			break;
		case ID_GEN_BG:
			colorGenBG = (FXColor)(FXuval)ptr;
			txtGen->setBackColor(colorGenBG);
			break;
		}

	return 1;
	}

/**
 Actualizacion color CODIGO GENERADO.
*/

long guiWindow::onUpdColorGen(FXObject *sender, FXSelector sel, void *ptr) {
	FXColor color;

	switch( FXSELID(sel) ) {
		case ID_GEN_FG:
			color = colorGenFG;
			break;
		case ID_GEN_BG:
			color = colorGenBG;
			break;
		}

	sender->handle(this, FXSEL(SEL_COMMAND, ID_SETINTVALUE), (void *)&color);

	return 1;
	}


/**
 Cambio en el numero de digitos para Numeros de linea
 del Codigo Fuente.
*/

long guiWindow::onCmdNLinea(FXObject *sender, FXSelector sel, void *ptr) {
	switch( FXSELID(sel) ) {
		case ID_INC_NUM:
				numDig++;
				break;
		case ID_DEC_NUM:
				numDig = (numDig-1<0)?0:(numDig-1);
				break;
		}

	txtCod->setBarColumns(numDig);

	return 1;
	}

////////////////////////////////////////////
//
// Funciones actualizacion BARRA de ESTADO
//
////////////////////////////////////////////


// Actualizacion op en Curso en la barra de estado
/**
 @todo onUpdOperacion La mayoria del codigo YA NO VALE
	Solo hay que pasar el valor de dtsGUI.txtOP
*/

long guiWindow::onUpdOperacion(FXObject *sender, FXSelector, void *) {
	sender->handle(this,FXSEL(SEL_COMMAND,ID_SETSTRINGVALUE)
		,(void*)&(dtsGUI.txtOP));

	return 1;
	}

// Actualizacion Lexema en Barra de estado

long guiWindow::onUpdLexema(FXObject *sender, FXSelector, void *) {
	sender->handle(this, FXSEL(SEL_COMMAND, ID_SETSTRINGVALUE)
			, (void *)&dtsGUI.txtDato);

	}

// Actualizacion resultado operacion en Barra de estado

long guiWindow::onUpdResultado(FXObject *sender, FXSelector, void *) {
	sender->handle(this, FXSEL(SEL_COMMAND, ID_SETSTRINGVALUE)
			, (void *)&dtsGUI.txtRes);
	}

// Actualizacion del Titulo campo Barra estado

long guiWindow::onUpdCaption(FXObject *sender, FXSelector, void *ptr) {
	sender->handle(this, FXSEL(SEL_COMMAND, ID_SETSTRINGVALUE)
		, (void *)&dtsGUI.cptDato);
	return 1;
	}


/**
 Actualizacion texto seleccionado en Cod Fuente.
 @todo Repasar la actualizacion del Highlight...
*/

long guiWindow::onUpdCodigo(FXObject *sender, FXSelector, void *) {

	if ( dtsGUI.iniSel != -1 ) {

		// Solo cambiamos la seleccion si status == 0|-1
		if ( dtsGUI.status == -1 ) {
			// Hubo algun error...
			txtCod->setHiliteTextColor(FXRGB(255,255,255));
			txtCod->setHiliteBackColor(FXRGB(255,25,25));
		} else if ( dtsGUI.status == 0 ) {
			txtCod->setHiliteTextColor(colorCodSelFG);
			txtCod->setHiliteBackColor(colorCodSelBG);
			}

		txtCod->setHighlight(iniSelCod, tamSelCod);

		return 1;

	} else {
		/** @todo Realmente hace falta eliminar el HighLight ??? */
		// txtCod->killHighlight();
		return 0;
		}

	}


/**
 Actualizacion texto seleccionado en la Gramatica.
*/

long guiWindow::onUpdGramatica(FXObject *sender, FXSelector, void *) {
	if ( flagGram ) {
		txtGram->setHiliteTextColor(colorGramActFG);
		txtGram->setHiliteBackColor(colorGramActBG);
		txtGram->setHighlight(posGram, tamGram);
		return 1;
	} else {
		txtGram->killHighlight();
		return 0;
		}
	}


///////////////////		UTILIDADES	/////////////////////////


/**
 Reinicializacion.
 Sincronizacion con el proceso compilador
 @todo Crear nueva funcion "sincronizar" con la parte comun
	a onCmdTerminar
*/

long guiWindow::onCmdReiniciar(FXObject *sender, FXSelector, void *) {
	char msj[4], msjIni[6];
	int nbytes, tam, i, c;
	FXString nuevoCod;


	// Si estamos en medio de una OP la terminamos
	// para sincronizarnos con el hijo

	if ( codOp == OP_PRUEBAS ) {
		gstActual->post();
		// fprintf(stderr, "DEBUG Ejecutado gstActual->POST() antes de Reiniciar\n");
	} else {	
		fprintf(stderr, "\nDEBUG onCmdReiniciar codOp != OP_PRUEBAS\n");
		}


	// Estamos en OP_POST
	// Enviamos msj al hijo para que REINICIE

	strcpy(msj, "REI");
	nbytes = write(pipePH[1], msj, 4 * sizeof(char));

	// Esperamos respuesta
	nbytes = read(pipeHP[0], msj, 4 * sizeof(char));
	printf("\nPADRE recibio respuesta a REI: %s\n", msj);

	////////////////	Limpiar el entorno

	// Limpiamos la tabla

	miTabla->reiniciar();


	// No deberia haber texto seleccionado
	// ya que estamos en OP_POST

	// Si se ha elegido nuevo CODIGO hay que cargarlo...

	if ( status == REINI_COD ) {
		nuevoCod.assign(fCodigo, strlen(fCodigo)+1);
		cargarArchivo(nuevoCod, txtCod);
		}


	// Vuelta a empezar

	/*********
	regTS.lexema = strdup("<NO_APL>");

	if ( regTS.lexema == NULL ) {
		perror("REINI regTS.lexema");
		printf("REINI error mem regTS.lexema");
		}

	codOp = OP_ESPERA;

	cadResultado = "";
	flagResultado = 1;
	cadDatosOp = "<NO_APL>";
	flagLexema = 1;
	**********************************/

	status = LISTO_INICIAR;
	flagTexto = 0;

	// Codigo generado vuelve a estar en blanco...
	/** @todo Podemos hacer esto en onCmdIniciar() */

	flagGen = 0;
	txtGen->removeText(0, txtGen->getLength());

	// y la ventana de MENSAJES del COMPILADOR tambien

	txtLog->removeText(0, txtLog->getLength());

	lineaEstado->setNormalText("Reinicio completo...\n");
	
	return 1;
	}


/*********************************************
  Calculo situacion analisis en fichero YACC
 *********************************************/

void guiWindow::calcPosGram(void) {
	int nbytes, posIni, tamPet;
	char msj[4];
	FXString strNum;

	nbytes = read(pipeHP[0], &posIni, sizeof(int));
	nbytes = read(pipeHP[0], &tamPet, sizeof(int));

	strNum = FXStringVal(posIni);

	// 14 = TamaÃ±o de la parte FIJA de la llamada a informar()
	//    = "informar(, ); "
	posIni += 14;
	posIni += strNum.length();
	strNum = FXStringVal(tamPet);
	posIni += strNum.length();

	posGram = posIni;
	tamGram = tamPet;

	// Centramos el texto en la linea que contiene la peticion
	
	txtGram->setCenterLine(posGram);
	flagGram = 1;

	// Mensaje de respuesta al hijo

	strcpy(msj, "ACK");
	nbytes = write(pipePH[1], msj, 4 * sizeof(char));
	}
