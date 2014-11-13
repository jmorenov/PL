/*return ( */
/*Declaraciones.*/
%{
	#include "y.tab.h"
	#include <stdio.h>
   int numero_linea = 1;
%}
/*Reglas.*/
%%
\/\/(.)*       {}
\/\*(.)*\*\/   {}
"\n"           {numero_linea ++;}
(" ")*         {}
("\t")*        {}
"principal"    {return ( MAIN );}
"mientras"     {return ( WHILE );}
"entero"       {return ( TIPO_DATO );}
"real"         {return ( TIPO_DATO );}
"bool"         {return ( TIPO_DATO );}
"caracter"     {return ( TIPO_DATO );}
"cadena"       {return ( TIPO_DATO );}
"pila entero"  {return ( TIPO_DATO );}
"pila real"    {return ( TIPO_DATO );}
"pila bool"    {return ( TIPO_DATO );}
"pila caracter" {return ( TIPO_DATO );}
"Verdadero"    {return ( BOOL );}
"Falso"        {return ( BOOL );}
"salida"       {return ( OUTPUT );}
"si"           {return ( IF );}
"sino"         {return ( ELSE );}
"entrada"      {return ( INPUT );}
"devolver"     {return ( RETURN );}
"interruptor"  {return ( SWITCH );}
"romper"       {return ( BREAK);}
"=="        {return ( OP_IGUALDAD );}
"="         {return ( ASIG); }
"{"         {return ( INI_BLOQUE );}
"}"         {return ( FIN_BLOQUE );}
"("         {return ( PARIZQ );}
")"         {return ( PARDER );}
"||"        {return ( OR_LOGICO );}
"|"         {return ( OR_BIT );}
"*"         {return ( MULTIPLICAT );}
"/"         {return ( MULTIPLICAT );}
"%"         {return ( MULTIPLICAT );}
">>"        {return ( REDIRECT_E );}
"<<"        {return ( REDIRECT_S );}
"&&"        {return ( AND_LOGICO );}
"++"        {return ( INCREMENTO );}
"<="        {return ( OP_RELACIONAL );}
">="        {return ( OP_RELACIONAL );}
"!="        {return ( OP_IGUALDAD );}
"<"         {return ( OP_RELACIONAL );}
">"         {return ( OP_RELACIONAL );}
","         {return ( COMA );}
"&"         {return ( UNARIO );}
"#"         {return ( UNARIO );}
"!"         {return ( UNARIO );}
";"         {return ( FIN_SENTENC );}
"+"         {return ( MAS_MENOS );}
"-"         {return ( MAS_MENOS );}
"["         {return ( I_CONS_PILA);}
"]"         {return ( F_CONS_PILA);}
":"	    {return ( DOS_PUNTOS);}
"FIN_VAR_LOCAL"         {return ( F_VAR_LOCAL );}
"INI_VAR_LOCAL"         {return ( I_VAR_LOCAL );}
[A-Za-z_]([A-Za-z0-9_])*  {return ( NOMBRE );}
\"[^\"]*\"              {return ( CADENA );}
[0-9]+"."([0-9])*       {return ( REAL );}
[0-9]+                  {return ( ENTERO );}
\'[A-Za-z]\'		{return ( CHAR );}
.                       {printf("Error léxico en la línea: %d\n", numero_linea);}
%%

