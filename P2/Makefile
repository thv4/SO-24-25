p2 : p2.c comandos.h lista.h general.h comandos.o lista.o general.o listaArchivo.h listaArchivo.o listaMemoria.h listaMemoria.o
	gcc -o p2 p2.c comandos.o lista.o general.o listaArchivo.o listaMemoria.o -Wall

comandos.o : comandos.c comandos.h 
	gcc -c comandos.c

lista.o : lista.c lista.h
	gcc -c lista.c

general.o : general.c general.h
	gcc -c general.c

limpiar : 
	rm p2 comandos.o lista.o general.o listaArchivo.o listaMemoria.o

listaArchivo.o : listaArchivo.c listaArchivo.h
	gcc -c listaArchivo.c

listaMemoria.o : listaMemoria.c listaMemoria.h
	gcc -c listaMemoria.c
