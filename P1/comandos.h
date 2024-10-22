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
#include <dirent.h>

void authors(char * trozos[]);
void pid();
void ppid();
void cd(char * trozos[]);
void date(char * trozos[]);
void historic(char * trozos[], tList L, ftList fL);
void Cmd_open(char * tr[], ftList * L);
void Cmd_close (char *tr[], ftList *L);
void Cmd_dup (char * tr[], ftList *L);
void infosys();
void help(char * trozos[]);
void makefile(char * trozos[]);
void cwd();
void makedir(char * trozos[]);
void listfile(char * trozos[]);
