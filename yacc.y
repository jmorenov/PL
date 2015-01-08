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

%token OP_PM
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
%token BOOL
%token RETURN
%token LIMIT_CHAR
%token WHILE
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

block : start_block local_var_dec sub_progs sentences end_block;

sub_progs : sub_progs sub_prog | ;

sub_prog : header_subprogram block;

local_var_dec : START_VAR_DEC local_var END_VAR_DEC | ;

header_program : type MAIN;

start_block : BEGIN_P;

end_block : END;

local_var : local_var var_body | var_body;

var_body : type list_id SEMICOLON;

header_subprogram : type ID PL parameters PR;

parameters : parameters COMMA type ID | type ID | ;

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
sentence_list_start_cursor;

sentence_assign : ID ASSIGN expr SEMICOLON;

sentence_if_then_else : IF expr sentence | IF expr sentence ELSE sentence;

sentence_while : WHILE expr sentence;

sentence_input : INPUT list_id SEMICOLON;

sentence_output : OUTPUT list_expr_cad SEMICOLON;

sentence_return : RETURN expr SEMICOLON;

sentence_do_until : DO sentence UNTIL expr SEMICOLON;

sentence_list_forward_back : expr OP_LIST SEMICOLON;

sentence_list_start_cursor : OP_LIST_START_CURSOR expr SEMICOLON;

expr : PL expr PR |
OP_UNIT expr |
expr OP_BIN expr |
expr OP_PM expr |
ID |
const |
function_call | ;

list_id : list_id COMMA ID | ID;

list_expr : list_expr COMMA expr | expr;

function_call : ID PL list_expr PR;

type : TYPE | LIST TYPE;

const : INT |
FLOAT |
LIMIT_CHAR CHAR LIMIT_CHAR |
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
list_char : list_char COMMA LIMIT_CHAR CHAR LIMIT_CHAR | LIMIT_CHAR CHAR LIMIT_CHAR;

list_of_bool : BEGIN_LIST list_bool END_LIST;
list_bool : list_bool COMMA BOOL | BOOL;

list_expr_cad : list_expr_cad COMMA expr_cad | expr_cad;

expr_cad : expr | CAD;

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

void yyerror( const char *msg )
{
	fprintf(stderr,"[Linea %d]: %s\n", linea_actual, msg) ;
}


