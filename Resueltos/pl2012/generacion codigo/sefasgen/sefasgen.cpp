/**
 @file
 Implementacion de la clase Sefasgen
*/

#include <fx.h>
#include <signal.h>
#include "sefasgen.h"


// Implementacion del objeto
FXIMPLEMENT(Sefasgen, FXApp, NULL, 0)

// Construccion de ventanas
Sefasgen::Sefasgen(const FXString& nomApp, const FXString &nomVendor)
	:FXApp(nomApp, nomVendor)
	{

	// Gestion de señales
	addSignal(SIGINT, this, FXApp::ID_QUIT);

	}

// Destructor
Sefasgen::~Sefasgen(void) {
	printf("Destructor Sefasgen...\n");
	}

/**
 Inicio de la aplicacion.
*/
 
void Sefasgen::init(int& argc, char** argv, FXbool connect){

	FXApp::init(argc,argv,connect);

	}


/**
 Salir
*/

void Sefasgen::exit(FXint code){

  // Escribir el registro y despues salir
  FXApp::exit(code);
  }


