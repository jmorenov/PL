# Un script SED para personalizar
# los mensajes de error

s/"syntax error"/msjerror[yystate]/g
w y.tab.copia
