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

mtPosL mFindItem(size_t size, char filtro[], char tipo[], mtList L) {
   mtPosL i;
   for(i=L; i != NULL; i = i->next) {
       if ((i->data.size == size) && (strcmp(i->data.type, tipo))) {
           return i;
       }
       if (strcmp(i->data.other, filtro) && (strcmp(i->data.type, tipo))) {
           return i;
       }
       if (strcmp(i->data.other, filtro) && (strcmp(i->data.type, tipo))) {
           return i;
       }
   }
   return NULL;
}

void mRemoveElement(mtPosL p, mtList *L) {
   mtPosL prev = NULL;
   mtPosL actual = *L;

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

void mDeleteList(mtList *L) {
   mtPosL temp;

   while (*L != NULL) {
       temp = *L;
       *L = (*L)->next;
       free(temp);
   }
}

void mPrintList (char tipo[], mtList L) {
   mtPosL i;
   char sfecha[64];
   struct tm *fechaReserva;
   
   if(tipo == NULL) {
       printf("******Lista de bloques asignados para el proceso ");
       pid();
   } else {
       printf("******Lista de bloques asignados %s para el proceso ", tipo);
       pid();
   }

   for (i=L; i != NULL; i= i->next) {
       if(tipo == NULL) {
           fechaReserva = localtime(&i->data.fecha);
           strftime(sfecha, sizeof(sfecha),"%b %d %H:%M",fechaReserva);
           printf("\t%s\t\t%d %s %s", i->data.memAd, i->data.size,sfecha, i->data.type);
       } else {
           if (strcmp(tipo, i->data.type) == 0) {
              fechaReserva = localtime(&i->data.fecha);
               strftime(sfecha, sizeof(sfecha),"%b %d %H:%M",fechaReserva);
               printf("\t%s\t\t%d %s %s", i->data.memAd, i->data.size,sfecha, i->data.type);
           } else if (strcmp(tipo, i->data.type) == 0) {
               fechaReserva = localtime(&i->data.fecha);
               strftime(sfecha, sizeof(sfecha),"%b %d %H:%M",fechaReserva);
               printf("\t%s\t\t%d %s %s (key %s)", i->data.memAd, i->data.size,sfecha, i->data.type,i->data.other);
           } else if (strcmp(tipo, i->data.type) == 0) {
               fechaReserva = localtime(&i->data.fecha);
               strftime(sfecha, sizeof(sfecha),"%b %d %H:%M",fechaReserva);
               printf("\t%s\t\t%d %s %s (key %s)", i->data.memAd, i->data.size,sfecha, i->data.type, i->data.other);
           } else {
               fechaReserva = localtime(&i->data.fecha);
               strftime(sfecha, sizeof(sfecha),"%b %d %H:%M",fechaReserva);
               printf("\t%s\t\t%d %s %s (descriptor %s)", i->data.memAd, i->data.size,sfecha, i->data.type, i->data.other);
           }
       }
   }
}