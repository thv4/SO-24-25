/*
Mario Denis Radu Trifu (m.denis.radu@udc.es)
Mario Ozón Casais (mario.ozon@udc.es)
*/

#include "lista.h"

bool createNode(tPosL *p) {
    *p = malloc(sizeof(**p));
    return (*p != NULL);
}

void createList(tList *L) {
    *L = NULL;
}

bool insertElement(tItemL d, tList *L) {
    tPosL i, j;

    if (!createNode(&i)) {
        return false;
    } else {
        i->data = d;
        i->next = NULL;
        if (*L == NULL) {
            *L = i;
        } else {
            for (j = *L; j->next != NULL; j = j->next);
            j->next = i;
        }
        return true;
    }
}

tPosL findItem(int id, tList L) {
    tPosL i;
    for (i = L; i != NULL; i = i->next) {
        if (i->data.id == id) {
            return i;
        }
    }
    return NULL;
}

void removeElement(tPosL p, tList *L){
    tPosL i;
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

void printList (tList L) {
    tPosL i;
    for (i = L; i != NULL; i = i->next) {
        printf("%d  %s", i->data.id, i->data.comando);
    }
}

void printN (tList L, int n) {
    tPosL i;
    int ultimo = ultimoElemento(L), resta = 0;
    if (n > ultimo) {
        printf("no\n");
    }
    resta = ultimo - n;
    for (i = L; i != NULL; i = i->next) {
        if (i->data.id >= resta) {
            printf("%d  %s", i->data.id, i->data.comando);
        }
    }
}

int ultimoElemento (tList L) {
    tPosL i;
    int nElemento = 1;

    for (i = L; i != NULL; i = i->next) {
        nElemento++;
    }
    return nElemento;
}

void deleteList(tList *L) {
    tPosL temp;

    while (*L != NULL) {
        temp = *L;
        *L = (*L)->next;
        free(temp);
    }
}
