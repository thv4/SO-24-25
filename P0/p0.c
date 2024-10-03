/*
Mario Denis Radu Trifu (m.denis.radu@udc.es)
Mario Ozón Casais (mario.ozon@udc.es)
*/

#include "comandos.h"
#include "general.h"
#include "lista.h"

int main(){
    char cadena[256];
    char * trozos[256];
    char copiaCadena[256];
    int numeroTrozos = 0, i = 1;
    tList lista;
    tItemL item;

    createList(&lista);
    while (true) {
        imprimirPromp();
        leerEntrada(cadena, sizeof cadena);
        strcpy(copiaCadena, cadena);
        numeroTrozos = TrocearCadena(cadena, trozos);
        if (trozos[0] != NULL && strcmp(trozos[0], "historic") != 0) {
            item.id = i;
            strcpy(item.comando, copiaCadena);
            insertElement(item, &lista);
            i++;
        } else if (trozos[0] != NULL && strcmp(trozos[0], "historic") == 0) {
            if (trozos[1] == NULL || (atoi (trozos[1]) < 0)) {
                item.id = i;
                strcpy(item.comando, copiaCadena);
                insertElement(item, &lista);
                i++;
            }
        }

        if (numeroTrozos > 0 && procesarEntrada(trozos, lista)) {
            break;
        }
    }
}