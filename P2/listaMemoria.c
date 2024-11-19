#include "listaMemoria.h"
#include "comandos.h"

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

mtPosL mFindItem(char tipo[], int filtro, char filtro2[], mtList L) {
   mtPosL i;
   mtItemL item;
   for(i=L; i != NULL; i = i->next) {
        if ((strcmp("malloc",i->data.type) == 0) && (strcmp(i->data.type, tipo) == 0)) {
            if ((i->data.size == filtro)) {
                return i;
            }
        }
        if ((strcmp("shared",i->data.type) == 0) && (strcmp(i->data.type, tipo) == 0)) {
            if (i->data.other2 == filtro) {
                return i;
            }
        }
        if((strcmp("mmap",i->data.type) == 0) && (strcmp(i->data.type, tipo) == 0)) {
            if (strcmp(i->data.other1,filtro2) == 0) {
                return i;
            }
        }
   }
   return NULL;
}

mtPosL mFindMemAd(char *tr[], mtList L) {
    mtPosL i;
    char * memAd;

   for(i=L; i != NULL; i = i->next) {
        sscanf(tr[0], "%p", &memAd); // Pasar de string a puntero
        if(i->data.memAd == memAd){
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
   if(L == NULL) {
       printf("******Lista de bloques asignados para el proceso ");
       pid();
       return;
   }
   if(tipo == NULL) {
       printf("******Lista de bloques asignados para el proceso ");
       pid();
   } else {
       printf("******Lista de bloques asignados %s para el proceso ", tipo);
       pid();
   }

   for (i=L; i != NULL; i= i->next) {
       if(tipo == NULL) { // impresión sin filtros 
           fechaReserva = localtime(&i->data.fecha);
           strftime(sfecha, sizeof(sfecha),"%b %d %H:%M",fechaReserva);
           printf("\t%p\t\t%d %s ", i->data.memAd, i->data.size,sfecha);
           if (strcmp(i->data.type, "malloc") == 0) {
                printf("%s", i->data.type);
           }
           if (strcmp(i->data.type, "shared") == 0) {
                printf("%s (key %d)",i->data.type, i->data.other2);
           }
           if (strcmp(i->data.type, "mmap") == 0) {
                printf("%s (descriptor %d)", i->data.other1, i->data.other2);
           }
           printf("\n");
       } else {
           if (strcmp(tipo, "malloc") == 0 && strcmp(tipo, i->data.type) == 0) { // impresion malloc
              fechaReserva = localtime(&i->data.fecha);
               strftime(sfecha, sizeof(sfecha),"%b %d %H:%M",fechaReserva);
               printf("\t%p\t\t%d %s %s\n", i->data.memAd, i->data.size,sfecha, i->data.type);
           } else if (strcmp(tipo, "shared") == 0 && strcmp(tipo, i->data.type) == 0) {  // impresion shared
               fechaReserva = localtime(&i->data.fecha);
               strftime(sfecha, sizeof(sfecha),"%b %d %H:%M",fechaReserva);
               printf("\t%p\t\t%d %s %s (key %d)\n", i->data.memAd, i->data.size,sfecha, i->data.type,i->data.other2);
           }  else if (strcmp(tipo, "mmap") == 0 && strcmp(tipo, i->data.type) == 0){ // impresion mmap
               fechaReserva = localtime(&i->data.fecha);
               strftime(sfecha, sizeof(sfecha),"%b %d %H:%M",fechaReserva);
               printf("\t%p\t\t%d %s %s (descriptor %d)\n", i->data.memAd, i->data.size,sfecha, i->data.other1, i->data.other2);
           }
       }
   }
}