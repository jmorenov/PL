# fichero Makefile
#

# nombre del fichero ejecutable
#
TARGETS= gui

# Directorio de fox
#
FOXDIR = /usr/local/lib

# banderas para el compilador (C y C++). Se indican los directorios donde se puenden
# encontrar ficheros para incluir mediante la opcion -I
# la opcion -g sirve para permitir la depuración
#
# CFLAGS=    -g -DXWINDOWS -DSHM -I/usr/include -I$(FOXDIR) -I.
# CXXFLAGS=  -g -DXWINDOWS -DSHM -I/usr/include -I$(FOXDIR) -I.

CFLAGS=    -g -I/usr/include -I$(FOXDIR) -I.
CXXFLAGS=  -g -I/usr/include -I$(FOXDIR) -I.


# banderas pra el enlazador
# Se indica directorios donde encontrar las funciontecas con -L. Usando -l seguido del
# nombre se indica la funcionteca que se desea enlazar.
#
LDFLAGS= -L/usr/lib -lFOX-1.2

# definicion del compilador
#
CC = g++

# Sufijos
#
.SUFFIXES: .cc .c .o

# Reglas
# $< -> Todas las dependencias que han cambiado
# $@ -> El fichero objetivo (target)
# $^ -> Todas las dependencias

# Como pasar de .cc a .o
#
.cc.o:
	$(CC) $(CXXFLAGS) -c $<

# Como pasar de .o a ejecutable (sin sufijo)
#
.o:
	$(CC) $(LDFLAGS) $^ -o $@

# orden que sera ejecutada por defecto
#
default : $(TARGETS)

# regla de ejecucion
#

$(TARGETS) : $(TARGETS).o opTS.o gstBreak.o prefs.o \
	fuentes.o reglas.o claseTS.o dlgIncludes.o gestorOP.o \
	esquema.o scanner.o y.tab.o sefasgen.o main.o

opTS.o: opTS.c opTS.h

gui.o: gui.cpp gui.h

gstBreak.o: gstBreak.cpp

prefs.o: prefs.cpp

fuentes.o: fuentes.cpp

reglas.o: reglas.cpp

claseTS.o: claseTS.cpp

dlgIncludes.o: dlgIncludes.cpp

gestorOP.o: gestorOP.cpp

esquema.o: esquema.cpp

sefasgen.o: sefasgen.cpp

main.o: main.cpp

#
# Parser para el esquema de traduccion
scanner.o : trad.lex trad.y genMsjs
	byacc -d -t -v trad.y
	flex -oscanner.c trad.lex
	cat y.output | ./genMsjs | cat > msj.err
	sed -nf tradMsjs.sed y.tab.c
	mv y.tab.copia y.tab.c
	gcc -c scanner.c
	gcc -c y.tab.c

genMsjs : mes.l
	flex mes.l
	gcc -o genMsjs lex.yy.c

#
#
clean:
	rm -f *.o
	rm -f $(TARGETS)

#
#
redo:
	touch *.cpp
	make

#
#
superclean:
	rm -f *.o
	rm *~
	rm -f $(TARGETS)
