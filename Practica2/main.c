/*********************************************************
**
** Fichero: MAIN.C
** Función: Pruebas de FLEX para practicas Proc.Leng
**
*********************************************************/
#include <stdio.h>
#include <stdlib.h>
extern FILE *yyin ;
FILE *abrir_entrada( int argc, char *argv[] )
{
	FILE *f= NULL ;
	if ( argc > 1 )
	{
		f= fopen(argv[1],"r");
		if (f==NULL)
		{
			fprintf(stderr,"fichero ’%s’ no encontrado\n",argv[1]);
			exit(1);
		}
		else
			printf("leyendo fichero ’%s’.\n",argv[1]);
	}
	else
		printf("leyendo entrada estándar.\n");

	return f ;
}

/************************************************************/
int main( int argc, char *argv[] )
{
	yyin= abrir_entrada(argc,argv) ;
	int val;	
	val = yylex();
	while (val != 0)
	{	printf ("%d ", val) ;
		val= yylex() ;
	}

	exit (0);
}