
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 1 "prueba.y"

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

typedef struct {
	char *EtiquetaEntrada;
	char *EtiquetaSalida;
	char *EtiquetaElse;
	char *NombreVarControl;
}DescriptorDeInstrControl;

typedef enum {
	parametro_formal, // si es parametro formal	
	marca, //marca comienzo bloque
	procedimiento, //si es subprograma
	variable, // si es variable
	descriptor,
	cadena,	
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
	DescriptorDeInstrControl descriptor;
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
entradaTS TF[MAX_TS];
int topeTF=-1;
dtipo tipoTMP,tipoArray;

typedef struct {
	int atrib;  /* Atributo del símbolo (si tiene) */
	char *lexema; /* Nombre del lexema */
	dtipo tipo; /* Tipo del símbolo */
	char * var; /*nombre variable temporal*/
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
unsigned int compruebaTipos(atributos a,atributos op, atributos b)
{
	unsigned int tipo = 10;
	//printf("%s, tipo = %d--%s, tipo = %d\n",a.lexema,a.tipo,b.lexema,b.tipo);

	if(a.tipo == array && b.tipo == array){
		int indice_a = topArray, indice_b = topArray;
		
		int existeArray = 0;

		while( existeArray == 0 && indice_a>=0)
		{		
			if ( !strcmp(TA[indice_a].nombre,a.lexema) ){
				existeArray = 1;
				//printf("%s, tipo = %d\n",TA[indice_a].nombre,TA[indice_a].tipoDato);				
				a.tipo = TA[indice_a].tipoDato;
			}
			else{	indice_a--;}
		}
		existeArray = 0;
		if(existeArray){
			while( existeArray == 0 && indice_b>=0)
			{		//printf("%s, tipo = %d\n",TA[topeTMP].nombre,TA[topeTMP].tipoDato);
				if ( !strcmp(TA[indice_b].nombre,b.lexema) ){
					existeArray = 1;
					//printf("%s, tipo = %d\n",TA[indice_b].nombre,TA[indice_b].tipoDato);
					b.tipo = TA[indice_b].tipoDato;
				}
				else{	indice_b--;}
			}
		}
		if(existeArray){
			if(TA[indice_a].dimensiones != TA[indice_b].dimensiones){
				fprintf(stderr,"[Linea %d]: dimensiones incompatibles\n",linea_actual);
			}
			else if((TA[indice_a].TamDimen1 != TA[indice_b].TamDimen2) || (TA[indice_a].TamDimen2 != TA[indice_b].TamDimen1) ){
				fprintf(stderr,"[Linea %d]: dimensiones incompatibles\n",linea_actual);
			}
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
	return tipo;
}
unsigned int compruebaTipos2(atributos a,atributos op, atributos b)
{
	unsigned int tipo = 10;
	int existe = 0;
	int topeTMP = TOPE ;

	while( existe == 0 && topeTMP>=0)
	{	if ( !strcmp(TS[topeTMP].nombre,a.lexema) ){
			existe = 1;
			tipo = TS[topeTMP].tipoDato;
		}
		topeTMP--;
	}

	if(existe){
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
/********************************************
**************generacion codigo**************
*********************************************/
int temp = 0;
int etiq = 0;
int varPrinc=1;
int decIF = 0,decElse=0;
FILE * fi,* f,* fp;
char * llamada;


char * temporal(){
	char * cadena;
	cadena = (char *) malloc(20);
	sprintf(cadena, "temp%d",temp);
	temp++;
	return cadena;
}
char * etiqueta(){
	char * cadena;
	cadena = (char *) malloc(20);
	sprintf(cadena, "etiqueta_%d",etiq);
	etiq++;
	return cadena;
}
/***
tipo = 1.aritmetica o logica
		 2. if then else
		 3. bucle
		 4. asignacion
****/

void generaFich(){
	llamada = (char *) malloc(200);	
	fp = fopen("dec_fun","w");
	fputs("#include <stdio.h>\n",fp);
	
	f = fopen("codigo.c","w");
	fputs("#include <stdio.h>\n",f);
	fputs("#include \"dec_fun\"\n",f);
	fi = f;

}
void generaDecVar(atributos a){
	char * sent;
	sent = (char *) malloc(1000);

	if(tipoTMP == entero){
		sprintf(sent,"int %s;\n",a.var);
		fputs(sent,fi);
	}
	else if(tipoTMP == real){
		sprintf(sent,"float %s;\n",a.var);
		fputs(sent,fi);
	}
	else if(tipoTMP == caracter){
		sprintf(sent,"char %s;\n",a.var);
		fputs(sent,fi);
	}
	else if(tipoTMP == booleano){
		TOPE++;
		TS[TOPE].entrada = descriptor;
		TS[TOPE].descriptor.EtiquetaSalida = etiqueta();
		sprintf(sent,"int %s;\n",a.var);
		fputs(sent,fi);
	}
	free(sent);
}

void genera(int tipo,atributos dest,atributos a, atributos op, atributos b){
	char * sent;
	sent = (char *) malloc(200);

	if(tipo == 1){
		
		sprintf(sent,"int %s;\n%s = %s %s %s;\n",dest.var,dest.var,a.var,op.var,b.var);
		fputs(sent,fi);
	}
	else if(tipo == 4 ){
		sprintf(sent,"%s %s %s %s\n",dest.var,a.var,op.var,b.var);
		fputs(sent,fi);
	}
	free(sent);
}
/*	1. else y salida
	2. entrada y salida
*/
void insertaDesc(int tipo){
	topeTF++;	
	TF[topeTF].entrada = descriptor;
	if(tipo == 1){
		TF[topeTF].descriptor.EtiquetaElse = etiqueta();
		TF[topeTF].descriptor.EtiquetaSalida = etiqueta();
	}else if(tipo == 2){
		TF[topeTF].descriptor.EtiquetaEntrada = etiqueta();
		TF[topeTF].descriptor.EtiquetaSalida = etiqueta();
	}
}
void eliminaDesc(){
	topeTF--;
}
/*	1.if con else
	2.while
	3.if sin else
*/
void insertaCond(int tipo){
	
	char * cadena, *sent;
	int topeTMP = topeTF;

	cadena = (char *) malloc(20);
	sent = (char *) malloc(150);
	
	
	while(TF[topeTMP].entrada != descriptor){
		topeTMP--;	
	}
	if(tipo == 1){
		sprintf(cadena, "temp%d",temp-1);
		TF[topeTMP].nombre = (char *) malloc(50);
		strcpy(TF[topeTMP].nombre,cadena);
		sprintf(sent,"if(!%s) goto %s;\n",cadena,TF[topeTMP].descriptor.EtiquetaElse);
	}
	else if(tipo == 2){
				sprintf(cadena, "temp%d",temp-1);
				sprintf(sent,"if(!%s) goto %s;\n",cadena,TF[topeTMP].descriptor.EtiquetaSalida);
			}
	

	fputs(sent,fi);

	free(sent);
	free(cadena);
}

void insertaEtiqElse(){
	int topeTMP = topeTF;
	char * sent;
	sent = (char *) malloc(200);

	while(TF[topeTMP].entrada != descriptor){
		topeTMP--;
	}
	if(decElse == 1){
		sprintf(sent,"goto %s;\n%s:\n",TF[topeTMP].descriptor.EtiquetaSalida,TF[topeTMP].descriptor.EtiquetaElse);
	}
	else{
		sprintf(sent,"%s:",TF[topeTMP].descriptor.EtiquetaElse);
		}
	fputs(sent,fi);
}

void insertaEtiqSalida(){
	int topeTMP = topeTF;
	char * sent;
	sent = (char *) malloc(200);

	while(TF[topeTMP].entrada != descriptor){
		topeTMP--;
	}
	
	sprintf(sent,"%s:\n",TF[topeTMP].descriptor.EtiquetaSalida);
	
	fputs(sent,fi);
}
void insertaEtiqEntrada(){
	int topeTMP = topeTF;
	char * sent;
	sent = (char *) malloc(200);

	while(TF[topeTMP].entrada != descriptor){
		topeTMP--;
	}
	
	sprintf(sent,"%s:\n",TF[topeTMP].descriptor.EtiquetaEntrada);
	fputs(sent,fi);
}
void insertaGotoEntrada(){
	int topeTMP = topeTF;
	char * sent;
	sent = (char *) malloc(200);

	while(TF[topeTMP].entrada != descriptor){
		topeTMP--;
	}
	
	sprintf(sent,"goto %s;\n",TF[topeTMP].descriptor.EtiquetaEntrada);
	fputs(sent,fi);
}
void generaEntSal(int tipo,atributos a){
	
	if(tipo == 1){
		fputs("scanf(\"%",fi);
		if(a.tipo == entero) fputs("d",fi);
		else if(a.tipo == real) fputs("f",fi);
		else if(a.tipo == caracter) fputs("c",fi);
		else if(a.tipo == booleano) fputs("d",fi);
		fputs("\",&",fi);
		fputs(a.var,fi);
		fputs(");",fi);
		fputs("\n",fi);
	}
	else{
		if(a.tipo != desconocido){		
			fputs("printf(\"%",fi);
			if(a.tipo == entero) fputs("d",fi);
			else if(a.tipo == real) fputs("f",fi);
			else if(a.tipo == caracter) fputs("c",fi);
			else if(a.tipo == booleano) fputs("d",fi);		
			fputs("\",",fi);
			fputs(a.var,fi);
			fputs(");",fi);
		}else {
			fputs("printf(",fi);
			fputs(a.var,fi);
			fputs(");",fi);
		}
		fputs("\n",fi);
	}
}
/*********************************
********** PROCEDIMIENTO**********
*********************************/

void genera_procedimiento(atributos a){
	char * sent;
	sent = (char *) malloc(200); 
	sprintf(sent,"void %s(",a.lexema);
	fputs(sent,fi);
}
void genera_parametro(atributos tipo, atributos a){
	char * sent;
	sent = (char *) malloc(1000);

	if(tipo.tipo == entero){
		sprintf(sent,"int %s",a.var);
		fputs(sent,fi);
	}
	else if(tipo.tipo == real){
		sprintf(sent,"float %s",a.var);
		fputs(sent,fi);
	}
	else if(tipo.tipo == caracter){
		sprintf(sent,"char %s",a.var);
		fputs(sent,fi);
	}
	else if(tipo.tipo == booleano){
		sprintf(sent,"int %s",a.var);
		fputs(sent,fi);
	}
	free(sent);

}
void copia_param(int tipo, atributos a){
	if(tipo == 2)
		if(!strcmp(a.var,"verdad")){
			sprintf(llamada,"%s, 1",llamada);
		}
		else if(!strcmp(a.var,"falso")){
			sprintf(llamada,"%s, 0",llamada);
		} 
		else
		{sprintf(llamada,"%s, %s",llamada,a.var);
		}
	else
	{	if(!strcmp(a.var,"verdad")){
			sprintf(llamada,"1");
		}
		else if(!strcmp(a.var,"falso")){
			sprintf(llamada,"0");
		} 
		else
		{	sprintf(llamada,"%s",a.var);
		}

	}
}


/* Line 189 of yacc.c  */
#line 764 "y.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     PRINCIPAL = 258,
     PROCEDIMIENTO = 259,
     TIPO = 260,
     CONST = 261,
     ASIG = 262,
     MASMENOS = 263,
     OPUNARIO = 264,
     PARIZQ = 265,
     PARDER = 266,
     INIBLQ = 267,
     FINBLQ = 268,
     BEG = 269,
     END = 270,
     COMA = 271,
     PYC = 272,
     SI = 273,
     SINO = 274,
     MIENTRAS = 275,
     HACER = 276,
     HASTA = 277,
     ENT = 278,
     SAL = 279,
     IDENT = 280,
     CORCHETEIZQ = 281,
     CORCHETEDER = 282,
     CADENA = 283,
     ANDLOG = 284,
     ORLOG = 285,
     OREXCL = 286,
     OPIG = 287,
     OPREL = 288,
     OPMUL = 289
   };
#endif
/* Tokens.  */
#define PRINCIPAL 258
#define PROCEDIMIENTO 259
#define TIPO 260
#define CONST 261
#define ASIG 262
#define MASMENOS 263
#define OPUNARIO 264
#define PARIZQ 265
#define PARDER 266
#define INIBLQ 267
#define FINBLQ 268
#define BEG 269
#define END 270
#define COMA 271
#define PYC 272
#define SI 273
#define SINO 274
#define MIENTRAS 275
#define HACER 276
#define HASTA 277
#define ENT 278
#define SAL 279
#define IDENT 280
#define CORCHETEIZQ 281
#define CORCHETEDER 282
#define CADENA 283
#define ANDLOG 284
#define ORLOG 285
#define OREXCL 286
#define OPIG 287
#define OPREL 288
#define OPMUL 289




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 874 "y.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   227

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  35
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  50
/* YYNRULES -- Number of rules.  */
#define YYNRULES  92
/* YYNRULES -- Number of states.  */
#define YYNSTATES  163

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   289

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     4,     8,    12,    13,    14,    22,    23,
      27,    28,    29,    33,    34,    41,    46,    51,    54,    56,
      57,    62,    63,    66,    68,    69,    74,    78,    82,    84,
      86,    88,    90,    95,   102,   105,   107,   108,   111,   113,
     114,   117,   118,   121,   122,   125,   126,   129,   130,   133,
     135,   137,   142,   148,   155,   156,   160,   161,   168,   172,
     176,   182,   183,   190,   191,   197,   201,   203,   207,   210,
     214,   218,   222,   226,   230,   234,   237,   241,   243,   245,
     247,   249,   253,   255,   257,   262,   269,   271,   273,   277,
     279,   283,   285
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      36,     0,    -1,    -1,    38,    37,    39,    -1,     3,    10,
      11,    -1,    -1,    -1,    12,    40,    49,    41,    42,    57,
      13,    -1,    -1,    42,    43,    44,    -1,    -1,    -1,    46,
      45,    39,    -1,    -1,     4,    25,    10,    47,    48,    11,
      -1,     4,    25,    10,    11,    -1,    48,    16,     5,    25,
      -1,     5,    25,    -1,     1,    -1,    -1,    14,    50,    51,
      15,    -1,    -1,    51,    52,    -1,    52,    -1,    -1,     5,
      53,    54,    17,    -1,     1,    54,    17,    -1,    54,    16,
      55,    -1,    55,    -1,     1,    -1,    25,    -1,    56,    -1,
      25,    26,     6,    27,    -1,    25,    26,     6,    16,     6,
      27,    -1,    57,    58,    -1,    58,    -1,    -1,    59,    39,
      -1,    65,    -1,    -1,    60,    66,    -1,    -1,    61,    69,
      -1,    -1,    62,    71,    -1,    -1,    63,    72,    -1,    -1,
      64,    73,    -1,    74,    -1,     1,    -1,    80,     7,    78,
      17,    -1,    18,    10,    78,    11,    58,    -1,    18,    10,
      78,    11,    58,    67,    -1,    -1,    19,    68,    58,    -1,
      -1,    20,    10,    78,    11,    70,    58,    -1,    23,    54,
      17,    -1,    24,    79,    17,    -1,    21,    58,    22,    78,
      17,    -1,    -1,    25,    10,    75,    77,    11,    17,    -1,
      -1,    25,    10,    76,    11,    17,    -1,    77,    16,    78,
      -1,    78,    -1,    10,    78,    11,    -1,     9,    78,    -1,
      78,    33,    78,    -1,    78,    34,    78,    -1,    78,    29,
      78,    -1,    78,    30,    78,    -1,    78,    32,    78,    -1,
      78,    31,    78,    -1,     8,    78,    -1,    78,     8,    78,
      -1,    80,    -1,     6,    -1,    83,    -1,     1,    -1,    79,
      16,    81,    -1,    81,    -1,    25,    -1,    25,    26,    78,
      27,    -1,    25,    26,    78,    16,    78,    27,    -1,    78,
      -1,    28,    -1,    82,    84,     6,    -1,     6,    -1,    26,
      82,    27,    -1,    16,    -1,    17,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   739,   739,   739,   740,   741,   743,   741,   754,   754,
     755,   757,   757,   760,   759,   765,   771,   776,   780,   783,
     783,   784,   787,   788,   790,   790,   791,   794,   803,   811,
     813,   814,   816,   818,   821,   821,   823,   823,   829,   830,
     830,   833,   833,   842,   842,   848,   848,   854,   854,   860,
     861,   863,   874,   882,   889,   889,   892,   892,   904,   906,
     908,   914,   913,   922,   921,   929,   936,   945,   949,   957,
     963,   969,   975,   981,   987,   993,   995,  1001,  1004,  1005,
    1006,  1008,  1009,  1011,  1012,  1014,  1017,  1021,  1026,  1027,
    1030,  1032,  1032
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "PRINCIPAL", "PROCEDIMIENTO", "TIPO",
  "CONST", "ASIG", "MASMENOS", "OPUNARIO", "PARIZQ", "PARDER", "INIBLQ",
  "FINBLQ", "BEG", "END", "COMA", "PYC", "SI", "SINO", "MIENTRAS", "HACER",
  "HASTA", "ENT", "SAL", "IDENT", "CORCHETEIZQ", "CORCHETEDER", "CADENA",
  "ANDLOG", "ORLOG", "OREXCL", "OPIG", "OPREL", "OPMUL", "$accept",
  "Programa", "$@1", "Cabecera_programa", "bloque", "$@2", "$@3",
  "Declar_de_subprogs", "$@4", "Declar_de_subprog", "$@5",
  "Cabecera_subprog", "$@6", "parametros", "Declar_de_variables_locales",
  "$@7", "Variables_locales", "Cuerpo_declar_variables", "$@8",
  "lista_nombres", "id_array", "array", "Sentencias", "Sentencia", "$@9",
  "$@10", "$@11", "$@12", "$@13", "$@14", "sentencia_asignacion",
  "sentencia_if", "sentencia_else", "$@15", "sentencia_while", "$@16",
  "sentencia_entrada", "sentencia_salida", "sentencia_hacer_hasta",
  "llamada_procedimiento", "$@17", "$@18", "expresiones", "expresion",
  "exp_cadenas", "id_posArray", "exp_cadena", "lista_constantes",
  "agregado", "coma_pyc", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    35,    37,    36,    38,    40,    41,    39,    43,    42,
      42,    45,    44,    47,    46,    46,    48,    48,    48,    50,
      49,    49,    51,    51,    53,    52,    52,    54,    54,    54,
      55,    55,    56,    56,    57,    57,    59,    58,    58,    60,
      58,    61,    58,    62,    58,    63,    58,    64,    58,    58,
      58,    65,    66,    66,    68,    67,    70,    69,    71,    72,
      73,    75,    74,    76,    74,    77,    77,    78,    78,    78,
      78,    78,    78,    78,    78,    78,    78,    78,    78,    78,
      78,    79,    79,    80,    80,    80,    81,    81,    82,    82,
      83,    84,    84
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     3,     3,     0,     0,     7,     0,     3,
       0,     0,     3,     0,     6,     4,     4,     2,     1,     0,
       4,     0,     2,     1,     0,     4,     3,     3,     1,     1,
       1,     1,     4,     6,     2,     1,     0,     2,     1,     0,
       2,     0,     2,     0,     2,     0,     2,     0,     2,     1,
       1,     4,     5,     6,     0,     3,     0,     6,     3,     3,
       5,     0,     6,     0,     5,     3,     1,     3,     2,     3,
       3,     3,     3,     3,     3,     2,     3,     1,     1,     1,
       1,     3,     1,     1,     4,     6,     1,     1,     3,     1,
       3,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     2,     0,     1,     0,     4,     5,     3,
      21,    19,     6,     0,    10,     0,    24,     0,    23,     0,
      29,    30,     0,    28,    31,     0,    20,    22,    50,    83,
       0,     0,    35,     0,     0,     0,     0,     0,     0,    38,
      49,     0,     0,     0,    26,     0,    61,     0,     0,     9,
      11,     7,    34,    37,     0,    40,     0,    42,     0,    44,
       0,    46,     0,    48,     0,     0,    27,    25,     0,     0,
      80,    78,     0,     0,     0,    83,     0,     0,    77,    79,
       0,     0,     0,     0,     0,    87,    86,     0,    82,     0,
       0,     0,    32,     0,    66,     0,    75,    68,     0,    89,
       0,     0,     0,    84,     0,     0,     0,     0,     0,     0,
      13,    12,     0,     0,    58,     0,    59,     0,    51,     0,
       0,     0,    64,    67,    91,    92,    90,     0,    76,     0,
      71,    72,    74,    73,    69,    70,    15,     0,     0,    56,
      81,     0,    33,    62,    65,    88,    85,    18,     0,     0,
      52,     0,    60,    17,    14,     0,    54,    53,    57,     0,
       0,    16,    55
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     6,     3,     9,    10,    14,    19,    30,    49,
      81,    50,   137,   149,    12,    13,    17,    18,    25,    22,
      23,    24,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    55,   157,   160,    57,   151,    59,    61,    63,    40,
      68,    69,    93,    86,    87,    78,    88,   100,    79,   127
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -46
static const yytype_int16 yypact[] =
{
      23,    10,    55,   -46,    56,   -46,    61,   -46,   -46,   -46,
      64,   -46,   -46,    97,   -46,    20,   -46,    98,   -46,   176,
     -46,    49,    37,   -46,   -46,    20,   -46,   -46,   -46,    -2,
      96,   192,   -46,    61,    99,    87,    92,   105,   119,   -46,
     -46,   150,   114,   133,   -46,   126,   148,   166,   153,   -46,
     -46,   -46,   -46,   -46,   134,   -46,   163,   -46,    20,   -46,
       5,   -46,   202,   -46,   166,    -9,   -46,   -46,   166,   168,
     -46,   -46,   166,   166,   166,   155,   177,    50,   -46,   -46,
     172,    61,   166,   166,   130,   -46,   120,   139,   -46,   162,
      17,   179,   -46,    -6,   120,   169,   -46,   -46,    57,   -46,
      89,   166,   166,   -46,   166,   166,   166,   166,   166,   166,
     178,   -46,    63,    93,   -46,     5,   -46,   166,   -46,   160,
     173,   166,   -46,   -46,   -46,   -46,   -46,   189,   164,   104,
       8,   137,    77,    36,     1,   -46,   -46,   113,   202,   -46,
     -46,   131,   -46,   -46,   120,   -46,   -46,   -46,   181,     6,
     183,   202,   -46,   -46,   -46,   203,   -46,   -46,   -46,   182,
     202,   -46,   -46
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -46,   -46,   -46,   -46,   -29,   -46,   -46,   -46,   -46,   -46,
     -46,   -46,   -46,   -46,   -46,   -46,   -46,   194,   -46,   -22,
     175,   -46,   -46,   -30,   -46,   -46,   -46,   -46,   -46,   -46,
     -46,   -46,   -46,   -46,   -46,   -46,   -46,   -46,   -46,   -46,
     -46,   -46,   -46,   -45,   -46,   -19,    94,   -46,   -46,   -46
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -64
static const yytype_int16 yytable[] =
{
      41,    52,    77,    45,    53,   120,    70,    91,    46,   101,
     121,    71,    41,    72,    73,    74,   101,   154,    92,    90,
       4,    20,   155,    94,    47,   101,     1,    96,    97,    98,
      75,    76,    89,    85,   118,   109,    84,   112,   113,   106,
     107,   108,   109,    41,   101,    21,   104,   105,   106,   107,
     108,   109,   111,    43,    44,     5,   128,   129,   101,   130,
     131,   132,   133,   134,   135,   101,   102,     7,   123,   108,
     109,   101,   141,     8,   138,    42,   144,   103,    11,   104,
     105,   106,   107,   108,   109,   101,   104,   105,   106,   107,
     108,   109,   104,   105,   106,   107,   108,   109,    15,    15,
      48,   101,    16,    16,   139,   124,   125,    56,   150,   107,
     108,   109,   101,    26,   147,    58,   126,    54,   148,    41,
      65,   158,   104,   105,   106,   107,   108,   109,   101,    60,
     162,   146,    41,   104,   105,   106,   107,   108,   109,   101,
      62,    41,    43,    67,    82,   101,    43,   114,   152,   104,
     105,   106,   107,   108,   109,   115,   116,    64,    21,   -63,
     104,   105,   106,   107,   108,   109,   104,    70,   106,   107,
     108,   109,    71,    83,    72,    73,    74,    28,    80,    95,
      -8,    47,   110,    99,   117,   119,   122,   142,   -36,   136,
     143,    75,    76,    28,   -39,   145,   -41,   -47,   109,   -43,
     -45,    29,   156,    28,   -36,    51,   153,   161,   159,   140,
     -39,    27,   -41,   -47,   -36,   -43,   -45,    29,    66,     0,
     -39,     0,   -41,   -47,     0,   -43,   -45,    29
};

static const yytype_int16 yycheck[] =
{
      19,    31,    47,    25,    33,    11,     1,    16,    10,     8,
      16,     6,    31,     8,     9,    10,     8,    11,    27,    64,
      10,     1,    16,    68,    26,     8,     3,    72,    73,    74,
      25,    26,    62,    28,    17,    34,    58,    82,    83,    31,
      32,    33,    34,    62,     8,    25,    29,    30,    31,    32,
      33,    34,    81,    16,    17,     0,   101,   102,     8,   104,
     105,   106,   107,   108,   109,     8,    16,    11,    11,    33,
      34,     8,   117,    12,    11,    26,   121,    27,    14,    29,
      30,    31,    32,    33,    34,     8,    29,    30,    31,    32,
      33,    34,    29,    30,    31,    32,    33,    34,     1,     1,
       4,     8,     5,     5,    11,    16,    17,    20,   138,    32,
      33,    34,     8,    15,     1,    23,    27,    18,     5,   138,
       6,   151,    29,    30,    31,    32,    33,    34,     8,    24,
     160,    27,   151,    29,    30,    31,    32,    33,    34,     8,
      21,   160,    16,    17,    10,     8,    16,    17,    17,    29,
      30,    31,    32,    33,    34,    16,    17,     7,    25,    11,
      29,    30,    31,    32,    33,    34,    29,     1,    31,    32,
      33,    34,     6,    10,     8,     9,    10,     1,    25,    11,
       4,    26,    10,     6,    22,     6,    17,    27,    12,    11,
      17,    25,    26,     1,    18,     6,    20,    21,    34,    23,
      24,    25,    19,     1,    12,    13,    25,    25,     5,   115,
      18,    17,    20,    21,    12,    23,    24,    25,    43,    -1,
      18,    -1,    20,    21,    -1,    23,    24,    25
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,    36,    38,    10,     0,    37,    11,    12,    39,
      40,    14,    49,    50,    41,     1,     5,    51,    52,    42,
       1,    25,    54,    55,    56,    53,    15,    52,     1,    25,
      43,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      74,    80,    26,    16,    17,    54,    10,    26,     4,    44,
      46,    13,    58,    39,    18,    66,    20,    69,    23,    71,
      24,    72,    21,    73,     7,     6,    55,    17,    75,    76,
       1,     6,     8,     9,    10,    25,    26,    78,    80,    83,
      25,    45,    10,    10,    54,    28,    78,    79,    81,    58,
      78,    16,    27,    77,    78,    11,    78,    78,    78,     6,
      82,     8,    16,    27,    29,    30,    31,    32,    33,    34,
      10,    39,    78,    78,    17,    16,    17,    22,    17,     6,
      11,    16,    17,    11,    16,    17,    27,    84,    78,    78,
      78,    78,    78,    78,    78,    78,    11,    47,    11,    11,
      81,    78,    27,    17,    78,     6,    27,     1,     5,    48,
      58,    70,    17,    25,    11,    16,    19,    67,    58,     5,
      68,    25,    58
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1455 of yacc.c  */
#line 739 "prueba.y"
    {generaFich();}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 739 "prueba.y"
    {fputs("\n}\n",fi);}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 741 "prueba.y"
    { TS_InsertaMARCA();}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 743 "prueba.y"
    {	if(varPrinc==1){ 
					varPrinc=0; 
					fputs("int main(){\n",fi);
				}
			}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 751 "prueba.y"
    {	TS_VaciarENTRADAS(); 
			}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 754 "prueba.y"
    {fi = fp;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 757 "prueba.y"
    {subProg = 1;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 757 "prueba.y"
    {fputs("\n}\n",fi); if(subProg == 0) {fi = f;} subProg = 0;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 760 "prueba.y"
    {	TS_InsertaSubprog((yyvsp[(2) - (3)]));
								genera_procedimiento((yyvsp[(2) - (3)]));
								
							}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 764 "prueba.y"
    {fputs("){\n",fi);}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 766 "prueba.y"
    {	TS_InsertaSubprog((yyvsp[(2) - (4)]));
									genera_procedimiento((yyvsp[(2) - (4)]));
									fputs("){\n",fi);
								}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 772 "prueba.y"
    {TS_InsertaParam((yyvsp[(4) - (4)]));
						fputs(", ",fi);
						genera_parametro((yyvsp[(3) - (4)]),(yyvsp[(4) - (4)]));
					}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 777 "prueba.y"
    {TS_InsertaParam((yyvsp[(2) - (2)]));
						genera_parametro((yyvsp[(1) - (2)]),(yyvsp[(2) - (2)]));						
					}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 783 "prueba.y"
    { decVar = 1; }
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 783 "prueba.y"
    { decVar = 0; }
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 790 "prueba.y"
    {tipoTMP = (yyvsp[(1) - (1)]).tipo;tipoArray = (yyvsp[(1) - (1)]).tipo;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 792 "prueba.y"
    {fprintf(stderr,"[Linea %d]: %s no es un tipo.\n",linea_actual,(yyvsp[(1) - (3)]).lexema);}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 795 "prueba.y"
    {	if(decVar){existeVar((yyvsp[(3) - (3)]));
							TS_InsertaIdent((yyvsp[(3) - (3)]));
							//if(subProg == 0){
								generaDecVar((yyvsp[(3) - (3)]));
							//}
						}
						
					}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 804 "prueba.y"
    {	if(decVar){ existeVar((yyvsp[(1) - (1)]));
							TS_InsertaIdent((yyvsp[(1) - (1)]));
							//if(subProg == 0){
								generaDecVar((yyvsp[(1) - (1)]));
							//}
						}
					}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 813 "prueba.y"
    {(yyval).tipo=asignaTipo((yyvsp[(1) - (1)]));}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 817 "prueba.y"
    {tipoTMP = array;dim = 1;tamdim1=atoi((yyvsp[(3) - (4)]).lexema);tamdim2=0;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 819 "prueba.y"
    {tipoTMP = array;dim = 2;tamdim1=atoi((yyvsp[(3) - (6)]).lexema);tamdim2=atoi((yyvsp[(5) - (6)]).lexema);}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 823 "prueba.y"
    {	if(decIF==1){ 
						{insertaCond(1);} 
						fputs("{\n",fi);
						decIF++;
					}
				}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 830 "prueba.y"
    { decIF=1;insertaDesc(1);}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 832 "prueba.y"
    {decIF = 0;eliminaDesc();}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 833 "prueba.y"
    {	if(decIF==1){ 
							insertaCond(1);
							fputs("{\n",fi);
							decIF++;	
						}
						insertaDesc(2);
						insertaEtiqEntrada();
						fputs("{\n",fi);
					}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 842 "prueba.y"
    {	if(decIF==1){ 
							insertaCond(1);
							fputs("{\n",fi);
							decIF++;
						}
					}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 848 "prueba.y"
    {	if(decIF==1){ 
							insertaCond(1);
							fputs("{\n",fi);
							decIF++;
						}
					}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 854 "prueba.y"
    {	if(decIF==1){ 
							insertaCond(1);
							fputs("{\n",fi);
							decIF++;
						}
					}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 864 "prueba.y"
    {	(yyval).tipo =  compruebaTipos2((yyvsp[(1) - (4)]),(yyvsp[(2) - (4)]),(yyvsp[(3) - (4)]));
									if(decIF==1){ 
										insertaCond(1);
										fputs("{\n",fi);
										decIF++;
									}
									genera(4,(yyvsp[(1) - (4)]),(yyvsp[(2) - (4)]),(yyvsp[(3) - (4)]),(yyvsp[(4) - (4)]));
								}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 875 "prueba.y"
    {	if((yyvsp[(3) - (5)]).tipo != booleano) 
							fprintf(stderr,"[Linea %d]: no hay expresion tipo logica \n",linea_si);
						(yyval).var = (yyvsp[(3) - (5)]).var;
						fputs("}\n",fi);
						insertaEtiqElse();
						fputs("{}\n",fi);
					}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 884 "prueba.y"
    {	if((yyvsp[(3) - (6)]).tipo != booleano) 
							fprintf(stderr,"[Linea %d]: no hay expresion tipo logica \n",linea_si);
							(yyval).var = (yyvsp[(3) - (6)]).var;
					}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 889 "prueba.y"
    {decElse=1;fputs("}\n",fi);insertaEtiqElse();fputs("{\n",fi);decElse=0;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 890 "prueba.y"
    {fputs("}\n",fi);insertaEtiqSalida();fputs("{}\n",fi);}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 892 "prueba.y"
    {insertaCond(2);}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 893 "prueba.y"
    {	if((yyvsp[(3) - (6)]).tipo != booleano) 
								fprintf(stderr,"[Linea %d]: no hay expresion tipo logica \n",linea_si);
							
							(yyval).var = (yyvsp[(3) - (6)]).var;
							fputs("}\n",fi);
							insertaGotoEntrada();
							insertaEtiqSalida();
							fputs("{}\n",fi);
						}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 904 "prueba.y"
    {generaEntSal(1,(yyvsp[(2) - (3)]));}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 906 "prueba.y"
    {generaEntSal(2,(yyvsp[(2) - (3)]));}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 909 "prueba.y"
    {if((yyvsp[(4) - (5)]).tipo != booleano) 
									fprintf(stderr,"[Linea %d]: no hay expresion tipo logica \n",linea_si);}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 914 "prueba.y"
    { strcpy(idProc,(yyvsp[(1) - (2)]).lexema); proc =1; existeProc((yyvsp[(1) - (2)]));
									
								}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 918 "prueba.y"
    {proc = 0; /*verificaNumPar(posParam);*/ posParam=0;
									fputs((yyvsp[(1) - (6)]).lexema,fi);fputs("(",fi);fputs(llamada,fi);fputs(");\n",fi);
								}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 922 "prueba.y"
    {strcpy(idProc,(yyvsp[(1) - (2)]).lexema); proc =1; existeProc((yyvsp[(1) - (2)])); }
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 924 "prueba.y"
    {proc = 0; /*verificaNumPar(posParam);*/ posParam=0;
										fputs((yyvsp[(1) - (5)]).lexema,fi);fputs("();\n",fi);
									}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 930 "prueba.y"
    {	if(proc == 1) 
						{	posParam++;
							verificaParam((yyvsp[(3) - (3)]),posParam);
							copia_param(2,(yyvsp[(3) - (3)]));
						}
					}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 937 "prueba.y"
    {	if(proc == 1) 
							{	posParam++;
								verificaParam((yyvsp[(1) - (1)]),posParam);
								copia_param(1,(yyvsp[(1) - (1)]));
							}
						}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 946 "prueba.y"
    {	(yyval).tipo = (yyvsp[(2) - (3)]).tipo;
						(yyval).var = (yyvsp[(1) - (3)]).var;
					}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 950 "prueba.y"
    {	(yyval).tipo = (yyvsp[(2) - (2)]).tipo;
						(yyval).var = (char*) malloc(100);
						sprintf((yyval).var,"%s",temporal());
						fputs((yyvsp[(1) - (2)]).var,fi);
						fputs((yyval).var,fi);
						fputs("\n",fi);
					}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 958 "prueba.y"
    {	(yyval).tipo =  compruebaTipos((yyvsp[(1) - (3)]),(yyvsp[(2) - (3)]),(yyvsp[(3) - (3)]));
						(yyval).var = (char*) malloc(100);
						sprintf((yyval).var,"%s",temporal());
						genera(1,(yyval),(yyvsp[(1) - (3)]),(yyvsp[(2) - (3)]),(yyvsp[(3) - (3)]));
					}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 964 "prueba.y"
    {	(yyval).tipo = compruebaTipos((yyvsp[(1) - (3)]),(yyvsp[(2) - (3)]),(yyvsp[(3) - (3)]));
						(yyval).var = (char*) malloc(100);
						sprintf((yyval).var,"%s",temporal());
						genera(1,(yyval),(yyvsp[(1) - (3)]),(yyvsp[(2) - (3)]),(yyvsp[(3) - (3)]));
					}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 970 "prueba.y"
    {	(yyval).tipo = compruebaTipos((yyvsp[(1) - (3)]),(yyvsp[(2) - (3)]),(yyvsp[(3) - (3)]));
						(yyval).var = (char*) malloc(100);
						sprintf((yyval).var,"%s",temporal());
						genera(1,(yyval),(yyvsp[(1) - (3)]),(yyvsp[(2) - (3)]),(yyvsp[(3) - (3)]));
					}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 976 "prueba.y"
    {	(yyval).tipo = compruebaTipos((yyvsp[(1) - (3)]),(yyvsp[(2) - (3)]),(yyvsp[(3) - (3)]));
						(yyval).var = (char*) malloc(100);
						sprintf((yyval).var,"%s",temporal());
						genera(1,(yyval),(yyvsp[(1) - (3)]),(yyvsp[(2) - (3)]),(yyvsp[(3) - (3)]));
					}
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 982 "prueba.y"
    {	(yyval).tipo = compruebaTipos((yyvsp[(1) - (3)]),(yyvsp[(2) - (3)]),(yyvsp[(3) - (3)]));
						(yyval).var = (char*) malloc(100);
						sprintf((yyval).var,"%s",temporal());
						genera(1,(yyval),(yyvsp[(1) - (3)]),(yyvsp[(2) - (3)]),(yyvsp[(3) - (3)]));
					}
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 988 "prueba.y"
    {	(yyval).tipo = compruebaTipos((yyvsp[(1) - (3)]),(yyvsp[(2) - (3)]),(yyvsp[(3) - (3)]));
						(yyval).var = (char*) malloc(100);
						sprintf((yyval).var,"%s",temporal());
						genera(1,(yyval),(yyvsp[(1) - (3)]),(yyvsp[(2) - (3)]),(yyvsp[(3) - (3)]));
					}
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 994 "prueba.y"
    {(yyval).tipo = (yyvsp[(2) - (2)]).tipo;}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 996 "prueba.y"
    {	(yyval).tipo = compruebaTipos((yyvsp[(1) - (3)]),(yyvsp[(2) - (3)]),(yyvsp[(3) - (3)]));
						(yyval).var = (char*) malloc(100);
						sprintf((yyval).var,"%s",temporal());
						genera(1,(yyval),(yyvsp[(1) - (3)]),(yyvsp[(2) - (3)]),(yyvsp[(3) - (3)]));
					}
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 1001 "prueba.y"
    {	
										(yyval).tipo = (yyvsp[(1) - (1)]).tipo;
									}
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 1004 "prueba.y"
    {(yyval).tipo = (yyvsp[(1) - (1)]).tipo;}
    break;

  case 83:

/* Line 1455 of yacc.c  */
#line 1011 "prueba.y"
    { (yyval).tipo=asignaTipo((yyvsp[(1) - (1)])); strcpy((yyval).lexema,(yyvsp[(1) - (1)]).lexema); }
    break;

  case 84:

/* Line 1455 of yacc.c  */
#line 1013 "prueba.y"
    {	(yyval).tipo=asignaTipoArray((yyvsp[(1) - (4)])); strcpy((yyval).lexema,(yyvsp[(1) - (4)]).lexema); }
    break;

  case 85:

/* Line 1455 of yacc.c  */
#line 1015 "prueba.y"
    {	(yyval).tipo=asignaTipoArray((yyvsp[(1) - (6)]));strcpy((yyval).lexema,(yyvsp[(1) - (6)]).lexema); }
    break;

  case 86:

/* Line 1455 of yacc.c  */
#line 1018 "prueba.y"
    {	(yyval).tipo = (yyvsp[(1) - (1)]).tipo;
					(yyval).var = (yyvsp[(1) - (1)]).var;
				}
    break;

  case 87:

/* Line 1455 of yacc.c  */
#line 1022 "prueba.y"
    {	(yyval).var = (yyvsp[(1) - (1)]).var;
					(yyval).tipo = (yyvsp[(1) - (1)]).tipo;
				}
    break;



/* Line 1455 of yacc.c  */
#line 2809 "y.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1675 of yacc.c  */
#line 1036 "prueba.y"

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



