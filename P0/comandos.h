/*
Mario Denis Radu Trifu (m.denis.radu@udc.es)
Mario Ozón Casais (mario.ozon@udc.es)
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>
#include <sys/utsname.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "lista.h"
#include "listaArchivo.h"

void authors(char * trozos[]);
void pid();
void ppid();
void cd(char * trozos[]);
void date(char * trozos[]);
void historic(char * trozos[], tList L, ftList fL);
void Cmd_open(char * tr[], ftList * L);
void infosys();
