#ifndef LISTADIR_H
#define LISTADIR_H

#include <stdio.h>
#include <sys/types.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct dtNode * dtPosL;

typedef struct dtIteml{
    char directorio[256];
} dtIteml;

typedef struct dtNode {
    dtIteml data;
    dtPosL next;
} dtNode;

typedef dtPosL dtList;

bool dCreateNode(dtPosL *p);
void dCreateList(dtList *L);
bool dInsertElement(dtIteml d, dtList *L);
void dRemoveElement(dtPosL p, dtList *L);
void dtListItems(dtList L);
dtPosL dfindItem(char dir[], dtList L);

#endif