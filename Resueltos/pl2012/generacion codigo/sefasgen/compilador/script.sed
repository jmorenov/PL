# Un script para hacer que la salida
# DEBUG de YACC sea por stderr
# e incorporar mensajes de error personalizados
# en vez de "syntax error"

s/printf("%sdebug/fprintf(stderr,"%sdebug/g
s/"syntax error"/msjerror[yystate]/g
w y.tab.c
