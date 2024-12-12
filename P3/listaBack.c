#include "listaBack.h"

bool bCreateNode(btPosL *p) {
   *p = malloc(sizeof(**p));
   return (*p != NULL);
}

void bCreateList(btList *L) {
   *L = NULL;
}

bool bInsertElement(btItemL d, btList *L) {
   btPosL i, j;

   if (!bCreateNode(&i)) {
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

void bRemoveElement(btPosL p, btList *L) {
   btPosL prev = NULL;
   btPosL actual = *L;

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

void bDeleteList(btList *L) {
   btPosL temp;

   while (*L != NULL) {
       temp = *L;
       *L = (*L)->next;
       free(temp);
   }
}

void bPrintList(btList *L){
    struct passwd *sReal;
    struct tm *fechaReserva;
    char sfecha[64];

    sReal = getpwuid(getuid());
   
     for (btPosL i = *L; i != NULL; i = i->next) {
        fechaReserva = localtime(&i->data.fecha);
        strftime(sfecha, sizeof(sfecha),"%b %d %H:%M",fechaReserva);
        printf("%d  %s p = %d %s %s ()", i->data.pid, sReal->pw_name, i->data.prioridad, sfecha, i->data.senal);
    }
}