%{
/*********************************************************
**
** Fichero: PRUEBA.Y
** Función: Pruebas de YACC para practicas de PL
**
********************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
void yyerror( char * msg ) ;
int linea_actual = 1 ;
int linea_si;

typedef enum {
	parametro_formal, // si es parametro formal	
	marca, //marca comienzo bloque
	procedimiento, //si es subprograma
	variable, // si es variable	
} tipoEntrada;

typedef enum {
	entero,
	real,
	caracter,
	booleano,
	array,
	desconocido,
	no_asignado
}dtipo ;

typedef struct {
	tipoEntrada entrada ;
	char *nombre;
	dtipo tipoDato;
	unsigned int parametros;
	unsigned int dimensiones;
	int TamDimen1;
	int TamDimen2;
} entradaTS ;

#define MAX_TS 500
unsigned int TOPE=0,top=-1,topArray=-1; /* Tope de la pila */
unsigned int subProg=0; /* Indicador de comienzo de bloque de un subprog */
unsigned int decVar=0,dim,tamdim1,tamdim2;
unsigned int proc = 0,posParam = 0;
char idProc[100];

entradaTS TS[MAX_TS]; /* Pila de la tabla de símbolos */
entradaTS TP[MAX_TS];
entradaTS TA[MAX_TS];
dtipo tipoTMP,tipoArray;

typedef struct {
	int atrib;  /* Atributo del símbolo (si tiene) */
	char *lexema; /* Nombre del lexema */
	dtipo tipo; /* Tipo del símbolo */
	dtipo tipoArray;
	unsigned int dimensiones;
	int TamDimen1;
	int TamDimen2;
} atributos;

#define YYSTYPE atributos //a partir de esta definición cada tipo tiene estructura de atributos

void TS_InsertaMARCA()
{
	if(TOPE != 0) TOPE++;

	TS[TOPE].entrada = marca;
	TS[TOPE].nombre = "MARCA_INICIAL";

	if(subProg == 1){
		int topeTMP = TOPE;
		while(TS[topeTMP].entrada != procedimiento && topeTMP > 0)
		{	//printf("tope = %d, parametro = %s\n",topeTMP,TS[topeTMP].nombre);
			if(TS[topeTMP].entrada == parametro_formal)
			{	
				TOPE++;
				TS[TOPE].entrada = parametro_formal;
				TS[TOPE].nombre = TS[topeTMP].nombre;
				TS[TOPE].tipoDato = TS[topeTMP].tipoDato;

				if(TS[topeTMP].tipoDato == array)
				{	TS[TOPE].dimensiones = TS[topeTMP].dimensiones;
					TS[TOPE].TamDimen1 = TS[topeTMP].TamDimen1;
					TS[TOPE].TamDimen2 = TS[topeTMP].TamDimen2;
				}
			}
			topeTMP--;
		}
	}
}

void TS_VaciarENTRADAS()
{	/*printf("%d. %d: %s\n",TOPE,TS[TOPE].entrada,TS[TOPE].nombre);
	printf("____________________________\n");
	
	int topeTMP = TOPE;
	
	while( topeTMP >= 0){
		
		printf("%d. %d: %s",topeTMP,TS[topeTMP].entrada,TS[topeTMP].nombre);
		if(TS[topeTMP].entrada == array)
		{	printf(" %d: %d: %d",TS[topeTMP].dimensiones,TS[topeTMP].TamDimen1,TS[topeTMP].TamDimen2);
		}
		if(TS[topeTMP].entrada == procedimiento)
		{	printf(" %d: ",TS[topeTMP].parametros);
		}
		printf("\n");		
		topeTMP--;
	}
	printf("____________________________\n");*/
	
	while(TS[TOPE].entrada != marca) {TOPE--;}
	TOPE--;
}

void TS_InsertaSubprog(atributos a){

	TOPE++;
	TS[TOPE].entrada = procedimiento;
	TS[TOPE].nombre = a.lexema;
	TS[TOPE].parametros = 0;

	top++;
	TP[top].entrada = procedimiento;
	TP[top].nombre = a.lexema;
	TP[top].parametros = 0;	
}
void TS_InsertaParam(atributos a){

	TOPE++;	
	TS[TOPE].entrada = parametro_formal;
	TS[TOPE].nombre = a.lexema;
	TS[TOPE].tipoDato = a.tipo;

	top++;
	TP[top].entrada = parametro_formal;
	TP[top].nombre = a.lexema;
	TP[top].tipoDato = a.tipo;

	int topeTMP = TOPE;

	while(TS[topeTMP].entrada != procedimiento && topeTMP >= 0){	
		topeTMP--;
	}
	TS[topeTMP].parametros++;

	topeTMP = top;

	while(TP[topeTMP].entrada != procedimiento){	
		topeTMP--;
	}
	TP[topeTMP].parametros++;

	/*topeTMP = top;

	while( topeTMP >= 0){
		
		printf("%d. %d: %s",topeTMP,TP[topeTMP].entrada,TP[topeTMP].nombre);
		if(TP[topeTMP].entrada == procedimiento)
		{	printf(" %d: ",TP[topeTMP].parametros);
		}
		printf("\n");		
		topeTMP--;
	}
	printf("____________________________\n");*/
}
void TS_InsertaIdent(atributos a){

	TOPE++;	
	TS[TOPE].entrada = variable;
	TS[TOPE].nombre = a.lexema;
	TS[TOPE].tipoDato = tipoTMP;
	
	if(TS[TOPE].tipoDato == array)
	{	TS[TOPE].entrada = array;
		TS[TOPE].dimensiones = dim;
		TS[TOPE].TamDimen1 = tamdim1;
		TS[TOPE].TamDimen2 = tamdim2;
		topArray++;		
		TA[topArray].entrada = variable;
		TA[topArray].nombre = a.lexema;
		TA[topArray].tipoDato = tipoArray;
		TA[topArray].dimensiones = dim;
		TA[topArray].TamDimen1 = tamdim1;
		TA[topArray].TamDimen2 = tamdim2;
		
	}
}
void existeVar(atributos a)
{	
	int topeTMP = TOPE ;
	
	while(TS[topeTMP].entrada != marca && topeTMP >= 0)
	{	
		if(TS[topeTMP].entrada == parametro_formal)
		{
			if(strcmp(TS[topeTMP].nombre, a.lexema) == 0)
			{
				fprintf(stderr,"[Linea %d]: %s: existe.\n",linea_actual,a.lexema);
			}
		}
		topeTMP--;
	}
}
void existeProc(atributos a)
{	
	int topeTMP = TOPE ,existe=0;
	
	while(topeTMP >= 0 && existe == 0)
	{	
		if( !strcmp(a.lexema,TS[topeTMP].nombre) )
		{
			existe=1;
		}
		topeTMP--;
	}
	if(existe == 0){
		fprintf(stderr,"[Linea %d]: %s: no existe o fuera de ambito.\n",linea_actual,a.lexema);
	}
}

void verificaNumPar(unsigned int num)
{
	int topeTMP = top, existe = 0;
	
	while( existe == 0 && topeTMP>=0)
	{	if( !strcmp(TP[topeTMP].nombre,idProc) ){
			existe = 1;
		}
		else{
			topeTMP--;
		}
	}
	if(existe == 1){
		if(TP[topeTMP].parametros != num){
			fprintf(stderr,"[Linea %d]: %s: numero de  parametros incorrecto.\n",linea_actual,TP[topeTMP].nombre);
		}
	}
}
void verificaParam(atributos a,unsigned int pos)
{
	int topeTMP = top ;
	
	while(strcmp(TP[topeTMP].nombre,idProc) && topeTMP>=0)
	{	
		topeTMP--;
	}

	if(topeTMP>=0){
		if(pos <= TP[topeTMP].parametros){
			if ( TP[topeTMP+pos].tipoDato == real && a.tipo == entero ){
				a.tipo = real;
			}
			//printf("param: %d: ,tipo = %d. lexema:%s, tipo= %d \n",pos,TP[topeTMP+pos].tipoDato,a.lexema,a.tipo);
			if(TP[topeTMP].parametros==0){
				fprintf(stderr,"[Linea %d]: %s: no tiene parametros.\n",linea_actual,TP[topeTMP].nombre);
			}
			else if (TP[topeTMP+pos].tipoDato != a.tipo ){
					fprintf(stderr,"[Linea %d]:tipo del %dº parametro incompatible.\n",linea_actual,pos);
			}
		}
	}
}
unsigned int asignaTipo(atributos a)
{
	int topeTMP = TOPE ;
	unsigned int tipo = -1;
	int existe = 0;

	while( existe == 0 && topeTMP>=0)
	{	if ( !strcmp(TS[topeTMP].nombre,a.lexema) ){
			existe = 1;
			tipo = TS[topeTMP].tipoDato;
		}
		topeTMP--;
	}
	
	return tipo;
}
unsigned int asignaTipoArray(atributos a)
{
	int topeTMP = topArray ;
	unsigned int tipo = -1;
	int existe = 0;

	while( existe == 0 && topeTMP>=0)
	{		//printf("%s, tipo = %d\n",TA[topeTMP].nombre,TA[topeTMP].tipoDato);
			if ( !strcmp(TA[topeTMP].nombre,a.lexema) ){
			existe = 1;
			tipo = TA[topeTMP].tipoDato;
		}
		topeTMP--;
	}
	//printf("_____________________\n");
	return tipo;
}
int tempDimen1 = 0, tempDimen2 = 0;

unsigned int compruebaTipos(atributos a,atributos op, atributos b)
{
	unsigned int tipo = 10;
	int topeTMP = TOPE;
	int indice_a = topArray, indice_b = topArray;
	int existeArray = 0;
	int existe = 0;

	while( existe == 0 && topeTMP>=0)
	{	if ( !strcmp(TS[topeTMP].nombre,a.lexema) ){
			existe = 1;
			tipo = TS[topeTMP].tipoDato;
		}
		topeTMP--;
	}

	//printf("%s, tipo = %d--%s, tipo = %d\n",a.lexema,a.tipo,b.lexema,b.tipo);
	if(existe){
		if(a.tipo == array){
			while( existeArray == 0 && indice_a>=0)
			{		
				if ( !strcmp(TA[indice_a].nombre,a.lexema) ){
					existeArray = 1;			
					a.tipo = TA[indice_a].tipoDato;
				}
				else{	indice_a--;}
			}
		}
		if(existeArray && b.tipo == array){
			
			existeArray=0;
			while( existeArray == 0 && indice_b>=0)
			{	if ( !strcmp(TA[indice_b].nombre,b.lexema) ){
					existeArray = 1;
				}
				else{	indice_b--;}
			}
			//
			//printf("%s[%d,%d]\n",TA[indice_b].nombre,TA[indice_b].TamDimen1,TA[indice_b].TamDimen2);
			if(existeArray){
				
				b.tipo = TA[indice_b].tipoDato;
						
				tempDimen1 = TA[indice_a].TamDimen1;
				tempDimen2 = TA[indice_b].TamDimen2;
			}
			if ( a.tipo == real && b.tipo == entero ){
				b.tipo = real;
			}
			if ( a.tipo == entero && b.tipo == real ){
				a.tipo = real;
			}
		}
		if ( a.atrib > b.atrib ){
			if ( a.tipo == real && b.tipo == entero ){
				b.tipo = real;
			}
		}
		if ( b.atrib > a.atrib ){
			if ( a.tipo == entero && b.tipo == real ){
				a.tipo = real;
			}
		}
		
		if(a.tipo != b.tipo){
			fprintf(stderr,"[Linea %d]: tipos incompatible\n",linea_actual);
		}
		else{
			tipo = a.tipo;		
		}
		if(op.tipo == booleano) tipo = booleano;
	}
	else
	{	fprintf(stderr,"[Linea %d]: %s no existe\n",linea_actual,a.lexema);
	}

	return tipo;
}
unsigned int compruebaTipos2(atributos a,atributos op, atributos b)
{
	unsigned int tipo = 10;
	int existe = 0;
	int topeTMP = TOPE ;

	int indice_a = topArray, indice_b = topArray;
	int existeArray = 0;

	while( existe == 0 && topeTMP>=0)
	{	if ( !strcmp(TS[topeTMP].nombre,a.lexema) ){
			existe = 1;
			tipo = TS[topeTMP].tipoDato;
		}
		topeTMP--;
	}
	if(existe){
		if(a.tipo == array){
			while( existeArray == 0 && indice_a>=0)
			{		
				if ( !strcmp(TA[indice_a].nombre,a.lexema) ){
					existeArray = 1;
					a.tipo = TA[indice_a].tipoDato;
				}
				else{	indice_a--;}
			}
			if(TA[indice_a].TamDimen1 != tempDimen1 || TA[indice_a].TamDimen2 != tempDimen2)
			{	fprintf(stderr,"[Linea %d]: dimensiones incompatibles\n",linea_actual);
			}	
		}
	
		if ( a.atrib > b.atrib ){
			if ( a.tipo == real && b.tipo == entero ){
				b.tipo = real;
			}
		}
		if ( b.atrib > a.atrib ){
			if ( a.tipo == entero && b.tipo == real ){
				a.tipo = real;
			}
		}
		if(a.tipo != b.tipo){
			fprintf(stderr,"[Linea %d]: tipos incompatible\n",linea_actual);
		}
		else{
			tipo = a.tipo;		
		}
		if(op.tipo == booleano) tipo = booleano;
	}
	else
	{			fprintf(stderr,"[Linea %d]: %s no existe\n",linea_actual,a.lexema);
	}
	return tipo;
}
%}

%error-verbose

%token PRINCIPAL
%token PROCEDIMIENTO
%token TIPO
%token CONST	
%token ASIG	
%token MASMENOS
%token OPUNARIO
%token PARIZQ
%token PARDER
%token INIBLQ
%token FINBLQ
%token BEG
%token END
%token COMA
%token PYC
%token SI
%token SINO	
%token MIENTRAS
%token HACER
%token HASTA
%token ENT
%token SAL
%token IDENT
%token CORCHETEIZQ
%token CORCHETEDER
%token CADENA
%token ANDLOG
%token ORLOG
%token OREXCL
%token OPIG
%token OPREL
%token OPMUL

%left ORLOG
%left ANDLOG
%left OREXCL
%left OPIG
%left OPREL
%left MASMENOS
%left OPMUL
%right OPUNARIO
%%
/**
Sección de producciones que definen la gramática.
**/

Programa : Cabecera_programa bloque;
Cabecera_programa : PRINCIPAL PARIZQ PARDER;
bloque :	INIBLQ { TS_InsertaMARCA(); } Declar_de_variables_locales Declar_de_subprogs Sentencias FINBLQ { TS_VaciarENTRADAS(); }
			;
Declar_de_subprogs : Declar_de_subprogs Declar_de_subprog
							|
							;
Declar_de_subprog : Cabecera_subprog {subProg = 1;} bloque {subProg = 0;} 
							;
Cabecera_subprog : 	PROCEDIMIENTO IDENT PARIZQ {TS_InsertaSubprog($2);} parametros PARDER
							| PROCEDIMIENTO IDENT PARIZQ PARDER {TS_InsertaSubprog($2);}
							;
parametros:	parametros COMA TIPO IDENT {TS_InsertaParam($4);}
				| TIPO IDENT {TS_InsertaParam($2);}
				| error
				;

Declar_de_variables_locales : BEG { decVar = 1; } Variables_locales END { decVar = 0; }
										|
										;

Variables_locales :	Variables_locales Cuerpo_declar_variables 
							| Cuerpo_declar_variables
							;
Cuerpo_declar_variables :  TIPO {tipoTMP = $1.tipo;tipoArray = $1.tipo;} lista_nombres PYC 
									|  error  
										//{fprintf(stderr,"[Linea %d]: %s no es un tipo.\n",linea_actual,$1.lexema);}
									;
lista_nombres:	lista_nombres COMA id_array 
					{ if(decVar){existeVar($3);
						TS_InsertaIdent($3);}
					}
					| id_array
					{ if(decVar){ existeVar($1);
						TS_InsertaIdent($1);}
					}
					| error
					;
id_array:	IDENT
				| array
				;
array:	IDENT CORCHETEIZQ CONST CORCHETEDER 
			{tipoTMP = array;dim = 1;tamdim1=atoi($3.lexema);tamdim2=0;}
			| IDENT CORCHETEIZQ CONST COMA CONST CORCHETEDER 
				{tipoTMP = array;dim = 2;tamdim1=atoi($3.lexema);tamdim2=atoi($5.lexema);}
			;
Sentencias : Sentencias Sentencia | Sentencia;

Sentencia :	bloque
				| sentencia_asignacion
				| sentencia_if
				| sentencia_while
				| sentencia_entrada
				| sentencia_salida
				| sentencia_hacer_hasta
				| llamada_procedimiento
				| error
				;
sentencia_asignacion : id_posArray ASIG expresion PYC
								{$$.tipo =  compruebaTipos2($1,$2,$3);}
								;

sentencia_if :	SI PARIZQ expresion PARDER	Sentencia 
					{if($3.tipo != booleano) 
						fprintf(stderr,"[Linea %d]: no hay expresion tipo logica \n",linea_si);}
					| SI PARIZQ expresion PARDER
					  Sentencia sentencia_else 
					{if($3.tipo != booleano) 
						fprintf(stderr,"[Linea %d]: no hay expresion tipo logica \n",linea_si);}					
					;
sentencia_else : SINO Sentencia;

sentencia_while : MIENTRAS PARIZQ expresion PARDER Sentencia 
						{if($3.tipo != booleano) 
							fprintf(stderr,"[Linea %d]: no hay expresion tipo logica \n",linea_si);}
						;

sentencia_entrada : ENT lista_nombres PYC;

sentencia_salida : SAL exp_cadenas PYC;

sentencia_hacer_hasta : HACER Sentencia HASTA expresion PYC
								{if($4.tipo != booleano) 
									fprintf(stderr,"[Linea %d]: no hay expresion tipo logica \n",linea_si);}
								;

llamada_procedimiento : IDENT PARIZQ { strcpy(idProc,$1.lexema); proc =1; existeProc($1); }
								 expresiones PARDER PYC 
								{proc = 0; verificaNumPar(posParam); posParam=0;}
							
								| IDENT PARIZQ {strcpy(idProc,$1.lexema); proc =1; existeProc($1); } PARDER PYC 
								{proc = 0; verificaNumPar(posParam); posParam=0;}
								;

expresiones : expresiones COMA expresion 
					{	if(proc == 1) 
						{	posParam++;
							verificaParam($3,posParam);
						}
					}
					| expresion
						{	if(proc == 1) 
							{	posParam++;
								verificaParam($1,posParam);
							}
						}
					;

expresion :   	PARIZQ expresion PARDER 
					{	$$.tipo = $2.tipo;					
					} 
					| OPUNARIO expresion 
					{	$$.tipo = $2.tipo;
						}
					| expresion OPREL expresion 
					{	$$.tipo =  compruebaTipos($1,$2,$3);
					}
					| expresion OPMUL expresion 
					{	$$.tipo = compruebaTipos($1,$2,$3);
					}
					| expresion ANDLOG expresion 
					{	$$.tipo = compruebaTipos($1,$2,$3);
					}
					| expresion ORLOG expresion 
					{	$$.tipo = compruebaTipos($1,$2,$3);
					}
					| expresion OPIG expresion 
					{	$$.tipo = compruebaTipos($1,$2,$3);
					}
					| expresion OREXCL expresion 
					{	$$.tipo = compruebaTipos($1,$2,$3);
					}
					| MASMENOS  expresion %prec OPUNARIO 
					{$$.tipo = $2.tipo;}
					| expresion MASMENOS expresion 
					{	$$.tipo = compruebaTipos($1,$2,$3);}
					| id_posArray{	
										$$.tipo = $1.tipo;
									}
					| CONST {$$.tipo = $1.tipo;}
					| agregado
					| error
					;
exp_cadenas:	exp_cadenas COMA exp_cadena 
					| exp_cadena
					;
id_posArray: 	IDENT { $$.tipo=asignaTipo($1); strcpy($$.lexema,$1.lexema); }
					| IDENT CORCHETEIZQ expresion CORCHETEDER 
						{	$$.tipo=asignaTipoArray($1); strcpy($$.lexema,$1.lexema); }
					| IDENT CORCHETEIZQ expresion COMA expresion CORCHETEDER
						{	$$.tipo=asignaTipoArray($1);strcpy($$.lexema,$1.lexema); }
					;
exp_cadena: expresion 
				| CADENA
				;
lista_constantes : lista_constantes coma_pyc CONST 
						| CONST
						;

agregado: CORCHETEIZQ lista_constantes CORCHETEDER;

coma_pyc: COMA | PYC;


/** esto representa la cadena vacía **/ ;
%%
/** aqui incluimos el fichero generado por el ’lex’
*** que implementa la función ’yylex’
**/
#ifdef DOSWINDOWS
#include "lexyy.c"
#else
#include "lex.yy.c"
#endif
/**
Variable de entorno que indica la plataforma
se debe implementar la función yyerror. En este caso
simplemente escribimos el mensaje de error en pantalla
**/

void yyerror( char *msg )
{
	fprintf(stderr,"[Linea %d]: %s\n", linea_actual, msg) ;
}


