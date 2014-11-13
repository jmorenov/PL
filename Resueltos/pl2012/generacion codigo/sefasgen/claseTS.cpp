/**
 Implementacion clase Tabla de Simbolos
*/

#include <string.h>
#include "claseTS.h"

/** Descripciones tipos de la TS */

FXchar *nomTiposTS[] = { "MARCA", "PROC", "VARIABLE", "PAR_FORMAL"
				, "DESC_CTRL", "FUNCION", "RANGO" };


/** Descripcion tipos de dato admitidos por el lenguaje */

FXchar *nomTiposDato[] = { "NO_ASIGNADO", "DESCONOCIDO"
				, "ENTERO", "REAL"
				, "LISTA_REAL", "LISTA_ENTERO"
				, "BOOLEANO", "LISTA_BOOLEANO"
				, "CARACTER", "LISTA_CARACTER"
				, "STRING", "ARRAY", "CJTO", "PILA"
				};

/** Cabecera de las columnas */

FXchar *cabecera[] = { "Lexema", "TipoTS", "Tipo dato", "Num parametros"
		, "Num dimensiones", "Var control", "Etq Entrada"
		, "Etq Salida", "Etq Else"
		};


// Implementacion

FXIMPLEMENT(FXTabSim, FXTable, NULL, 0)

/**
 Constructor.
*/

FXTabSim::FXTabSim(FXComposite *p, FXObject *tgt, FXSelector sel, FXuint opts, FXint x
	, FXint y, FXint w, FXint h, FXint pl, FXint pr, FXint pt, FXint pb) : FXTable(p, tgt
	, sel, opts, x, y, w, h, pl, pr, pt, pb)
	{
	FXint i;
	FXint *clave;

	setTableSize(10,9);

	for ( i = 0; i < 9; i++ )
		setColumnText(i, cabecera[i]);

	tope = -1;
	numRegs = 0;
	bloque = -1;

	bloques = new FXArray<FXint>;

	colores.size(14);
	}

/**
 Destructor.
*/

FXTabSim::~FXTabSim(void) {
	delete bloques;
	}

/**
 Cambio de ALGUN color.
*/

void FXTabSim::setColor(FXint indx, FXColor clr) {
	
	if ( indx == NORMAL_FG ) {
		colores[NORMAL_FG] = clr;
		setTextColor(clr);
	} else if ( indx == NORMAL_BG ) {
		colores[NORMAL_BG] = clr;
		setColorBG(clr);
	} else {
		colores[indx] = clr;
		}

	}

/**
 Cambio del color de fondo de las celdas.
*/

void FXTabSim::setColorBG(FXColor clr) {
	// Probamos con pares/impares

	FXTable::setCellColor(0, 0, clr);
	FXTable::setCellColor(0, 1, clr);
	FXTable::setCellColor(1, 0, clr);
	FXTable::setCellColor(1, 1, clr);
	}



/**
 Limpieza items seleccionados.
*/

void FXTabSim::limpiar(void) {
	FXint sr, er, sc, ec;
	FXint i, j;

	sr = getSelStartRow();
	er = getSelEndRow();
	sc = getSelStartColumn();
	ec = getSelEndColumn();

	printf("ANTES LIMPIAR sr %d er %d sc %d ec %d\n", sr, er, sc, ec);

	/********************
	for ( i = sr; i <= er; i++ )
		for( j = sc; j <= ec; j++ )
			deselectItem(i,j);
	 *******************************************/

	if ( sr != -1 && sc != -1 )
		killSelection();

	/*******************
	sr = getSelStartRow();
	er = getSelEndRow();
	sc = getSelStartColumn();
	ec = getSelEndColumn();

	printf("TRAS KILL SELECTION sr %d er %d sc %d ec %d\n", sr, er, sc, ec);

	if ( sr != -1 && ec != -1 )
		deselectItem(sr, ec);
	*************************************/
	}

/**
 Reiniciar la tabla.

 Eliminar todos los items y poner contadores a 0
*/

void FXTabSim::reiniciar(void) {
	FXint i;

	limpiar();
	clearItems();

	setTableSize(10,9);

	for ( i = 0; i < 9; i++ )
		setColumnText(i, cabecera[i]);

	tope = -1;
	numRegs = 0;

	bloques->clear();
	}

// Cadena correspondiente a un tipo

FXchar *FXTabSim::nombreTipo(tDato t) {
	return nomTiposDato[t];
	}


/**
 Insercion nuevo Simbolo en la TS.
 @param reg Nuevo registro a insertar
 @return Insercion correcta o no
*/

FXbool FXTabSim::intro(stEntrada reg) {
	FXint nFilas, nCols, i, j, npars;
	FXString id;
	FXint colFin, num;
	FXString strAux;
	FXint nuevoBlq;
	FXint indx, fin, posMarca;


	nFilas = getNumRows();

	if ( (tope+1) == nFilas )
		insertRows(nFilas);

	if ( reg.tipoTs == MARCA ) {
		numRegs++;
		tope++;

		posMarca = tope;

		setItemText(tope, COL_LEXEMA, "FIN_PARAMS");
		setItemText(tope, COL_TIPOTS, nomTiposTS[reg.tipoTs]);
		setItemText(tope, COL_NPAR, "<ACTIVOS>");

		// El bloque empieza en la posicion siguiente a la marca
		bloques->append(posMarca+1);

		// Copia de los parametros como variables locales
		indx = tope;
		fin = 0;

		do {

			nFilas = getNumRows();
			if ( (tope+1) == nFilas )
				insertRows(nFilas, 5);

			indx--;
			strAux = getItemText(indx, COL_TIPOTS);
			if ( strcmp(strAux.text(), "PAR_FORMAL") == 0 ) {
				tope++;
				strAux = getItemText(indx, COL_LEXEMA);
				setItemText(tope, COL_LEXEMA, strAux.text());
				setItemText(tope, COL_TIPOTS, "COPIA_PARAM");
				strAux = getItemText(indx, COL_TDATO);
				setItemText(tope, COL_TDATO, strAux.text());
			} else {
				fin = 1;
				}

		} while ( !fin );

				
		itemSelMin = posMarca;
		itemSelMax = tope+1;

		setSelTextColor(colores[NEW_FG]);
		setSelBackColor(colores[NEW_BG]);

		// selectRange(posMarca, tope, COL_LEXEMA, COL_NPAR);
		selectRange(posMarca, tope, COL_LEXEMA, COL_ETQ_ELSE);

		return true;
		}

	if ( reg.tipoTs == DESC_CTRL ) {

		tope++;
		numRegs++;

		setItemText(tope, COL_LEXEMA, reg.lexema);
		setItemText(tope, COL_TIPOTS, nomTiposTS[reg.tipoTs]);
		setItemText(tope, COL_NOM_CTRL, reg.nomVarCtrl);
		setItemText(tope, COL_ETQ_ENT, reg.etqtEnt);
		setItemText(tope, COL_ETQ_SAL, reg.etqtSal);
		setItemText(tope, COL_ETQ_ELSE, reg.etqtElse);

		itemSelMin = tope;
		itemSelMax = tope+1;

		setSelTextColor(colores[NEW_FG]);
		setSelBackColor(colores[NEW_BG]);
		selectRange(tope, tope, COL_LEXEMA, COL_ETQ_ELSE);

		return true;
		}

	// Si es un parametro formal buscamos si el simbolo
	// esta duplicado hasta el proc/funcion

	if ( reg.tipoTs == PAR_FORMAL ) {
		indx = tope;
		strAux = getItemText(indx, COL_TIPOTS);

		while ( compare(strAux.text(), "PAR_FORMAL") == 0 )
			{
			strAux = getItemText(indx, COL_LEXEMA);
			if ( compare(strAux.text(), reg.lexema) == 0 ) {
				// Simbolo duplicado => Lo marcamos
				setSelTextColor(colores[DUP_FG]);
				setSelBackColor(colores[DUP_BG]);

				//selectRange(indx, indx, COL_LEXEMA, COL_TDATO);
				selectRange(indx, indx, COL_LEXEMA, COL_ETQ_ELSE);
				return false;
				}

			strAux = getItemText(--indx, COL_TIPOTS);
			}

		// Solo queda comparar con el proc/funcion
		if ( compare(strAux.text(), "PROC") == 0 ) {
			strAux = getItemText(indx, COL_LEXEMA);
			if ( compare(strAux.text(), reg.lexema) == 0 ) {
				// Simbolo duplicado
				setSelTextColor(colores[DUP_FG]);
				setSelBackColor(colores[DUP_BG]);

				//selectRange(indx, indx, COL_LEXEMA, COL_TDATO);
				selectRange(indx, indx, COL_LEXEMA, COL_ETQ_ELSE);
				return false;
				}
			}

		// Ya podemos insertarlo
		tope++;
		setItemText(tope, COL_LEXEMA, reg.lexema);
		setItemText(tope, COL_TIPOTS, nomTiposTS[reg.tipoTs]);
		setItemText(tope, COL_TDATO, nomTiposDato[reg.tipoDato]);

		// Actualizamos num de parametros del proc
		setItemText(iniProc, COL_NPAR, FXStringVal(++numPar));

		// Seleccionamos nuevo simbolo
		setSelTextColor(colores[NEW_FG]);
		setSelBackColor(colores[NEW_BG]);

		// Otra forma: seleccionar SIEMPRE la fila entera
		//selectRange(tope, tope, COL_LEXEMA, COL_TDATO);
		selectRange(tope, tope, COL_LEXEMA, COL_ETQ_ELSE);

		return true;
		}
				

	// Verificamos que el simbolo NO ha sido declarado previamente
	// => Hasta encontrar MARCA !!!!

	if ( bloques->no() > 0 )
		j = (*bloques)[bloques->no()-1];
	else
		j = 0;


	while ( (j <= tope) && (tope != -1) ) {

		strAux = getItemText(j, COL_TIPOTS);

		/************   Ya no hace falta
		if ( strcmp(strAux.text(), "MARCA") == 0 )
			j++;
		********************************/


		if ( strcmp(reg.lexema, getItemText(j, COL_LEXEMA).text()) == 0 ) {
			// Simbolo ya declarado... Lo Marcamos
			printf("Simbolo repetido: %s y %s\n"
				, getItemText(j, COL_LEXEMA).text(), reg.lexema);

			itemSelMin = j;
			itemSelMax = j+1;

			setSelTextColor(colores[DUP_FG]);
			setSelBackColor(colores[DUP_BG]);

			// selectRange(j, j, COL_LEXEMA, COL_TDATO);
			selectRange(j, j, COL_LEXEMA, COL_ETQ_ELSE);
			return false;
		
		} else {
			j++;
			}

		}

	// Si no lo hemos encontrado podemos insertarlo
	
	numRegs++;
	tope++;

	FXTable::setItemText(tope, COL_LEXEMA, reg.lexema);
	FXTable::setItemText(tope, COL_TIPOTS, nomTiposTS[reg.tipoTs]);
	// FXTable::setItemText(tope, COL_TDATO, nomTiposDato[reg.tipoDato]);

	if ( reg.tipoTs == PROC ) {
		FXTable::setItemText(tope, COL_NPAR, "0");
		iniProc = tope;
		numPar = 0;
		colFin = COL_NPAR;

		/*******************************
		blqAnt = (bloque == -1)?0:bloque;
		bloque = tope;
		nuevoBlq = tope;
		bloques->append(nuevoBlq);
		printf(">> Ini BLOQUE: %d\n", (*bloques)[bloques->no()-1]);
		************************************************************/

	} else if ( reg.tipoTs == PAR_FORMAL ) {
		FXTable::setItemText(tope, COL_TDATO, nomTiposDato[reg.tipoDato]);
		FXTable::setItemText(iniProc, COL_NPAR, FXStringVal(++numPar));
		colFin = COL_TDATO;
	} else {
		FXTable::setItemText(tope, COL_TDATO, nomTiposDato[reg.tipoDato]);
		colFin = COL_TDATO;
		}


	// Seleccionamos nuevo simbolo

	setSelTextColor(colores[NEW_FG]);
	setSelBackColor(colores[NEW_BG]);

	// Otra forma: seleccionar SIEMPRE la fila entera
	// selectRange(tope, tope, COL_LEXEMA, colFin);
	selectRange(tope, tope, COL_LEXEMA, COL_ETQ_ELSE);

	itemSelMin = tope;
	itemSelMax = tope+1;

	return true;
	}

/**
 Busqueda de un simbolo en la TS.
 @param id lexema del simbolo buscado
 @return Tipo de dato del Simbolo DESC si no se encuentra
*/

tDato FXTabSim::buscarSIM(char *id) {
	FXint i, j, num, fin;
	FXString nomTipo;
	FXString strAux;
	FXint *tipo;
	FXchar clave[20];

	j = tope;

	while ( j > 0 ) {

		// Los parametros formales NO sirven
		fin = 0;
		do {

			strAux = getItemText(j, COL_TIPOTS);
			if ( strcmp(strAux.text(), "PAR_FORMAL") != 0 )
				fin = 1;
			else
				j--;

		} while ( fin == 0 );

		strAux = getItemText(j, COL_LEXEMA);

		if ( strcmp(strAux.text(), id) == 0 ) {

			nomTipo = getItemText(j, COL_TDATO);

			for ( i = 0
				; strcmp(nomTipo.text(), nomTiposDato[i]) != 0
				; i++ );

			printf("Encontrado %s tipo: %d\n", id, i);

			// Seleccionamos el item encontrado en la TS
			setSelTextColor(colores[SIM_FG]);
			setSelBackColor(colores[SIM_BG]);
			// selectRange(j, j, COL_LEXEMA, COL_TDATO);
			selectRange(j, j, COL_LEXEMA, COL_ETQ_ELSE);
			itemSelMin = j;
			itemSelMax = j+1;

			return (tDato)i;

		} else {
			j--;
			}
		}

	return DESC;
	}


/**
 Marcar los simbolos a eliminar.
 Simbolos definidos en el bloque actual
 Buscar hasta encontrar una MARCA con PARAMETROS ACTIVOS !!!!
*/

void FXTabSim::marcar(void) {
	FXint i;
	FXint filaFin, filaIni;
	FXint iniLocales;
	FXint blqActual;

	setSelTextColor(colores[DEL_FG]);
	setSelBackColor(colores[DEL_BG]);

	if ( bloques->no() == 0 ) {
		printf("ACCESO A BLOQUES VACIO!!!\n");
		blqActual = 2;
	} else {
		blqActual = (*bloques)[bloques->no()-1];
		}

	selectRange(blqActual-1, tope, COL_LEXEMA, COL_ETQ_ELSE);

	return;
	}

/**
 Eliminar simbolos del bloque actual
*/

void FXTabSim::sacar(void) {
	FXint iniLocales;
	FXint blqActual;

	if ( bloques->no() == 0 )
		printf("ACCESO A BLOQUES VACIO en sacar()!!!\n");

	blqActual = (*bloques)[bloques->no()-1];
	printf("blqActual: %d tope: %d\n", blqActual, tope);

	removeRows(blqActual-1, tope-blqActual+2);
	bloques->remove(bloques->no()-1);
	tope = blqActual-2;

	if ( bloques->no() > 0 )
		printf("Tras SACAR blqActual: %d\n", (*bloques)[bloques->no()-1]);


	return;
	}

/**
 Buscar un procedimiento en la TS.
 Selecciona el procedimiento para busqueda de 
 parametros posterior.
 @return Num de parametros del procedimiento
	-1 si no esta declarado
*/

int FXTabSim::buscarPROC(char *lex) {
	FXint index;
	FXString lexAct;
	FXString strNParam;

	index = tope;

	do {
		lexAct = getItemText(index, COL_TIPOTS);

		printf("Index: %d TipoTS: %s\n", index, lexAct.text());

		/** @todo Tener en cuenta las FUNCIONES */
		if ( compare(lexAct.text(), "PROC") == 0 ) {
			lexAct = getItemText(index, COL_LEXEMA);
			printf("Es un PROC >> Lexema: %s\n", lexAct.text());
			if ( compare(lexAct.text(), lex) == 0 ) {
				// Encontrado...
				iniProc = index;
				posParam = iniProc+1;
				strNParam = getItemText(index, COL_NPAR);
				numPar = FXIntVal(strNParam.text());

				// Lo marcamos
				setSelTextColor(colores[PROC_FG]);
				setSelBackColor(colores[PROC_BG]);
				selectRange(index, index
					, COL_LEXEMA, COL_ETQ_ELSE);

				return numPar;
				}
			}

		index--;

	} while ( index > -1 );

	return -1;
	}


/**
 Busqueda del tipo de un parametro.
 @return Resultado puede ser:
		0 - Ok
		1 - Numero de argumentos incorrecto
		2 - Tipo incorrecto
*/

FXint FXTabSim::buscarPARAM(tDato tipo) {
	FXint resultado, i;
	tDato tipoParam;

	if ( posParam > iniProc + numPar )
		return 1;

	// Seleccionamos el parametro formal comparado
	setSelTextColor(colores[PARAM_FG]);
	setSelBackColor(colores[PARAM_BG]);
	selectRange(posParam, posParam, COL_LEXEMA, COL_ETQ_ELSE);


	// Busqueda inversa...
	/** @todo Usar un hash para convertir Nombres en Numeros */

	for ( i = 0
		; strcmp(nomTiposDato[i]
		, getItemText(posParam, COL_TDATO).text()) != 0
		; i++);

	tipoParam = (tDato)i;

	posParam++;

	if ( tipo == tipoParam )
		return 0;
	else
		return 2;
	}

		
/**
 Busqueda de una etiqueta correspondiente
 al ultimo Descriptor de Control
 @param tipo Tipo de etiqueta buscada
*/

char *FXTabSim::buscarETQ(unsigned char tipo) {
	FXString strAux;
	FXint index;
	char *nom;

	index = tope;

	do {
		strAux = getItemText(index, COL_TIPOTS);
		if ( strcmp(strAux.text(), "DESC_CTRL") == 0 ) {
			switch( tipo ) {
				case ETQ_ENT:
					strAux = getItemText(index, COL_ETQ_ENT);
					break;
				case ETQ_SAL:
					strAux = getItemText(index, COL_ETQ_SAL);
					break;
				case ETQ_ELSE:
					strAux = getItemText(index, COL_ETQ_ELSE);
					break;
				default:
					printf("Tipo de etiqueta NO VALIDO!!!\n");
					return NULL;
					break;
				}

			nom = (char *) malloc ((strAux.length()+1) * sizeof(char));
			if ( nom == NULL ) {
				// perror("Mem dinamica NOMBRE ETIQUETA");
				nom = (char *) malloc(3 * sizeof(char));
				strcpy(nom, "EM");
				return nom;
				}

			strcpy(nom, strAux.text());
			return nom;
			}

		index--;

	} while ( index > -1 );

	nom = (char *) malloc(3 * sizeof(char));
	strcpy(nom, "EB");

	return nom;
	}

/**
 Seleccionar elementos a sacar hasta el ultimo Desc de Control.
 @return Num de registros a eliminar
*/

int FXTabSim::marcarCTRL(void) {
	FXint index, num;
	FXString strAux;

	index = tope+1;

	do {
		index--;
		strAux = getItemText(index, COL_TIPOTS);

	} while ( strcmp(strAux.text(), "DESC_CTRL") != 0 );

	num = tope-index+1;
	indexCtrl = index;

	setSelTextColor(colores[DEL_FG]);
	setSelBackColor(colores[DEL_BG]);
	selectRange(index, tope, COL_LEXEMA, COL_ETQ_ELSE);

	return num;
	}

/**
 Sacar hasta el ultimo Desc. de Control.
*/

void FXTabSim::sacarCTRL(void) {

	printf("indexCtrl: %d tope: %d\n", indexCtrl, tope);

	// removeRows(indexCtrl, tope-indexCtrl+1);
	removeRows(indexCtrl);

	tope = indexCtrl-1;

	printf("Nuevo tope: %d\n", tope);
	}






	
