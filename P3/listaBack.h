#ifndef LISTABACK_H
#define LISTABACK_H

#include <stdio.h>
#include <sys/types.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct btNode * btPosL;

typedef struct btItemL {
    pid_t pid;
    time_t fecha;
    char senal[200];
    char *comando[20];
    int prioridad;

} btItemL;

typedef struct btNode {
    btItemL data;
    btPosL next;
}btNode;

typedef btPosL btList;

#endif