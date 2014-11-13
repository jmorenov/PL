#ifndef lint
/*static char yysccsid[] = "from: @(#)yaccpar	1.9 (Berkeley) 02/21/93";*/
static char yyrcsid[] = "$Id: skeleton.c,v 1.2 1997/06/23 02:51:17 tdukes Exp $";
#endif
#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define yyclearin (yychar=(-1))
#define yyerrok (yyerrflag=0)
#define YYRECOVERING (yyerrflag!=0)
#define YYPREFIX "yy"
#line 2 "FINAL.y"

/**
 @todo Revisar gestion memoria dinamica...
*/

/* Basta incluir este archivo...*/

#include "sefasgen.h"


tDato tempTipoDato, tipoTemp, tipoAux;
int estado;
unsigned int flag = 0;

char *etqTemp;

int nParam = 0;
int contParam;
int totalParam;
unsigned char tipoOK;
int tamCadena;

/*-----------------------------------*/


#line 39 "y.tab.c"
#define PROCEDIMIENTO 257
#define DELIM_VAR1 258
#define DELIM_VAR2 259
#define LEER 260
#define ESCRIBIR 261
#define SI 262
#define SINO 263
#define MIENTRAS 264
#define SWITCH 265
#define CASO 266
#define SALTAR 267
#define DEFECTO 268
#define LLAVE_ABRE 269
#define LLAVE_CIERRA 270
#define PARENT_ABRE 271
#define PARENT_CIERRA 272
#define CORCHETE_ABRE 273
#define CORCHETE_CIERRA 274
#define PUNTO_COMA 275
#define COMA 276
#define TIPO 277
#define OP_ARIT12 278
#define OP_ARIT2 279
#define OP_LOGICO1 280
#define OP_LOGICO2 281
#define OP_LOGICO3 282
#define CADENA 283
#define IDENTIFICADOR 284
#define VALOR 285
#define OP_LISTAS1 286
#define OP_LISTAS2 287
#define OP_LISTAS3 288
#define DOSPUNTOS 289
#define PRINCIPAL 290
#define IGUAL 291
#define OP_LISTAS4 292
#define UNARIO 293
#define YYERRCODE 256
short yylhs[] = {                                        -1,
    3,    0,    1,    1,    5,    2,    4,    4,    4,    4,
    6,    6,   10,   10,   13,   11,   12,   12,   15,   14,
   16,   14,   14,    7,    7,   17,   19,   18,   20,   20,
   20,   21,   21,   22,   22,   22,   22,   22,   22,   22,
   22,   22,   22,   22,   23,   23,   23,   23,   24,   24,
   24,    8,    8,    9,    9,   25,   25,   25,   25,   25,
   26,   26,   26,   27,   34,   34,   34,   36,   28,   35,
   35,   38,   29,   37,   37,   37,   37,   31,   41,   42,
   39,   43,   40,   40,   32,   33,   44,   44,   44,   44,
   44,   45,   30,
};
short yylen[] = {                                         2,
    0,    3,    4,    1,    0,    4,    3,    3,    2,    2,
    3,    0,    2,    1,    0,    3,    2,    3,    0,    4,
    0,    3,    1,    2,    1,    2,    0,    6,    1,    0,
    1,    4,    2,    3,    3,    3,    3,    2,    1,    3,
    2,    1,    1,    1,    2,    2,    3,    5,    3,    1,
    3,    2,    2,    2,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    3,    3,    1,    0,    0,    3,    3,
    1,    0,    3,    3,    3,    1,    1,    2,    0,    0,
    7,    0,    3,    0,    5,    5,    5,    6,    5,    4,
    5,    0,    5,
};
short yydefred[] = {                                      0,
    4,    0,    0,    1,    0,    0,    0,    5,    2,    3,
    0,    0,    0,    0,   15,    0,   14,    6,   60,    0,
   68,   72,   79,    0,    0,    0,    0,    0,    0,   25,
    0,    0,   55,   56,   57,   58,   59,   61,   62,   63,
    0,    0,   11,   13,   27,    0,    0,    0,    0,    0,
    0,    0,    0,    0,   24,   52,   53,   26,   54,   82,
   78,   23,    0,   16,    0,    0,   71,    0,   44,    0,
    0,    0,   77,   43,   39,    0,    0,   42,    0,    0,
    0,    0,    0,    0,    0,   17,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,   45,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   50,
   83,   22,   18,    0,   31,    0,    0,    0,   70,   40,
    0,    0,    0,   37,    0,    0,   75,    0,   80,   85,
    0,    0,    0,   86,   93,    0,    0,    0,   20,   33,
   28,    0,    0,    0,    0,    0,    0,    0,   49,   51,
    0,    0,   81,    0,    0,    0,   32,   91,    0,   89,
   88,
};
short yydgoto[] = {                                       3,
    4,    9,    6,   13,   11,   14,   27,   28,  110,   16,
   17,   64,   42,   65,  114,   87,   30,   31,   66,  117,
  118,   77,   78,  111,   32,   33,   34,   35,   36,   37,
   38,   39,   40,  108,   68,   46,   79,   47,   41,   61,
   48,  144,   85,  106,   52,
};
short yysindex[] = {                                   -213,
    0, -271,    0,    0, -239, -227, -220,    0,    0,    0,
 -172, -208, -182, -147,    0, -232,    0,    0,    0, -153,
    0,    0,    0, -143, -152, -148, -147, -102, -102,    0,
 -227, -140,    0,    0,    0,    0,    0,    0,    0,    0,
 -117, -246,    0,    0,    0, -127, -210, -110, -250, -103,
 -250, -104, -102, -102,    0,    0,    0,    0,    0,    0,
    0,    0, -105,    0, -111,  -95,    0,  -99,    0, -250,
 -250, -250,    0,    0,    0, -250,   39,    0,  -98, -250,
   -6,  -82,   39, -250, -135,    0,  -85,  -87, -251,  -91,
    5,  -86, -222, -149, -250, -250, -250, -250,    0, -250,
 -250, -193,   16, -135,  -90, -248,   39, -214, -102,    0,
    0,    0,    0,  -77,    0,  -84,  -78,  -74,    0,    0,
   49,   52, -222,    0, -241,   27,    0,   39,    0,    0,
  -83,  -76,  -75,    0,    0, -250, -253, -120,    0,    0,
    0,  -66, -250, -135, -135,  -72, -135,   39,    0,    0,
  -64, -241,    0,  -55, -135,  -54,    0,    0,  -49,    0,
    0,
};
short yyrindex[] = {                                      0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
 -109,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  -44,    0,  -46,  -40,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
 -162,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  -38,  -34,    0,    0,    0,    0,    0,    0,
    0,    0,  -33,    0,    0,    0,    0,  -29,    0,    0,
    0,    0,    0,    0,    0,    0, -204,    0,  -16,    0,
    0,    0,  -13, -175,    0,    0,    0,  -12,  -43,    0,
    0, -107,  -41,  -53,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0, -165,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  -30,    0,    0,
  -18,  -23,  -31,    0,  -89,    0,    0, -156,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0, -160,    0,    0,
    0,  -71,    0, -189,    0,    0,    0,    0, -186,    0,
    0,
};
short yygindex[] = {                                      0,
    0,  232,    0,    0,    0,    0,    0,  -26,  -14,    0,
  249,    0,    0,    0,    0,    0,  240,    0,    0,    0,
    0,  -47,    0,  -88,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,
};
#define YYTABLESIZE 340
short yytable[] = {                                      29,
   53,   81,   19,   83,  115,   69,   21,   22,   23,   62,
   24,   25,   54,   56,   57,  130,  149,  132,    5,  133,
   70,  134,   91,   92,   93,  116,   43,   71,   94,   72,
   26,    7,  103,   74,   75,   76,  107,   63,   56,   57,
   98,    8,    1,    2,   15,   69,  101,  121,  122,  123,
  124,   10,  125,  126,  128,  153,  154,  135,  156,   98,
   70,  136,   69,   99,  100,  101,  159,   71,   15,   72,
   76,   76,   73,   74,   75,   76,   90,   70,   90,   87,
   90,   87,  137,   87,   71,   12,   72,   18,  148,  127,
   74,   75,   76,   84,  138,  152,   67,   84,   84,   84,
   67,   84,   84,   84,   84,   84,   66,   84,   19,   20,
   66,   65,   21,   22,   23,   65,   24,   25,   74,   74,
   19,   84,   56,   57,   21,   22,   23,   49,   24,   25,
   45,   50,   98,  109,   59,   19,   26,  100,  101,   21,
   22,   23,   51,   24,   25,   60,   12,   12,   26,  150,
   12,   12,   12,   19,   12,   12,   67,   21,   22,   23,
   80,   24,   25,   26,   38,   82,   84,   38,   38,   86,
   38,   38,   88,   38,   12,   89,   90,  102,   38,   38,
   38,   26,   47,  105,   38,   47,   47,  113,   47,   47,
  112,   47,  119,  141,  131,   98,   47,   47,  139,  140,
   48,  142,   47,   48,   48,  145,   48,   48,  146,   48,
  151,  158,  160,  147,   48,   48,  155,  161,   46,  157,
   48,   46,   46,    9,   46,   46,   92,   46,   30,   10,
   41,    7,   46,   41,   41,    8,   41,   41,   46,   41,
   36,   29,   21,   36,   36,   69,   36,   36,   35,   36,
   41,   35,   35,   34,   35,   35,   34,   34,   73,   34,
   36,   64,   58,   19,   44,  104,   55,    0,   35,    0,
    0,   95,   96,   34,   97,   98,  120,    0,    0,   99,
  100,  101,   95,   96,    0,   97,   98,  129,    0,    0,
   99,  100,  101,   95,   96,    0,   97,   98,    0,    0,
    0,   99,  100,  101,   95,   96,    0,   97,   98,    0,
    0,    0,   99,  100,  101,    0,   95,   96,  143,   97,
   98,    0,    0,    0,   99,  100,  101,   96,    0,   97,
   98,    0,   97,   98,   99,  100,  101,   99,  100,  101,
};
short yycheck[] = {                                      14,
   27,   49,  256,   51,  256,  256,  260,  261,  262,  256,
  264,  265,   27,   28,   29,  104,  270,  266,  290,  268,
  271,  270,   70,   71,   72,  277,  259,  278,   76,  280,
  284,  271,   80,  284,  285,  286,   84,  284,   53,   54,
  282,  269,  256,  257,  277,  256,  288,   95,   96,   97,
   98,  272,  100,  101,  102,  144,  145,  272,  147,  282,
  271,  276,  256,  286,  287,  288,  155,  278,  277,  280,
  275,  276,  283,  284,  285,  286,  266,  271,  268,  266,
  270,  268,  109,  270,  278,  258,  280,  270,  136,  283,
  284,  285,  286,  256,  109,  143,  272,  260,  261,  262,
  276,  264,  265,  266,  267,  268,  272,  270,  256,  257,
  276,  272,  260,  261,  262,  276,  264,  265,  275,  276,
  256,  284,  137,  138,  260,  261,  262,  271,  264,  265,
  284,  284,  282,  269,  275,  256,  284,  287,  288,  260,
  261,  262,  291,  264,  265,  263,  256,  257,  284,  270,
  260,  261,  262,  256,  264,  265,  284,  260,  261,  262,
  271,  264,  265,  284,  272,  269,  271,  275,  276,  275,
  278,  279,  284,  281,  284,  271,  276,  276,  286,  287,
  288,  284,  272,  266,  292,  275,  276,  275,  278,  279,
  276,  281,  284,  272,  285,  282,  286,  287,  276,  284,
  272,  276,  292,  275,  276,  289,  278,  279,  285,  281,
  277,  267,  267,  289,  286,  287,  289,  267,  272,  284,
  292,  275,  276,  270,  278,  279,  271,  281,  272,  270,
  272,  270,  286,  275,  276,  270,  278,  279,  292,  281,
  272,  272,  276,  275,  276,  275,  278,  279,  272,  281,
  292,  275,  276,  272,  278,  279,  275,  276,  275,  278,
  292,  275,   31,  276,   16,  272,   27,   -1,  292,   -1,
   -1,  278,  279,  292,  281,  282,  272,   -1,   -1,  286,
  287,  288,  278,  279,   -1,  281,  282,  272,   -1,   -1,
  286,  287,  288,  278,  279,   -1,  281,  282,   -1,   -1,
   -1,  286,  287,  288,  278,  279,   -1,  281,  282,   -1,
   -1,   -1,  286,  287,  288,   -1,  278,  279,  292,  281,
  282,   -1,   -1,   -1,  286,  287,  288,  279,   -1,  281,
  282,   -1,  281,  282,  286,  287,  288,  286,  287,  288,
};
#define YYFINAL 3
#ifndef YYDEBUG
#define YYDEBUG 1
#endif
#define YYMAXTOKEN 293
#if YYDEBUG
char *yyname[] = {
"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"PROCEDIMIENTO","DELIM_VAR1",
"DELIM_VAR2","LEER","ESCRIBIR","SI","SINO","MIENTRAS","SWITCH","CASO","SALTAR",
"DEFECTO","LLAVE_ABRE","LLAVE_CIERRA","PARENT_ABRE","PARENT_CIERRA",
"CORCHETE_ABRE","CORCHETE_CIERRA","PUNTO_COMA","COMA","TIPO","OP_ARIT12",
"OP_ARIT2","OP_LOGICO1","OP_LOGICO2","OP_LOGICO3","CADENA","IDENTIFICADOR",
"VALOR","OP_LISTAS1","OP_LISTAS2","OP_LISTAS3","DOSPUNTOS","PRINCIPAL","IGUAL",
"OP_LISTAS4","UNARIO",
};
char *yyrule[] = {
"$accept : PROGRAMA",
"$$1 :",
"PROGRAMA : CABECERA_PROGRAMA $$1 BLOQUE",
"CABECERA_PROGRAMA : PROCEDIMIENTO PRINCIPAL PARENT_ABRE PARENT_CIERRA",
"CABECERA_PROGRAMA : error",
"$$2 :",
"BLOQUE : LLAVE_ABRE $$2 CUERPO_BLOQUE LLAVE_CIERRA",
"CUERPO_BLOQUE : DEC_VAR DEC_PROCEDIMIENTOS BLQ_SENTENCIAS",
"CUERPO_BLOQUE : DEC_VAR DEC_PROCEDIMIENTOS SENTENCIA",
"CUERPO_BLOQUE : DEC_VAR BLQ_SENTENCIAS",
"CUERPO_BLOQUE : DEC_VAR SENTENCIA",
"DEC_VAR : DELIM_VAR1 CUERPO_DECLA_VARS DELIM_VAR2",
"DEC_VAR :",
"CUERPO_DECLA_VARS : CUERPO_DECLA_VARS DEC_TIPO",
"CUERPO_DECLA_VARS : DEC_TIPO",
"$$3 :",
"DEC_TIPO : TIPO $$3 CONJ_PALABRAS",
"CONJ_PALABRAS : IDENTIFICADOR PUNTO_COMA",
"CONJ_PALABRAS : LISTA_PALS IDENTIFICADOR PUNTO_COMA",
"$$4 :",
"LISTA_PALS : LISTA_PALS IDENTIFICADOR $$4 COMA",
"$$5 :",
"LISTA_PALS : IDENTIFICADOR $$5 COMA",
"LISTA_PALS : error",
"DEC_PROCEDIMIENTOS : DEC_PROCEDIMIENTOS DEC_PROC",
"DEC_PROCEDIMIENTOS : DEC_PROC",
"DEC_PROC : CABECERA BLOQUE",
"$$6 :",
"CABECERA : PROCEDIMIENTO IDENTIFICADOR $$6 PARENT_ABRE PARAMETROS PARENT_CIERRA",
"PARAMETROS : LISTA_PARAMS",
"PARAMETROS :",
"PARAMETROS : error",
"LISTA_PARAMS : LISTA_PARAMS COMA TIPO IDENTIFICADOR",
"LISTA_PARAMS : TIPO IDENTIFICADOR",
"EXPRESION : EXPRESION OP_ARIT12 EXPRESION",
"EXPRESION : EXPRESION OP_ARIT2 EXPRESION",
"EXPRESION : EXPRESION OP_LOGICO2 EXPRESION",
"EXPRESION : EXPRESION OP_LOGICO3 EXPRESION",
"EXPRESION : OP_ARIT12 EXPRESION",
"EXPRESION : VALOR",
"EXPRESION : PARENT_ABRE EXPRESION PARENT_CIERRA",
"EXPRESION : OP_LOGICO1 EXPRESION",
"EXPRESION : OPERAR_LISTA",
"EXPRESION : IDENTIFICADOR",
"EXPRESION : error",
"OPERAR_LISTA : EXPRESION OP_LISTAS1",
"OPERAR_LISTA : OP_LISTAS1 EXPRESION",
"OPERAR_LISTA : EXPRESION OP_LISTAS2 EXPRESION",
"OPERAR_LISTA : EXPRESION OP_LISTAS3 EXPRESION OP_LISTAS4 EXPRESION",
"SENTENCIAS : LLAVE_ABRE BLQ_SENTENCIAS LLAVE_CIERRA",
"SENTENCIAS : SENTENCIA",
"SENTENCIAS : LLAVE_ABRE SENTENCIA LLAVE_CIERRA",
"BLQ_SENTENCIAS : BLQ_SENTENCIAS SENTENCIA",
"BLQ_SENTENCIAS : SENTENCIA SENTENCIA",
"SENTENCIA : OP_SIMPLE PUNTO_COMA",
"SENTENCIA : OP_COMPUESTA",
"OP_SIMPLE : ASIG",
"OP_SIMPLE : ENTRADA",
"OP_SIMPLE : SALIDA",
"OP_SIMPLE : LLAMADA_PROCEDIMIENTO",
"OP_SIMPLE : error",
"OP_COMPUESTA : SENTENCIA_SI",
"OP_COMPUESTA : SENTENCIA_MIENTRAS",
"OP_COMPUESTA : SENTENCIA_EN_CASO",
"ASIG : IDENTIFICADOR IGUAL EXPRESION",
"LISTA_EXP : LISTA_EXP COMA EXPRESION",
"LISTA_EXP : EXPRESION",
"LISTA_EXP :",
"$$7 :",
"ENTRADA : LEER $$7 LISTA_IDS",
"LISTA_IDS : LISTA_IDS COMA IDENTIFICADOR",
"LISTA_IDS : IDENTIFICADOR",
"$$8 :",
"SALIDA : ESCRIBIR $$8 LISTA_ARG",
"LISTA_ARG : LISTA_ARG COMA EXPRESION",
"LISTA_ARG : LISTA_ARG COMA CADENA",
"LISTA_ARG : EXPRESION",
"LISTA_ARG : CADENA",
"SENTENCIA_SI : PARTE_IF PARTE_ELSE",
"$$9 :",
"$$10 :",
"PARTE_IF : SI $$9 PARENT_ABRE EXPRESION PARENT_CIERRA $$10 SENTENCIAS",
"$$11 :",
"PARTE_ELSE : SINO $$11 SENTENCIAS",
"PARTE_ELSE :",
"SENTENCIA_MIENTRAS : MIENTRAS PARENT_ABRE EXPRESION PARENT_CIERRA SENTENCIAS",
"SENTENCIA_EN_CASO : SWITCH IDENTIFICADOR LLAVE_ABRE LISTA_CASOS LLAVE_CIERRA",
"LISTA_CASOS : LISTA_CASOS CASO VALOR DOSPUNTOS SENTENCIAS",
"LISTA_CASOS : LISTA_CASOS CASO VALOR DOSPUNTOS SENTENCIAS SALTAR",
"LISTA_CASOS : LISTA_CASOS DEFECTO DOSPUNTOS SENTENCIAS SALTAR",
"LISTA_CASOS : CASO VALOR DOSPUNTOS SENTENCIAS",
"LISTA_CASOS : CASO VALOR DOSPUNTOS SENTENCIAS SALTAR",
"$$12 :",
"LLAMADA_PROCEDIMIENTO : IDENTIFICADOR $$12 PARENT_ABRE LISTA_EXP PARENT_CIERRA",
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
#line 1194 "FINAL.y"


#include "plantilla.c"
#line 393 "y.tab.c"
#define YYABORT goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR goto yyerrlab
#ifdef __cplusplus
extern "C" { 
char * getenv();
int yylex();
int yyparse();
}

#endif
int
#if defined(__STDC__)
yyparse(void)
#else
yyparse()
#endif
{
    register int yym, yyn, yystate;
#if YYDEBUG
    register char *yys;
#ifndef __cplusplus
    extern char *getenv();
#endif

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
    if ((yyn = yydefred[yystate]) != 0) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            fprintf(stderr,"%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            fprintf(stderr,"%sdebug: state %d, shifting to state %d\n",
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
                    fprintf(stderr,"%sdebug: state %d, error recovery shifting\
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
                    fprintf(stderr,"%sdebug: error recovery discarding state %d\n",
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
            fprintf(stderr,"%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = (-1);
        goto yyloop;
    }
yyreduce:
#if YYDEBUG
    if (yydebug)
        fprintf(stderr,"%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    yyval = yyvsp[1-yym];
    switch (yyn)
    {
case 1:
#line 53 "FINAL.y"
{ informar(942, 13); pet_GenIni(); }
break;
case 3:
#line 58 "FINAL.y"
{
	yyvsp[-2].tipoDato = NO_ASIG;
	informar(1087, 22); pet_introTS(yyvsp[-2], PROC);

	/*************************
	 MARCA
	 TODO: La MARCA se debe introducir al empezar el BLOQUE


	yylval.lexema = strdup("FIN_PARS");
	yylval.tipoDato = NO_ASIG;
	informar(1292, 27); pet_introTS(yylval, MARCA);
	********************************************************/
	}
break;
case 5:
#line 76 "FINAL.y"
{
	/*******  Aqui deberia INSERTARSE la MARCA !!!  ******/
	/*************************
	 MARCA
	 TODO: La MARCA se debe introducir al empezar el BLOQUE
	********************************************************/

	yylval.lexema = strdup("FIN_PARS");
	yylval.tipoDato = NO_ASIG;
	informar(1714, 27); pet_introTS(yylval, MARCA);

	informar(1764, 42); pet_GenIniBlq(NULL, yyvsp[0].colIni, yyvsp[0].colFin);
	}
break;
case 6:
#line 90 "FINAL.y"
{
	informar(1863, 14); pet_SacarTS();

	informar(1900, 16); pet_GenFinBlq();
	}
break;
case 15:
#line 112 "FINAL.y"
{ 
	/* Esta SI HACE FALTA que este ENMEDIO*/
	/* Si NO, Tenemos que esperar a reconocer TODO !!!*/
	tempTipoDato = yyvsp[0].tipoDato;
	}
break;
case 17:
#line 121 "FINAL.y"
{
	/* Modificado para permitir Localizacion de tokens */
	/* ORIGINAL: yylval.tipoDato tempTipoDato*/
	yyvsp[-1].tipoDato = tempTipoDato;
	informar(2547, 35); estado = pet_introTS(yyvsp[-1], VARIABLE);


	/* TODO: Solo generar la Declaracion de Variables*/
	/* si la peticion de Introduccion ha sido correcta !!!!!*/

	if ( estado ) {
		informar(2734, 38); pet_GenDecVar(yyvsp[-1].tipoDato, yyvsp[-1].lexema);
		}
	}
break;
case 18:
#line 136 "FINAL.y"
{
	/* Modificado para permitir Localizacion de tokens  */
	yyvsp[-1].tipoDato = tempTipoDato;
	informar(2926, 35); estado = pet_introTS(yyvsp[-1], VARIABLE);

	/* if ( flagREI ) YYABORT;*/

	if ( estado ) {
		informar(3031, 38); pet_GenDecVar(yyvsp[-1].tipoDato, yyvsp[-1].lexema);
		}
	}
break;
case 19:
#line 150 "FINAL.y"
{
	/* MOD */
	yyvsp[0].tipoDato = tempTipoDato;
	informar(3182, 35); estado = pet_introTS(yyvsp[0], VARIABLE);

	/* if ( flagREI ) YYABORT;*/

	if ( estado ) {
		informar(3287, 38); pet_GenDecVar(yyvsp[0].tipoDato, yyvsp[0].lexema);
		}
	}
break;
case 21:
#line 163 "FINAL.y"
{
	/* MOD */
	yyvsp[0].tipoDato = tempTipoDato;
	informar(3418, 35); estado = pet_introTS(yyvsp[0], VARIABLE);

	/* if ( flagREI ) YYABORT;*/

	if ( estado ) {
		informar(3523, 38); pet_GenDecVar(yyvsp[0].tipoDato, yyvsp[0].lexema);
		}
	}
break;
case 26:
#line 183 "FINAL.y"
{
	informar(3705, 20); pet_GenFinDecProc();
	}
break;
case 27:
#line 189 "FINAL.y"
{
	/* MOD */
	yyvsp[0].tipoDato = NO_ASIG;

	/* TODO: Hay que verificar que el PROC no esta declarado*/
	/* Si es asi NO generar CODIGO*/
	informar(3921, 31); estado = pet_introTS(yyvsp[0], PROC);

	if ( estado ) 
		informar(3992, 35); pet_GenDecProc(yyvsp[0].lexema, NO_ASIG);
	}
break;
case 28:
#line 201 "FINAL.y"
{
	informar(4094, 21); pet_GenFinCabecera();

	/***********************************************
	 Ahora metemos otra marca de bloque "}"
	 Nos servira para conservar los parametros
	 cuando acabe el bloque

	 NOOO !!!!  Solo 1 Marca por Bloque!!!
	yylval.tipoDato = NO_ASIG;
	yylval.nParam = -1;
	yylval.lexema = strdup("FIN_PARS");
	informar(4425, 27); pet_introTS(yylval, MARCA);
	************************************************/
	}
break;
case 30:
#line 220 "FINAL.y"
{
	informar(4564, 28); pet_GenParam(NO_ASIG, NULL);
	}
break;
case 32:
#line 227 "FINAL.y"
{
	yyvsp[0].tipoDato = yyvsp[-1].tipoDato;
	informar(4713, 37); estado = pet_introTS(yyvsp[0], PAR_FORMAL);

	if ( estado )
		informar(4789, 37); pet_GenParam(yyvsp[-1].tipoDato, yyvsp[0].lexema);
	}
break;
case 33:
#line 235 "FINAL.y"
{
	/* MOD3*/
	yyvsp[0].tipoDato = yyvsp[-1].tipoDato;
	informar(4913, 37); estado = pet_introTS(yyvsp[0], PAR_FORMAL);

	if ( estado )
		informar(4989, 37); pet_GenParam(yyvsp[-1].tipoDato, yyvsp[0].lexema);
	}
break;
case 34:
#line 246 "FINAL.y"
{
	/**********************************************
	  COMPROBACION DE TIPOS

	  NO SE PIDE LA ASIGNACION DE VALORES !!!!!!!
	  OP_ARIT12 = "+", "-"
	 **********************************************/

	if ( yyvsp[-2].tipoDato == yyvsp[0].tipoDato ) {
		/************************************************** 
		  La suma/resta se puede hacer para cualquier tipo
		  EXCEPTO para booleanos
		 **************************************************/

		if ( (yyvsp[-2].tipoDato != BOOLEANO) 
			&& (yyvsp[-2].tipoDato != LISTA_BOOLEANO) ) {

			yyval.tipoDato = yyvsp[-2].tipoDato;

			/* Hay que definir las operaciones para listas 	*/
			/* $2.nParam define la operacion		*/
			/* 1 = Suma, 2 = Resta				*/

			/*  operar(&($$), $1, $3, $2.nParam);*/
 
		} else {

			fprintf(stderr, "ERROR linea: %d ", yylineno);
			fprintf(stderr, "Op +/- con tipo de dato");
			fprintf(stderr, "incorrecto");

			yyval.tipoDato = DESC;
			}
	} else {

		fprintf(stderr, "ERROR linea: %d OP_A12 ", yylineno);
		fprintf(stderr, "Tipos no coinciden ");
		yyval.tipoDato = DESC;
		}

	/******************************************
	  Asignacion variables de localizacion
	  TODO: Verificacion TIPO por OPERADOR !!!
	 ******************************************/

	informar(6288, 31); estado = pet_VerifTIPO(yyvsp[-2], yyvsp[0]);

	yyval.linIni = yyvsp[-2].linIni;
	yyval.colIni = yyvsp[-2].colIni;
	yyval.linFin = yyvsp[0].linFin;
	yyval.colFin = yyvsp[0].colFin;

	informar(6439, 27); yyval.nomTemp = pet_GenTemp();

	if ( estado ) {
		yyval.tipoDato = yyvsp[-2].tipoDato;
		informar(6536, 39); pet_GenDecVar(yyval.tipoDato, yyval.nomTemp);

		fprintf(stderr, "ASIG %s = %s %s %s\n"
			, yyval.nomTemp, yyvsp[-2].nomTemp
			, yyvsp[-1].lexema, yyvsp[0].nomTemp);

		informar(6698, 66); pet_GenAsig(4, yyval.nomTemp, yyvsp[-2].nomTemp
			, yyvsp[-1].lexema, yyvsp[0].nomTemp);
	} else {
		yyval.tipoDato = DESC;
		}
	}
break;
case 35:
#line 315 "FINAL.y"
{
	/***********************************
	  Comprobacion de tipos
	 ***********************************/

	if ( yyvsp[-2].tipoDato == yyvsp[0].tipoDato ) {
		
		if ( (yyvsp[-2].tipoDato == BOOLEANO) 
			|| (yyvsp[-2].tipoDato == LISTA_BOOLEANO) ) {

			fprintf(stderr, "Error linea %d", yylineno);
			fprintf(stderr, " OP_A2 no definida para ");
			fprintf(stderr, "BOOLEANO o LISTA_BOOLEANO\n");

			yyval.tipoDato = DESC;
		
		} else {
			yyval.tipoDato = yyvsp[-2].tipoDato;
			}

	} else {
		fprintf(stderr, "Error linea: %d ", yylineno);
		fprintf(stderr, "OP_A2 Tipos no coinciden\n");
		yyval.tipoDato = DESC;
		}

	/***************************************
	  Asignacion variables de localizacion
	 ***************************************/

	/* TODO: Verificacion TIPO correcto para OPERADOR*/
	informar(7614, 31); estado = pet_VerifTIPO(yyvsp[-2], yyvsp[0]);

	yyval.linIni = yyvsp[-2].linIni;
	yyval.colIni = yyvsp[-2].colIni;
	yyval.linFin = yyvsp[0].linFin;
	yyval.colFin = yyvsp[0].colFin;

	informar(7765, 27); yyval.nomTemp = pet_GenTemp();

	if ( estado ) {
		yyval.tipoDato = yyvsp[-2].tipoDato;
		informar(7862, 39); pet_GenDecVar(yyval.tipoDato, yyval.nomTemp);

		fprintf(stderr, "ASIG %s = %s %s %s\n"
			, yyval.nomTemp, yyvsp[-2].nomTemp
			, yyvsp[-1].lexema, yyvsp[0].nomTemp);

		informar(8024, 66); pet_GenAsig(4, yyval.nomTemp, yyvsp[-2].nomTemp
			, yyvsp[-1].lexema, yyvsp[0].nomTemp);

	} else {
		yyval.tipoDato = DESC;
		}

	}
break;
case 36:
#line 372 "FINAL.y"
{
	/***********************************************
	  Como en C o solo se puede con BOOLEANOS ???
	  OP_LOGICO2 = "&&" o "||"
	 ***********************************************/

	/***************************************
	  Asignacion variables de localizacion
	 ***************************************/

	informar(8493, 31); estado = pet_VerifTIPO(yyvsp[-2], yyvsp[0]);

	yyval.linIni = yyvsp[-2].linIni;
	yyval.colIni = yyvsp[-2].colIni;
	yyval.linFin = yyvsp[0].linFin;
	yyval.colFin = yyvsp[0].colFin;

	if ( estado ) {
		if ( (yyvsp[-2].tipoDato == BOOLEANO) 
			|| (yyvsp[-2].tipoDato == LISTA_BOOLEANO) ) {

			informar(8740, 27); yyval.nomTemp = pet_GenTemp();
			yyval.tipoDato = yyvsp[-2].tipoDato;

			informar(8822, 39); pet_GenDecVar(yyval.tipoDato, yyval.nomTemp);

			fprintf(stderr, "ASIG %s = %s %s %s\n"
				, yyval.nomTemp, yyvsp[-2].nomTemp
				, yyvsp[-1].lexema, yyvsp[0].nomTemp);

			informar(8988, 67); pet_GenAsig(4, yyval.nomTemp, yyvsp[-2].nomTemp
				, yyvsp[-1].lexema, yyvsp[0].nomTemp);

		} else {
			yyval.nomTemp = strdup("tempNO_BOOL\n");
			yyval.tipoDato = DESC;

			fprintf(stderr, "ERROR Linea: %d Tipos no booleanos\n"
				, yylineno);
			}

	} else {
		fprintf(stderr, "Error Linea: %d ", yylineno);
		fprintf(stderr, "Tipos no coinciden\n");

		yyval.tipoDato = DESC;
		yyval.nomTemp = strdup("tempERRTipo");
		}
 	}
break;
case 37:
#line 422 "FINAL.y"
{
	/***************************************
	  OP_LOGICO3 = "<", "<=", ... , "!="
	 ***************************************/

	informar(9567, 31); estado = pet_VerifTIPO(yyvsp[-2], yyvsp[0]);

	yyval.linIni = yyvsp[-2].linIni;
	yyval.colIni = yyvsp[-2].colIni;
	yyval.linFin = yyvsp[0].linFin;
	yyval.colFin = yyvsp[0].colFin;

	if ( estado ) {

		informar(9737, 27); yyval.nomTemp = pet_GenTemp();
		yyval.tipoDato = BOOLEANO;

		informar(9814, 39); pet_GenDecVar(yyval.tipoDato, yyval.nomTemp);

		fprintf(stderr, "ASIG %s = %s %s %s\n"
			, yyval.nomTemp, yyvsp[-2].nomTemp
			, yyvsp[-1].lexema, yyvsp[0].nomTemp);

		informar(9976, 67); pet_GenAsig(4, yyval.nomTemp, yyvsp[-2].nomTemp
				, yyvsp[-1].lexema, yyvsp[0].nomTemp);

	} else {
		fprintf(stderr, "Error Linea: %d ", yylineno);
		fprintf(stderr, "Tipos no coinciden\n");

		yyval.tipoDato = DESC;
		yyval.nomTemp = strdup("tempERRTipo");
		}
 	}
break;
case 38:
#line 457 "FINAL.y"
{
	if ( (yyvsp[0].tipoDato == ENTERO) || (yyvsp[0].tipoDato == LISTA_ENTERO)
		|| (yyvsp[0].tipoDato == REAL ) || (yyvsp[0].tipoDato == LISTA_REAL) )

		yyval.tipoDato = yyvsp[0].tipoDato;

	else {
		fprintf(stderr, "\nError linea %d", yylineno);
		fprintf(stderr, " Op con tipo de dato incorrecto\n");

		yyval.tipoDato = DESC;
		}

	/***************************************
	  Asignacion variables de localizacion
	 ***************************************/

	/* TODO: Check TIPO para OPERADOR...*/

	yyval.linIni = yyvsp[-1].linIni;
	yyval.colIni = yyvsp[-1].colIni;
	yyval.linFin = yyvsp[0].linFin;
	yyval.colFin = yyvsp[0].colFin;

	informar(10834, 27); yyval.nomTemp = pet_GenTemp();

	/* Falta Declaracion de TEMP*/
	/* Conversion en cadena*/
	/* Asignacion*/
	yyval.tipoDato = yyvsp[0].tipoDato;
	informar(10983, 39); pet_GenDecVar(yyval.tipoDato, yyval.nomTemp);
	informar(11045, 56); pet_GenAsig(3, yyval.nomTemp, yyvsp[-1].lexema, yyvsp[0].nomTemp, NULL);
 	}
break;
case 39:
#line 491 "FINAL.y"
{
	yyval.tipoDato = yyvsp[0].tipoDato;

	/* CONVERSION de un VALOR en una CADENA*/

	yyval.nomTemp = convCadena(yyval.tipoDato, yyvsp[0].valor);
	fprintf(stderr, "[COMP] convCadena $$.nomTemp: %s\n", yyval.nomTemp);


	/***************************************
	  Asignacion variables de localizacion
	 ***************************************/

	yyval.linIni = yyvsp[0].linIni;
	yyval.colIni = yyvsp[0].colIni;
	yyval.linFin = yyvsp[0].linFin;
	yyval.colFin = yyvsp[0].colFin;
	}
break;
case 40:
#line 510 "FINAL.y"
{
	yyval.tipoDato = yyvsp[-1].tipoDato;

	/***************************************
	  Asignacion variables de localizacion
	  CHECK-TODO: Asignar localizacion a los parentesis
	 ***************************************/

	yyval.linIni = yyvsp[-2].linIni;
	yyval.colIni = yyvsp[-2].colIni;
	yyval.linFin = yyvsp[0].linFin;
	yyval.colFin = yyvsp[0].colFin;

	yyval.nomTemp = strdup(yyvsp[-1].nomTemp);

	/* DEBUG*/
	fprintf(stderr, "nombre Temp: %s\n", yyval.nomTemp);
	}
break;
case 41:
#line 529 "FINAL.y"
{
	/******************************************
	  OP_LOGICO1 = "!"
	  Solo para BOOLEANOS
	  CHECK: Asignar localizacion al OP_LOGICO1
	 ******************************************/

	if ( (yyvsp[0].tipoDato == BOOLEANO) || (yyvsp[0].tipoDato == LISTA_BOOLEANO) )
		yyval.tipoDato = yyvsp[0].tipoDato;
	else {
		fprintf(stderr, "\nError linea: %d ", yylineno);
		fprintf(stderr, "Tipo de dato incorrecto\n");
	
		yyval.tipoDato = DESC;
		}

	/***************************************
	  Asignacion variables de localizacion
	 ***************************************/

	/* TODO: Check TIPO para OPERADOR...*/

	yyval.linIni = yyvsp[-1].linIni;
	yyval.colIni = yyvsp[-1].colIni;
	yyval.linFin = yyvsp[0].linFin;
	yyval.colFin = yyvsp[0].colFin;
	}
break;
case 43:
#line 558 "FINAL.y"
{ 
	informar(12745, 35); yyval.tipoDato = pet_BuscarTS(yylval);

	/* if ( flagREI ) YYABORT;*/


	/***************************************
	  Asignacion variables de localizacion
	 ***************************************/

	yyval.linIni = yyvsp[0].linIni;
	yyval.colIni = yyvsp[0].colIni;
	yyval.linFin = yyvsp[0].linFin;
	yyval.colFin = yyvsp[0].colFin;

	/* De nuevo copiamos...*/

	yyval.nomTemp = strdup(yyvsp[0].lexema);
	}
break;
case 45:
#line 581 "FINAL.y"
{
	/************************************
	  OP_LISTAS1 = "#", "->", "<<", ">>"
	 ************************************/

	if ( (yyvsp[-1].tipoDato != LISTA_ENTERO) && (yyvsp[-1].tipoDato != LISTA_REAL)
		&& (yyvsp[-1].tipoDato != LISTA_CARACTER)
		&& (yyvsp[-1].tipoDato != LISTA_BOOLEANO) ) {

		fprintf(stderr, "Error linea: %d ", yylineno);
		fprintf(stderr, "OP_LISTAS1 con tipo incorrecto: ");
		/* impTipo($1.tipoDato);*/
		/* printf("\n");*/

		yyval.tipoDato = DESC;
	} else {

		if ( yyvsp[0].nParam == 1 )

			/* # es cardinalidad de la lista */
			yyval.tipoDato = ENTERO;

		else

			/**********************************************
			  En otro caso, devolvemos LISTA_TIPO o TIPO ??
			  Hay que decidirlo...
			 **********************************************/
			
			yyval.tipoDato = yyvsp[-1].tipoDato;
		}
	}
break;
case 46:
#line 614 "FINAL.y"
{
	/*************************************
	  Se debe BORRAR esta Regla !!!!
	**************************************/
	}
break;
case 47:
#line 620 "FINAL.y"
{
	/********************************************
	  OP_LISTAS2 = 
		"@"  nParam = 1
		"++" nParam = 2
		"%"  nParam = 3

	  La posicion de una lista debe ser un entero

	  ++ es para Meter en la lista ??  <LISTA> ++ <VALOR>
	  Valor de POS: <LISTA> @ <POS>
	  Borrar:  <LISTA> % <POS>
	  Insertar en pos: <LISTA> . <POS> \ <VALOR>
	 ***********************************************/

	if ( (yyvsp[-2].tipoDato != LISTA_ENTERO) && (yyvsp[-2].tipoDato != LISTA_REAL)
		&& (yyvsp[-2].tipoDato != LISTA_CARACTER)
		&& (yyvsp[-2].tipoDato != LISTA_BOOLEANO) ) {

		fprintf(stderr, "Error linea: %d ", yylineno);
		fprintf(stderr, "OP_LISTAS2 con tipo incorrecto: \n");
		/* impTipo($1.tipoDato);*/
		/* printf("\n");*/

		yyval.tipoDato = DESC;

	} else if ( yyvsp[-1].nParam == 1 || yyvsp[-1].nParam == 3 ) {

		if ( yyvsp[0].tipoDato != ENTERO ) {
			fprintf(stderr, "\nError linea %d ", yylineno);
			fprintf(stderr, "Posicion no entera: ");
			/* impTipo($3.tipoDato);*/
			fprintf(stderr, "\n");

			yyval.tipoDato = DESC;
		} else {

			switch( yyvsp[-2].tipoDato ) {
				case LISTA_ENTERO:
						yyval.tipoDato = ENTERO;
						break;
				case LISTA_REAL:
						yyval.tipoDato = REAL;
						break;
				case LISTA_CARACTER:
						yyval.tipoDato = CARACTER;
						break;
				case LISTA_BOOLEANO:
						yyval.tipoDato = BOOLEANO;
						break;
				default:
						fprintf(stderr, "\nFallo !LISTA\n");
						yyval.tipoDato = DESC;
						break;
				}
			}
	} else {

		/* Insercion en la lista */

		switch( yyvsp[-2].tipoDato ) {
			case LISTA_ENTERO:
					if ( yyvsp[0].tipoDato != ENTERO )
						flag = 1;
					else
						yyval.tipoDato = ENTERO;
					break;
			case LISTA_REAL:
					if ( yyvsp[0].tipoDato != REAL )
						flag = 1;
					else
						yyval.tipoDato = REAL;
					break;
			case LISTA_CARACTER:
					if ( yyvsp[0].tipoDato != CARACTER )
						flag = 1;
					else
						yyval.tipoDato = CARACTER;
					break;
			case LISTA_BOOLEANO:
					if ( yyvsp[0].tipoDato != BOOLEANO )
						flag = 1;
					else
						yyval.tipoDato = BOOLEANO;
					break;
			default:
					fprintf(stderr, "\nTIPO != LISTA!!!\n");
					flag = 1;
			}

		if ( flag == 1 ) {
			fprintf(stderr, "\nError linea %d ", yylineno);
			fprintf(stderr, "OP_LISTAS2 el tipo del valor (");
			/* impTipo($3.tipoDato);*/
			fprintf(stderr, ") no coincide con el de la lista (");
			/* impTipo($1.tipoDato);*/
			fprintf(stderr, ")\n");

			yyval.tipoDato = DESC;
			flag = 0;
			}
		}
	}
break;
case 48:
#line 724 "FINAL.y"
{
	/**************************************************
	  TODO: Comprobacion de tipos para OP_LISTAS...
	  TODO: No deberia ser muy dificil...con PETBUSCAR
	
	OP_LISTAS3 = .
	OP_LISTAS4 = \

	Insertar en POS: <LISTA> . <POS> . <VALOR>


	if ( ($1.tipoDato != LISTA_ENTERO) && ($1.tipoDato != LISTA_REAL)
		&& ($1.tipoDato != LISTA_CARACTER)
		&& ($1.tipoDato != LISTA_BOOLEANO) ) {

		fprintf(stderr, "ERR Error linea: %d ", yylineno);
		fprintf(stderr, "ERR OP_LISTAS2 con tipo incorrecto\n");

		$$.tipoDato = DESC;

	} else if ( $3.tipoDato != ENTERO ) {
		fprintf(stderr, "\nError linea %d ", yylineno);
		fprintf(stderr, "Posicion no entera\n");

		$$.tipoDato = DESC;

	} else {

		switch( $1.tipoDato ) {
			case LISTA_ENTERO:
					if ( $5.tipoDato != ENTERO )
						flag = 1;
					else
						$$.tipoDato = ENTERO;
					break;
			case LISTA_REAL:
					if ( $5.tipoDato != REAL )
						flag = 1;
					else
						$$.tipoDato = REAL;
					break;
			case LISTA_CARACTER:
					if ( $5.tipoDato != CARACTER )
						flag = 1;
					else
						$$.tipoDato = CARACTER;
					break;
			case LISTA_BOOLEANO:
					if ( $5.tipoDato != BOOLEANO )
						flag = 1;
					else
						$$.tipoDato = BOOLEANO;
					break;
			default:
					printf("\nTIPO != LISTA!!!\n");
					flag = 1;
			}

		if ( flag == 1 ) {
			fprintf(stderr, "\nError linea %d ", yylineno);
			fprintf(stderr, "OP_LISTAS2 el tipo del valor (");
			fprintf(stderr, ") no coincide tipo lista (");
			fprintf(stderr, ")\n");

			$$.tipoDato = DESC;
			flag = 0;
			}
		}

	***************************************************/
	}
break;
case 64:
#line 824 "FINAL.y"
{
	/** 
	 @todo TODO: No hay porque hacerlo en 2 partes...
	 Para eso estan $1, $2.... 
	 */

	informar(18601, 28); tipoTemp = pet_BuscarTS(yyvsp[-2]);
	yyvsp[-2].tipoDato = tipoTemp;
	informar(18677, 31); estado = pet_VerifTIPO(yyvsp[-2], yyvsp[0]);

	/*************************************************************
	  Comprobacion de tipos MANUAL en el HIJO
	  NO deberia hacer falta porque se lo hemos pedido al PADRE
	 *************************************************************/

	if ( tipoTemp != yyvsp[0].tipoDato ) {
		fprintf(stderr, "[ERR] Error linea: %d ASIGNACION "
			, yylineno);
		fprintf(stderr, "tipos no coinciden\n");
		/* impTipo(tipoTemp);*/
		/* printf(" y ");*/
		/* impTipo($4.tipoDato);*/
		/* printf("\n");*/
		}


	fprintf(stderr, "[COMP] Misma comprobacion tipo ");
	fprintf(stderr, "segun PADRE: %s\n", (estado == 1)?"OK":"ERR");

	informar(19328, 60); pet_GenIniBlq("/** Asignacion **/\n", yyvsp[-2].colIni, yyvsp[0].colFin);

	/* Peticion de ASIGNACION*/

	informar(19440, 50); pet_GenAsig(2, yyvsp[-2].lexema, yyvsp[0].nomTemp, NULL, NULL);

	informar(19514, 16); pet_GenFinBlq();
	}
break;
case 65:
#line 864 "FINAL.y"
{
	fprintf(stderr, "[COMP] Argumentos R1\n");
	informar(19645, 29); tipoOK = pet_BuscarPARAM(yyvsp[0]);
	contParam++;

	if ( tipoOK && yyvsp[-2].tipoDato == NO_ASIG ) {
		yyval.tipoDato = NO_ASIG;
		tamCadena = strlen(yyvsp[-2].variables)
			+ 2 + strlen(yyvsp[0].nomTemp) + 1;

		yyval.variables = (char *) malloc(tamCadena * sizeof(char));
		if ( yyval.variables == NULL ) {
			perror("LISTA_EXP");
			yyval.tipoDato = DESC;
		} else {
			strcpy(yyval.variables, yyvsp[-2].variables);
			strcat(yyval.variables, ", ");
			strcat(yyval.variables, yyvsp[0].nomTemp);
			fprintf(stderr, "DEBUG ListaEXP %s\n"
				, yyval.variables);

			/* Deberiamos poder liberar memoria !!!*/
			free(yyvsp[0].nomTemp);
			free(yyvsp[-2].variables);
			}
	} else {
		yyval.tipoDato = DESC;
		}
	}
break;
case 66:
#line 894 "FINAL.y"
{
	fprintf(stderr, "[COMP] Argumentos R2\n");
	informar(20360, 29); tipoOK = pet_BuscarPARAM(yyvsp[0]);
	contParam++;
	if ( tipoOK ) {
		yyval.tipoDato = NO_ASIG;
		/* Crear la lista de expresiones...*/
		yyval.variables = strdup(yyvsp[0].nomTemp);
		fprintf(stderr, "DEBUG ListaExp %s\n", yyvsp[0].nomTemp);
		/* Deberiamos poder liberar la memoria*/
		/* de nomTemp ???? y toda la demas...*/
		free(yyvsp[0].nomTemp);
	} else
		yyval.tipoDato = DESC;
	}
break;
case 67:
#line 910 "FINAL.y"
{
	/****************
	  Cuidado AQUI !!!
	  Se admiten listas de expresiones
	  que empiezan por COMA !!!!
	 ************************************/
	
	yyval.tipoDato = NO_ASIG;
	yyval.variables = strdup("<< SIN_ARGUMENTOS >>");
	}
break;
case 68:
#line 923 "FINAL.y"
{
	informar(20981, 62); pet_GenIniBlq("/** Sent ENTRADA **/\n", yyvsp[0].colIni, yyvsp[0].colFin);
	}
break;
case 69:
#line 927 "FINAL.y"
{
	informar(21083, 41); pet_GenENTRADA(yyvsp[0].formato, yyvsp[0].variables);

	informar(21148, 16); pet_GenFinBlq();
	}
break;
case 70:
#line 935 "FINAL.y"
{ 
	informar(21240, 31); tipoAux = pet_BuscarTS(yylval);

	informar(21295, 104); pet_GenCadFormato(yyvsp[-2].colIni, yyvsp[0].colFin
		, &(yyval.formato), &(yyval.variables), tipoAux
		, yyvsp[0].lexema, SCAN);

	/* Asignamos variables de localizacion*/
	yyval.colIni = yyvsp[-2].colIni;
	yyval.colFin = yyvsp[0].colFin;	
	}
break;
case 71:
#line 947 "FINAL.y"
{
	informar(21536, 31); tipoAux = pet_BuscarTS(yylval);

	informar(21591, 104); pet_GenCadFormato(yyvsp[0].colIni, yyvsp[0].colFin
		, &(yyval.formato), &(yyval.variables), tipoAux
		, yyvsp[0].lexema, SCAN);

	/* Asignamos variables de localizacion*/
	yyval.colIni = yyvsp[0].colIni;
	yyval.colFin = yyvsp[0].colFin;
	}
break;
case 72:
#line 961 "FINAL.y"
{
	informar(21836, 61); pet_GenIniBlq("/** Sent SALIDA **/\n", yyvsp[0].colIni, yyvsp[0].colFin);
	}
break;
case 73:
#line 965 "FINAL.y"
{
	informar(21937, 40); pet_GenSALIDA(yyvsp[0].formato, yyvsp[0].variables);

	informar(22001, 16); pet_GenFinBlq();
	}
break;
case 74:
#line 973 "FINAL.y"
{
	informar(22087, 110); pet_GenCadFormato(yyvsp[-2].colIni, yyvsp[0].colFin
		, &(yyval.formato), &(yyval.variables), yyvsp[0].tipoDato
		, yyvsp[0].nomTemp, PRINT);

	/* Asignamos variables de localizacion*/
	yyval.colIni = yyvsp[-2].colIni;
	yyval.colFin = yyvsp[0].colFin;
	}
break;
case 75:
#line 983 "FINAL.y"
{
	informar(22341, 104); pet_GenCadFormato(yyvsp[-2].colIni, yyvsp[0].colFin
		, &(yyval.formato), &(yyval.variables), STRING
		, yyvsp[0].lexema, PRINT);

	/* Asignamos variables de localizacion*/
	yyval.colIni = yyvsp[-2].colIni;
	yyval.colFin = yyvsp[0].colFin;
	}
break;
case 76:
#line 993 "FINAL.y"
{
	informar(22577, 110); pet_GenCadFormato(yyvsp[0].colIni, yyvsp[0].colFin
		, &(yyval.formato), &(yyval.variables), yyvsp[0].tipoDato
		, yyvsp[0].nomTemp, PRINT);

	/* Asignamos variables de localizacion*/
	yyval.colIni = yyvsp[0].colIni;
	yyval.colFin = yyvsp[0].colFin;
	}
break;
case 77:
#line 1003 "FINAL.y"
{
	informar(22816, 104); pet_GenCadFormato(yyvsp[0].colIni, yyvsp[0].colFin
		, &(yyval.formato), &(yyval.variables), STRING
		, yyvsp[0].lexema, PRINT);

	/* Asignamos variables de localizacion*/
	yyval.colIni = yyvsp[0].colIni;
	yyval.colFin = yyvsp[0].colFin;
	}
break;
case 79:
#line 1017 "FINAL.y"
{
	/* Bloque SENTENCIA if*/
	informar(23117, 65); pet_GenIniBlq("/**  Sentencia IF   **/\n", yyvsp[0].colIni, yyvsp[0].colFin);

	informar(23206, 28); yyvsp[0].etqtElse = pet_GenEtiq();
	informar(23257, 27); yyvsp[0].etqtSal = pet_GenEtiq();
	informar(23307, 27); yyvsp[0].etqtEnt = pet_GenEtiq();
	yyvsp[0].nomVarCtrl = strdup("<NO_APL>");
	yyvsp[0].tipoTs = DESC_CTRL;
	yyvsp[0].tipoDato = NO_ASIG;
	yyvsp[0].lexema = strdup("<CTRL_SI>");

	/* Veamos que pasa....*/
	informar(23501, 27); pet_introTS(yyvsp[0], DESC_CTRL);
	}
break;
case 80:
#line 1033 "FINAL.y"
{
	/************************************************
	  La comprobacion $4.tipoDato == BOOLEANO
	  debe hacerse ya que POSIBLEMENTE la Expresion
	  NO se encuentre en la TS

	  DEBUG Aunque haya ERROR SEMANTICO nuevo Bloque 
	 ************************************************/

	/* Pequeña chapuza para que se vea todo...*/

	yyvsp[0].tipoDato = BOOLEANO;
	informar(23941, 31); estado = pet_VerifTIPO(yyvsp[-1], yyvsp[0]);
	
	if ( yyvsp[-1].tipoDato != BOOLEANO ) {
		/** @todo Gestion de msj por pipeERR en PADRE */
		fprintf(stderr, "ERR SEMANTICO Linea %d: ", yylineno);
		fprintf(stderr, "Expresion NO booleana en Condicion\n");
		informar(24199, 74); pet_GenIniBlq("/**  Parte if EXP no BOOL  **/"
			, yyvsp[-1].colIni, yyvsp[-1].colFin);
	} else {
		/* informar(24310, 44); pet_GenSalto($4.nomTemp, $1.etqtElse, COND);*/
		informar(24378, 42); pet_GenSaltoCond(yyvsp[-1].nomTemp, yyvsp[-4].etqtElse);
		informar(24444, 65); pet_GenIniBlq("/**  Parte if   **/\n"
			, yyvsp[-1].colIni, yyvsp[-1].colFin);
		}

	}
break;
case 81:
#line 1062 "FINAL.y"
{
	/* Salto incondicional a la etiqueta de salida*/
	/* informar(24606, 45); pet_GenSalto($4.nomTemp, $1.etqtSal, INCOND);*/
	informar(24674, 31); pet_GenSaltoInCond(yyvsp[-6].etqtSal);

	/* fin del bloque PARTE_IF*/

	informar(24758, 16); pet_GenFinBlq();

	/* Paso 7 -> Se emite la etiqueta parte ELSE*/
	informar(24844, 24); pet_EscEtq(yyvsp[-6].etqtElse);
	}
break;
case 82:
#line 1077 "FINAL.y"
{ 
	informar(24921, 62); pet_GenIniBlq("/**  Parte else  **/\n", yyvsp[0].colIni, yyvsp[0].colFin);
	}
break;
case 83:
#line 1081 "FINAL.y"
{
	/* Fin Bloque Else*/

	informar(25045, 16); pet_GenFinBlq();

	/* Fin bloque sentencia IF*/

	informar(25114, 16); pet_GenFinBlq();

	/* Escribir etiqueta SALIDA*/
	/* indexCtrl = buscaCtrl();*/
	informar(25212, 33); etqTemp = pet_BuscarEtq(ETQ_SAL);

	/* escEtqta(tSimbolos[indexCtrl].etqtSalida);*/
	informar(25316, 20); pet_EscEtq(etqTemp);
	free(etqTemp);
	/* Eliminar simbolos de la TS*/
	/* TODO: Implementar sacaCtrl();*/

	informar(25441, 16); pet_SacarCTRL();
	}
break;
case 84:
#line 1103 "FINAL.y"
{
	/* Fin bloque sentencia IF*/
	informar(25517, 16); pet_GenFinBlq();

	/* Buscar y escribir etiqueta de SALIDA*/
	informar(25598, 33); etqTemp = pet_BuscarEtq(ETQ_SAL);
	informar(25654, 20); pet_EscEtq(etqTemp);
	free(etqTemp);

	/* Eliminar simbolos de la TS*/
	informar(25745, 16); pet_SacarCTRL();
	}
break;
case 92:
#line 1134 "FINAL.y"
{
	/**********************
	  La peticion deberia devolver el numero
	  de argumentos

	  De momento vale porque no se puede llamar
	  a un proc dentro de la llamada a otro
	  pero CUIDADO con las Funciones SI y la
	  liamos !!!!!!!!!!!!
	  Para solucionarlo tenemos el campo de 
	  numero de Parametros COOOOÑO !!!!
	 ******************************************/
	informar(26611, 31); yyvsp[0].nParam = pet_BuscarPROC(yyvsp[0]);
	contParam = 0;
	if ( yyvsp[0].nParam < 0 )
		fprintf(stderr, "[ERR] Proc no declarado: %s\n", yyvsp[0].lexema);
	else {
		/* Usamos */
		yyvsp[0].tipoDato = NO_ASIG;
		informar(26813, 68); pet_GenIniBlq("/** Llamada a PROC **/\n"
			, yyvsp[0].colIni, yyvsp[0].colFin);
		/*****************************
		  Aqui NO !!!
		  Primero hay que generar los temporales
		  para la Lista de Expresiones

		informar(27031, 26); pet_GenLlamada($1.lexema);
		******************************************/
		}
	}
break;
case 93:
#line 1165 "FINAL.y"
{
	/******************************
	  Deberiamos comprobar si el 
	  numero de parametros leidos coincide
	  con el declarado y si la lista de
	  argumentos es correcta en su TOTALIDAD
	  Muuuuuuuuuuucho cuidado que con las
	  funciones se puede liar la grande !!!
	*******************************************/

	if ( contParam != yyvsp[-4].nParam && yyvsp[-4].nParam >= 0 ) {
		fprintf(stderr, "[ERR] Linea %d Num parametros no concuerda\n", yylineno);
		fprintf(stderr, "[ERR] Declarados: %d  Usados: %d\n"
			, yyvsp[-4].nParam, contParam);
	} else if ( yyvsp[-1].tipoDato != NO_ASIG ) {
		fprintf(stderr, "[ERR] Linea %d Llamada a PROC incorrecta\n", yylineno);
	} else {
		/* Llamada CORRECTA*/
		informar(27842, 40); pet_GenLlamada(yyvsp[-4].lexema, yyvsp[-1].variables);
		/* TODO: Liberar MEMORIA*/
		free(yyvsp[-1].variables);
		}

	informar(27959, 16); pet_GenFinBlq();
	}
break;
#line 1670 "y.tab.c"
    }
    yyssp -= yym;
    yystate = *yyssp;
    yyvsp -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            fprintf(stderr,"%sdebug: after reduction, shifting from state 0 to\
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
                fprintf(stderr,"%sdebug: state %d, reading %d (%s)\n",
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
        fprintf(stderr,"%sdebug: after reduction, shifting from state %d \
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
