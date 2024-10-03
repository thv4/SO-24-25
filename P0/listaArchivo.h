#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

typedef char tString[100];
typedef struct ftNode * ftPosL;

typedef struct ftItemL {
    int descriptor;
    tString fname;
    mode_t OpMode;
} ftItemL;

typedef struct ftNode {
    ftItemL data;
    ftPosL next;
}ftNode;

typedef ftPosL ftList;

bool fCreateNode(ftPosL *p);
void fCreateList(ftList *L);
bool fInsertElement(ftItemL d, ftList *L);
ftPosL fFindItem(tString nombre, ftList L);
void fRemoveElement(ftPosL p, ftList *L);
void fDeleteList(ftList *L);
void fPrintList (ftList L);