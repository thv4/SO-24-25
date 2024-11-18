/*
Mario Denis Radu Trifu (m.denis.radu@udc.es)
Mario Ozón Casais (mario.ozon@udc.es)
*/

#include <stdbool.h>
#include <dirent.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>
#include <stdlib.h>
#include "lista.h"
#include "listaArchivo.h"

void imprimirPromp();
void leerEntrada(char * cadena, int tamaño);
int TrocearCadena(char * cadena, char * trozos[]);
bool procesarEntrada();
void printPermisos(struct stat file_stat);
void printFechaMod(struct stat file_stat);
void printPropGrupo(struct stat file_stat);
void printLink(struct dirent * infofile);
void listDirRecursively(char *basePath, int showHidden, int showLong, int showLinks, int showAcc);
void printLink2(char * infofile);
void revlistDirRecursively(char *basePath, int showHidden, int showLong, int showLinks, int showAcc);
void delrecDir(char *path);

void * MapearFichero();
void * ObtenerMemoriaShmget ();
void do_AllocateMalloc();
void do_AllocateMmap();
void do_AllocateCreateshared();
void do_AllocateShared();

void do_DeallocateMalloc();
void do_DeallocateMmap();
void do_DeallocateDelkey();
void do_DeallocateShared();
void do_DeallocateGenerico();
