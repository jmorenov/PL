.SUFFIXES:

prueba: main.o lex.yy.o
	gcc -o prueba main.o lex.yy.o
lex.yy.o: lex.yy.c
	gcc -c lex.yy.c
main.o: main.c
	gcc -c main.c
lex.yy.c: tokensLex.l
	flex -ll tokensLex.l
limpia:
	rm -f prueba main.o lex.yy.o lex.yy.c
todo:
	make prueba
