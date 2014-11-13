%{	
#define MAXLONBUFFER 200
char buffer[MAXLONBUFFER];
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
"procedimiento"	{ return 	PROCEDIMIENTO;}
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
"entrada"	{ return 	ENTRADA;}
"salida"	{ return 	SALIDA;}
"verdad"	{ return 	CONST;}
"falso"	{ return 	CONST;}
{digito}+	{ return  CONST;}
{digito}+\.{digito}+	{ return  CONST;}
"\'"{caracter}"\'"	{ return  CONST;}
"\""{caracter}+"\""	{ return  CONSTCADENA;}
{letra}{alphanum}* { return  IDENT;}
{blanco}+ {}
{finLinea} {linea_actual++;}
{otros} {printf(buffer, MAXLONBUFFER, "el(los) caracter(es) ’%s’ no forma(n) ningun token conocido",yytext); yyerror(buffer);}

