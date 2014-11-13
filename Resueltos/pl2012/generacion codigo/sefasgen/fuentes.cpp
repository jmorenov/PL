/**
 Implementacion dialogo Fuentes.
*/


#include "gui.h"
#include "fuentes.h"


// Implementacion

FXIMPLEMENT(dlgFuentes, FXDialogBox, NULL, 0)

/** Constructor. */

dlgFuentes::dlgFuentes(guiWindow *owner):FXDialogBox(owner,"Cambiar fuentes",DECOR_TITLE
	|DECOR_BORDER|DECOR_RESIZE,0,0,0,0, 0,0,0,0, 4,4) {

	FXVerticalFrame  *vert = new FXVerticalFrame(this,LAYOUT_SIDE_TOP|LAYOUT_FILL_X
		|LAYOUT_FILL_Y);


	FXMatrix *matrix1 = new FXMatrix(vert, 5,MATRIX_BY_ROWS|PACK_UNIFORM_HEIGHT
		|LAYOUT_FILL_X|LAYOUT_FILL_Y|FRAME_THICK|FRAME_RAISED
		,0,0,0,0, 4,4,4,4, 4, 4);

	new FXLabel(matrix1, "Tabla Simbolos:", NULL, JUSTIFY_LEFT|LAYOUT_CENTER_Y
		|LAYOUT_FILL_ROW|LAYOUT_FILL_X);
	new FXLabel(matrix1, "Codigo fuente:", NULL, JUSTIFY_LEFT|LAYOUT_CENTER_Y
		|LAYOUT_FILL_ROW|LAYOUT_FILL_X);
	new FXLabel(matrix1, "Gramatica:", NULL
		, JUSTIFY_LEFT|LAYOUT_CENTER_Y|LAYOUT_FILL_ROW|LAYOUT_FILL_X);
	new FXLabel(matrix1, "Codigo generado:", NULL
		, JUSTIFY_LEFT|LAYOUT_CENTER_Y|LAYOUT_FILL_ROW|LAYOUT_FILL_X);
	new FXLabel(matrix1, "Mensajes Compilador:", NULL
		, JUSTIFY_LEFT|LAYOUT_CENTER_Y|LAYOUT_FILL_ROW|LAYOUT_FILL_X);
	

	// Nombre Fuentes actuales

	FXTextField *tfTab = new FXTextField(matrix1, 30, owner, guiWindow::ID_FNT_TAB);
	tfTab->setEditable(FALSE);
	FXTextField *tfCod = new FXTextField(matrix1, 30, owner, guiWindow::ID_FNT_COD);
	tfCod->setEditable(FALSE);
	FXTextField *tfGram = new FXTextField(matrix1, 30, owner, guiWindow::ID_FNT_GRAM);
	tfGram->setEditable(FALSE);
	FXTextField *tfGen = new FXTextField(matrix1, 30, owner, guiWindow::ID_FNT_GEN);
	tfGen->setEditable(FALSE);
	FXTextField *tfLog = new FXTextField(matrix1, 30, owner, guiWindow::ID_FNT_LOG);
	tfLog->setEditable(FALSE);

	// Botones para cambiar de fuente
	new FXButton(matrix1, "Cambiar", NULL, owner, guiWindow::ID_NEW_FNT_TAB);
	new FXButton(matrix1, "Cambiar", NULL, owner, guiWindow::ID_NEW_FNT_COD);
	new FXButton(matrix1, "Cambiar", NULL, owner, guiWindow::ID_NEW_FNT_GRAM);
	new FXButton(matrix1, "Cambiar", NULL, owner, guiWindow::ID_NEW_FNT_GEN);
	new FXButton(matrix1, "Cambiar", NULL, owner, guiWindow::ID_NEW_FNT_LOG);

	// Botones Aceptar/Cancelar

	new FXHorizontalSeparator(vert,SEPARATOR_RIDGE|LAYOUT_FILL_X);
	FXHorizontalFrame *closebox = new FXHorizontalFrame(vert
		,LAYOUT_BOTTOM|LAYOUT_FILL_X|PACK_UNIFORM_WIDTH);

	new FXButton(closebox,"&Aceptar",NULL,this,FXDialogBox::ID_ACCEPT,BUTTON_INITIAL
		|BUTTON_DEFAULT|LAYOUT_RIGHT|FRAME_RAISED|FRAME_THICK,0,0,0,0, 20,20);
	new FXButton(closebox,"&Cancelar",NULL,this,FXDialogBox::ID_CANCEL,BUTTON_DEFAULT
		|LAYOUT_RIGHT|FRAME_RAISED|FRAME_THICK,0,0,0,0, 20,20);

	}



	
