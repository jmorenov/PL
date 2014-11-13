# Esquema de traduccion para SEFASGEN
#
# IMPORTANTE: Los "\n" se deben incluir
# de modo EXPLICITO !!!!
# Del Nivel de Tabulacion se ocupa el
# programa

# Inicio de PROGRAMA
# Regla 0
# TODO Sustituir TOOOODAS las ocurrencias de '\n'

# Probamos a ver si puedo poner +1 "\n"

REGLA iniProg
	"#include <stdio.h>\n"
	"#include __VAR_TDAS__\n"
	"#include __VAR_FUNCS__\n\n"
	"main()\n"
FIN_REGLA

# Regla 1
# Regla Inicio de Bloque
# NO INCLUIR '\n' en la CADENA !!!
REGLA iniBlq
	"{ "
	CAD_OPC
	"\n"
FIN_REGLA

# Regla 2
# Declaracion de variables

REGLA decVar
	TIPO
	" "
	CAD
	";\n"
FIN_REGLA


# Regla 3
# Regla para FIN Bloque

REGLA finBloque
	"}\n"
FIN_REGLA

# Regla 4
# Asignacion

REGLA asig
	CAD
	" = "
	CAD
	CAD_OPC
	CAD_OPC
	";\n"
FIN_REGLA

# Regla 5
# Sentencia de SALIDA
# Cuidado que la cadena que describe los argumentos
# debe incluir espacios !!!!

REGLA salida
	"printf(\""
	CAD
	"\""
	CAD
	" );\n"
FIN_REGLA

# Regla 6
# Sentencia de ENTRADA
# Idem

REGLA entrada
	"scanf( "
	CAD
	CAD
	" );\n"
FIN_REGLA

# Regla 7
# Salto INCONDICIONAL

REGLA saltoIncond
	"goto "
	CAD
	";\n"
FIN_REGLA

# Regla 8
# Salto CONDICIONAL

REGLA saltoCond
	"if ( !"
	CAD
	" ) goto "
	CAD
	";\n"
FIN_REGLA

# Regla 9
# Escribir ETIQUETA

REGLA escEtiqueta
	CAD
	":\n"
FIN_REGLA

# Regla 10
# Declaracion de Procedimientos
# Cuidado que solo tenemos PROCS de momento
# Usar el tipo de Dato NO_ASIG como void
# La Cadena que envia el compilador
# es el NOMBRE del PROC !!!
# TODO Se podria hacer todo de una vez ??????

REGLA decProc
	TIPO
	" "
	CAD
	"("
FIN_REGLA

# Regla 11
# Parametro de una declaracion de proc

REGLA paramDec
	TIPO
	" "
	CAD
FIN_REGLA

# Regla 12
# Fin PROTOTIPO en Declaracion de PROC

REGLA finProto
	" )\n"
FIN_REGLA

# Regla 13
# Fin Declaracion de PROC...
# Añadir un ";" para no tener
# LISTA_CAMPOS VACIA y no tener conflictos ???

REGLA finDeclaracion
FIN_REGLA

# Regla 14
# Llamada a PROC

REGLA callProc
	CAD
	"( "
	CAD
	" );\n"
FIN_REGLA
