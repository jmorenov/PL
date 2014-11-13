/**
 @file
 Interfaz grafico para la gestion TS.
*/

#include <fx.h>
#include <FXTable.h>
#include <FXText.h>
#include <FXArray.h>
#include <FXFont.h>
#include <FXFontDialog.h>
#include <FXObjectList.h>
#include <FXRex.h>
#include <FXString.h>
#include <FXPNGIcon.h>
#include "reglas.h"
#include "claseTS.h"

#include "gestorOP.h"

/** @name Constantes Estado Interfaz */
//@{

#define PENDIENTE 	0
#define LISTO_INICIAR	1
#define LISTO_PASO	2
#define TERMINADO	3
#define COMPILADOR_OK	4
#define CODIGO_OK	5
#define REINI_COMP	6
#define REINI_COD	7

//@}

/** @name Constantes de operacion TS
@todo Eliminarlas !!! Ya no se utilizan!!! */
//@{

#define OP_PRUEBAS	500

#define OP_ESPERA 	0
#define OP_POST 	1
#define OP_INTRO 	2
#define OP_SACAR 	3
#define OP_BUSCAR_PROC 	4
#define OP_BUSCAR_PARAM 5
#define OP_BUSCAR_SIM 	6
#define OP_VERIF_TIPO 	7
#define FIN_COMPILACION 8


//@}

/**
@name Constantes operacion Generacion Codigo
@todo Eliminarlas !!! Ya no se utilizan!!! 
*/
//@{

#define OP_GEN_TEMP	9
#define OP_GEN_CADFMT	10
#define OP_GEN_ETQ	11
#define OP_BUSQ_ETQ	12
#define OP_SACAR_CTRL	13

#define OP_GEN_INI 	14
#define OP_GEN_FIN 	15
#define OP_GEN_DEC_VAR 	16
#define OP_GEN_INIBLQ 	17
#define OP_GEN_FINBLQ 	18
#define OP_GEN_ASIG	19
#define OP_GEN_ES	20
#define OP_GEN_SALTO	21
#define OP_GEN_ESCETQ	22
#define OP_GEN_DEC_PROC 23
#define OP_GEN_PARAM	24
#define OP_GEN_FIN_CAB	25
#define OP_GEN_FIN_DEC_PROC	26
#define OP_GEN_CALL_PROC	27



//@}


// Constantes varias

#define COL_TABULADOR 4

// Nombres de las columnas en la tabla GUI
// y de los tipos 
/** @todo Eliminar nombres columnas... YA NO SE USAN!!! */
#define COL_LEXEMA 	0
#define COL_TENT 	1
#define COL_TDATO 	2
#define COL_NPAR	3


/**
 @class guiWindow.

 Ventana principal, gestion comunicacion y demas
*/


class guiWindow : public FXMainWindow {

	// Macro para declaracion jerarquia de clases
	FXDECLARE(guiWindow)

private:

	FXVerticalFrame 	*logFrame;	// Marco logs
	FXVerticalFrame		*tablaFrame;	// Marco tabla
	FXVerticalFrame		*codFrame;	// Marco para COD FUENTE
	FXVerticalFrame		*gramFrame;	// Marco para GRAMATICA
	FXVerticalFrame		*genFrame;	// Marco para COD GENERADO
	FXVerticalFrame		*txtLogFrame;
	FXVerticalFrame		*procFrame;	// Marco para COD PROCS

	FXTable			*tabla;		// GUI Tabla de simbolos
	FXMenuBar		*menubar;
	FXMenuPane		*filemenu;
	FXMenuPane		*prefsmenu;
	FXMenuPane		*genmenu;
	FXStatusBar		*statusbar;	// Barra de estado
	FXStatusLine		*lineaEstado;	// Linea de la barra
	FXSplitter		*splitter;
	FXSplitter		*splitA;
	FXTabBook		*libro;
	FXTabItem		*tabCod;
	FXTabItem		*tabGram;
	FXTabItem		*tabGen;
	FXTabItem		*tabProc;

	FXchar *rutaCompilador;
	FXchar *fCompilador;
	FXchar *fCodigo;
	FXchar *fGramatica;

	int			status;		// Estado compilacion
	int			codOp;		// Op en curso
	int			itemSelMin;	// Item seleccionado
	int			itemSelMax;	// Idem...

	FXToolBar		*barraOp;	// Barra de herramientas
						// para op compilacion
	FXText			*txtCod;	// Texto para CODIGO
	FXText			*txtGram;	// Idem GRAMATICA
	FXText			*txtGen;	// Idem COD GENERADO

	FXText			*txtLog;	// Mensajes del compilador
	FXText			*txtProcs;	// Declaracion procs

	/** @name Iconos Barra de Herramientas */
	//@{
	
	FXIcon			*icoIni;
	FXIcon			*icoPaso;
	FXIcon			*icoFin;
	FXIcon			*icoNxtBreak;

	FXIcon			*icoIncNum;
	FXIcon			*icoDecNum;

	FXIcon			*icoNewBreak;

	//@}

	int			flagLexema;	// Indica si debe cambiar
						// lexema en barra de estado
	unsigned char		flagResultado;	// Idem para Resultado op
	unsigned char		flagTexto;	// Indica texto insertado...
	FXString		cadResultado;
	unsigned char		flagGram;	// Gramatica Cargada ??
	FXint			posGram;
	FXint			tamGram;
	FXString		cadCaption;
	FXString		cadDatosOp;	// Datos relativos Op TS

	FXint			nivTab;		// Niv Tabulacion GEN COD
	FXint			nivTab2;	// Niv Tabulacion COD FUNCIONES
	FXchar			flagGen;	/**< Se genero codigo? */
	FXchar			flagFunc;	/**< Generacion de funciones */

	FXString		incDatos;
	FXString		incFuncs;


	/** Posicion de inicio de la seleccion en COD FUENTE */
	/** @todo Limpiar ESTO Ya no debe hacer FALTA !!!! */
	// FXint			iniSel;
	/** Numero de caracteres de la seleccion en COD FUENTE */
	// FXint			tamSel;

	FXToolBar		*barraCod;	/**< Barra de Herramientas para codigo */
	FXint			breaks[10];	/**< Breakpoints */
	FXint			numBreaks;	/**< Num breakpoints establecidos */
	FXint			sigBreak;	/**< Indice siguiente breakpoint */
	FXbool			flagAuto;	/**< Compilacion hasta breakpoint? */


	/** @todo Los arrays de pueden definir dinamicamente !!!! */

	struct stRegla		reglasLog[MAX_NUM_REGLAS];	/**< Reglas de coloreado LOG    */
	FXint			numReglas;			/**< Numero de reglas definidas */
	FXHiliteStyle		estilosLog[MAX_NUM_REGLAS];	/**< Estilos de coloreado
									para mensajes
									del compilador */
	FXHiliteStyle		estiloBreak;			/**< Estilo BREAKPOINTS */

	FXTabSim		*miTabla;
	FXint			numDig;		/**< Num digitos para numeros de linea */

	/** @name Gestores de operacion */
	//@{

	gestorOP		*gestores[20];
	gestorOP		*gstActual;
	FXint			numGestores;

	DatosBarra		dtsGUI;		/**< Valor elementos GUI a actualizar */
	FXint			iniSelCod;	/**< Posicion inicio seleccion en Codigo */
	FXint			tamSelCod;	/**< Tam seleccion en Codigo */

	FXString		nomEsquema;	/**< Nombre del archivo que describe
							el esquema de traduccion */

	//@}

	/** @todo Array de colores para Codigo y Gramatica ?? */

	/** @name Colores Tabla de Simbolos */
	//@{
	FXArray<FXColor>	coloresTab;
	//@}

	/** @name Colores Cod. Fuente */
	//@{
	FXColor			colorCodFG;
	FXColor			colorCodBG;
	FXColor			colorCodSelFG;
	FXColor			colorCodSelBG;
	FXColor			colorCodErrFG;
	FXColor			colorCodErrBG;
	FXColor			colorCodNLinFG;
	FXColor			colorCodNLinBG;
	//@}

	/** @name Colores Gramatica */
	//@{
	FXColor			colorGramFG;
	FXColor			colorGramBG;
	FXColor			colorGramActFG;
	FXColor			colorGramActBG;
	//@}

	/** @name Colores Cod. Generado */
	//@{
	FXColor			colorGenFG;
	FXColor			colorGenBG;
	//@}

	/** @name Fuentes configurables */
	//@{
	FXFont			*fntTab;
	FXFont			*fntCod;
	FXFont			*fntGram;
	FXFont			*fntGen;
	FXFont			*fntLog;
	//@}


protected:

	guiWindow(){}
	// virtual ~guiWindow();

public:

	long onCmdIniciar(FXObject *, FXSelector, void *);
	long onUpdIniciar(FXObject *, FXSelector, void *);
	long onCmdPaso(FXObject *, FXSelector, void *);
	long onUpdPaso(FXObject *, FXSelector, void *);
	long onRcvPipe(FXObject *, FXSelector, void *);
	long onCmdAbrirCompilador(FXObject *, FXSelector, void *);
	long onCmdAbrirCodigo(FXObject *, FXSelector, void *);
	long onCmdAbrirGramatica(FXObject *, FXSelector, void *);

	/** @name Gestion campos de la Barra de estado */
	//@{
	long onUpdOperacion(FXObject *, FXSelector, void *);
	long onUpdLexema(FXObject *, FXSelector, void *);
	long onUpdResultado(FXObject *, FXSelector, void *);
	long onUpdCaption(FXObject *, FXSelector, void *);
	//@}

	long onUpdCodigo(FXObject *, FXSelector, void *);
	long onCmdReiniciar(FXObject *, FXSelector, void *);
	long onCmdTerminar(FXObject *, FXSelector, void *);
	long onRcvErr(FXObject *, FXSelector, void *);
	long onUpdGramatica(FXObject *, FXSelector, void *);

	long onCmdGuardar(FXObject *, FXSelector, void *);

	long onCmdSetBreak(FXObject *, FXSelector, void *);
	long onUpdSetBreak(FXObject *, FXSelector, void *);

	long guiWindow::onUpdNxtBreak(FXObject *sender, FXSelector, void *);
	long guiWindow::onCmdNxtBreak(FXObject *sender, FXSelector, void *);

	/** @name Gestion de breaks */
	//@{

	void iniciar(void);
	long chkBreak(FXObject *sender, FXSelector, void *);
	long ejecutarPRE(FXObject *sender, FXSelector, void *);
	long ejecutarPOST(FXObject *sender, FXSelector, void *);

	//@}


	long guiWindow::onCmdPrefs(FXObject *sender, FXSelector, void *);
	long guiWindow::onCmdFuentes(FXObject *sender, FXSelector, void *);
	long guiWindow::onCmdGuardarPrefs(FXObject *sender, FXSelector, void *);

	/**
	 @name Funciones para gestion de Fuentes
	*/
	//@{

	long guiWindow::onUpdLeerFuentes(FXObject *sender, FXSelector, void *);

	FXString guiWindow::leerFuente(FXuint idGUI);
	long guiWindow::onCmdCambiarFnt(FXObject *sender, FXSelector, void *);

	//@}

	long guiWindow::onCmdReglas(FXObject *sender, FXSelector sel, void *);

	long guiWindow::onCmdIncludes(FXObject *sender, FXSelector sel, void *);


	/**
	 @name Funciones Cambio colores del interfaz
	 @todo Juntar todas las funciones en 2 tal y como se hace para
		la gramatica
	*/
	//@{

	/********   Gestion colores TABLA	*****************/

	long guiWindow::onCmdColorTab(FXObject *sender, FXSelector, void *);
	long guiWindow::onUpdColorTab(FXObject *sender, FXSelector, void *);


	/*********   Gestion colores CODIGO FUENTE	****************/

	long guiWindow::onCmdCodFG(FXObject *, FXSelector, void *);
	long guiWindow::onUpdCodFG(FXObject *, FXSelector, void *);
	long guiWindow::onCmdCodBG(FXObject *, FXSelector, void *);
	long guiWindow::onUpdCodBG(FXObject *, FXSelector, void *);
	long guiWindow::onCmdCodSelFG(FXObject *, FXSelector, void *);
	long guiWindow::onUpdCodSelFG(FXObject *, FXSelector, void *);
	long guiWindow::onCmdCodSelBG(FXObject *, FXSelector, void *);
	long guiWindow::onUpdCodSelBG(FXObject *, FXSelector, void *);

	long guiWindow::onCmdCodErrFG(FXObject *, FXSelector, void *);
	long guiWindow::onUpdCodErrFG(FXObject *, FXSelector, void *);
	long guiWindow::onCmdCodErrBG(FXObject *, FXSelector, void *);
	long guiWindow::onUpdCodErrBG(FXObject *, FXSelector, void *);

	long guiWindow::onCmdCodNLinFG(FXObject *, FXSelector, void *);
	long guiWindow::onUpdCodNLinFG(FXObject *, FXSelector, void *);

	long guiWindow::onCmdCodNLinBG(FXObject *, FXSelector, void *);
	long guiWindow::onUpdCodNLinBG(FXObject *, FXSelector, void *);

	/***********   Gestion de colores de la GRAMATICA	*******/

	long guiWindow::onCmdColorGram(FXObject *, FXSelector, void *);
	long guiWindow::onUpdColorGram(FXObject *, FXSelector, void *);

	/*****   Idem para el CODIGO GENERADO	********/

	long guiWindow::onCmdColorGen(FXObject *, FXSelector, void *);
	long guiWindow::onUpdColorGen(FXObject *, FXSelector, void *);

	//@}

	long guiWindow::onCmdNLinea(FXObject *, FXSelector, void *);


	// Utilidades
	FXbool cargarArchivo(FXString, FXText *);
	FXbool guardarArchivo(FXString file, FXText *);
	// FXbool reiniciar(void);
	void calcPosGram(void);
	FXbool nuevoBreak(FXint pos);
	void leerRegistro(void);
	void escribirRegistro(void);

	// Creacion del ARRAY de GESTORES

	void crearGestores();

	
	/** @name Gestion grafica operaciones TS */
	/** @todo Eliminar TOOOODAS estas funciones innecesarias */
	//@{
	// Operaciones basicas
	// Ahora tenemos gestorOP !!!!

	// Generacion de codigo
	// FXint gestMsjGen(void);
	// long pre_genIni(void);
	// FXint post_genIni(void);
	// long pre_genFin(void);
	// FXint post_genFin(void);
	// long pre_genDecVar(void);
	// FXint post_genDecVar(void);

	// Funciones relacionadas con la generacion de
	// codigo que NO generan codigo
	// long pre_genNomTemp(void);
	// FXint post_genNomTemp(void);
	// long pre_genCadFmt(void);
	// FXint post_genCadFmt(void);
	// long pre_genEtiqueta(void);
	// FXint post_genEtiqueta(void);
	// long pre_sacarCtrl(void);
	// FXint post_sacarCtrl(void);
	// long pre_busqEtq(void);
	// FXint post_busqEtq(void);

	/*************
	long pre_genAsig(void);
	FXint post_genAsig(void);
	long pre_genIniBlq(void);
	FXint post_genIniBlq(void);
	long pre_genFinBlq(void);
	FXint post_genFinBlq(void);
	long pre_genES(void);
	FXint post_genES(void);
	long pre_genSalto(void);
	FXint post_genSalto(void);
	long pre_genEscEtq(void);
	FXint post_genEscEtq(void);

	long pre_genDecProc(void);
	FXint post_genDecProc(void);

	long pre_genDecParam(void);
	FXint post_genDecParam(void);

	long pre_genFinCabecera(void);
	FXint post_genFinCabecera(void);

	long pre_genFinDecProc(void);
	FXint post_genFinDecProc(void);

	long pre_genLlamada(void);
	FXint post_genLlamada(void);
	*********************************/
	//@}

	/** @name Funciones para el PARSER */
	//@{

	void leerEsquema(FXString nom);

	//@}

	/** @name Identificadores de mensajes FOX
	 Usos varios, entre otros indicar cuando un widget cambia
	 o debe actualizarse y actuar ante pulsaciones de botones/menus.
	*/
	//@{

	enum {
		ID_INICIAR = FXMainWindow::ID_LAST,
		ID_PASO,
		ID_PIPE,
		ID_ABRIR_COMP,
		ID_ABRIR_COD,
		ID_ABRIR_GRAM,
		ID_OPERACION,
		ID_LEXEMA,
		ID_RESULTADO,
		ID_TXTCOD,
		ID_REINICIAR,
		ID_TERMINAR,
		ID_ERR,
		ID_TXTGRAM,
		ID_TXTGEN,
		ID_PANEL,
		ID_CAPLEX,
		ID_GUARDAR_GEN,
		ID_SET_BREAK,
		ID_NXT_BREAK,
		ID_PREFS,
		ID_GUARDAR_PREFS,

		ID_TAB_FG,
		ID_TAB_BG,
		ID_TAB_NEW_FG,
		ID_TAB_NEW_BG,
		ID_TAB_SIM_FG,
		ID_TAB_SIM_BG,
		ID_TAB_DEL_FG,
		ID_TAB_DEL_BG,
		ID_TAB_DUP_FG,
		ID_TAB_DUP_BG,
		ID_TAB_PROC_FG,
		ID_TAB_PROC_BG,
		ID_TAB_PARAM_FG,
		ID_TAB_PARAM_BG,

		ID_COD_FG,
		ID_COD_BG,
		ID_COD_SEL_FG,
		ID_COD_SEL_BG,
		ID_COD_ERR_FG,
		ID_COD_ERR_BG,
		ID_COD_NLIN_FG,
		ID_COD_NLIN_BG,

		ID_GRAM_FG,
		ID_GRAM_BG,
		ID_GRAM_ACT_FG,
		ID_GRAM_ACT_BG,
		ID_GEN_FG,
		ID_GEN_BG,
		ID_FUENTES,
		ID_FNT_TAB,
		ID_NEW_FNT_TAB,
		ID_FNT_COD,
		ID_NEW_FNT_COD,
		ID_FNT_GRAM,
		ID_NEW_FNT_GRAM,
		ID_FNT_GEN,
		ID_NEW_FNT_GEN,
		ID_FNT_LOG,
		ID_NEW_FNT_LOG,
		ID_REGLAS,

		ID_FIN_AUTOPASO,
		ID_EXEC_PRE,
		ID_EXEC_POST,

		ID_INC_NUM,
		ID_DEC_NUM,

		ID_INCLUDES,

		ID_LAST
		};

	//@}

	guiWindow(FXApp *);
	virtual void create();
	virtual ~guiWindow();
};



