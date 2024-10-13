/*
Mario Denis Radu Trifu (m.denis.radu@udc.es)
Mario Ozón Casais (mario.ozon@udc.es)
*/

#include "comandos.h"
#include "general.h"

void authors(char * trozos[]) {
    if (trozos[1] != NULL && strcmp(trozos[1],"-l")==0){
        printf("m.denis.radu\nmario.ozon\n");
    } else if (trozos[1] != NULL && strcmp(trozos[1],"-n")==0) {
        printf("Mario Denis Radu Trifu\nMario Ozón Casais\n");
    } else {
        printf("Logins: m.denis.radu\nmario.ozon\n");
        printf("Names: Mario Denis Radu Trifu\nMario Ozón Casais\n");
    }
}

void pid() {
    printf("%d\n",getpid());
}

void ppid() {
    printf("%d\n",getppid());
}

void cd(char * trozos[]) {
    char directorio[256];

    if (trozos[1] == NULL) {
        printf("%s\n", getcwd(directorio, sizeof directorio));
    } else {
        chdir(trozos[1]);
    }
}

void date(char * trozos[]) {
    char sfecha[100];
    time_t ltime;
    struct tm *newtime;

    ltime = time(NULL);
    newtime = localtime(&ltime);

    if (trozos[1] != NULL && strcmp(trozos[1],"-d")==0){
        strftime(sfecha, sizeof(sfecha),"%d/%m/%y", newtime);
        printf("%s\n", sfecha);
    } else if (trozos[1] != NULL && strcmp(trozos[1],"-t")==0){
        strftime(sfecha, sizeof(sfecha),"%T",newtime);
        printf("%s\n",sfecha);
    } else {
        strftime(sfecha, sizeof(sfecha),"%d/%m/%y  %T",newtime);
        printf("%s\n", sfecha);
    }
}

void historic(char * trozos[], tList L, ftList fL) {
    int N, ultId = 0;
    tPosL comando;
    tItemL itemNuevo;
    char * trozo[100];
    char copiaTrozo[100];

    if (trozos[1] == NULL) {
        printList(L);
    } else {
        N = atoi (trozos[1]);
        if (trozos[1] != NULL && N < 0) {
            N = N * -1;
            printN(L, N);
        } else if (trozos[1] != NULL && N > 0){
            comando = findItem(N, L);

            ultId = ultimoElemento(L);
            strcpy(copiaTrozo, comando->data.comando);
            strcpy(itemNuevo.comando, copiaTrozo);
            itemNuevo.id = ultId + 1;
            insertElement(itemNuevo, &L);

            TrocearCadena(copiaTrozo, trozo);
            procesarEntrada(trozo, L, fL);
        }
    }
}

void Cmd_open(char * tr[], ftList *L) {
    int i,df, mode=0;
    ftItemL item;

    if (tr[1]==NULL) { /*no hay parametro*/
        fPrintList(*L);
        return;
    }
    for (i=2; tr[i]!=NULL; i++) {
      if (!strcmp(tr[i],"cr")) mode|=O_CREAT;
      else if (!strcmp(tr[i],"ex")) mode|=O_EXCL;
      else if (!strcmp(tr[i],"ro")) mode|=O_RDONLY;
      else if (!strcmp(tr[i],"wo")) mode|=O_WRONLY;
      else if (!strcmp(tr[i],"rw")) mode|=O_RDWR;
      else if (!strcmp(tr[i],"ap")) mode|=O_APPEND;
      else if (!strcmp(tr[i],"tr")) mode|=O_TRUNC;
      else break;
    }
    df = open(tr[1],mode,0777);
    if (df ==-1) {
        perror ("Imposible abrir fichero\n");
    }else {
        item.OpMode = mode;
        item.descriptor = df;
        strcpy(item.fname, tr[1]);
        fInsertElement(item,L);
        printf ("Anadida entrada a la tabla ficheros abiertos\n");
    }
}

void infosys() {
    struct utsname datos;
    uname(&datos);
    printf("Machine: %s\nNode name: %s\nOperating system release: %s"
    "\nOperating system version: %s\nHardaware identifier: %s\nNIS/YP domain: %s\n"
    ,datos.machine, datos.nodename, datos.release, datos.sysname, datos.version, datos.__domainname);
}
