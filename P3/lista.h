/*
Mario Denis Radu Trifu (m.denis.radu@udc.es)
Mario Ozón Casais (mario.ozon@udc.es)
*/

#ifndef LISTA_H
#define LISTA_H

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>


typedef char tComando[100];
typedef struct tNode * tPosL;

typedef struct tItemL {
    tComando comando;
    int id;
} tItemL;

typedef struct tNode {
    tItemL data;
    tPosL next;
}tNode;

typedef tPosL tList;

bool createNode(tPosL *p);
void createList(tList *L);
bool insertElement(tItemL d, tList *L);
tPosL findItem(int id, tList L);
void removeElement(tPosL p, tList *L);
void printList (tList L);
void printN (tList L, int n);
int ultimoElemento (tList L);
void deleteList(tList *L);

#endif