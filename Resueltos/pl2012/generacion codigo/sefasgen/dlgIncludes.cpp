/**
 @file
 Implementacion clase dlgIncludes.
*/

#include "gui.h"
#include "dlgIncludes.h"

// Implementacion

FXIMPLEMENT(dlgIncludes, FXDialogBox,NULL,0)


// Constructor

dlgIncludes::dlgIncludes(guiWindow *owner):FXDialogBox(owner
	,"Cambiar nombre includes",DECOR_TITLE
	|DECOR_BORDER|DECOR_RESIZE,0,0,0,0, 0,0,0,0, 4,4)
	, tgtDatos(nomDatos)
	, tgtFuncs(nomFuncs)
	, tgtEsquema(nomEsquema) {

	FXVerticalFrame  *vert = new FXVerticalFrame(this
		,LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);

	FXHorizontalFrame *h1 = new FXHorizontalFrame(vert
		, LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);

	new FXLabel(h1, "Include para TDAs:", NULL, JUSTIFY_LEFT
		|LAYOUT_CENTER_Y|LAYOUT_CENTER_X
		|LAYOUT_FILL_Y|LAYOUT_FILL_X);

	FXTextField *tfDatos = new FXTextField(h1, 50, &tgtDatos
		, FXDataTarget::ID_VALUE);
	

	FXHorizontalFrame *h2 = new FXHorizontalFrame(vert
		, LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);

	new FXLabel(h2, "Include para Funciones:", NULL, JUSTIFY_LEFT
		|LAYOUT_CENTER_Y|LAYOUT_CENTER_X
		|LAYOUT_FILL_Y|LAYOUT_FILL_X);

	FXTextField *tfFuncs = new FXTextField(h2, 50, &tgtFuncs
		, FXDataTarget::ID_VALUE);

	FXHorizontalFrame *h3 = new FXHorizontalFrame(vert
		, LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);

	new FXLabel(h3, "Esquema de traduccion:", NULL, JUSTIFY_LEFT
		|LAYOUT_CENTER_Y|LAYOUT_CENTER_X
		|LAYOUT_FILL_Y|LAYOUT_FILL_X);

	FXTextField *tfEsq = new FXTextField(h3, 50, &tgtEsquema
		, FXDataTarget::ID_VALUE);

	// Botones Aceptar/Cancelar

	// Parte inferior

	new FXHorizontalSeparator(vert,SEPARATOR_RIDGE|LAYOUT_FILL_X);

	FXHorizontalFrame *closebox = new FXHorizontalFrame(vert
		,LAYOUT_BOTTOM|LAYOUT_FILL_X|PACK_UNIFORM_WIDTH);

	new FXButton(closebox,"&Aceptar",NULL, this, FXDialogBox::ID_ACCEPT
		,BUTTON_INITIAL|BUTTON_DEFAULT|LAYOUT_RIGHT|FRAME_RAISED|FRAME_THICK,0,0,0,0, 20,20);
	new FXButton(closebox,"&Cancelar",NULL, this, FXDialogBox::ID_CANCEL
		,BUTTON_DEFAULT|LAYOUT_RIGHT|FRAME_RAISED|FRAME_THICK,0,0,0,0, 20,20);

	}






