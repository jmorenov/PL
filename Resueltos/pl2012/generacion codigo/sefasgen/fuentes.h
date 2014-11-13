/**
 Ventana de cambio de Fuentes.
*/

#ifndef __FUENTES_H__
#define __FUENTES_H__

#include <fx.h>
#include <FXDialogBox.h>

class guiWindow;

class dlgFuentes : public FXDialogBox {

	FXDECLARE(dlgFuentes)

protected:

  // FXIcon          *pal;

private:

  dlgFuentes(){};
  dlgFuentes(const dlgFuentes&);
  dlgFuentes& operator=(const dlgFuentes&);

public:

  // Crear dialogo Fuentes
 dlgFuentes(guiWindow *owner);

  // Propietario es la guiWindow
  // FXApp* getApp() const { return FXDialogBox::getApp(); }


  // Clean up
  // virtual ~Prefs();
  };

#endif
	


