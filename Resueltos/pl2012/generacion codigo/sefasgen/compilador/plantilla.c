#include "msj.err"

void yyerror(char *s)
{
	fprintf(stderr, "[ERR] SINTACTICO Error(Linea %d): %s y aparece %s\n"
		, yylineno, s, yytext);
};


int main(int argc, char *argv[])
	{
	char msj[6], msjResp[4];
	int nbytes, res;

	if ( argc != 2 ) {
		fprintf(stderr, "COMPILADOR Num args incorrecto!!!\n");
		fprintf(stderr, "COMP Uso: %s <cod_fuente>\n", argv[0]);
		exit(0);
	} else {
		yyin = fopen(argv[1], "r");

		if ( yyin == NULL ) {
			fprintf(stderr, "ERROR apertura fichero: %s\n"
				,argv[1]);
			exit(1);
			}
		}

	// Debemos esperar mensaje de comienzo del padre !!!

	nbytes = read(0, msj, 6 * sizeof(char));

	fprintf(stderr, "Compilador empieza: %s\n", msj);

	if ( strcmp(msj, "FINAL") == 0 ) {
		// Debemos terminar....
		// fclose(yyin);
		// Nos despedimos...
		strcpy(msjResp, "PRE");
		nbytes = write(1, msjResp, 4 * sizeof(char));
		fprintf(stderr, "COMP termino antes de EMPEZAR\n");

		exit(0);
		}

		
	flagREI = 0;

	res = yyparse();

	if ( res == 1 ) {

		// Recibida orden de REINICIAR
		// Cuidado !!! Puede ser error SINTACTICO
		fprintf(stderr, "Compilador recibio REINICIAR...\n");
		strcpy(msj, "ACK");
		write(1, msj, 4 * sizeof(char));
		reiniciar();

	} else {

		// FIN ANALISIS
		fprintf(stderr, "TERMINO ANALISIS\n");

		// Mandamos mensaje de FIN al padre

		strcpy(msj, "F");
		nbytes = write(1, msj, sizeof(char));

		// y esperamos respuesta

		fprintf(stderr, "COMPILADOR esperando...\n");
		nbytes = read(0, msj, 4 * sizeof(char));
		if ( strcmp(msj, "REI") == 0 ) {
			// Empezamos de nuevo
			reiniciar();
		} else if ( strcmp(msj, "FIN") == 0 ) {
			// Papa quiere que terminemos...
			// Le respondemos y nos vamos
			strcpy(msj, "ACK");
			nbytes = write(1, msj, 4 * sizeof(char));
			}

		fprintf(stderr, "PAPA ya no quiere mas de mi\n");
		}


	return 0;
	}
