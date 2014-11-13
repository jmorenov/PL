#ifndef lint
static char yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93";
#endif
#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define yyclearin (yychar=(-1))
#define yyerrok (yyerrflag=0)
#define YYRECOVERING (yyerrflag!=0)
#define YYPREFIX "yy"
#line 7 "trad.y"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "msj.err"
#include "regTrad.h"

#define CAMPO_NULO 255

#define YYSTYPE char *

extern int yylineno;
extern char *yytext;

extern Traduccion rgls[MAX_REGLAS];
extern int nRgls;

int indxRegla = 0;
int indxCampo = 0;
int i;

/******************
int tipoTemp;
char *argTemp;

int tipos[MAX_CAMPOS];
char *args[MAX_CAMPOS];
*************************/
#line 40 "y.tab.c"
#define ID 257
#define STRING 258
#define VAR 259
#define CAD 260
#define TIPO 261
#define CAD_OPC 262
#define REGLA 263
#define FIN_REGLA 264
#define YYERRCODE 256
short yylhs[] = {                                        -1,
    0,    0,    3,    1,    2,    2,    4,    4,    4,    4,
    4,    4,
};
short yylen[] = {                                         2,
    2,    1,    0,    5,    2,    1,    1,    1,    1,    1,
    1,    0,
};
short yydefred[] = {                                      0,
    0,    0,    2,    3,    1,    0,   11,    9,    7,    8,
   10,    0,    6,    4,    5,
};
short yydgoto[] = {                                       2,
    3,   12,    6,   13,
};
short yysindex[] = {                                   -250,
 -252, -250,    0,    0,    0, -251,    0,    0,    0,    0,
    0, -258,    0,    0,    0,
};
short yyrindex[] = {                                      0,
    0,    0,    0,    0,    0, -249,    0,    0,    0,    0,
    0,    0,    0,    0,    0,
};
short yygindex[] = {                                      0,
   10,    0,    0,    2,
};
#define YYTABLESIZE 15
short yytable[] = {                                       7,
    8,    9,   10,   11,    4,   14,    7,    8,    9,   10,
   11,    5,    1,   15,   12,
};
short yycheck[] = {                                     258,
  259,  260,  261,  262,  257,  264,  258,  259,  260,  261,
  262,    2,  263,   12,  264,
};
#define YYFINAL 2
#ifndef YYDEBUG
#define YYDEBUG 1
#endif
#define YYMAXTOKEN 264
#if YYDEBUG
char *yyname[] = {
"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"ID","STRING","VAR","CAD","TIPO",
"CAD_OPC","REGLA","FIN_REGLA",
};
char *yyrule[] = {
"$accept : ESQUEMA",
"ESQUEMA : ESQUEMA DEC_REGLA",
"ESQUEMA : DEC_REGLA",
"$$1 :",
"DEC_REGLA : REGLA ID $$1 LISTA_CAMPOS FIN_REGLA",
"LISTA_CAMPOS : LISTA_CAMPOS TIPO_CAMPO",
"LISTA_CAMPOS : TIPO_CAMPO",
"TIPO_CAMPO : CAD",
"TIPO_CAMPO : TIPO",
"TIPO_CAMPO : VAR",
"TIPO_CAMPO : CAD_OPC",
"TIPO_CAMPO : STRING",
"TIPO_CAMPO :",
};
#endif
#ifndef YYSTYPE
typedef int YYSTYPE;
#endif
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 500
#define YYMAXDEPTH 500
#endif
#endif
int yydebug;
int yynerrs;
int yyerrflag;
int yychar;
short *yyssp;
YYSTYPE *yyvsp;
YYSTYPE yyval;
YYSTYPE yylval;
short yyss[YYSTACKSIZE];
YYSTYPE yyvs[YYSTACKSIZE];
#define yystacksize YYSTACKSIZE
#line 106 "trad.y"

void yyerror(char *s)
{
	fprintf(stderr, "ERROR (Linea %d) %s y aparece %s\n"
		, yylineno, s, yytext);
}

/********
int main() {
	yyparse();
	return 0;
	}
 *******************/



#line 159 "y.tab.c"
#define YYABORT goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR goto yyerrlab
int
yyparse()
{
    register int yym, yyn, yystate;
#if YYDEBUG
    register char *yys;
    extern char *getenv();

    if (yys = getenv("YYDEBUG"))
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = (-1);

    yyssp = yyss;
    yyvsp = yyvs;
    *yyssp = yystate = 0;

yyloop:
    if (yyn = yydefred[yystate]) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yyssp >= yyss + yystacksize - 1)
        {
            goto yyoverflow;
        }
        *++yyssp = yystate = yytable[yyn];
        *++yyvsp = yylval;
        yychar = (-1);
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;
#ifdef lint
    goto yynewerror;
#endif
yynewerror:
    yyerror(msjerror[yystate]);
#ifdef lint
    goto yyerrlab;
#endif
yyerrlab:
    ++yynerrs;
yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yyssp]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yyssp, yytable[yyn]);
#endif
                if (yyssp >= yyss + yystacksize - 1)
                {
                    goto yyoverflow;
                }
                *++yyssp = yystate = yytable[yyn];
                *++yyvsp = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yyssp);
#endif
                if (yyssp <= yyss) goto yyabort;
                --yyssp;
                --yyvsp;
            }
        }
    }
    else
    {
        if (yychar == 0) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = (-1);
        goto yyloop;
    }
yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    yyval = yyvsp[1-yym];
    switch (yyn)
    {
case 3:
#line 43 "trad.y"
{
	/**********
	printf("Regla: %d id: %s\n", indxRegla, $2);
	printf("\tFormato: %s\n", $4);
	***************/

	rgls[indxRegla].nombre = strdup(yyvsp[0]);
	free(yyvsp[0]);	

	rgls[indxRegla].numCampos = 0;
	indxCampo = 0;
	}
break;
case 4:
#line 56 "trad.y"
{
	/*********
	printf("Fin regla: %d\n", indxRegla);
	*************/

	indxRegla++;
	nRgls++;
	}
break;
case 7:
#line 71 "trad.y"
{
	rgls[indxRegla].numCampos++;
	rgls[indxRegla].tipos[indxCampo] = ARG_CAD;
	indxCampo++;
	}
break;
case 8:
#line 77 "trad.y"
{
	rgls[indxRegla].numCampos++;
	rgls[indxRegla].tipos[indxCampo] = ARG_TIPO;
	indxCampo++;
	}
break;
case 9:
#line 83 "trad.y"
{
	rgls[indxRegla].numCampos++;
	rgls[indxRegla].tipos[indxCampo] = ARG_VAR;
	indxCampo++;
	}
break;
case 10:
#line 89 "trad.y"
{
	rgls[indxRegla].numCampos++;
	rgls[indxRegla].tipos[indxCampo] = ARG_CAD_OPC;
	indxCampo++;
	}
break;
case 11:
#line 95 "trad.y"
{
	rgls[indxRegla].numCampos++;
	rgls[indxRegla].tipos[indxCampo] = ARG_STRING;
	rgls[indxRegla].args[indxCampo] = strdup(yyvsp[0]);
	free(yyvsp[0]);
	indxCampo++;
	}
break;
#line 368 "y.tab.c"
    }
    yyssp -= yym;
    yystate = *yyssp;
    yyvsp -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yyssp = YYFINAL;
        *++yyvsp = yyval;
        if (yychar < 0)
        {
            if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
            if (yydebug)
            {
                yys = 0;
                if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
                if (!yys) yys = "illegal-symbol";
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == 0) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yyssp, yystate);
#endif
    if (yyssp >= yyss + yystacksize - 1)
    {
        goto yyoverflow;
    }
    *++yyssp = yystate;
    *++yyvsp = yyval;
    goto yyloop;
yyoverflow:
    yyerror("yacc stack overflow");
yyabort:
    return (1);
yyaccept:
    return (0);
}
