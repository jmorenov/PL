/***************************************
  Gestor de Operaciones del Compilador
 ***************************************/

#ifndef __GESTOR_OP__
#define __GESTOR_OP__

#include <fx.h>
#include "tabsim.h"
#include "claseTS.h"

#define PRINT 	0
#define SCAN 	1

#define COND 	0
#define INCOND	1

#define ETQ_ENT		0
#define ETQ_SAL		1
#define ETQ_ELSE	2


/**
 Descripcion resultado operacion.
 Valor distintos elementos de la interfaz que
 cambian para reflejar la operacion.
*/

struct datos {
	FXString cptOP;		/**< Caption para la operacion */
	FXString txtOP;		/**< Nombre operacion */
	FXString cptDato;	/**< Caption para datos op */
	FXString txtDato;	/**< Dato de la op: lexema del simbolo
					, tipo de dato... */
	FXString txtRes;	/**< Contenido del campo Resultado */

	FXint iniSel;
	FXint tamSel;

	FXint	status;		/** Resultado de la OP */
	};

typedef struct datos DatosBarra;

/**
 @class gestorOP
 Gestor de operaciones del compilador ( ABSTRACTA ).
*/

class gestorOP {

private:
	FXint 		codigo;		/**< Codigo de operacion */
	DatosBarra	datos;

public:
	gestorOP(FXchar *, FXchar *, FXchar *, FXchar *);
	void setCptOP(FXchar *cpt) { datos.cptOP = cpt; }
	FXString getCptOP(void) { return datos.cptOP; }
	void setTxtOP(FXchar *txt) { datos.txtOP = txt; }
	FXString getTxtOP(void) { return datos.txtOP; }
	void setCptDato(FXchar *cpt) { datos.cptDato = cpt; }
	FXString getCptDato(void) { return datos.cptDato; }
	void setTxtDato(FXchar *txt) { datos.txtDato = txt; }
	FXString getTxtDato(void) { return datos.txtDato; }
	void setTxtRes(FXchar *res) { datos.txtRes = res; }
	FXString getTxtRes(void) { return datos.txtRes; }
	void setIni(int i) { datos.iniSel = i; }
	void setTam(int t) { datos.tamSel = t; }
	void setStatus(FXint s) { datos.status = s; }

	FXint& cod(void) { return codigo; }

	DatosBarra getDatos() { return datos; }

	virtual DatosBarra pre() = 0;
	virtual DatosBarra post() = 0;

};

/**
 @class gestorINS
 Gestor para la Insercion de nuevos Simbolos
*/

class gestorINS : public gestorOP {

private:
	stEntrada reg;
	FXTabSim *tabla;
	int dfIN;		/**< Desc Fichero entrada */
	int dfOUT;		/**< Desc Fichero salida */
public:
	gestorINS(FXTabSim *t, int in, int out);
	virtual DatosBarra pre();
	virtual DatosBarra post();
	// void getSeleccion(int *ini, int *tam);
};


/**
 @class gestorBSIM
 Gestor para la Busqueda de Simbolos
*/

class gestorBSIM : public gestorOP {

private:
	stEntrada reg;
	FXTabSim *tabla;
	int dfIN;		/**< Desc Fichero entrada */
	int dfOUT;		/**< Desc Fichero salida */
public:
	gestorBSIM(FXTabSim *t, int in, int out);
	virtual DatosBarra pre();
	virtual DatosBarra post();
};


/**
 @class gestorBPROC
 Gestor para la Busqueda de Simbolos
*/

class gestorBPROC : public gestorOP {

private:
	stEntrada reg;
	FXTabSim *tabla;
	int dfIN;		/**< Desc Fichero entrada */
	int dfOUT;		/**< Desc Fichero salida */
public:
	gestorBPROC(FXTabSim *t, int in, int out);
	virtual DatosBarra pre();
	virtual DatosBarra post();
};


/**
 @class gestorBPARAM
 Gestor para la Busqueda de Simbolos
*/

class gestorBPARAM : public gestorOP {

private:
	stEntrada reg;
	FXTabSim *tabla;
	int dfIN;		/**< Desc Fichero entrada */
	int dfOUT;		/**< Desc Fichero salida */
public:
	gestorBPARAM(FXTabSim *t, int in, int out);
	virtual DatosBarra pre();
	virtual DatosBarra post();
};


/**
 @class gestorDEL
 Gestor para Sacar Simbolos
*/

class gestorDEL : public gestorOP {

private:
	stEntrada reg;
	FXTabSim *tabla;
	int dfIN;		/**< Desc Fichero entrada */
	int dfOUT;		/**< Desc Fichero salida */
public:
	gestorDEL(FXTabSim *t, int in, int out);
	virtual DatosBarra pre();
	virtual DatosBarra post();
};


/**
 @class gestorVERIF
 Gestor para Verificar Tipos de Dato
*/

class gestorVERIF : public gestorOP {

private:
	stEntrada reg;
	FXTabSim *tabla;
	int dfIN;		/**< Desc Fichero entrada */
	int dfOUT;		/**< Desc Fichero salida */
	unsigned char tDatoAux;	/**< Tipo 2a entrada	*/
public:
	gestorVERIF(FXTabSim *t, int in, int out);
	virtual DatosBarra pre();
	virtual DatosBarra post();
};


/**
 @class gestorTEMP
 Gestor para crear nombres de vars temporales
*/

class gestorTEMP : public gestorOP {

private:
	stEntrada reg;
	FXTabSim *tabla;
	int dfIN;		/**< Desc Fichero entrada */
	int dfOUT;		/**< Desc Fichero salida */
	FXString base;
public:
	gestorTEMP(FXTabSim *t,int in, int out, FXchar *b);
	virtual DatosBarra pre();
	virtual DatosBarra post();
};


/**
 @class gestorCADFMT
 Gestor para crear Cadenas de Formato
*/

class gestorCADFMT : public gestorOP {

private:
	stEntrada reg;
	FXTabSim *tabla;
	int dfIN;		/**< Desc Fichero entrada */
	int dfOUT;		/**< Desc Fichero salida */
	unsigned char tipoES;	/**< Entrada o Salida */
	tDato tipo;
	FXchar *nombre;

public:
	gestorCADFMT(FXTabSim *t, int in, int out);
	virtual DatosBarra pre();
	virtual DatosBarra post();
};


/**
 @class gestorETIQ
 Gestor para crear Nombre de Etiqueta
*/

class gestorETIQ : public gestorOP {

private:
	stEntrada reg;
	FXTabSim *tabla;
	int dfIN;		/**< Desc Fichero entrada */
	int dfOUT;		/**< Desc Fichero salida */
	FXString base;
public:
	gestorETIQ(FXTabSim *t, int in, int out, FXchar *);
	virtual DatosBarra pre();
	virtual DatosBarra post();
};


/**
 @class gestorBUSQ_ETIQ
 Gestor para Busqueda de Etiquetas
*/

class gestorBUSQ_ETIQ : public gestorOP {

private:
	stEntrada reg;
	FXTabSim *tabla;
	int dfIN;		/**< Desc Fichero entrada */
	int dfOUT;		/**< Desc Fichero salida */
	unsigned char tEtiqueta;	/**< Tipo de etiqueta: Entrada, Salida, Else*/


public:
	gestorBUSQ_ETIQ(FXTabSim *t, int in, int out);
	virtual DatosBarra pre();
	virtual DatosBarra post();
};


/**
 @class gestorDEL_CTRL
 Gestor para Busqueda de Etiquetas
*/

class gestorDEL_CTRL : public gestorOP {

private:
	stEntrada reg;
	FXTabSim *tabla;
	int dfIN;		/**< Desc Fichero entrada */
	int dfOUT;		/**< Desc Fichero salida */
	int numReg;		/**< Numero de registros a eliminar */

public:
	gestorDEL_CTRL(FXTabSim *t, int in, int out);
	virtual DatosBarra pre();
	virtual DatosBarra post();
};


/**
 @class gestorGENCOD
 Gestor para la generacion de Codigo

 TODO: Cuidado que esta la funcion generacion
	de codigo Fin Procedimiento !!!!
	NO GENERA CODIGO pero es MUY IMPORTANTE
	para esta CLASE !!!!
*/

class gestorGENCOD : public gestorOP {

private:
	// stEntrada reg;
	// FXTabSim *tabla;
	int dfIN;		/**< Desc Fichero entrada */
	int dfOUT;		/**< Desc Fichero salida */
	FXText *txtMAIN;	/**< Campo de texto para MAIN */
	FXText *txtPROCS;	/**< Campo de texto para PROCedimientoS */
	FXText *txtActual;	/**< Campo de texto en uso */
	unsigned char tipo;	/**< Tipo de codigo a generar */

	int numTabs[2];
	unsigned char destino;
	int pos;		/**< Indica si estamos
					dentro de una declaracion de proc */

	FXbool multiParams;

public:
	gestorGENCOD(FXText *t1, FXText *t2, int in, int out);
	virtual DatosBarra pre();
	virtual DatosBarra post();
	void traducir(void);		/**< Creacion de la traduccion */
	void leerCampo(FXint nc);
};



#endif

