/*
Mario Denis Radu Trifu (m.denis.radu@udc.es)
Mario Ozón Casais (mario.ozon@udc.es)
*/

#include "comandos.h"
#include "general.h"
#include "listaArchivo.h"
#include "listaMemoria.h"

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

void historic(char * trozos[], tList L, ftList fL, mtList mL) {
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
            procesarEntrada(trozo, L, &fL, &mL);
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
        printf("makefile  makedir  listfile  cwd  listdir\n");
        printf("reclist  revlist  erase  delrec\n");
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
    } else if (strcmp(trozos[1],"makefile")==0) {
        printf("makefile [name]	Crea un fichero de nombre name\n");
    } else if (strcmp(trozos[1],"makedir")==0) {
        printf("makedir [name]	Crea un directorio de nombre name\n");
    } else if (strcmp(trozos[1],"listfile")==0) {
        printf("listfile [-long][-link][-acc] name1 name2 ..	lista ficheros;\n");
        printf("\t-long: listado largo\n");
        printf("\t-acc: acesstime\n");
        printf("\t-link: si es enlace simbolico, el path contenido\n");
    } else if (strcmp(trozos[1],"cwd")==0) {
        printf("cwd 	Muestra el directorio actual del shell\n");
    } else if (strcmp(trozos[1],"listdir")==0) {
        printf("listdir [-hid][-long][-link][-acc] n1 n2 ..	lista contenidos de directorios\n");
        printf("\t-long: listado largo\n");
        printf("\t-hid: incluye los ficheros oculto\n");
        printf("\t-acc: acesstime\n");
        printf("\t-link: si es enlace simbolico, el path contenido\n");
    } else if (strcmp(trozos[1],"reclist")==0) {
        printf("reclist [-hid][-long][-link][-acc] n1 n2 ..	lista recursivamente contenidos de directorios (subdirs despues)\n");
        printf("\t-long: listado largo\n");
        printf("\t-hid: incluye los ficheros oculto\n");
        printf("\t-acc: acesstime\n");
        printf("\t-link: si es enlace simbolico, el path contenido\n");
    } else if (strcmp(trozos[1],"revlist")==0) {
        printf("revlist [-hid][-long][-link][-acc] n1 n2 ..	lista recursivamente contenidos de directorios (subdirs antes)\n");
        printf("\t-long: listado largo\n");
        printf("\t-hid: incluye los ficheros oculto\n");
        printf("\t-acc: acesstime\n");
        printf("\t-link: si es enlace simbolico, el path contenido\n");
    } else if (strcmp(trozos[1],"erase")==0) {
        printf("erase [name1 name2 ..]	Borra ficheros o directorios vacios\n");
    } else if (strcmp(trozos[1],"delrec")==0) {
        printf("delrec [name1 name2 ..]	Borra ficheros o directorios no vacios recursivamente\n");
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
    bool lonG= false, hid = false, acc = false, link = false;
    int i, j = 1;

    if(trozos[1]==NULL){
        cwd();
    }
    // Verificacion de las etiquetas 
    for (i = 1; trozos[i] != NULL ; i++){
        if (strcmp(trozos[i], "-long") == 0) {
            lonG = true;
            j++;
        } else if (strcmp(trozos[i], "-hid") == 0) {
            hid = true;
            j++;
        } else if (strcmp(trozos[i], "-acc") == 0) {
            acc = true;
            j++;
        } else if (strcmp(trozos[i], "-link") == 0) {
            link = true;
            j++;
        }
    }

    for (; trozos[j] != NULL; j++) { 
        
        struct stat file_stat;

        if (lstat(trozos[j], &file_stat) == -1) {
            perror("Error obteniendo información del archivo");
            continue;
        }

        if (!hid && trozos[j][0] == '.' && trozos[j][1] != '/' ) {
            continue;
        }
        
        if (lonG) {
            printFechaMod(file_stat);                    
            printf("  %lu  (%lu)", file_stat.st_nlink, file_stat.st_ino);  
            printPropGrupo(file_stat);                   
            printPermisos(file_stat);                    
            printf("%ld\t%s", file_stat.st_size, trozos[j]);  
            if (link) {
                printLink2(trozos[j]);                   
            } else {
                printf("\n");
            }
        } else if (acc) {
            printFechaMod(file_stat);
            printf("  %ld  %s", file_stat.st_size, trozos[j]);
            if (link) {
                printLink2(trozos[j]);                   
            } else {
                printf("\n");
            } 
        } else if (link) {
            printf("%ld  %s", file_stat.st_size, trozos[j]); 
            printLink2(trozos[j]);                       
        } else {
            printf("%ld\t%s\n", file_stat.st_size, trozos[j]);
        }
    }  
}

void cwd(){
    char directorio[256];
    printf("%s\n", getcwd(directorio, sizeof directorio));
}

void listdir(char * trozos[]){ 
    DIR *dir;
    struct dirent *infodir;
    bool lonG= false, hid = false, acc = false, link = false;
    int i;
    char *directorio;

    for (i = 1; trozos[i] != NULL ; i++){
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
    directorio = trozos[i-1];
    dir = opendir(directorio);

    if (!dir) {
        perror("El directorio no existe");
        return;
    }

    while((infodir = readdir(dir)) != NULL){
        struct stat file_stat;
        char rutaCompleta[1024]; 

        snprintf(rutaCompleta, sizeof(rutaCompleta), "%s/%s", directorio, infodir->d_name);

        if (lstat(rutaCompleta, &file_stat) == -1) {
            perror("Error obteniendo información del archivo");
            continue;
        }

        if (hid) {
            if(!lonG){
                if(acc){
                    printFechaMod(file_stat);
                }
                printf("%ld\t%s",file_stat.st_size,infodir->d_name);
                if (link) {
                    printLink(infodir);
                } else {
                    printf("\n");
                }
            }else{
                printFechaMod(file_stat);
                printf("  %lu  (%lu)",file_stat.st_nlink, file_stat.st_ino);
                printPropGrupo(file_stat);
                printPermisos(file_stat);
                printf("%ld\t%s",file_stat.st_size,infodir->d_name);
                if (link) {
                    printLink(infodir);
                } else {
                    printf("\n");
                }
            }
            
        } else if (lonG) {  
            if((strcmp(infodir->d_name,".")!=0) && (strcmp(infodir->d_name,"..")!=0) && (infodir->d_name[0]!='.')){
                printFechaMod(file_stat);
                printf("  %lu  (%lu)",file_stat.st_nlink, file_stat.st_ino);
                printPropGrupo(file_stat);
                printPermisos(file_stat);
                printf("%ld\t%s",file_stat.st_size,infodir->d_name);
                if (link) {
                    printLink(infodir);
                } else {
                    printf("\n");
                } 
            }
        }else {
            if((strcmp(infodir->d_name,".")!=0) && (strcmp(infodir->d_name,"..")!=0) && (infodir->d_name[0]!='.')){
                if(acc){
                    printFechaMod(file_stat);
                }
                printf("%ld\t%s",file_stat.st_size,infodir->d_name);
                if (link) {
                    printLink(infodir);
                } else {
                    printf("\n");
                } 
            }
        }
    }
    closedir(dir);
}

void erase (char * trozos[]){ 
    
    if(trozos[1]==NULL){
        perror("Error: No se especificó el nombre del archivo a eliminar\n");
    }else{
        for(int i = 1; trozos[i]!=NULL; i++){
            struct stat info;
            stat(trozos[i],&info);
            if (stat(trozos[i], &info) == 0) {
                if (S_ISREG(info.st_mode)) {
                // Archivo
                    if (remove(trozos[i]) == 0) {
                        printf("Archivo %s eliminado con éxito\n", trozos[i]);
                    } else {
                        perror("Error al eliminar el archivo");
                    }
                } else if (S_ISDIR(info.st_mode)) {
                    // Directorio
                    if (rmdir(trozos[i]) == 0) {
                        printf("Directorio %s eliminado con éxito\n", trozos[i]);
                    } else {
                        perror("Error al eliminar el directorio (debe estar vacío)");
                    }
                } else {
                    // Ni un archivo ni un directorio (puede ser otro tipo de archivo)
                    printf("%s no es un archivo ni un directorio\n", trozos[i]);
                }
            } else {
                perror("Error al obtener la información del archivo");
            }
        }
    }
}

void reclist(char * trozos[]) {
    char path[1000];  
    int showHidden = 0, showLong = 0, showLinks = 0, showAcc = 0;
    int i = 1; 

    while (trozos[i] != NULL && trozos[i][0] == '-') {
        if (strcmp(trozos[i], "-hid") == 0)
            showHidden = 1;
        else if (strcmp(trozos[i], "-long") == 0)
            showLong = 1;
        else if (strcmp(trozos[i], "-link") == 0)
            showLinks = 1;
        else if (strcmp(trozos[i], "-acc") == 0)
            showAcc = 1;
        i++;  
    }
    
    if (trozos[i] == NULL) {
        strcpy(path, ".");
        listDirRecursively(path, showHidden, showLong, showLinks, showAcc);
    } else {

        for (; trozos[i] != NULL; i++) {
            struct stat info;
            if (stat(trozos[i], &info) == 0 && S_ISDIR(info.st_mode)) {
                strcpy(path, trozos[i]);
                listDirRecursively(path, showHidden, showLong, showLinks, showAcc);
            } else {
                printf("Error: %s no es un directorio válido\n", trozos[i]);
            }
        }
    }
}

void revlist(char * trozos[]) {
    char path[1000];
    int showHidden = 0, showLong = 0, showLinks = 0, showAcc = 0;
    int i = 1;

    while (trozos[i] != NULL && trozos[i][0] == '-') {
        if (strcmp(trozos[i], "-hid") == 0)
            showHidden = 1;
        else if (strcmp(trozos[i], "-long") == 0)
            showLong = 1;
        else if (strcmp(trozos[i], "-link") == 0)
            showLinks = 1;
        else if (strcmp(trozos[i], "-acc") == 0)
            showAcc = 1;
        i++;
    }

    if (trozos[i] == NULL) {
        strcpy(path, ".");
        revlistDirRecursively(path, showHidden, showLong, showLinks, showAcc);
    } else {

        for (; trozos[i] != NULL; i++) {
            struct stat info;
            if (stat(trozos[i], &info) == 0 && S_ISDIR(info.st_mode)) {
                strcpy(path, trozos[i]);
                revlistDirRecursively(path, showHidden, showLong, showLinks, showAcc);
            } else {
                printf("Error: %s no es un directorio válido\n", trozos[i]);
            }
        }
    }
}

void delrec(char *trozos[]) {
    // Verificar si se pasaron argumentos
    if (trozos[1] == NULL) {
        fprintf(stderr, "Error: No se han especificado archivos o directorios para eliminar\n");
        return;
    }

    // Recorrer los argumentos (archivos o directorios)
    for (int i = 1; trozos[i] != NULL; i++) {
        struct stat info;

        // Obtener información sobre el archivo o directorio
        if (stat(trozos[i], &info) == 0) {
            if (S_ISREG(info.st_mode)) {
                // Es un archivo regular
                if (remove(trozos[i]) == 0) {
                    printf("Archivo %s eliminado con éxito\n", trozos[i]);
                } else {
                    perror("Error al eliminar el archivo");
                }
            } else if (S_ISDIR(info.st_mode)) {
                // Es un directorio, eliminar recursivamente
                delrecDir(trozos[i]);
            } else {
                // No es ni un archivo ni un directorio válido
                printf("%s no es un archivo ni un directorio válido\n", trozos[i]);
            }
        } else {
            // Error al obtener la información del archivo o directorio
            perror("Error al obtener la información del archivo/directorio");
        }
    }
}

void allocate(char *trozos[], mtList * mL){
    char * tr[10];
    if (trozos[1] == NULL) {
        mPrintList(NULL,*mL);
        return;
    }
    if (strcmp(trozos[1], "-malloc") == 0) {
        tr[0] = trozos[2];
        do_AllocateMalloc(tr, mL);
    } else if (strcmp(trozos[1], "-mmap") == 0) {
        tr[0] = trozos[2];
        tr[1] = trozos[3];
        do_AllocateMmap(tr, mL);
    } else if (strcmp(trozos[1], "-createshared") == 0) {
        tr[0] = trozos[2];
        tr[1] = trozos[3];
        do_AllocateCreateshared(tr, mL);
    } else if (strcmp(trozos[1], "-shared") == 0) {
        tr[0] = trozos[2];
        do_AllocateShared(tr, mL);
    }
}