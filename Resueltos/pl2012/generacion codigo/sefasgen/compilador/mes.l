%{
	static unsigned n_estado = 0;
	static unsigned i=0;
	char simbolo[256];

%}

digito [0-9]
letra [a-zA-Z._]

%option noyywrap

%%

state.{digito}+.*        {if (n_estado>0) printf("\", \n");
				else printf("char *msjerror[]={ \n");

			printf(" \t \" Error (%d) esperaba ", n_estado);
			++n_estado;}

{letra}+..((shift)|(reduce)|(accept)).*    {
				i=0;
				while (i<256)
					{simbolo[i]=0; ++i;}
				 i=0;
				while ((yytext[i]!=' ')&&(i < yyleng))
				       { simbolo[i]=yytext[i];
					++i;}
				 if ( !(((simbolo[0]=='e')&&
					(simbolo[1]=='r')&&
					(simbolo[2]=='r')&&
					(simbolo[3]=='o')&&
					(simbolo[4]=='r'))||
					(simbolo[0] =='.')))
					{if ((simbolo[0]=='e')&&
					     (simbolo[1]=='n')&&
					     (simbolo[2]=='d'))
					     printf("FIN_DE_PROGRAMA ");
					else printf("%s ",simbolo);};

					}

\n
.    ;
%%
main()
{
	yylex();
	printf("\" };\n");
}
