/*
Mario Denis Radu Trifu (m.denis.radu@udc.es)
Mario Ozón Casais (mario.ozon@udc.es)
*/

#include "comandos.h"
#include "general.h"
#include "listaArchivo.h"

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
        strftime(sfecha, sizeof(sfecha),"%d/%m/%Y", newtime);
        printf("%s\n", sfecha);
    } else if (trozos[1] != NULL && strcmp(trozos[1],"-t")==0){
        strftime(sfecha, sizeof(sfecha),"%T",newtime);
        printf("%s\n",sfecha);
    } else {
        strftime(sfecha, sizeof(sfecha),"%d/%m/%Y  %T",newtime);
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
            itemNuevo.id = ultId;
            insertElement(itemNuevo, &L);

            TrocearCadena(copiaTrozo, trozo);
            procesarEntrada(trozo, L, &fL);
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

void Cmd_close (char *tr[], ftList *L) {
    int df;
    ftPosL p;

    if (tr[1]==NULL || (df=atoi(tr[1]))<0) { /*no hay parametro*/
        fPrintList(*L);/*o el descriptor es menor que 0*/
        return;
    }
    if (close(df)==-1)
        perror("Inposible cerrar descriptor");
    else {
        p = fFindItem(atoi(tr[1]), *L);
         if (p == NULL) {
            printf("Error: descriptor %d no encontrado en la lista\n", df);
        } else {
            fRemoveElement(p, L);
            printf("Eliminada entrada a la tabla ficheros abiertos para descriptor %d\n", df);
        }

    }
}

void Cmd_dup (char * tr[], ftList *L) { 
    int df, duplicado;
    char aux[500],*p;
    ftItemL copia;
    ftPosL original;
    
    if (tr[1]==NULL || (df=atoi(tr[1]))<0) { /*no hay parametro*/
        fPrintList(*L);                 /*o el descriptor es menor que 0*/
        return;
    }
    
    duplicado=dup(df);
    if (duplicado == -1) {
        perror("Error al duplicar el descriptor");
        return;
    }
    
    original = fFindItem(atoi(tr[1]), *L);
    if (original == NULL) {
        printf("Error: descriptor no encontrado en la lista\n");
        return;
    }

    p = original->data.fname;
    sprintf (aux,"dup %d (%s)",df, p);

    copia.descriptor = duplicado;
    strcpy(copia.fname, aux);
    copia.OpMode = original->data.OpMode;

    fInsertElement(copia, L);
}

void infosys() {
    struct utsname datos;
    uname(&datos);
    printf("Machine: %s\nNode name: %s\nOperating system release: %s"
    "\nOperating system version: %s\nHardaware identifier: %s\nNIS/YP domain: %s\n"
    ,datos.machine, datos.nodename, datos.release, datos.sysname, datos.version, datos.__domainname);
}

void help(char * trozos[]) {
    if (trozos[1] == NULL) {
        printf("authors  pid  pppid  cd  date\n");
        printf("historic  open  dup  close  infosys\n");
    } else if (strcmp(trozos[1],"authors")==0) {
        printf("authors [-n|-l]	Muestra los nombres y/o logins de los autores\n");
    }else if (strcmp(trozos[1],"pid")==0){
        printf("pid     Muestra el pid del shell\n");
    } else if (strcmp(trozos[1], "ppid")==0){
        printf("ppid 	Muestra el pid del proceso padre del shell\n");
    } else if (strcmp(trozos[1],"cd")==0) {
        printf("cd [dir] Cambia de directorio\n");
    } else if(strcmp(trozos[1],"date")==0){
        printf("date [-d|-t]	Muestra la fecha y/o la hora actual\n");
    } else if(strcmp(trozos[1],"historic")==0) {
        printf("historic [-c|-N|N]	Muestra (o borra)el historico de comandos\n");
        printf("\t-N: muestra los N primeros\n");
        printf("\t-c: borra el historico\n");
        printf("\tN: repite el comando N\n");
    } else if (strcmp(trozos[1],"open")==0){
        printf("open fich m1 m2...	Abre el fichero fich\n");
        printf("\ty lo anade a la lista de ficheros abiertos del shell\n");
        printf("\tm1, m2..es el modo de apertura (or bit a bit de los siguientes)\n");
        printf("\tcr: O_CREAT	ap: O_APPEND\n");
        printf("\tex: O_EXCL 	ro: O_RDONLY\n");
        printf("\trw: O_RDWR 	wo: O_WRONLY\n");
        printf("\ttr: O_TRUNC\n");
    } else if (strcmp(trozos[1],"close")==0){
        printf("close df	Cierra el descriptor df y elimina el correspondiente fichero de la lista de ficheros abiertos\n");
    } else if (strcmp(trozos[1],"dup")==0){
        printf("dup df	Duplica el descriptor de fichero df y anade una nueva entrada a la lista ficheros abiertos\n");
    } else if (strcmp(trozos[1],"infosys")==0) {
        printf("infosys 	Muestra informacion de la maquina donde corre el shell\n");
    } 
}

void makefile(char * trozos[]){
int fd;

fd = creat(trozos[1], 0777);
if (fd ==-1) {
        perror ("Imposible crear fichero\n");
    }
}

void makedir(char * trozos[]){
    int status;

    status = mkdir(trozos[1], 0777);
    if (status ==-1) {
        perror ("Imposible crear directorio\n");
    }
}

void listfile(char * trozos[]){
    DIR *dir;
    struct dirent *infofile;
    int i;

    if(trozos[1]==NULL){
        cwd();
    } else if ((strcmp(trozos[1],"-acc") == 0 || strcmp(trozos[1],"-link") == 0 || strcmp(trozos[1],"-long") == 0) && trozos[2] == NULL) {
        printf("Indique los archivos\n");
    }

    dir = opendir(".");
    if (dir == NULL) {
            perror("No se pudo abrir el directorio");
    }
    while ((infofile = readdir(dir)) != NULL) {
        for (i = 1; trozos[i] != NULL; i++) {
            if (strcmp(infofile->d_name, trozos[i]) == 0) {
                struct stat file_stat;

                if (lstat(infofile->d_name, &file_stat) == -1) {
                    perror("Error obteniendo información del archivo");
                    continue;
                }

                if (strcmp(trozos[1], "-long") == 0) {
                    // Para la fecha de modificación:
                    struct tm *tm_info = localtime(&file_stat.st_mtime);
                    char buffer[20];
                    strftime(buffer, 20, "%Y/%m/%d-%H:%M", tm_info);
                    // Para el propietario y grupo:
                    struct passwd *pw = getpwuid(file_stat.st_uid);
                    struct group *gr = getgrgid(file_stat.st_gid);

                    printf("%s  %lu  (%lu)\t%s\t%s  ", buffer, file_stat.st_nlink, file_stat.st_ino, pw->pw_name, gr->gr_name);

                    // Para los permisos:
                    printPermisos(file_stat);
                    printf("%ld  %s\n", file_stat.st_size,infofile->d_name);
                } else if (strcmp(trozos[1], "-acc") == 0) {
                    // Para la fecha de modificación:
                    struct tm *tm_info = localtime(&file_stat.st_mtime);
                    char buffer[20];
                    strftime(buffer, 20, "%Y/%m/%d-%H:%M", tm_info);

                    printf("%s  %ld  %s\n",buffer, file_stat.st_size, infofile->d_name);
                } else if (strcmp(trozos[1], "-link") == 0) {
                    char linkname[1024];
                    ssize_t link = readlink(infofile->d_name,linkname, sizeof(linkname) - 1);

                    if (link != -1) {
                        linkname[link] = '\0';  // Asegúrate de que la cadena esté terminada
                        printf("%ld  %s --> %s\n",file_stat.st_size, infofile->d_name,linkname);   
                    } else {
                        perror("Error al leer el enlace simbólico");
                    }
                }else {
                    printf("%ld  %s\n",file_stat.st_size, infofile->d_name);
                }  
            }

        }  
    }
    closedir(dir);
}

void cwd(){
    char directorio[256];
    printf("%s\n", getcwd(directorio, sizeof directorio));
}

void listdir(char * trozos[]){
    DIR *dir;
    struct dirent *infodir;
    bool lonG= false, hid = false, acc = false, link = false;

    for (int i = 1; trozos[i] != NULL ; i++){
        if (strcmp(trozos[i], "-long") == 0) {
            lonG = true;
        } else if (strcmp(trozos[i], "-hid") == 0) {
            hid = true;
        } else if (strcmp(trozos[i], "-acc") == 0) {
            acc = true;
        } else if (strcmp(trozos[i], "-link") == 0) {
            link = true;
        }
    }

    dir = opendir(".");
    while((infodir = readdir(dir)) != NULL){

        for (int i = 1; trozos[i]!=NULL; i++) {
            if (hid) {
                if(!lonG){


                }else{

                }
                
            } else if (lonG && !hid) {
            
            }
        }
    }
    closedir(dir);
}

