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
/**
***
	La siguiente declaracion permite que ’yyerror’ se pueda invocar desde el
	fuente de lex
**/
void yyerror( const char * msg ) ;
/**
	La siguiente variable se usará para conocer el numero de la línea
	que se esta leyendo en cada momento. También es posible usar la variable
	’yylineno’ que también nos muestra la línea actual. Para ello es necesario
	invocar a flex con la opción ’-l’ (compatibilidad con lex).
**/
int linea_actual = 1 ;
int linea_si;
typedef enum {
    marca,
    funcion,
    variable,
    parametro_formal,
} tipoEntrada;
typedef enum {
    boolean,
    integer,
    real,
    character,
    list,
    unknown,
    unassigned
} dtype ;
typedef struct {
    tipoEntrada entrada ;
    char *nombre;
    dtype tipoDato;
    unsigned int parametros;
    unsigned int dimensiones;
    int TamDimen1;
    int TamDimen2;
} entradaTS ;
#define MAX_TS 500
unsigned int TOPE=0, top=-1;
unsigned int subProg=0; /* Indicador de comienzo de bloque de un subprog */
unsigned int decVar=0,dim,tamdim1,tamdim2;
unsigned int func = 0,posParam = 0;
char idFuncion[100];
entradaTS TS[MAX_TS]; /* Pila de la tabla de símbolos */
entradaTS TP[MAX_TS];
entradaTS TA[MAX_TS];
dtype tipoTMP,tipoArray;
typedef struct {
    int    attrib ;
    char  *lexema ;
    dtype  type ;
} atributos ;
#define YYSTYPE atributos
void TS_InsertaMARCA()
{
	if(TOPE != 0) TOPE++;
	TS[TOPE].entrada = marca;
	TS[TOPE].nombre = "MARCA_INICIAL";
	if(subProg == 1){
		int topeTMP = TOPE;
		while(TS[topeTMP].entrada != funcion && topeTMP > 0)
		{	//printf("tope = %d, parametro = %s\n",topeTMP,TS[topeTMP].nombre);
			if(TS[topeTMP].entrada == parametro_formal)
			{	
				TOPE++;
				TS[TOPE].entrada = parametro_formal;
				TS[TOPE].nombre = TS[topeTMP].nombre;
				TS[TOPE].tipoDato = TS[topeTMP].tipoDato;
				/*if(TS[topeTMP].tipoDato == array)
				{	TS[TOPE].dimensiones = TS[topeTMP].dimensiones;
					TS[TOPE].TamDimen1 = TS[topeTMP].TamDimen1;
					TS[TOPE].TamDimen2 = TS[topeTMP].TamDimen2;
				}*/
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
void TS_InsertaSUBPROG(atributos a)
{
	TOPE++;
	TS[TOPE].entrada = funcion;
	TS[TOPE].nombre = a.lexema;
	TS[TOPE].parametros = 0;
	top++;
	TP[top].entrada = funcion;
	TP[top].nombre = a.lexema;
	TP[top].parametros = 0;	
}
void TS_InsertaPARAMF(atributos a)
{
	TOPE++;	
	TS[TOPE].entrada = parametro_formal;
	TS[TOPE].nombre = a.lexema;
	TS[TOPE].tipoDato = a.type;
	top++;
	TP[top].entrada = parametro_formal;
	TP[top].nombre = a.lexema;
	TP[top].tipoDato = a.type;
	int topeTMP = TOPE;
	while(TS[topeTMP].entrada != funcion && topeTMP >= 0){	
		topeTMP--;
	}
	TS[topeTMP].parametros++;
	topeTMP = top;
	while(TP[topeTMP].entrada != funcion){	
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
void TS_InsertaIDENT(atributos a)
{
	TOPE++;	
	TS[TOPE].entrada = variable;
	TS[TOPE].nombre = a.lexema;
	TS[TOPE].tipoDato = tipoTMP;
	
	/*if(TS[TOPE].tipoDato == array)
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
	}*/
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
void existeFuncion(atributos a)
{	
	int topeTMP = TOPE ,existe=0;
	
	while(topeTMP >= 0 && existe == 0)
	{	
		if(TS[topeTMP].entrada == funcion && !strcmp(a.lexema,TS[topeTMP].nombre))
		{
			existe=1;
		}
		topeTMP--;
	}
	if(existe == 0)
	{
		fprintf(stderr,"[Linea %d]: %s: no existe o fuera de ambito.\n",linea_actual,a.lexema);
		return topeTMP+1;
	}
}
void verificaNumPar(unsigned int num)
{
	int topeTMP = top, existe = 0;
	
	while( existe == 0 && topeTMP>=0)
	{	if( !strcmp(TP[topeTMP].nombre,idFuncion) ){
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
	
	while(strcmp(TP[topeTMP].nombre,idFuncion) && topeTMP>=0)
	{	
		topeTMP--;
	}
	if(topeTMP>=0){
		if(pos <= TP[topeTMP].parametros){
			if ( TP[topeTMP+pos].tipoDato == real && a.type == integer ){
				a.type = real;
			}
			//printf("param: %d: ,tipo = %d. lexema:%s, tipo= %d \n",pos,TP[topeTMP+pos].tipoDato,a.lexema,a.tipo);
			if(TP[topeTMP].parametros==0){
				fprintf(stderr,"[Linea %d]: %s: no tiene parametros.\n",linea_actual,TP[topeTMP].nombre);
			}
			else if (TP[topeTMP+pos].tipoDato != a.type ){
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
/*unsigned int asignaTipoArray(atributos a)
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
int tempDimen1 = 0, tempDimen2 = 0;*/
unsigned int checkType(atributos a,atributos op, atributos b)
{
	unsigned int tipo = 2;
	int topeTMP = TOPE;
	//int indice_a = topArray, indice_b = topArray;
	int existeArray = 0;
	int existe = 0;
	while( existe == 0 && topeTMP>=0)
	{	
		if(!strcmp(TS[topeTMP].nombre,a.lexema))
		{
			existe = 1;
			tipo = TS[topeTMP].tipoDato;
		}
		topeTMP--;
	}
	if(existe || a.attrib >= 286)
	{
		/*if(a.tipo == array)
		{
			while( existeArray == 0 && indice_a>=0)
			{		
				if ( !strcmp(TA[indice_a].nombre,a.lexema) ){
					existeArray = 1;			
					a.tipo = TA[indice_a].tipoDato;
				}
				else{	indice_a--;}
			}
		}
		if(existeArray && b.tipo == array)
		{
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
		}*/
			if ( a.type == real && b.type == integer )
			{
				b.type = real;
			}
			if ( a.type == integer && b.type == real )
			{
				b.type = integer;
			}
			//printf("%s, tipo = %d attrib = %d -- %s, tipo = %d attrib = %d\n",a.lexema,a.type,a.attrib, b.lexema,b.type, b.attrib);
		if(a.type != b.type)
		{
			fprintf(stderr,"[Linea %d]: tipos incompatible\n ",linea_actual);
		}
		else
		{
			tipo = a.type;		
		}
		if(op.type == boolean)
			tipo = boolean;
	}
	else
	{
		fprintf(stderr,"[Linea %d]: %s no existe\n",linea_actual,a.lexema);
	}
	return tipo;
}
%}
/**
Para uso de mensajes de error sintáctico con BISON.
La siguiente declaración provoca que ’bison’, ante un error sintáctico,
visualice mensajes de error con indicación de los tokens que se esperaban
en el lugar en el que produjo el error (SÓLO FUNCIONA CON BISON=2.1).
Para Bison2.1 es mediante
 YYERROR_VERBOSE
En caso de usar mensajes de error mediante ’mes’ y ’mes2’ (ver apéndice D)
nada de lo anterior debe tenerse en cuenta.
**/
%error-verbose
/**
A continuación declaramos los nombres simbólicos de los tokens.
byacc se encarga de asociar a cada uno un código
**/
%token MAIN
%token IF
%token ELSE
%token DO
%token UNTIL
%left OP_BIN
%right OP_LIST
%left OP_LIST_START_CURSOR
%right OP_UNIT
%left OP_PM
%token TYPE
%token BEGIN_LIST
%token END_LIST
%token ASSIGN
%token PL
%token PR
%token BEGIN_P
%token END
%token COMMA
%token SEMICOLON
%token INPUT
%token OUTPUT
%token START_VAR_DEC
%token END_VAR_DEC
%token LIST
%token ID
%token RETURN
%token WHILE
%token BOOL
%token INT
%token FLOAT
%token CHAR
%token CAD
%%
/**
Sección de producciones que definen la gramática.
**/
/**
 * Práctica 3: Definición del lenguaje: BBAAD
 * Grupo 7
 * Francisco Javier Moreno Vega
 * Alberto Quesada Aranda
 * 18/12/2014
 */
/**
 * Definiciones básicas.
 */
program : header_program block;
block : start_block { TS_InsertaMARCA(); } local_var_dec sub_progs sentences end_block { TS_VaciarENTRADAS(); };
sub_progs : sub_progs sub_prog | ;
sub_prog : header_subprogram {subProg = 1;} block {subProg = 0;} ;
local_var_dec : START_VAR_DEC { decVar = 1; } local_var END_VAR_DEC { decVar = 0; }| ;
header_program : type MAIN PL PR;
start_block : BEGIN_P;
end_block : END;
local_var : local_var var_body | var_body;
var_body : type {tipoTMP = $1.type;} list_id SEMICOLON | error;
list_id : list_id COMMA ID {if(decVar){ existeVar($3);TS_InsertaIDENT($3);}}| 
					ID {if(decVar){ existeVar($1);TS_InsertaIDENT($1);}}| error;
header_subprogram : type ID PL {TS_InsertaSUBPROG($2);} parameters PR | type ID PL PR {TS_InsertaSUBPROG($2);};
parameters : parameters COMMA type ID {TS_InsertaPARAMF($4);} | type ID {TS_InsertaPARAMF($2);} | error;
sentences : sentences sentence | sentence;
sentence : block |
sentence_assign |
sentence_if_then_else |
sentence_while |
sentence_input |
sentence_output |
sentence_return |
sentence_do_until |
sentence_list_forward_back |
sentence_list_start_cursor |
error;
sentence_assign : ID ASSIGN expr SEMICOLON {$$.type =  checkType($1,$2,$3);};
sentence_if_then_else : IF PL expr PR sentence {if($3.type != boolean)
    fprintf(stderr,"[Linea %d]: no hay expresion tipo logica \n",linea_si);}
| IF PL expr PR sentence ELSE sentence {if($3.type != boolean)
    fprintf(stderr,"[Linea %d]: no hay expresion tipo logica \n",linea_si);}
;
sentence_while : WHILE PL expr PR sentence {if($3.type != boolean)
    fprintf(stderr,"[Linea %d]: no hay expresion tipo logica \n",linea_si);};
sentence_input : INPUT CAD COMMA list_id SEMICOLON | INPUT list_id SEMICOLON;
sentence_output : OUTPUT list_expr_cad SEMICOLON;
sentence_return : RETURN expr SEMICOLON;
sentence_do_until : DO sentence UNTIL PL expr PR SEMICOLON {if($4.type != boolean)
    fprintf(stderr,"[Linea %d]: no hay expresion tipo logica \n",linea_si);};
sentence_list_forward_back : expr OP_LIST SEMICOLON;
sentence_list_start_cursor : OP_LIST_START_CURSOR expr SEMICOLON;
expr : PL expr PR {	$$.type = $2.type;} |
OP_UNIT expr {	$$.type = $2.type;}|
ID { $$.type=asignaTipo($1); strcpy($$.lexema,$1.lexema); }|
const {$$.type = $1.type;}|
function_call |
expr OP_BIN expr {	$$.type =  checkType($1,$2,$3);}|
expr OP_PM expr {	$$.type =  checkType($1,$2,$3);}|
error;
function_call : ID PL { strcpy(idFuncion, $1.lexema); func =1; existeFuncion($1); } list_expr PR {func = 0; verificaNumPar(posParam); posParam=0;} | 
							ID PL { strcpy(idFuncion,$1.lexema); func =1; existeFuncion($1); } PR {func = 0; verificaNumPar(posParam); posParam=0;};
list_expr : list_expr COMMA expr {if(func == 1) {	posParam++; verificaParam($3,posParam);}} | 
						expr {if(func == 1){ posParam++; verificaParam($1,posParam);}} ;
type : TYPE | LIST TYPE;
const : INT |
FLOAT |
CHAR |
BOOL |
const_list;
const_list : list_of_int |
list_of_float |
list_of_char |
list_of_bool;
list_of_int : BEGIN_LIST list_int END_LIST;
list_int : list_int COMMA INT | INT;
list_of_float : BEGIN_LIST list_float END_LIST;
list_float : list_float COMMA FLOAT | FLOAT;
list_of_char : BEGIN_LIST list_char END_LIST;
list_char : list_char COMMA CHAR | CHAR;
list_of_bool : BEGIN_LIST list_bool END_LIST;
list_bool : list_bool COMMA BOOL | BOOL;
list_expr_cad : list_expr_cad COMMA expr_cad | expr_cad;
expr_cad : expr | CAD;
%%
/** aqui incluimos el fichero generado por el ’lex’
*** que implementa la función ’yylex’
**/
#ifdef DOSWINDOWS
#include "../generated/lexyy.c"
#else
#include "../generated/lex.yy.c"
#endif
/**
Variable de entorno que indica la plataforma
se debe implementar la función yyerror. En este caso
simplemente escribimos el mensaje de error en pantalla
**/
void yyerror( const char *msg )
{
	fprintf(stderr,"[Linea %d]: %s\n", linea_actual, msg) ;
}