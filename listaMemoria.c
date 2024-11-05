#include "listaMemoria.h"

bool mCreateNode(mtPosL *p) {
    *p = malloc(sizeof(**p));
    return (*p != NULL);
}

void mCreateList(mtList *L) {
    *L = NULL;
}

bool mInsertElement(mtItemL d, mtList *L) {
    mtPosL i, j;

    if (!mCreateNode(&i)) {
        return false;
    } else {
        i->data = d;
        i->next = NULL;
        if (*L == NULL) {
            *L = i;
        } else {
            j = *L;
            while (j->next != NULL) {
                j = j->next;
            }
            j->next = i;
        }
        return true;
    }
}

mtPosL mFindItem(int df, mtList L) {
    mtPosL i;
}

void mRemoveElement(mtPosL p, mtList *L) {
    mtPosL prev = NULL;
    mtPosL actual = *L; 
}

void mDeleteList(mtList *L) {
    mtPosL temp;

    while (*L != NULL) {
        temp = *L;
        *L = (*L)->next;
        free(temp);
    }
}

void mPrintList (mtList L) {
    mtPosL i;

}