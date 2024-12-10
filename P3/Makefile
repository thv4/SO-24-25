p3 : p3.c comandos.h lista.h general.h comandos.o lista.o general.o listaArchivo.h listaArchivo.o listaMemoria.h listaMemoria.o listaBack.o listaBack.h
	gcc -o p3 p3.c comandos.o lista.o general.o listaArchivo.o listaMemoria.o listaBack.o -Wall

comandos.o : comandos.c comandos.h
	gcc -c comandos.c

lista.o : lista.c lista.h
	gcc -c lista.c

general.o : general.c general.h
	gcc -c general.c

limpiar :
	rm p3 comandos.o lista.o general.o listaArchivo.o listaMemoria.o listaBack.o

listaArchivo.o : listaArchivo.c listaArchivo.h
	gcc -c listaArchivo.c

listaMemoria.o : listaMemoria.c listaMemoria.h
	gcc -c listaMemoria.c

listaBack.o : listaBack.c listaBack.h
	gcc -c listaBack.c
