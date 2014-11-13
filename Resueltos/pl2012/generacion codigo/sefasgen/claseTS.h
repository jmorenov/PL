/**
 @class FXTabSim
 Tabla de Simbolos.
*/

#ifndef __CLASE_TS__
#define __CLASE_TS__


#include <fx.h>
#include <FXTable.h>
#include <FXString.h>
#include <FXArray.h>
#include <FXHash.h>
#include "tabsim.h"

#define ETQ_ENT		0
#define ETQ_SAL		1
#define ETQ_ELSE	2


class FXTabSim : public FXTable {

	FXDECLARE(FXTabSim)

private:

	FXint numRegs;		/**< Numero de registros		*/
	FXint tope;		/**< Indice ultimo registro		*/
	FXint bloque;		/**< Indice Bloque actual		*/
	FXint blqAnt;		/**< Indice Bloque Anterior		*/
	FXint iniProc;		/**< Indice procedimiento actual 	*/
	FXint numPar;		/**< Numero de parametros proc actual 	*/
	FXint posParam;		/**< Posicion parametro actual		*/

	FXint itemSelMin;	/**< Indice Primer Item seleccionado 	*/
	FXint itemSelMax;	/**< Indice Ultimo Item seleccionado 	*/


	FXArray<FXColor> colores;	/**< Todos los colores configurables	*/
	FXArray<FXint> *bloques;	/**< Pila de bloques */

	FXint indexCtrl;		/**< Indice ultimo Desc. de Control	*/

	/** Indice de columna para los campos de registro */

	enum {
		COL_LEXEMA = 0
		, COL_TIPOTS
		, COL_TDATO
		, COL_NPAR
		, COL_NDIM
		, COL_NOM_CTRL
		, COL_ETQ_ENT
		, COL_ETQ_SAL
		, COL_ETQ_ELSE
		};


protected:

	FXTabSim(){}
	FXTabSim(const FXTabSim&){}

public:

	FXTabSim::FXTabSim(FXComposite *p, FXObject *tgt=NULL, FXSelector sel=0, FXuint opts=0
		, FXint x=0, FXint y=0, FXint w=0, FXint h=0, FXint pl=DEFAULT_MARGIN
		, FXint pr=DEFAULT_MARGIN, FXint pt=DEFAULT_MARGIN, FXint pb=DEFAULT_MARGIN);

	virtual ~FXTabSim();
	void limpiar(void);		/**< De-seleccionar items */
	void reiniciar(void);		/**< Limpiar toda la tabla */
	FXchar *nombreTipo(tDato t);	/**< Devolver Nombre de dato */


	/** @name Gestion de colores */
	//@{

	/** Gestion de TODOS los colores */

	void setColor(FXint indx, FXColor clr);
	void setColorBG(FXColor clr);

	//@}

	/** @name Operaciones gestion Simbolos */
	//@{

	FXbool intro(stEntrada reg);
	tDato buscarSIM(char *lex);
	void marcar(void);
	void sacar(void);
	int buscarPROC(char *lex);
	FXint buscarPARAM(tDato tipo);
	char *buscarETQ(unsigned char tipo);
	int marcarCTRL(void);
	void sacarCTRL(void);

	//@}


	/**
	 Indice de colores
	 @sa Enumeracion de guiWindow El ORDEN debe ser el MISMO !!!
	*/

	enum {
		NORMAL_FG,
		NORMAL_BG,
		NEW_FG,
		NEW_BG,
		SIM_FG,
		SIM_BG,
		DEL_FG,
		DEL_BG,
		DUP_FG,
		DUP_BG,
		PROC_FG,
		PROC_BG,
		PARAM_FG,
		PARAM_BG,
		};





};

#endif
