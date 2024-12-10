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
    sprintf (aux,"dup of fd: %d file: %s",df, p);

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
        printf("reclist  revlist  erase  delrec  allocate\n");
        printf("deallocate  memfill  memdump  memory  readfile\n");
        printf("writefile  read  write  recurse getuid\n");
        printf("setuid showvar\n");
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
    } else if (strcmp(trozos[1],"allocate")==0) {
        printf("allocate [-malloc|-shared|-createshared|-mmap]... Asigna un bloque de memoria\n");
        printf("\t-malloc tam: asigna un bloque malloc de tamano tam\n");
        printf("\t-createshared cl tam: asigna (creando) el bloque de memoria compartida de clave cl y tamano tam\n");
        printf("\t-shared cl: asigna el bloque de memoria compartida (ya existente) de clave cl\n");
        printf("\t-mmap fich perm: mapea el fichero fich, perm son los permisos\n");
    } else if (strcmp(trozos[1],"deallocate")==0) {
        printf("deallocate [-malloc|-shared|-delkey|-mmap|addr]..	Desasigna un bloque de memoria\n");
        printf("\t-malloc tam: desasigna el bloque malloc de tamano tam\n");
        printf("\t-shared cl: desasigna (desmapea) el bloque de memoria compartida de clave cl\n");
        printf("\t-delkey cl: elimina del sistema (sin desmapear) la clave de memoria cl\n");
        printf("\t-mmap fich: desmapea el fichero mapeado fich\n");
        printf("\taddr: desasigna el bloque de memoria en la direccion addr\n");
    } else if (strcmp(trozos[1],"memfill")==0) {
        printf("memfill addr cont byte 	Llena la memoria a partir de addr con byte\n");
    } else if (strcmp(trozos[1],"memdump")==0) {
        printf("memdump addr cont 	Vuelca en pantallas los contenidos (cont bytes) de la posicion de memoria addr\n");
    } else if (strcmp(trozos[1],"memory")==0) {
        printf("memory [-blocks|-funcs|-vars|-all|-pmap] ..	Muestra muestra detalles de la memoria del proceso\n");
        printf("\t-blocks: los bloques de memoria asignados\n");
        printf("\t-funcs: las direcciones de las funciones\n");
        printf("\t-vars: las direcciones de las variables\n");
        printf("\t:-all: todo\n");
        printf("\t-pmap: muestra la salida del comando pmap(o similar)\n");
    } else if (strcmp(trozos[1],"readfile")==0) {
        printf("readfile fiche addr cont 	Lee cont bytes desde fich a la direccion addr\n");
    } else if (strcmp(trozos[1],"writefile")==0) {
        printf("writefile fiche addr cont   Escribe cont bytes desde la direccion addr a fich\n");
    } else if (strcmp(trozos[1],"read")==0) {
        printf("read df addr cont	Transfiere cont bytes del fichero descrito por df a la dirección addr\n");
    } else if (strcmp(trozos[1],"write")==0) {
        printf("write df addr cont	Transfiere cont bytes desde la dirección addr al fichero descrito por df\n");
    } else if (strcmp(trozos[1],"recurse")==0) {
        printf("recurse [n]	Invoca a la funcion recursiva n veces\n");
    } else if (strcmp(trozos[1],"getuid")==0) {
        printf("getuid 	Muestra las credenciales del proceso que ejecuta el shell\n");
    } else if (strcmp(trozos[1],"setuid")==0) {
        printf("setuid [-l] id	Cambia las credenciales del proceso que ejecuta el shell\n");
        printf("\tid: establece la credencial al valor numerico id\n");
        printf("\t-l id: establece la credencial a login id\n");
    } else if (strcmp(trozos[1],"showvar")==0) {
        printf("showvar var	Muestra el valor y las direcciones de la variable de entorno var\n");
    } else if (strcmp(trozos[1],"changevar")==0) {
        printf("changevar [-a|-e|-p] var valor	Cambia el valor de una variable de entorno\n");
        printf("\t-a: accede por el tercer arg de main\n");
        printf("\t-e: accede mediante environ\n");
        printf("\t-p: accede mediante putenv\n");
    } else if (strcmp(trozos[1],"environ")==0) {
        printf("environ [-environ|-addr] 	Muestra el entorno del proceso\n");
        printf("\t-environ: accede usando environ (en lugar del tercer arg de main)\n");
        printf("\t-addr: muestra el valor y donde se almacenan environ y el 3er arg main \n");
    }
}

void makefile(char * trozos[]){
    int fd;

    fd = open(trozos[1], O_RDONLY);
    if (fd != -1) {
        close(fd);
        printf("Error: El fichero %s ya existe\n", trozos[1]);
        return;
    }

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

void allocate(char *trozos[], mtList * mL, ftList * fL){
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
        do_AllocateMmap(tr, mL, fL);
    } else if (strcmp(trozos[1], "-createshared") == 0) {
        tr[0] = trozos[2];
        tr[1] = trozos[3];
        do_AllocateCreateshared(tr, mL);
    } else if (strcmp(trozos[1], "-shared") == 0) {
        tr[0] = trozos[2];
        do_AllocateShared(tr, mL);
    }
}

void deallocate(char *trozos[], mtList * mL, ftList * fL) {
    char * tr[10];
    if (trozos[1] == NULL) {
        mPrintList(NULL,*mL);
        return;
    }
    if (strcmp(trozos[1], "-malloc") == 0) {
        tr[0] = trozos[2];
        do_DeallocateMalloc(tr, mL);
    } else if (strcmp(trozos[1], "-mmap") == 0) {
        tr[0] = trozos[2];
        do_DeallocateMmap(tr, mL, fL);
    } else if (strcmp(trozos[1], "-shared") == 0) {
        tr[0] = trozos[2];
        do_DeallocateShared(tr, mL);
    } else if (strcmp(trozos[1], "-delkey") == 0) {
        tr[0] = trozos[2];
        do_DeallocateDelkey(tr);        
    } else {
        tr[0] = trozos[1];
        do_DeallocateGenerico(tr, mL, fL);
    }
}

void memfill(char *trozos[]) {
    void * memAd;
    unsigned char byte;
    unsigned char cont;

    if (trozos[1] == NULL || trozos[2] == NULL || trozos[3] == NULL) {
        return;
    }

    byte = strtoul(trozos[3],NULL,10);
    cont = strtoul(trozos[2],NULL,10);

    sscanf(trozos[1], "%p", &memAd); 
    printf("Llenando %s bytes de memoria con el byte  %c(%X) a partir de la direccion %s\n", trozos[2],(char)byte,byte,trozos[1]);
    LlenarMemoria(memAd, cont, byte);
}

void memdump(char *trozos[]) {
    unsigned char *arr;
    size_t i;
    void * memAd;

    sscanf(trozos[1], "%p", &memAd);
    arr=(unsigned char *) memAd;

    for (i=0; i<atoi(trozos[2]);i++) {
        printf("%4c",(char)arr[i]);
    }
    printf("\n");
    for (i=0; i<atoi(trozos[2]);i++) {
        printf("%4X",arr[i]);
    }
    printf("\n");
}

void memory(char *trozos[],  mtList * mL) {

    if (trozos[1] == NULL || strcmp(trozos[1], "-all") == 0) {
        do_MemoryVars();
        printf("\n");
        do_MemoryFuncs();
        printf("\n");
        mPrintList(NULL, *mL);
    } else if (strcmp(trozos[1], "-vars") == 0) {
        do_MemoryVars();
    } else if (strcmp(trozos[1], "-blocks") == 0) {
        mPrintList(NULL,*mL);
    } else if (strcmp(trozos[1], "-pmap") == 0) {
        Do_pmap();
    } else if (strcmp(trozos[1], "-funcs") == 0){
        do_MemoryFuncs();
    }
}

void Cmd_ReadFile(char *ar[]) {
    void *p;
    size_t cont=-1;  /*si no pasamos tamano se lee entero */
    ssize_t n;

    if (ar[1]==NULL || ar[2]==NULL){
        printf ("faltan parametros\n");
        return;
    }
    sscanf(ar[2], "%p", &p); /*convertimos de cadena a puntero*/  
    if (ar[3]!=NULL)
        cont=(size_t) atoll(ar[3]);
    if ((n=LeerFichero(ar[1],p,cont))==-1)
        perror ("Imposible leer fichero");
    else
        printf ("leidos %lld bytes de %s en %p\n",(long long) n,ar[1],p);
}

void Cmd_WriteFile(char *ar[]) {
    void *p;
    size_t cont=-1;  /*si no pasamos tamano se lee entero */
    ssize_t n;

    if (ar[1]==NULL || ar[2]==NULL){
        printf ("faltan parametros\n");
        return;
    }
    sscanf(ar[2], "%p", &p); /*convertimos de cadena a puntero*/  
    if (ar[3]!=NULL)
        cont=(size_t) atoll(ar[3]);
    if ((n=EscribirFichero(ar[1],p,cont))==-1)
        perror ("Imposible escribir fichero");
    else
        printf ("escritos %lld bytes en %s desde %p\n",(long long) n,ar[1],p);
}

void recurse(char *trozos[]) {
    int n;
    n = atoi(trozos[1]);

    if (trozos[1] == NULL) {
        perror("Introduzca el numero de las llamadas recursivas");
    } else if (n == 0) {
        perror("Introduce un valor correcto");
    } else {
        Recursiva(n);
    }
}


void Cmd_read(char *ar[], ftList *fL) {
    void *p;
    ftPosL item;
    size_t cont=-1;  /*si no pasamos tamano se lee entero */
    ssize_t n;
    char *inicio = NULL;

    if (ar[1]==NULL || ar[2]==NULL){
        printf ("faltan parametros\n");
        return;
    }

    item = fFindItem(atoi(ar[1]), *fL);
    if (item == NULL) {
        printf("Fichero no encontrado\n");
        return;
    }
    sscanf(ar[2], "%p", &p); /*convertimos de cadena a puntero*/

    if ((inicio = strstr(item->data.fname, "Mapeo de ")) != NULL) {
        inicio += strlen("Mapeo de ");
    } else if ((inicio = strstr(item->data.fname, "file: ")) != NULL) {
        inicio += strlen("file: ");
        printf("%s\n", inicio);
    } else {
        inicio = item->data.fname;
    }


    if (ar[3]!=NULL)
        cont=(size_t) atoll(ar[3]);
    if ((n=LeerFichero(inicio,p,cont))==-1)
        perror ("Imposible leer fichero");
    else
        printf ("leidos %lld bytes del descriptor %s en %p\n",(long long) n,ar[1],p);
}

void Cmd_write(char *ar[], ftList *fL) {
    void *p;
    ftPosL item;
    size_t cont=-1;  /*si no pasamos tamano se lee entero */
    ssize_t n;
    char *inicio = NULL;

    if (ar[1]==NULL || ar[2]==NULL){
        printf ("faltan parametros\n");
        return;
    }

    item = fFindItem(atoi(ar[1]), *fL);
    if (item == NULL) {
        printf("Fichero no encontrado\n");
        return;
    }
    sscanf(ar[2], "%p", &p); /*convertimos de cadena a puntero*/

    if ((inicio = strstr(item->data.fname, "Mapeo de ")) != NULL) {
        inicio += strlen("Mapeo de ");
    } else if ((inicio = strstr(item->data.fname, "file: ")) != NULL) {
        inicio += strlen("file: ");
    } else {
        inicio = item->data.fname;
    }


    if (ar[3]!=NULL)
        cont=(size_t) atoll(ar[3]);
    if ((n=EscribirFichero2(inicio,p,cont))==-1)
        perror ("Imposible escribir fichero");
    else
        printf ("escritos %lld bytes en %s desde %p\n",(long long) n,ar[1],p);
}

void Cmd_getuid(char *trozos[]) {
    uid_t usuarioReal;
    uid_t usuarioEfectivo;
    struct passwd *sReal;
    struct passwd *sEfectivo;

    usuarioReal = getuid();
    usuarioEfectivo = geteuid();

    if ((sReal = getpwuid(usuarioReal)) == NULL || (sEfectivo = getpwuid(usuarioEfectivo)) == NULL) {
        printf("usuario no encontrado\n");
        return;
    }

    printf("Credencial real: %d, (%s)\n",usuarioReal, sReal->pw_name);
    printf("Credencial efectica:  %d, (%s)\n", usuarioEfectivo, sEfectivo->pw_name);
}

void Cmd_setuid(char *trozos[]){
    uid_t nuevoUID;
    struct passwd *usuario; //a partir del login
    int aux;
    
    if(trozos[1] == NULL){
        Cmd_getuid(trozos);
        //perror("Introduce un id nuevo");
        return;
    }

    if(strcmp(trozos[1],"-l") == 0){
        if(trozos[2] == NULL){
            Cmd_getuid(trozos);
            //perror("Introduce un nombre de usuario");
            return;
        }

        usuario = getpwnam(trozos[2]);
        if (usuario == NULL){
            printf("Usuario no existente %s\n", trozos[2]);
            return;
        }
        nuevoUID = usuario->pw_uid;
    } else {
        nuevoUID = atoi(trozos[1]);
    }

    if (setuid(nuevoUID) == -1){
        perror("Error al cambiar el UID efectivo");
    } else {
        printf("Credencial cambiada a %d\n", nuevoUID);
    }
}

void showVar(char * trozos[]) {
    int n;
    extern char ** environ;

    if(trozos[1] == NULL) {
        printEnvVars();
    } else {
        if ((n = BuscarVariable(trozos[1], ar3)) != -1) { // Hecho como en la shell de referencia verificar si hacerlo como en el enunciado
            printf("Con arg3 main %s (%p) @%p\n",ar3[n], ar3[n], &ar3[n]);
            printf("Con environ %s (%p) @%p\n",environ[n], environ[n], &environ[n]);
            printf("Con getenv %s (%p)\n", getenv(trozos[1]), getenv(trozos[1])); 
        } else if ((n = BuscarVariable(trozos[1], environ)) != -1) {
            printf("Con environ %s (%p) @%p\n",environ[n], environ[n], &environ[n]);
            printf("Con getenv %s (%p)\n", getenv(trozos[1]), getenv(trozos[1])); 
        } else {
            printf("Variable de entorno no encontrada\n");
        }
    }
}

void changeVar(char * trozos[]) {
    extern char ** environ;
    char * envVar;

    if(trozos[1] == NULL || trozos[2] == NULL || trozos[3] == NULL) {
        printf("Uso: changevar [-a|-e|-p] var valor\n");
    } else {
        if (strcmp(trozos[1],"-a") == 0) {
            if(CambiarVariable(trozos[2], trozos[3], ar3) == -1) {
                printf("Error al cambiar la variable de entorno\n");
            }
        } else if (strcmp(trozos[1],"-e") == 0) {
            if(CambiarVariable(trozos[2], trozos[3], environ) == -1) {
                printf("Error al cambiar la variable de entorno\n");
            }
        } else if (strcmp(trozos[1],"-p") == 0) {
            envVar=malloc(1024);
            strcpy(envVar, "");
            strcat(envVar, trozos[2]);
            strcat(envVar, "=");
            strcat(envVar, trozos[3]);
            if(putenv(envVar) != 0) {
                printf("Error al cambiar la variable de entorno\n");
            }
        }
    }
}

void Cmd_environ(char * trozos[]) {
    extern char ** environ;

    if (trozos[1] == NULL) {
        printEnvVars();
    } else if (strcmp(trozos[1], "-environ") == 0) {
        printEnvVars2();
    } else if (strcmp(trozos[1], "-addr") == 0) {
        printf("environ: %p (almacenado en %p)\n", environ, &environ);
        printf("main arg3: %p (almacenado en %p)\n", &ar3, ar3);
    }
}

void Cmd_fork (char *tr[]) {
	pid_t pid;
	
	if ((pid=fork())==0){
/*		VaciarListaProcesos(&LP); Depende de la implementaciÃ³n de cada uno*/
		printf ("ejecutando proceso %d\n", getpid());
	}
	else if (pid!=-1)
		waitpid (pid,NULL,0);
}

void Cmd_exec(char * tr[]) {
    char **args = &tr[1];

    if (tr[1] == NULL) {
        printf("Uso invalido del comando\n");
    } else if(execvp(args[0],args) == -1) {
        printf("Error al hacer exec\n");
        return;
    }
}

void cmd_fg(char *tr[]){
	int pid;
    char **args = &tr[1];

	if ((pid=fork())==0){
		if (execvp(args[0], args)==-1)	
			perror ("Cannot execute");
		exit(255);
	}
	waitpid (pid,NULL,0);
}