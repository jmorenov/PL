/**
 Dialogo para nombre de los includes
*/

#ifndef __DLG_INCLUDES_H__
#define __DLG_INCLUDES_H__

#include "fx.h"
#include <FXDialogBox.h>

class guiWindow;

/**
 @class dlgIncludes
 Dialogo para definir nombres de los Includes
*/

class dlgIncludes : public FXDialogBox {
  FXDECLARE(dlgIncludes)

protected:

  // FXIcon          *pal;

private:

	FXDataTarget	tgtDatos;
	FXDataTarget	tgtFuncs;
	FXDataTarget	tgtEsquema;

	dlgIncludes(){};
	dlgIncludes(const dlgIncludes&);
	dlgIncludes& operator=(const dlgIncludes&);

public:

	FXString nomDatos;
	FXString nomFuncs;
	FXString nomEsquema;

	// Constructor
	dlgIncludes(guiWindow *owner);

	// Destructor
	// virtual ~dlgIncludes();
};


#endif
	
