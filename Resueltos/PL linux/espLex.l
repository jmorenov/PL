%{	
	#include "tabla.h"
	int linea = 1;
%}

letra	[a-zA-Z]
digito	[0-9]
alphanum [a-zA-Z0-9_]
blanco	[ \t]
finLinea [\n]
caracter [^\"\""]
otros .

%option noyywrap

%%

"principal"	{ return 	PRINCIPAL;}
"entero"	{ return 	TIPO;}
"real"	{ return 	TIPO;}
"caracter"	{ return 	TIPO;}
"boolean"	{ return 	TIPO;}
"pila"	{ return 	PILA;}
"["	{ return 	CORCHETEIZQ;}
"]"	{ return 	CORCHETEDER;}
"="	{ return 	ASIG;}
"++" { return 	MASMAS;}
"-"	{ return 	MASMENOS;}
"+"	{ return 	MASMENOS;}
"*"	{ return 	OPBIN;}
"/"	{ return 	OPBIN;}
">"	{ return 	OPBIN;}
"<"	{ return 	OPBIN;}
">="	{ return 	OPBIN;}
"<="	{ return 	OPBIN;}
"=="	{ return 	OPBIN;}
"!="	{ return 	OPBIN;}
"||"	{ return 	OPBIN;}
"&&"	{ return 	OPBIN;}
"^"	{ return 	OPBIN;}
"!"	{ return 	OPUNARIO;}
"#"	{ return 	OPUNARIO;}
"&"	{ return 	OPUNARIO;}
"--"	{ return 	OPUNARIO;}
"("	{ return 	PARIZQ;}
")"	{ return 	PARDER;}
"{"	{ return 	INIBLQ;}
"}"	{ return 	FINBLQ;}
"@"	{ return 	DELIMITADOR;}
","	{ return 	COMA;}
";"	{ return 	PYC;}
"si"	{ return 	SI;}
"sino"	{ return 	SINO;}
"mientras"	{ return 	MIENTRAS;}
"hacer"	{ return 	HACER ;}
"hasta"	{ return 	HASTA;}
"entrada"	{ return 	ENT;}
"salida"	{ return 	SAL;}
"verdad"	{ return 	CONST;}
"falso"	{ return 	CONST;}
{digito}+	{ return  CONST;}
{digito}+\.{digito}+	{ return  CONST;}
"\'"{caracter}"\'"	{ return  CONST;}
"\""{caracter}+"\""	{ return  CONST;}
{letra}{alphanum}* { return  IDENT;}
{blanco}+ {}
{finLinea} {linea++;printf("\n");}
{otros} printf ("\n(Linea %d) Error léxico: token %s\n", linea, yytext);

%%

int main ()
{
	int val;
	val = yylex();

	while (val != 0)
	{	printf ("%d ", val) ;
		val= yylex() ;
	}

	exit (0);
}

