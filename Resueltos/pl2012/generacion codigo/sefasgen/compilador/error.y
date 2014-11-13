void yyerror(char *s)
{
	fprintf(stderr, "HIJO SINTACTICO Error-> (Linea %d) %s y aparece %s\n"
		, yylineno, s, yytext);
}
