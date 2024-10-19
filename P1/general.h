/*
Mario Denis Radu Trifu (m.denis.radu@udc.es)
Mario Ozón Casais (mario.ozon@udc.es)
*/

#include <stdbool.h>
#include "lista.h"
#include "listaArchivo.h"

void imprimirPromp();
void leerEntrada(char * cadena, int tamaño);
int TrocearCadena(char * cadena, char * trozos[]);
bool procesarEntrada(char * trozos[], tList L, ftList *fL);
