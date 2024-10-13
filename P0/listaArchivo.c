#include "listaArchivo.h"
#include <stdio.h>


bool fCreateNode(ftPosL *p) {
    *p = malloc(sizeof(**p));
    return (*p != NULL);
}

void fCreateList(ftList *L) {
    *L = NULL;
}

bool fInsertElement(ftItemL d, ftList *L) {
    ftPosL i, j;

    if (!fCreateNode(&i)) {
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

ftPosL fFindItem(int df, ftList L) {
    ftPosL i;
    for (i = L; i != NULL; i = i->next) {
        if (i->data.descriptor == df) {
            return i;
        }
    }
    return NULL;
}

void fRemoveElement(ftPosL p, ftList *L) {
    ftPosL i;
    if (p == *L) {
        *L = (*L)->next;
    } else if(p->next == NULL) {
        for ( i = *L; i->next != p; i = i->next) {
            i->next = NULL;
        }
    } else {
        i = p->next;
        p->data = i->data;
        p->next = i->next;
        p = i;
    }
    free(p);
}

void fDeleteList(ftList *L) {
    ftPosL temp;

    while (*L != NULL) {
        temp = *L;
        *L = (*L)->next;
        free(temp);
    }
}

void fPrintList (ftList L) {
    ftPosL i;

    for (i = L; i != NULL; i = i->next) {
        printf("%d   %s   %d\n", i->data.descriptor, i->data.fname, i->data.OpMode);
    }
}
