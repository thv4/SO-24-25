/*
Mario Denis Radu Trifu (m.denis.radu@udc.es)
Mario Ozón Casais (mario.ozon@udc.es)
*/

#include "general.h"
#include "comandos.h"

void imprimirPromp(){ printf("$");}

void leerEntrada(char * cadena, int tamaño){
    fgets(cadena, tamaño, stdin);
}

int TrocearCadena(char * cadena, char * trozos[]) { 
    int i=1;

    if ((trozos[0]=strtok(cadena," \n\t")) == NULL) {
        return 0;
    }
    while ((trozos[i]=strtok(NULL," \n\t"))!=NULL) {
        i++;
    }
    return i;
}

bool procesarEntrada(char * trozos[], tList L) {
    if (strcmp(trozos[0],"authors")==0) {
        authors(trozos);
    }else if (strcmp(trozos[0],"pid")==0){
        pid();
    } else if (strcmp(trozos[0], "ppid")==0){
        ppid();
    } else if (strcmp(trozos[0],"cd")==0) {
        cd(trozos);
    } else if(strcmp(trozos[0],"date")==0){
        date(trozos);
    } else if(strcmp(trozos[0],"historic")==0) {
        historic(trozos, L);
    } else if (strcmp(trozos[0],"infosys")==0) {
        infosys();
    } else if (strcmp(trozos[0], "exit") == 0|| strcmp(trozos[0], "bye") == 0|| strcmp(trozos[0], "quit") == 0) {
        deleteList(&L);
        return true;
    }
    return false;
}
