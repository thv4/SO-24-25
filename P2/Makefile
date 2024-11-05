p2.out : p2.c comandos.h lista.h general.h comandos.o lista.o general.o listaArchivo.h listaArchivo.o
	gcc -o p2.out p2.c comandos.o lista.o general.o listaArchivo.o -Wall

comandos.o : comandos.c comandos.h 
	gcc -c comandos.c

lista.o : lista.c lista.h
	gcc -c lista.c

general.o : general.c general.h
	gcc -c general.c

limpiar : 
	rm p2.out comandos.o lista.o general.o listaArchivo.o

listaArchivo.o : listaArchivo.c listaArchivo.h
	gcc -c listaArchivo.c
