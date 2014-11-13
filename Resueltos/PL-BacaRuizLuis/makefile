all: ejecutar

ejecutar: lexico.c sintactico.y
	lex lexico.c
	yacc -d sintactico.y
	yacc sintactico.y
	gcc -o sintac y.tab.c -lfl
	yacc -v sintactico.y --report=all

clean: 
	rm lex.yy.c y.tab.c y.tab.h sintac y.output

clear: clean
c: clean
