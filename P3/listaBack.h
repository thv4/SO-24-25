#ifndef LISTABACK_H
#define LISTABACK_H

#include <stdio.h>
#include <sys/types.h>
#include <stdbool.h>
#include <stdlib.h>
#include <pwd.h>
#include <unistd.h>
#include <time.h>

typedef struct btNode * btPosL;

typedef struct btItemL {
    pid_t pid;
    time_t fecha;
    char senal[200];
    char ** comando;
    int prioridad;

} btItemL;

typedef struct btNode {
    btItemL data;
    btPosL next;
}btNode;

typedef btPosL btList;

bool bCreateNode(btPosL *p);
void bCreateList(btList *L);
bool bInsertElement(btItemL d, btList *L);
void bRemoveElement(btPosL p, btList *L);
void bDeleteList(btList *L);

#endif