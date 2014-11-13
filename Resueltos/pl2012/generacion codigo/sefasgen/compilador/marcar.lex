%{
/* Fichero: marcar.lex
 * Analizador de especificacion YACC
 * Inserta llamadas a funcion para informar()
 * de la situacion en el texto de cada Accion SEMANTICA
 * void informar(int numRegla, int numCar)
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_CAD 200

/*********** A partir de aqui VALE *********/

char flag;
int numCar = 0;
int tamPet;
int tam, n;
char *cadPet;
char *msj;

/****** char *cadInformar = "informar(";	***/

%}

LETRA	[a-zA-Z]
digito	[0-9]
alnum	[a-zA-Z_0-9]
blanco	[ \t]

DEST	[a-zA-Z0-9$.]
ARG	[a-zA-Z0-9$.&_]
SEP	([ \n\t]*,[ \n\t]*)

%option noyywrap
%option yylineno

%x ARGUM1 ARGUM2 FIN_PET

%%



({DEST}+" = ")?pet_{LETRA}+\(	{
				// fprintf(stderr, "INFO Empieza LEC_ARG\n");

				tamPet = yyleng;

				if ( tamPet > MAX_CAD ) {

					fprintf(stderr, "REALLOC cadPet");

					cadPet = (char *) realloc(cadPet
						, tamPet * sizeof(char));
					if ( cadPet == NULL ) {
						perror("REALLOC");
						exit(1);
						}
					}

				strcpy(cadPet, yytext);

				BEGIN ARGUM1;
				}

<ARGUM1>([ \n]+)?\"[^"\n]+\"		|
<ARGUM1>([ \n]+)?{ARG}+\({ARG}+\)	|
<ARGUM1>([ \n]+)?{ARG}+		{
			/**** Al menos tiene 1 argumento  ****/

			/**
			fprintf(stderr, "Reconocido 1 argumento\n");
			 **/

			tamPet += yyleng;

			if ( tamPet > MAX_CAD ) {

				fprintf(stderr, "REALLOC cadPet");

				cadPet = (char *) realloc(cadPet
					, tamPet * sizeof(char));
				if ( cadPet == NULL ) {
					perror("REALLOC");
					exit(1);
					}
				}


			strcat(cadPet, yytext);

			/**
			fprintf(stderr, "INFO Argum1: %s tam: %d\n"
				, yytext, yyleng);
			fprintf(stderr, "INFO cadPet: %s\n", cadPet);
			 **/

			BEGIN ARGUM2;
			}

<ARGUM1,ARGUM2>");"	{

		/***************************************
		 Hemos llegado al final de la peticion
		 Generamos la llamada a informar
		 ***************************************/

		tamPet += yyleng;

		if ( tamPet > MAX_CAD ) {

			fprintf(stderr, "REALLOC cadPet");

			cadPet = (char *) realloc (cadPet, tamPet * sizeof(char));
			if ( cadPet == NULL ) {
				perror("Mem REALLOC cadPet");
				exit(1);
				}
			}

		cadPet = strcat(cadPet, yytext);

		// strcpy(&cadPet[tamPet-yyleng], yytext);

		tam = tamPet + 14 + 20;

		if ( tam > MAX_CAD ) {

			fprintf(stderr, "REALLOC msj");

			msj = (char *) realloc(msj, tam * sizeof(char));
			if ( msj == NULL ) {
				perror("MEM msj");
				exit(1);
				}
			}


		do {
			flag = 0;

			n = snprintf(msj, tam, "informar(%d, %d); %s"
				, numCar, tamPet, cadPet);

			if (n > -1 && n < tam) {
				// Ha funcionado
				flag = 1;
			} else {
				if (n > -1)	/* glibc 2.1 */
					tam = n+1;
				else		/* glibc 2.0 */
					tam *= 2;
	
				msj = (char *) realloc(msj
					, tam * sizeof(char));

				if ( msj == NULL ) {
					perror("MEM msj");
					exit(1);
					}
				}

		} while ( flag == 0 );

		tam = strlen(msj);
		printf("%s", msj);
		numCar += tam;

		fprintf(stderr, "RECONOCIDA PETICION:\n%s\n", msj);

		/*********   Que problema hay con msj ???    *********/
		// free(msj);
		// free(cadPet);

		BEGIN 0;
		}


<ARGUM2>{SEP}{ARG}+\({ARG}+\)	|
<ARGUM2>{SEP}{ARG}+		{
		/*************************  
		 Añadimos nuevo argumento
		 *************************/

		/***
		fprintf(stderr, "NUEVO argumento: %s\n", yytext);
		 **/

		tamPet += yyleng;

		if ( tamPet > MAX_CAD ) {

			fprintf(stderr, "REALLOC cadPet");

			cadPet = (char *) realloc(cadPet, tamPet * sizeof(char));
			if ( cadPet == NULL ) {
				perror("REALLOC cadPet");
				exit(1);
				}
			}

		strcat(cadPet, yytext);
		}

<ARGUM1,ARGUM2>.	{
			fprintf(stderr, "ERROR Se escapo: %s\n", yytext);

			// free(cadPet);
			BEGIN 0;
			}

(.|\n)		{
		ECHO;
		numCar += yyleng;
		}

%%

int main()
{
	msj = (char *) malloc (200 * sizeof(char));
	if ( msj == NULL ) {
		perror("Mem msj INICIO");
		exit(1);
		}

	cadPet = (char *) malloc(200 * sizeof(char));
	if ( cadPet == NULL ) {
		perror("Mem cadPet INICIO");
		exit(1);
		}

	yylex();

	free(msj);
	free(cadPet);

	fprintf(stderr, "FIN ANALISIS\n");

	return 0;
}

