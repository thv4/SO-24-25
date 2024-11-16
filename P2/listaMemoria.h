#ifndef LISTAMEMORIA_H
#define LISTAMEMORIA_H


#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

typedef char mtString[200];
typedef struct mtNode * mtPosL;

typedef struct mtItemL {
    mtString memAd;
    size_t size;
    time_t fecha;
    mtString type;
    mtString other;
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
void mRemoveElement();
void mDeleteList();
void mPrintList();

#endif