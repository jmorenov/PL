/**
 @file
 Prototipos de funciones para el parser
 COMPILADAS en C
*/

#ifndef __PARSER_H__
#define __PARSER_H__

#include <stdio.h>
#include "regTrad.h"

extern FILE *yyin;

extern "C"
	{
	int yylex(void);	/**< Scanner lexico */
	int yyparse(void);	/**< El parser creado por YACC */
	}



#endif

