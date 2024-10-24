/*
Mario Denis Radu Trifu (m.denis.radu@udc.es)
Mario Ozón Casais (mario.ozon@udc.es)
*/

#include <stdbool.h>
#include <dirent.h>
#include "lista.h"
#include "listaArchivo.h"

void imprimirPromp();
void leerEntrada(char * cadena, int tamaño);
int TrocearCadena(char * cadena, char * trozos[]);
bool procesarEntrada(char * trozos[], tList L, ftList *fL);
void printPermisos(struct stat file_stat);
void printFechaMod(struct stat file_stat);
void printPropGrupo(struct stat file_stat);
void printLink(struct dirent * infofile);
void listDirRecursively(char *basePath, int showHidden, int showLong, int showLinks, int showAcc);
void printLink2(char * infofile);
void revlistDirRecursively(char *basePath, int showHidden, int showLong, int showLinks, int showAcc);
void delrecDir(char *path);

