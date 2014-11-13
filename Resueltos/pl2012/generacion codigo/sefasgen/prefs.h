/**
 Ventana de preferencias.
 Eleccion de colores y Fuentes para SEFASGEN
*/

#ifndef __PREFS_H__
#define __PREFS_H__

#include "fx.h"
#include <FXDialogBox.h>
#include <FXColorDialog.h>
#include <FXColorWell.h>

class guiWindow;

/**
 @class dlgPrefs
 Dialogo de Preferencias.
*/

class dlgPrefs : public FXDialogBox {
  FXDECLARE(dlgPrefs)

protected:

  // FXIcon          *pal;

private:

  dlgPrefs(){};
  dlgPrefs(const dlgPrefs&);
  dlgPrefs& operator=(const dlgPrefs&);

public:

  // Constructor
  dlgPrefs(guiWindow *owner);

  // Destructor
  // virtual ~dlgPrefs();
  };

#endif
	
