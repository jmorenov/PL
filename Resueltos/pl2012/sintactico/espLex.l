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
"entero"	{ return 	TIPO;}
"real"	{ return 	TIPO;}
"caracter"	{ return 	TIPO;}
"boolean"	{ return 	TIPO;}
"["	{ return 	CORCHETEIZQ;}
"]"	{ return 	CORCHETEDER;}
"="	{ return 	ASIG;}
"-"	{ return 	MASMENOS;}
"+"	{ return 	MASMENOS;}
"*"	{ return 	OPMUL;}
"/"	{ return 	OPMUL;}
"%"	{ return 	OPMUL;}
">"	{ return 	OPREL;}
"<"	{ return 	OPREL;}
">="	{ return 	OPREL;}
"<="	{ return 	OPREL;}
"=="	{ return 	OPIG;}
"!="	{ return 	OPIG;}
"||"	{ return 	ORLOG;}
"&&"	{ return 	ANDLOG;}
"^"	{ return 	OREXCL;}
"!"	{ return 	OPUNARIO;}
"**"	{ return 	OPMUL;}
"("	{ return 	PARIZQ;}
")"	{ return 	PARDER;}
"{"	{ return 	INIBLQ;}
"}"	{ return 	FINBLQ;}
"beg"	{ return 	BEG;}
"end"	{ return	END;}
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
"procedimiento" { return	PROCEDIMIENTO;}
{digito}+	{ return  CONST;}
{digito}+\.{digito}+	{ return  CONST;}
"\'"{caracter}"\'"	{ return  CONST;}
"\""{caracter}+"\""	{ return  CADENA;}
{letra}{alphanum}* { return  IDENT;}
{blanco}+ {}
{finLinea} {linea_actual++;}

{otros} {snprintf(buffer, MAXLONBUFFER, "el(los) caracter(es) '%s' no forma(n) ningun token conocido",yytext);
	yyerror(buffer);}
%%


