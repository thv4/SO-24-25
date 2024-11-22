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
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include "lista.h"
#include "listaArchivo.h"


void authors(char * trozos[]);
void pid();
void ppid();
void cd(char * trozos[]);
void date(char * trozos[]);
void historic();
void Cmd_open(char * tr[], ftList * L);
void Cmd_close (char *tr[], ftList *L);
void Cmd_dup (char * tr[], ftList *L);
void infosys();
void help(char * trozos[]);
void makefile(char * trozos[]);
void makedir(char * trozos[]);
void listfile(char * trozos[]);
void cwd();
void listdir(char * trozos[]);
void erase (char * trozos[]);
void reclist(char * trozos[]);
void revlist(char * trozos[]);
void delrec(char *trozos[]);

void allocate();
void deallocate();

void memfill();
void memdump();

void memory();
void Cmd_ReadFile();
void Cmd_WriteFile();
void Cmd_read();
void Cmd_write();
void recurse();