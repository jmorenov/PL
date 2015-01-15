	#define IF	256
	#define	ELSE	257
	#define	DO	258
	#define	UNTIL	259
	#define	OP_BIN	260
	#define	OP_LIST	261
	#define	OP_LIST_START_CURSOR	262
	#define	OP_UNIT	263
	#define	OP_PM	289
	#define	TYPE	264
	#define	BEGIN_LIST	265
	#define	END_LIST	266
	#define	ASSIGN	267
	#define	PL	268
	#define PR	269
	#define	BEGIN_P	270
	#define	END	271
	#define	COMMA	272
	#define	SEMICOLON	273
	#define	INPUT	274
	#define	OUTPUT	275
	#define	MAIN	276
	#define	START_VAR_DEC	277
	#define	END_VAR_DEC	278
	#define	LIST	279
	#define	ID	280
	#define BOOL 281
    #define RETURN 282
    #define LIMIT_CHAR 283
    #define DIGIT 284
    #define LETTER 285
    #define SYMBOL 286
    #define MINUS 287
    #define POINT 288
	#define WHILE 289
#define INT 290
#define FLOAT 291
#define CHAR 292
#define CAD 293

#define MAIN 256
%token IF
%token ELSE
%token DO
%token UNTIL

%left OP_BIN
%right OP_LIST
%left OP_LIST_START_CURSOR
%right OP_UNIT
%left OP_PM

%token TYPE
%token BEGIN_LIST
%token END_LIST
%token ASSIGN
%token PL
%token PR
%token BEGIN_P
%token END
%token COMMA
%token SEMICOLON
%token INPUT
%token OUTPUT
%token START_VAR_DEC
%token END_VAR_DEC
%token LIST
%token ID
%token BOOL
%token RETURN
%token WHILE
%token INT
%token FLOAT
%token CHAR
%token CAD