/*
Mario Denis Radu Trifu (m.denis.radu@udc.es)
Mario Ozón Casais (mario.ozon@udc.es)
*/

#ifndef LISTAMEMORIA_H
#define LISTAMEMORIA_H


#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

typedef char mtString[200];
typedef char *miPuntero;
typedef struct mtNode * mtPosL;

typedef struct mtItemL {
    miPuntero memAd;
    int size;
    time_t fecha;
    mtString type;
    mtString other1;
    int other2;
} mtItemL;

typedef struct mtNode {
    mtItemL data;
    mtPosL next;
}mtNode;

typedef mtPosL mtList;

bool mCreateNode();
void mCreateList();
bool mInsertElement();
mtPosL mFindItem();
mtPosL mFindMemAd();
void mRemoveElement();
void mDeleteList();
void mPrintList();

#endif