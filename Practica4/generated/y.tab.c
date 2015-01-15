/* A Bison parser, made by GNU Bison 2.7.12-4996.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.7.12-4996"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
/* Line 371 of yacc.c  */
#line 1 "yacc.y"

/*********************************************************
**
** Fichero: PRUEBA.Y
** Función: Pruebas de YACC para practicas de PL
**
********************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
/**
***
	La siguiente declaracion permite que ’yyerror’ se pueda invocar desde el
	fuente de lex
**/
void yyerror( const char * msg ) ;
/**
	La siguiente variable se usará para conocer el numero de la línea
	que se esta leyendo en cada momento. También es posible usar la variable
	’yylineno’ que también nos muestra la línea actual. Para ello es necesario
	invocar a flex con la opción ’-l’ (compatibilidad con lex).
**/

int linea_actual = 1 ;
int linea_si;

typedef enum {
    marca,
    funcion,
    variable,
    parametro_formal,
} tipoEntrada;

typedef enum {
    boolean,
    integer,
    real,
    character,
    list,
    unknown,
    unassigned
} dtype ;

typedef struct {
    tipoEntrada entrada ;
    char *nombre;
    dtype tipoDato;
    unsigned int parametros;
} entradaTS ;

#define MAX_TS 500
unsigned int TOPE=0, top=-1,topList=-1;
unsigned int subProg=0; /* Indicador de comienzo de bloque de un subprog */
unsigned int decVar=0,dim,tamdim1,tamdim2;
unsigned int func = 0,posParam = 0;
char idFuncion[100];

entradaTS TS[MAX_TS]; /* Pila de la tabla de símbolos */
entradaTS TP[MAX_TS];
entradaTS TA[MAX_TS];
dtype tipoTMP,tipoList;

typedef struct {
    int    attrib ;
    char  *lexema ;
    dtype  type ;
	dtype typeList;
} atributos ;


#define YYSTYPE atributos

void TS_InsertaMARCA()
{
	if(TOPE != 0) TOPE++;

	TS[TOPE].entrada = marca;
	TS[TOPE].nombre = "MARCA_INICIAL";

	if(subProg == 1){
		int topeTMP = TOPE;
		while(TS[topeTMP].entrada != funcion && topeTMP > 0)
		{
			if(TS[topeTMP].entrada == parametro_formal)
			{	
				TOPE++;
				TS[TOPE].entrada = parametro_formal;
				TS[TOPE].nombre = TS[topeTMP].nombre;
				TS[TOPE].tipoDato = TS[topeTMP].tipoDato;
			}
			topeTMP--;
		}
	}
}

void TS_VaciarENTRADAS()
{	
	while(TS[TOPE].entrada != marca)
	{
		TOPE--;
	}
	TOPE--;
}

void TS_InsertaSUBPROG(atributos a)
{
	TOPE++;
	TS[TOPE].entrada = funcion;
	TS[TOPE].nombre = a.lexema;
	TS[TOPE].parametros = 0;

	top++;
	TP[top].entrada = funcion;
	TP[top].nombre = a.lexema;
	TP[top].parametros = 0;	
}

void TS_InsertaPARAMF(atributos a)
{
	if(!existeVar(a))
	{
		TOPE++;	
		TS[TOPE].entrada = parametro_formal;
		TS[TOPE].nombre = a.lexema;
		TS[TOPE].tipoDato = a.type;

		top++;
		TP[top].entrada = parametro_formal;
		TP[top].nombre = a.lexema;
		TP[top].tipoDato = a.type;

		int topeTMP = TOPE;

		while(TS[topeTMP].entrada != funcion && topeTMP >= 0){	
			topeTMP--;
		}
		TS[topeTMP].parametros++;

		topeTMP = top;

		while(TP[topeTMP].entrada != funcion){	
			topeTMP--;
		}
		TP[topeTMP].parametros++;
	}
	else
	{
		fprintf(stderr,"[Linea %d]: %s: existe.\n",linea_actual,a.lexema);
	}
}

void TS_InsertaIDENT(atributos a)
{
	if(existeVar(a))
		fprintf(stderr,"[Linea %d]: %s: existe.\n",linea_actual,a.lexema);
	else
	{
		TOPE++;	
		TS[TOPE].entrada = variable;
		TS[TOPE].nombre = a.lexema;
		TS[TOPE].tipoDato = tipoTMP;
	}
}

int existeVar(atributos a)
{	
	int topeTMP = TOPE ;
	while(TS[topeTMP].entrada != marca && topeTMP >= 0)
	{	
		/*if(TS[topeTMP].entrada == parametro_formal)
		{*/
			if(strcmp(TS[topeTMP].nombre, a.lexema) == 0)
			{
				return 1;
			}
		//}
		topeTMP--;
	}
	return 0;
}

void existeFuncion(atributos a)
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
	{	if( !strcmp(TP[topeTMP].nombre,idFuncion) ){
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
	
	while(strcmp(TP[topeTMP].nombre,idFuncion) && topeTMP>=0)
	{	
		topeTMP--;
	}

	if(topeTMP>=0){
		if(pos <= TP[topeTMP].parametros){
			if ( TP[topeTMP+pos].tipoDato == real && a.type == integer ){
				a.type = real;
			}
			//printf("param: %d: ,tipo = %d. lexema:%s, tipo= %d \n",pos,TP[topeTMP+pos].tipoDato,a.lexema,a.tipo);
			if(TP[topeTMP].parametros==0){
				fprintf(stderr,"[Linea %d]: %s: no tiene parametros.\n",linea_actual,TP[topeTMP].nombre);
			}
			else if (TP[topeTMP+pos].tipoDato != a.type ){
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

unsigned int asignaTipoList(atributos a)
{
	int topeTMP = topList ;
	unsigned int tipo = -1;
	int existe = 0;

	while( existe == 0 && topeTMP>=0)
	{
		if ( !strcmp(TA[topeTMP].nombre,a.lexema) )
		{
			existe = 1;
			tipo = TA[topeTMP].tipoDato;
		}
		topeTMP--;
	}
	return tipo;
}

unsigned int checkType(atributos a,atributos op, atributos b)
{
	unsigned int tipo = 2;
	int topeTMP = TOPE;
	int indice_a = topList, indice_b = topList;
	int existeList = 0;
	int existe = 0;

	while( existe == 0 && topeTMP>=0)
	{	
		if(!strcmp(TS[topeTMP].nombre,a.lexema))
		{
			existe = 1;
			tipo = TS[topeTMP].tipoDato;
		}
		topeTMP--;
	}

	if(existe || a.attrib >= 286)
	{
		if(a.type == list)
		{
			while(existeList == 0 && indice_a>=0)
			{		
				if(!strcmp(TA[indice_a].nombre,a.lexema))
				{
					existeList = 1;			
					a.type = TA[indice_a].tipoDato;
				}
				else{	indice_a--;}
			}
		}
		if(existeList && b.type == list)
		{			
			existeList=0;
			while( existeList == 0 && indice_b>=0)
			{	if ( !strcmp(TA[indice_b].nombre,b.lexema) ){
					existeList = 1;
				}
				else{	indice_b--;}
			}
			if(existeList)
			{
				b.type = TA[indice_b].tipoDato;
			}
			if ( a.type == real && b.type == integer ){
				b.type = real;
			}
			if ( a.type == integer && b.type == real ){
				a.type = real;
			}
		}
			if ( a.type == real && b.type == integer )
			{
				b.type = real;
			}
			if ( a.type == integer && b.type == real )
			{
				b.type = integer;
			}
			//printf("%s, tipo = %d attrib = %d -- %s, tipo = %d attrib = %d\n",a.lexema,a.type,a.attrib, b.lexema,b.type, b.attrib);
		if(a.type != b.type)
		{
			fprintf(stderr,"[Linea %d]: tipos incompatible\n ",linea_actual);
		}
		else
		{
			tipo = a.type;		
		}
		if(op.type == boolean)
			tipo = boolean;
	}
	else
	{
		fprintf(stderr,"[Linea %d]: %s no existe\n",linea_actual,a.lexema);
	}
	return tipo;
}


/* Line 371 of yacc.c  */
#line 426 "generated/y.tab.c"

# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif


/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     MAIN = 258,
     IF = 259,
     ELSE = 260,
     DO = 261,
     UNTIL = 262,
     OP_BIN = 263,
     OP_LIST = 264,
     OP_LIST_START_CURSOR = 265,
     OP_UNIT = 266,
     OP_PM = 267,
     TYPE = 268,
     BEGIN_LIST = 269,
     END_LIST = 270,
     ASSIGN = 271,
     PL = 272,
     PR = 273,
     BEGIN_P = 274,
     END = 275,
     COMMA = 276,
     SEMICOLON = 277,
     INPUT = 278,
     OUTPUT = 279,
     START_VAR_DEC = 280,
     END_VAR_DEC = 281,
     LIST = 282,
     ID = 283,
     RETURN = 284,
     WHILE = 285,
     BOOL = 286,
     INT = 287,
     FLOAT = 288,
     CHAR = 289,
     CAD = 290
   };
#endif
/* Tokens.  */
#define MAIN 258
#define IF 259
#define ELSE 260
#define DO 261
#define UNTIL 262
#define OP_BIN 263
#define OP_LIST 264
#define OP_LIST_START_CURSOR 265
#define OP_UNIT 266
#define OP_PM 267
#define TYPE 268
#define BEGIN_LIST 269
#define END_LIST 270
#define ASSIGN 271
#define PL 272
#define PR 273
#define BEGIN_P 274
#define END 275
#define COMMA 276
#define SEMICOLON 277
#define INPUT 278
#define OUTPUT 279
#define START_VAR_DEC 280
#define END_VAR_DEC 281
#define LIST 282
#define ID 283
#define RETURN 284
#define WHILE 285
#define BOOL 286
#define INT 287
#define FLOAT 288
#define CHAR 289
#define CAD 290



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;

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



/* Copy the second part of user declarations.  */

/* Line 390 of yacc.c  */
#line 559 "generated/y.tab.c"

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
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef __attribute__
/* This feature is available in gcc versions 2.5 and later.  */
# if (! defined __GNUC__ || __GNUC__ < 2 \
      || (__GNUC__ == 2 && __GNUC_MINOR__ < 5))
#  define __attribute__(Spec) /* empty */
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif


/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(N) (N)
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
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
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
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

# define YYCOPY_NEEDED 1

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

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  7
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   202

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  36
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  48
/* YYNRULES -- Number of rules.  */
#define YYNRULES  93
/* YYNRULES -- Number of states.  */
#define YYNSTATES  164

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   290

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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     6,     7,    14,    17,    18,    19,    23,
      24,    29,    30,    35,    37,    39,    42,    44,    45,    50,
      52,    56,    58,    60,    61,    68,    73,    78,    81,    83,
      86,    88,    90,    92,    94,    96,    98,   100,   102,   104,
     106,   108,   110,   115,   121,   129,   135,   141,   145,   149,
     153,   161,   165,   169,   173,   175,   177,   179,   182,   186,
     190,   192,   193,   199,   200,   205,   209,   211,   213,   216,
     218,   220,   222,   224,   226,   228,   230,   232,   234,   238,
     242,   244,   248,   252,   254,   258,   262,   264,   268,   272,
     274,   278,   280,   282
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      37,     0,    -1,    45,    38,    -1,    -1,    46,    39,    43,
      40,    55,    47,    -1,    40,    41,    -1,    -1,    -1,    52,
      42,    38,    -1,    -1,    25,    44,    48,    26,    -1,    -1,
      71,     3,    17,    18,    -1,    19,    -1,    20,    -1,    48,
      49,    -1,    49,    -1,    -1,    71,    50,    51,    22,    -1,
       1,    -1,    51,    21,    28,    -1,    28,    -1,     1,    -1,
      -1,    71,    28,    17,    53,    54,    18,    -1,    71,    28,
      17,    18,    -1,    54,    21,    71,    28,    -1,    71,    28,
      -1,     1,    -1,    55,    56,    -1,    56,    -1,    38,    -1,
      57,    -1,    58,    -1,    59,    -1,    60,    -1,    61,    -1,
      62,    -1,    63,    -1,    64,    -1,    65,    -1,     1,    -1,
      28,    16,    66,    22,    -1,     4,    17,    66,    18,    56,
      -1,     4,    17,    66,    18,    56,     5,    56,    -1,    30,
      17,    66,    18,    56,    -1,    23,    35,    21,    51,    22,
      -1,    23,    51,    22,    -1,    24,    82,    22,    -1,    29,
      66,    22,    -1,     6,    56,     7,    17,    66,    18,    22,
      -1,    66,     9,    22,    -1,    10,    66,    22,    -1,    17,
      66,    18,    -1,    28,    -1,    72,    -1,    67,    -1,    11,
      66,    -1,    66,     8,    66,    -1,    66,    12,    66,    -1,
       1,    -1,    -1,    28,    17,    68,    70,    18,    -1,    -1,
      28,    17,    69,    18,    -1,    70,    21,    66,    -1,    66,
      -1,    13,    -1,    27,    13,    -1,    32,    -1,    33,    -1,
      34,    -1,    31,    -1,    73,    -1,    74,    -1,    76,    -1,
      78,    -1,    80,    -1,    14,    75,    15,    -1,    75,    21,
      32,    -1,    32,    -1,    14,    77,    15,    -1,    77,    21,
      33,    -1,    33,    -1,    14,    79,    15,    -1,    79,    21,
      34,    -1,    34,    -1,    14,    81,    15,    -1,    81,    21,
      31,    -1,    31,    -1,    82,    21,    83,    -1,    83,    -1,
      66,    -1,    35,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   433,   433,   435,   435,   437,   437,   439,   439,   441,
     441,   441,   443,   445,   447,   449,   449,   451,   451,   451,
     453,   454,   455,   457,   457,   457,   459,   459,   459,   461,
     461,   463,   464,   465,   466,   467,   468,   469,   470,   471,
     472,   473,   475,   477,   479,   483,   486,   486,   488,   490,
     492,   495,   497,   499,   500,   501,   502,   503,   504,   505,
     506,   508,   508,   509,   509,   511,   512,   514,   514,   516,
     517,   518,   519,   520,   522,   523,   524,   525,   527,   528,
     528,   530,   531,   531,   533,   534,   534,   536,   537,   537,
     539,   539,   541,   541
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "MAIN", "IF", "ELSE", "DO", "UNTIL",
  "OP_BIN", "OP_LIST", "OP_LIST_START_CURSOR", "OP_UNIT", "OP_PM", "TYPE",
  "BEGIN_LIST", "END_LIST", "ASSIGN", "PL", "PR", "BEGIN_P", "END",
  "COMMA", "SEMICOLON", "INPUT", "OUTPUT", "START_VAR_DEC", "END_VAR_DEC",
  "LIST", "ID", "RETURN", "WHILE", "BOOL", "INT", "FLOAT", "CHAR", "CAD",
  "$accept", "program", "block", "$@1", "sub_progs", "sub_prog", "$@2",
  "local_var_dec", "$@3", "header_program", "start_block", "end_block",
  "local_var", "var_body", "$@4", "list_id", "header_subprogram", "$@5",
  "parameters", "sentences", "sentence", "sentence_assign",
  "sentence_if_then_else", "sentence_while", "sentence_input",
  "sentence_output", "sentence_return", "sentence_do_until",
  "sentence_list_forward_back", "sentence_list_start_cursor", "expr",
  "function_call", "$@6", "$@7", "list_expr", "type", "const",
  "const_list", "list_of_int", "list_int", "list_of_float", "list_float",
  "list_of_char", "list_char", "list_of_bool", "list_bool",
  "list_expr_cad", "expr_cad", YY_NULL
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
     285,   286,   287,   288,   289,   290
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    36,    37,    39,    38,    40,    40,    42,    41,    44,
      43,    43,    45,    46,    47,    48,    48,    50,    49,    49,
      51,    51,    51,    53,    52,    52,    54,    54,    54,    55,
      55,    56,    56,    56,    56,    56,    56,    56,    56,    56,
      56,    56,    57,    58,    58,    59,    60,    60,    61,    62,
      63,    64,    65,    66,    66,    66,    66,    66,    66,    66,
      66,    68,    67,    69,    67,    70,    70,    71,    71,    72,
      72,    72,    72,    72,    73,    73,    73,    73,    74,    75,
      75,    76,    77,    77,    78,    79,    79,    80,    81,    81,
      82,    82,    83,    83
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     0,     6,     2,     0,     0,     3,     0,
       4,     0,     4,     1,     1,     2,     1,     0,     4,     1,
       3,     1,     1,     0,     6,     4,     4,     2,     1,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     4,     5,     7,     5,     5,     3,     3,     3,
       7,     3,     3,     3,     1,     1,     1,     2,     3,     3,
       1,     0,     5,     0,     4,     3,     1,     1,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     3,
       1,     3,     3,     1,     3,     3,     1,     3,     3,     1,
       3,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    67,     0,     0,     0,     0,    68,     1,    13,     2,
       3,     0,    11,     0,     9,     6,    12,     0,     0,    19,
       0,    16,    17,    41,     0,     0,     0,     0,     0,     0,
       0,     0,    54,     0,     0,    72,    69,    70,    71,    31,
       5,     7,     0,    30,    32,    33,    34,    35,    36,    37,
      38,    39,    40,     0,    56,     0,    55,    73,    74,    75,
      76,    77,    10,    15,     0,     0,     0,    60,    54,     0,
      57,    89,    80,    83,    86,     0,     0,     0,     0,     0,
      22,    21,     0,     0,    93,    92,     0,    91,     0,    61,
       0,     0,     0,    14,     4,    29,     0,     0,     0,     0,
       0,     0,     0,    52,    78,     0,    81,     0,    84,     0,
      87,     0,    53,     0,     0,    47,     0,    48,     0,     0,
       0,    49,     0,     8,    58,    51,    59,    23,    18,     0,
       0,    79,    82,    85,    88,     0,    20,    90,    42,    66,
       0,    64,     0,    25,     0,    43,     0,    46,    62,     0,
      45,    28,     0,     0,     0,     0,    65,    24,     0,    27,
      44,    50,     0,    26
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     3,    39,    12,    18,    40,    92,    15,    17,     4,
      10,    94,    20,    21,    64,    83,    41,   144,   152,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,   119,   120,   140,    22,    56,    57,    58,    75,
      59,    76,    60,    77,    61,    78,    86,    87
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -62
static const yytype_int16 yypact[] =
{
      -1,   -62,    21,    59,    -4,    51,   -62,   -62,   -62,   -62,
     -62,    53,    47,    62,   -62,   -62,   -62,     9,    54,   -62,
      12,   -62,   -62,    92,    81,   142,   166,   166,   153,   166,
       5,    13,     4,   166,    97,   -62,   -62,   -62,   -62,   -62,
     -62,   -62,   106,   -62,   -62,   -62,   -62,   -62,   -62,   -62,
     -62,   -62,   -62,   170,   -62,    96,   -62,   -62,   -62,   -62,
     -62,   -62,   -62,   -62,     7,   166,   102,   -62,   125,    41,
     135,   -62,   -62,   -62,   -62,     2,    16,    35,    36,    84,
     -62,   -62,   134,    40,   -62,    67,   111,   -62,   166,   136,
      83,   166,    -4,   -62,   -62,   -62,   166,   138,   166,   140,
     128,   103,   147,   -62,   -62,   137,   -62,   148,   -62,   154,
     -62,   158,   -62,     7,   162,   -62,    13,   -62,    91,   166,
     150,   -62,   110,   -62,   135,   -62,   -62,   173,   -62,   142,
     166,   -62,   -62,   -62,   -62,   141,   -62,   -62,   -62,    67,
      11,   -62,   142,   -62,    15,   187,   133,   -62,   -62,   166,
     -62,   -62,    72,   165,   142,   174,    67,   -62,    -1,   -62,
     -62,   -62,   167,   -62
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -62,   -62,    -3,   -62,   -62,   -62,   -62,   -62,   -62,   -62,
     -62,   -62,   -62,   181,   -62,   -61,   -62,   -62,   -62,   -62,
     -23,   -62,   -62,   -62,   -62,   -62,   -62,   -62,   -62,   -62,
     -22,   -62,   -62,   -62,   -62,     0,   -62,   -62,   -62,   -62,
     -62,   -62,   -62,   -62,   -62,   -62,   -62,    86
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -64
static const yytype_int16 yytable[] =
{
       5,     9,    66,   100,    69,    70,    80,    79,    80,    85,
      19,    90,     1,    19,    67,     8,   151,   104,    55,    95,
      88,    89,     1,   105,    27,     1,     2,    28,     1,   148,
      29,   106,   149,    81,     6,    81,     2,   107,    62,     2,
      82,    68,     2,   101,    35,    36,    37,    38,    84,    96,
     108,   110,   135,    98,    11,    23,   109,   111,    24,     7,
      25,   114,   115,   103,    26,    27,   118,     1,    28,   122,
      13,    29,    14,     8,   124,    96,   126,    30,    31,    98,
      16,     2,    32,    33,    34,    35,    36,    37,    38,   123,
     157,    96,    96,   158,    85,    98,    98,   139,    65,    96,
     -60,   -60,   112,    98,   -60,   121,   145,    23,   146,   102,
      24,    96,    25,   138,    91,    98,    26,    27,    96,   150,
      28,   129,    98,    29,    99,     8,    93,   156,   142,    30,
      31,   160,   116,   117,    32,    33,    34,    35,    36,    37,
      38,    96,    89,    23,   153,    98,    24,    98,    25,   114,
     128,   155,    26,    27,   -63,   113,    28,   127,   162,    29,
     125,     8,   114,   147,   130,    30,    31,    67,   141,   131,
      32,    33,    34,    35,    36,    37,    38,    27,    96,    97,
      28,   132,    98,    29,    71,    72,    73,    74,   133,   134,
     136,   143,   154,   159,    68,   163,   161,    35,    36,    37,
      38,    63,   137
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-62)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_uint8 yycheck[] =
{
       0,     4,    25,    64,    26,    27,     1,    29,     1,    31,
       1,    33,    13,     1,     1,    19,     1,    15,    18,    42,
      16,    17,    13,    21,    11,    13,    27,    14,    13,    18,
      17,    15,    21,    28,    13,    28,    27,    21,    26,    27,
      35,    28,    27,    65,    31,    32,    33,    34,    35,     8,
      15,    15,   113,    12,     3,     1,    21,    21,     4,     0,
       6,    21,    22,    22,    10,    11,    88,    13,    14,    91,
      17,    17,    25,    19,    96,     8,    98,    23,    24,    12,
      18,    27,    28,    29,    30,    31,    32,    33,    34,    92,
      18,     8,     8,    21,   116,    12,    12,   119,    17,     8,
       8,     9,    18,    12,    12,    22,   129,     1,   130,     7,
       4,     8,     6,    22,    17,    12,    10,    11,     8,   142,
      14,    18,    12,    17,    28,    19,    20,   149,    18,    23,
      24,   154,    21,    22,    28,    29,    30,    31,    32,    33,
      34,     8,    17,     1,   144,    12,     4,    12,     6,    21,
      22,    18,    10,    11,    18,    21,    14,    17,   158,    17,
      22,    19,    21,    22,    17,    23,    24,     1,    18,    32,
      28,    29,    30,    31,    32,    33,    34,    11,     8,     9,
      14,    33,    12,    17,    31,    32,    33,    34,    34,    31,
      28,    18,     5,    28,    28,    28,    22,    31,    32,    33,
      34,    20,   116
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    13,    27,    37,    45,    71,    13,     0,    19,    38,
      46,     3,    39,    17,    25,    43,    18,    44,    40,     1,
      48,    49,    71,     1,     4,     6,    10,    11,    14,    17,
      23,    24,    28,    29,    30,    31,    32,    33,    34,    38,
      41,    52,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    71,    72,    73,    74,    76,
      78,    80,    26,    49,    50,    17,    56,     1,    28,    66,
      66,    31,    32,    33,    34,    75,    77,    79,    81,    66,
       1,    28,    35,    51,    35,    66,    82,    83,    16,    17,
      66,    17,    42,    20,    47,    56,     8,     9,    12,    28,
      51,    66,     7,    22,    15,    21,    15,    21,    15,    21,
      15,    21,    18,    21,    21,    22,    21,    22,    66,    68,
      69,    22,    66,    38,    66,    22,    66,    17,    22,    18,
      17,    32,    33,    34,    31,    51,    28,    83,    22,    66,
      70,    18,    18,    18,    53,    56,    66,    22,    18,    21,
      56,     1,    54,    71,     5,    18,    66,    18,    21,    28,
      56,    22,    71,    28
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
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))

/* Error token number */
#define YYTERROR	1
#define YYERRCODE	256


/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
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
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  YYUSE (yytype);
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

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULL, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULL;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULL, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
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

  YYUSE (yytype);
}




/* The lookahead symbol.  */
int yychar;


#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval YY_INITIAL_VALUE(yyval_default);

/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

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

       Refer to the stacks through separate pointers, to allow yyoverflow
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
  int yytoken = 0;
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

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
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
  if (yypact_value_is_default (yyn))
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
      if (yytable_value_is_error (yyn))
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
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
        case 3:
/* Line 1787 of yacc.c  */
#line 435 "yacc.y"
    { TS_InsertaMARCA(); }
    break;

  case 4:
/* Line 1787 of yacc.c  */
#line 435 "yacc.y"
    { TS_VaciarENTRADAS(); }
    break;

  case 7:
/* Line 1787 of yacc.c  */
#line 439 "yacc.y"
    {subProg = 1;}
    break;

  case 8:
/* Line 1787 of yacc.c  */
#line 439 "yacc.y"
    {subProg = 0;}
    break;

  case 9:
/* Line 1787 of yacc.c  */
#line 441 "yacc.y"
    { decVar = 1; }
    break;

  case 10:
/* Line 1787 of yacc.c  */
#line 441 "yacc.y"
    { decVar = 0; }
    break;

  case 17:
/* Line 1787 of yacc.c  */
#line 451 "yacc.y"
    {tipoTMP = (yyvsp[(1) - (1)]).type;}
    break;

  case 20:
/* Line 1787 of yacc.c  */
#line 453 "yacc.y"
    {TS_InsertaIDENT((yyvsp[(3) - (3)]));}
    break;

  case 21:
/* Line 1787 of yacc.c  */
#line 454 "yacc.y"
    {TS_InsertaIDENT((yyvsp[(1) - (1)]));}
    break;

  case 23:
/* Line 1787 of yacc.c  */
#line 457 "yacc.y"
    {TS_InsertaSUBPROG((yyvsp[(2) - (3)]));}
    break;

  case 25:
/* Line 1787 of yacc.c  */
#line 457 "yacc.y"
    {TS_InsertaSUBPROG((yyvsp[(2) - (4)]));}
    break;

  case 26:
/* Line 1787 of yacc.c  */
#line 459 "yacc.y"
    {TS_InsertaPARAMF((yyvsp[(4) - (4)]));}
    break;

  case 27:
/* Line 1787 of yacc.c  */
#line 459 "yacc.y"
    {TS_InsertaPARAMF((yyvsp[(2) - (2)]));}
    break;

  case 42:
/* Line 1787 of yacc.c  */
#line 475 "yacc.y"
    {(yyval).type =  checkType((yyvsp[(1) - (4)]),(yyvsp[(2) - (4)]),(yyvsp[(3) - (4)]));}
    break;

  case 43:
/* Line 1787 of yacc.c  */
#line 477 "yacc.y"
    {if((yyvsp[(3) - (5)]).type != boolean)
    fprintf(stderr,"[Linea %d]: no hay expresion tipo logica \n",linea_si);}
    break;

  case 44:
/* Line 1787 of yacc.c  */
#line 479 "yacc.y"
    {if((yyvsp[(3) - (7)]).type != boolean)
    fprintf(stderr,"[Linea %d]: no hay expresion tipo logica \n",linea_si);}
    break;

  case 45:
/* Line 1787 of yacc.c  */
#line 483 "yacc.y"
    {if((yyvsp[(3) - (5)]).type != boolean)
    fprintf(stderr,"[Linea %d]: no hay expresion tipo logica \n",linea_si);}
    break;

  case 50:
/* Line 1787 of yacc.c  */
#line 492 "yacc.y"
    {if((yyvsp[(5) - (7)]).type != boolean)
    fprintf(stderr,"[Linea %d]: no hay expresion tipo logica \n",linea_si);}
    break;

  case 53:
/* Line 1787 of yacc.c  */
#line 499 "yacc.y"
    {	(yyval).type = (yyvsp[(2) - (3)]).type;}
    break;

  case 54:
/* Line 1787 of yacc.c  */
#line 500 "yacc.y"
    { (yyval).type=asignaTipo((yyvsp[(1) - (1)])); strcpy((yyval).lexema,(yyvsp[(1) - (1)]).lexema); }
    break;

  case 55:
/* Line 1787 of yacc.c  */
#line 501 "yacc.y"
    {(yyval).type = (yyvsp[(1) - (1)]).type;}
    break;

  case 57:
/* Line 1787 of yacc.c  */
#line 503 "yacc.y"
    {	(yyval).type = (yyvsp[(2) - (2)]).type; }
    break;

  case 58:
/* Line 1787 of yacc.c  */
#line 504 "yacc.y"
    {	(yyval).type =  checkType((yyvsp[(1) - (3)]),(yyvsp[(2) - (3)]),(yyvsp[(3) - (3)]));}
    break;

  case 59:
/* Line 1787 of yacc.c  */
#line 505 "yacc.y"
    {	(yyval).type =  checkType((yyvsp[(1) - (3)]),(yyvsp[(2) - (3)]),(yyvsp[(3) - (3)]));}
    break;

  case 61:
/* Line 1787 of yacc.c  */
#line 508 "yacc.y"
    { strcpy(idFuncion,(yyvsp[(1) - (2)]).lexema); func =1; existeFuncion((yyvsp[(1) - (2)])); }
    break;

  case 62:
/* Line 1787 of yacc.c  */
#line 508 "yacc.y"
    {func = 0; verificaNumPar(posParam); posParam=0;}
    break;

  case 63:
/* Line 1787 of yacc.c  */
#line 509 "yacc.y"
    { strcpy(idFuncion,(yyvsp[(1) - (2)]).lexema); func =1; existeFuncion((yyvsp[(1) - (2)])); }
    break;

  case 64:
/* Line 1787 of yacc.c  */
#line 509 "yacc.y"
    {func = 0; verificaNumPar(posParam); posParam=0;}
    break;

  case 65:
/* Line 1787 of yacc.c  */
#line 511 "yacc.y"
    {if(func == 1) {	posParam++; verificaParam((yyvsp[(3) - (3)]),posParam);}}
    break;

  case 66:
/* Line 1787 of yacc.c  */
#line 512 "yacc.y"
    {if(func == 1){ posParam++; verificaParam((yyvsp[(1) - (1)]),posParam);}}
    break;


/* Line 1787 of yacc.c  */
#line 2099 "generated/y.tab.c"
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
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
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
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
      if (!yypact_value_is_default (yyn))
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

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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

#if !defined yyoverflow || YYERROR_VERBOSE
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
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
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


/* Line 2050 of yacc.c  */
#line 542 "yacc.y"

/** aqui incluimos el fichero generado por el ’lex’
*** que implementa la función ’yylex’
**/
#ifdef DOSWINDOWS
#include "../generated/lexyy.c"
#else
#include "../generated/lex.yy.c"
#endif
/**
Variable de entorno que indica la plataforma
se debe implementar la función yyerror. En este caso
simplemente escribimos el mensaje de error en pantalla
**/

void yyerror( const char *msg )
{
	fprintf(stderr,"[Linea %d]: %s\n", linea_actual, msg) ;
}


