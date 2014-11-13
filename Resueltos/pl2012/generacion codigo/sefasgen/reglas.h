/**
 Cuadro de dialogo de Reglas para Mensajes Compilador.
*/

#ifndef __REGLAS_H__
#define __REGLAS_H__

#include <fx.h>
#include <FXRex.h>
#include <FXDataTarget.h>

#define MAX_NUM_REGLAS 50

class guiWindow;

/**
 Estructura que define una regla de coloreado.
*/

struct stRegla {
	FXString nombre;	/**< Nombre identificativo de la regla */
	FXString patron;	/**< Cuidado que es una cadena. NO es FXRex */
	FXColor colorFG;	/**< Color frente para el texto que encaja */
	FXColor colorBG;	/**< Color fondo para el texto que encaja */
	};


/**
 @class dlgReglas
 Dialogo para gestion de Reglas.
*/

class dlgReglas : public FXDialogBox {

	FXDECLARE(dlgReglas)

public:

	struct stRegla 	reglas[MAX_NUM_REGLAS];	/**< Reglas de coloreado */
	FXint		numReglas;			/**< Num de reglas definidas */

protected:

	FXList		*lstReglas;
	FXTextField 	*tfNombre;
	FXTextField 	*tfPatron;


private:

	FXint		indxRegla;			/**< Regla actual	 */
	FXString 	nomActual;			/**< Nombre regla actual */
	FXString 	patActual; 			/**< Patron regla actual */
	FXColor		fgActual;			/**< Color frente actual */
	FXColor		bgActual;			/**< Color fondo actual */

	/** @name Conectores de datos
	 Permiten actualizacion variables/widgets en sentido bidireccional
	*/
	//@{

	FXDataTarget tgtNombre;
	FXDataTarget tgtPatron;
	FXDataTarget tgtColorFG;
	FXDataTarget tgtColorBG;

	//@}


	dlgReglas(){}
  	dlgReglas(const dlgReglas&);
	dlgReglas& operator=(const dlgReglas&);

public:

	/** Constructor */
	dlgReglas(guiWindow *owner);

	// Owner is text window
	// Adie* getApp() const { return (Adie*)FXDialogBox::getApp(); }

	// Set filename patterns
	// void setPatterns(const FXString& patterns);

	// Get filename patterns
	// FXString getPatterns() const;

	// Set language syntax
	// void setSyntax(FXSyntax* syn);

	// Clean up
	// virtual ~Preferences();

	// Gestion de un nuevo Patron

	long onCmdNewRegla(FXObject *, FXSelector, void *);

	// Borrado de un patron
	long onCmdBorrarRegla(FXObject *, FXSelector, void *);

	// Seleccion y Actualizacion en la lista

	long onCmdIndex(FXObject *, FXSelector, void *);
	long onUpdIndex(FXObject *, FXSelector, void *);

	// Actualizacion Regla
	long onCmdCambio(FXObject *, FXSelector, void *);

	/** Mensajes gestionados por el objeto */
	enum {
		ID_NEW_REGLA = FXDialogBox::ID_LAST,
		ID_DEL_REGLA,
		ID_INDEX,
		ID_CAMBIO_NOM,
		ID_CAMBIO_PAT,
		ID_CAMBIO_FG,
		ID_CAMBIO_BG,
		ID_LAST,
		};

	};


#endif
	
