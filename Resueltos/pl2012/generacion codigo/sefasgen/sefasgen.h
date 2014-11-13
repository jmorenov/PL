/****************
 Clase SEFASGEN
 *****************/

#ifndef __SEFASGEN_H__
#define __SEFASGEN_H__

#include <fx.h>

/** @class Sefasgen
 Clase principal aplicacion
*/

class Sefasgen : public FXApp {

	FXDECLARE(Sefasgen)

private:
	Sefasgen(){}
	Sefasgen(const Sefasgen&);
	Sefasgen& operator=(const Sefasgen&);
	/** @todo Utilizar algo como esto para comprobar
		si el Esquema de Traduccion ha sido cargado

	FXbool loadSyntaxFile(const FXString& file);
	*/

/***
public:
  enum{
    ID_CLOSEALL=FXApp::ID_LAST,
    ID_LAST
    };
public:
  long onCmdCloseAll(FXObject*,FXSelector,void*);
******************/

public:

	// Constructor del objeto aplicacion
	Sefasgen(const FXString& nomAplicacion, const FXString& nomVendedor);

	// Inicializar la aplicacion
	virtual void init(int& argc,char** argv,FXbool connect=TRUE);

	// Terminar la aplicacion
	virtual void exit(FXint code=0);

	// Destructor
	virtual ~Sefasgen();

};


#endif

