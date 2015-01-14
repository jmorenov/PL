.SUFFIXES:

prueba: main.o y.tab.o
	gcc -o prueba main.o y.tab.o
y.tab.o: y.tab.c
	gcc -c y.tab.c
main.o: main.c
	gcc -c main.c
y.tab.c: yacc.y lex.yy.c
	yacc -v yacc.y
lex.yy.c: tokensLex.l
	flex -ll tokensLex.l
limpia:
	rm -f prueba main.o y.tab.o y.tab.c lex.yy.c y.output
todo:
	make limpia
	make prueba
