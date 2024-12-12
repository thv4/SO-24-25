#include "listaDir.h"

bool dCreateNode(dtPosL *p) {
   *p = malloc(sizeof(**p));
   return (*p != NULL);
}

void dCreateList(dtList *L) {
   *L = NULL;
}


bool dInsertElement(dtIteml d, dtList *L) {
   dtPosL i, j;

   if (!dCreateNode(&i)) {
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

void dRemoveElement(dtPosL p, dtList *L) {
   dtPosL prev = NULL;
    dtPosL actual = *L;

   if(p == *L) {
       *L = (*L)->next;
   } else {
       while (actual != NULL && actual != p) {
           prev = actual;
           actual = actual->next;
       }
       if (actual == p) {
           prev->next = actual->next;
       }
   }
   free(p);
}

void dtListItems(dtList L) {
    dtPosL actual = L;
    printf("Directorios en la lista:\n");
    while (actual != NULL) {
        printf("- %s\n", actual->data.directorio);
        actual = actual->next;
    }
}

dtPosL dfindItem(char dir[], dtList L) {
    dtPosL i;
    for (i = L; i != NULL; i = i->next) {
        if (strcmp(i->data.directorio,dir)==0) {
            return i;
        }
    }
    return NULL;
}