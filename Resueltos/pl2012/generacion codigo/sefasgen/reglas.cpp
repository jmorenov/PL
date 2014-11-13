/**
 Implementacion clase dlgReglas.
*/

#include <fx.h>
#include <FXRex.h>
#include <FXArray.h>
#include "reglas.h"
#include "gui.h"

// Mensajes y funciones encargadas de gestionarlos...

FXDEFMAP(dlgReglas) dlgReglasMap[] = {

// ________Tipo Mensaje________________ID______Manejador Mensaje
FXMAPFUNC(SEL_COMMAND, dlgReglas::ID_NEW_REGLA, dlgReglas::onCmdNewRegla),
FXMAPFUNC(SEL_COMMAND, dlgReglas::ID_DEL_REGLA, dlgReglas::onCmdBorrarRegla),
FXMAPFUNC(SEL_COMMAND, dlgReglas::ID_INDEX, dlgReglas::onCmdIndex),
FXMAPFUNC(SEL_UPDATE, dlgReglas::ID_INDEX, dlgReglas::onUpdIndex),
FXMAPFUNC(SEL_COMMAND, dlgReglas::ID_CAMBIO_NOM, dlgReglas::onCmdCambio),
FXMAPFUNC(SEL_COMMAND, dlgReglas::ID_CAMBIO_PAT, dlgReglas::onCmdCambio),
FXMAPFUNC(SEL_COMMAND, dlgReglas::ID_CAMBIO_FG, dlgReglas::onCmdCambio),
FXMAPFUNC(SEL_COMMAND, dlgReglas::ID_CAMBIO_BG, dlgReglas::onCmdCambio),
};


// Implementacion

FXIMPLEMENT(dlgReglas, FXDialogBox, dlgReglasMap, ARRAYNUMBER(dlgReglasMap))


/**
 Constructor.
*/

dlgReglas::dlgReglas(guiWindow *owner):FXDialogBox(owner,"Reglas",DECOR_TITLE|DECOR_BORDER
	|DECOR_RESIZE)
	{
	FXint i;


	// Interior
	FXVerticalFrame *vert = new FXVerticalFrame(this
		,LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);

	FXHorizontalFrame *horiz = new FXHorizontalFrame(vert
		, LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);

	// Lista de items creados y botones

	FXGroupBox *gbItems = new FXGroupBox(horiz,"Reglas creadas",FRAME_GROOVE|LAYOUT_LEFT
		|LAYOUT_FILL_Y,0,0,0,0, 4,4,4,4, 4, 4);

	FXHorizontalFrame *frmBotones = new FXHorizontalFrame(gbItems, LAYOUT_BOTTOM|LAYOUT_FILL_X);
	new FXButton(frmBotones, "Nueva", NULL, this, dlgReglas::ID_NEW_REGLA
		, LAYOUT_LEFT|FRAME_RAISED);
	new FXButton(frmBotones, "Eliminar", NULL, this, dlgReglas::ID_DEL_REGLA
		, LAYOUT_LEFT|FRAME_RAISED);

	lstReglas = new FXList(gbItems, this, dlgReglas::ID_INDEX
		,LIST_BROWSESELECT|HSCROLLER_NEVER|LAYOUT_FIX_WIDTH|LAYOUT_TOP|LAYOUT_FILL_Y
		, 0, 0, 150, 400);


	// Datos Regla Actual
	// Conectamos a la copia local del Dialogo
	indxRegla = 0;
	nomActual = reglas[0].nombre;
	patActual = reglas[0].patron;
	fgActual = reglas[0].colorFG;
	bgActual = reglas[0].colorBG;

	tgtNombre.connect(nomActual);
	tgtNombre.setTarget(this);
	tgtNombre.setSelector(ID_CAMBIO_NOM);

	tgtPatron.connect(patActual);
	tgtPatron.setTarget(this);
	tgtPatron.setSelector(ID_CAMBIO_PAT);

	tgtColorFG.connect(fgActual);
	tgtColorFG.setTarget(this);
	tgtColorFG.setSelector(ID_CAMBIO_FG);

	tgtColorBG.connect(bgActual);
	tgtColorBG.setTarget(this);
	tgtColorBG.setSelector(ID_CAMBIO_BG);


	FXVerticalFrame *vertDatos = new FXVerticalFrame(horiz, LAYOUT_LEFT|LAYOUT_FILL_Y);

	new FXLabel(vertDatos, "Nombre");
	tfNombre = new FXTextField(vertDatos, 20, &tgtNombre, FXDataTarget::ID_VALUE);
	tfNombre->setText("<Nuevo>");

	new FXLabel(vertDatos, "Patron");
	tfPatron = new FXTextField(vertDatos, 20, &tgtPatron, FXDataTarget::ID_VALUE);
	tfPatron->setText("<Patron>");

	FXMatrix *matColores = new FXMatrix(vertDatos, 2);

	new FXLabel(matColores, "Color Frente:");
	new FXLabel(matColores, "Color Fondo:");	

	new FXColorWell(matColores,FXRGB(0,0,0), &tgtColorFG, FXDataTarget::ID_VALUE
		,FRAME_SUNKEN|FRAME_THICK
		|LAYOUT_LEFT|LAYOUT_CENTER_Y|LAYOUT_FIX_WIDTH|LAYOUT_FIX_HEIGHT
		|LAYOUT_FILL_ROW,0,0,40,24);


	new FXColorWell(matColores,FXRGB(255,255,255), &tgtColorBG, FXDataTarget::ID_VALUE
		,FRAME_SUNKEN|FRAME_THICK
		|LAYOUT_LEFT|LAYOUT_CENTER_Y|LAYOUT_FIX_WIDTH|LAYOUT_FIX_HEIGHT
		|LAYOUT_FILL_ROW,0,0,40,24);
	
	// Parte inferior

	new FXHorizontalSeparator(vert,SEPARATOR_RIDGE|LAYOUT_FILL_X);

	FXHorizontalFrame *closebox = new FXHorizontalFrame(vert
		,LAYOUT_BOTTOM|LAYOUT_FILL_X|PACK_UNIFORM_WIDTH);

	new FXButton(closebox,"&Aceptar",NULL, this, FXDialogBox::ID_ACCEPT
		,BUTTON_INITIAL|BUTTON_DEFAULT|LAYOUT_RIGHT|FRAME_RAISED|FRAME_THICK,0,0,0,0, 20,20);
	new FXButton(closebox,"&Cancelar",NULL, this, FXDialogBox::ID_CANCEL
		,BUTTON_DEFAULT|LAYOUT_RIGHT|FRAME_RAISED|FRAME_THICK,0,0,0,0, 20,20);

	}


/**
 Insercion de un nuevo patron.
 Se actualiza la FXList y la lista de Reglas de la Aplicacion
*/

long dlgReglas::onCmdNewRegla(FXObject *sender, FXSelector sel, void *) {
	FXString nombre, patron;
	FXColor fg, bg;

	numReglas++;
	nombre = "<Nuevo>";
	patron = "<Nuevo patron>";
	fg = FXRGB(0, 0, 0);
	bg = FXRGB(255, 255, 255);

	indxRegla = numReglas-1;

	reglas[indxRegla].nombre = nombre;
	reglas[indxRegla].patron = patron;
	reglas[indxRegla].colorFG = fg;
	reglas[indxRegla].colorBG = bg;

	nomActual = reglas[indxRegla].nombre;
	patActual = reglas[indxRegla].patron;
	fgActual = fg;
	bgActual = bg;

	lstReglas->appendItem(nombre);
	lstReglas->selectItem(indxRegla);

	return 1;
	}

/**
 Borrado de la regla Actual.
*/

long dlgReglas::onCmdBorrarRegla(FXObject *sender, FXSelector, void *) {
	FXint i, j;

	// Borrado de la lista
	lstReglas->removeItem(indxRegla);

	// Actualizamos la lista de patrones

	numReglas--;

	for( i = indxRegla; i < numReglas; i++ ) {
		// printf("reglas[%d].nombre = %s ", i, reglas[i].nombre.text());
		reglas[i].nombre = reglas[i+1].nombre;
		// printf(" >>> %s\n", reglas[i].nombre.text());
		reglas[i].patron = reglas[i+1].patron;
		reglas[i].colorFG = reglas[i+1].colorFG;
		reglas[i].colorBG = reglas[i+1].colorBG;

		lstReglas->setItem(i, reglas[i+1].nombre);
		}

	if ( indxRegla == numReglas )
		indxRegla = numReglas-1;

	nomActual = reglas[indxRegla].nombre;
	patActual = reglas[indxRegla].patron;
	fgActual = reglas[indxRegla].colorFG;
	bgActual = reglas[indxRegla].colorBG;

	return 1;
	}


/**
 Seleccion en la lista de patrones.
*/

long dlgReglas::onCmdIndex(FXObject *sender, FXSelector sel, void *) {

	indxRegla = lstReglas->getCurrentItem();

	nomActual = reglas[indxRegla].nombre;
	patActual = reglas[indxRegla].patron;
	fgActual = reglas[indxRegla].colorFG;
	bgActual = reglas[indxRegla].colorBG;

	return 1;
	}


/**
 Actualizacion elementos de la lista.
*/

long dlgReglas::onUpdIndex(FXObject *sender, FXSelector sel, void *) {
	FXint i, tam;

	tam = lstReglas->getNumItems();
	

	if ( tam < numReglas )
		for ( i = 0; i < numReglas; i++ )
			lstReglas->insertItem(i, reglas[i].nombre);
	else
		for ( i = 0; i < numReglas; i++ )
			lstReglas->setItem(i, reglas[i].nombre);

	return 1;
	}

/**
 Gestion del cambio de algun elemento de una regla.
 @todo Se puede comprobar si el Patron es correcto con FXRex::parse !!!!
*/

long dlgReglas::onCmdCambio(FXObject *sender, FXSelector sel, void *) {

	// Actualizamos el nombre correspondiente

	switch( FXSELID(sel) ) {
		case ID_CAMBIO_NOM:
			reglas[indxRegla].nombre = nomActual;
			break;
		case ID_CAMBIO_PAT:
			reglas[indxRegla].patron = patActual;
			break;
		case ID_CAMBIO_FG:
			reglas[indxRegla].colorFG = fgActual;
			break;
		case ID_CAMBIO_BG:
			reglas[indxRegla].colorBG = bgActual;
			break;
		}


	return 1;
	}


