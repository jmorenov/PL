#
# SEFASGEN
#
# Makefile para contruir compilador
#
# Autor: Ferrer Gonzalez, Sergio
#

# Poner aqui el nombre del fichero
# con la especificacion YACC
GRAM = gram.y

# y aqui el nombre para el
# ejecutable del compilador
COMP = compilador
all : compilador

compilador : $(GRAM) genmens peticiones.c marcar
	./marcar < $(GRAM) > FINAL.y
	yacc -d -t -v FINAL.y
	flex scanner.lex
	mv y.tab.c y.tab.copia
	sed -nf script.sed y.tab.copia
	rm -f y.tab.copia
	cat y.output | ./genmens | cat > msj.err
	gcc -o $(COMP) y.tab.c peticiones.c lex.yy.c

genmens : mes.l
	flex mes.l
	gcc -o genmens lex.yy.c


# Scanner que inserta llamadas a informar()
# Esta funcion nos servira para localizar
# la funcion en uso en la gramatica

marcar : marcar.lex
	flex -omarcar.c marcar.lex
	gcc -o marcar marcar.c

#
# Version antigua ide modo TEXTO
# ide : ide.c opTS.c
#	gcc -Wall -o ide ide.c opTS.c
#
