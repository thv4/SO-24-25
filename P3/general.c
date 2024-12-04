/*
Mario Denis Radu Trifu (m.denis.radu@udc.es)
Mario Ozón Casais (mario.ozon@udc.es)
*/

#include "general.h"
#include "comandos.h"
#include "listaArchivo.h"
#include "listaMemoria.h"

#define TAMANO 2048

int extern1, extern2, extern3;
int externIni1 = 11, externIni2 = 22, externIni3 = 33; 

void imprimirPromp(){ printf("$ ");}

void leerEntrada(char * cadena, int tamaño){
    fgets(cadena, tamaño, stdin);
}

int TrocearCadena(char * cadena, char * trozos[]) {
    int i=1;

    if ((trozos[0]=strtok(cadena," \n\t")) == NULL) {
        return 0;
    }
    while ((trozos[i]=strtok(NULL," \n\t"))!=NULL) {
        i++;
    }
    return i;
}

bool procesarEntrada(char * trozos[], tList L, ftList *fL, mtList *mL) {
    if (strcmp(trozos[0],"authors")==0) {
        authors(trozos);
    }else if (strcmp(trozos[0],"pid")==0){
        pid();
    } else if (strcmp(trozos[0], "ppid")==0){
        ppid();
    } else if (strcmp(trozos[0],"cd")==0) {
        cd(trozos);
    } else if(strcmp(trozos[0],"date")==0){
        date(trozos);
    } else if(strcmp(trozos[0],"historic")==0) {
        historic(trozos, L, * fL, * mL);
    } else if (strcmp(trozos[0],"open")==0){
        Cmd_open(trozos, fL);
    } else if (strcmp(trozos[0],"close")==0){
        Cmd_close(trozos, fL);
    } else if (strcmp(trozos[0],"dup")==0){
        Cmd_dup(trozos, fL);
    } else if (strcmp(trozos[0],"infosys")==0) {
        infosys();
    } else if (strcmp(trozos[0],"help")==0){
        help(trozos);
    } else if (strcmp(trozos[0],"makefile")==0){
        makefile(trozos);
    } else if (strcmp(trozos[0],"cwd")==0){
        cwd();
    } else if(strcmp(trozos[0],"makedir")==0){
        makedir(trozos);
    } else if(strcmp(trozos[0],"listfile")==0){
        listfile(trozos);
    } else if(strcmp(trozos[0],"listdir")==0){
        listdir(trozos);
    } else if(strcmp(trozos[0],"erase")==0){
        erase(trozos);
    } else if(strcmp(trozos[0],"reclist")==0){
        reclist(trozos);
    } else if(strcmp(trozos[0],"revlist")==0) {
        revlist(trozos);
    } else if(strcmp(trozos[0],"delrec")==0){
        delrec(trozos);
    } else if(strcmp(trozos[0],"allocate")==0) {
        allocate(trozos, mL, fL);
    } else if(strcmp(trozos[0],"deallocate")==0) {
        deallocate(trozos, mL, fL);
    } else if (strcmp(trozos[0],"memfill")==0){
        memfill(trozos);
    } else if (strcmp(trozos[0],"memdump")==0) {
        memdump(trozos);
    } else if (strcmp(trozos[0],"memory")==0) {
        memory(trozos, mL);
    } else if (strcmp(trozos[0],"readfile")==0) {
        Cmd_ReadFile(trozos);
    } else if (strcmp(trozos[0],"recurse")==0) {
        recurse(trozos);
    } else if (strcmp(trozos[0],"read")==0) {
        Cmd_read(trozos, fL);
    } else if (strcmp(trozos[0],"writefile")==0) {
        Cmd_WriteFile(trozos);
    } else if (strcmp(trozos[0],"write")==0) {
        Cmd_write(trozos,fL);
    } else if (strcmp(trozos[0],"getuid")==0) {
        Cmd_getuid(trozos);
    } else if (strcmp(trozos[0], "exit") == 0|| strcmp(trozos[0], "bye") == 0|| strcmp(trozos[0], "quit") == 0) {
        deleteList(&L);
        fDeleteList(fL);
        mDeleteList(mL);
        return true;
    }
    return false;
}

void printPermisos(struct stat file_stat){
    printf( (S_ISDIR(file_stat.st_mode)) ? "d" : 
            (S_ISLNK(file_stat.st_mode)) ? "l" : "-");
    printf( (file_stat.st_mode & S_IRUSR) ? "r" : "-");
    printf( (file_stat.st_mode & S_IWUSR) ? "w" : "-");
    printf( (file_stat.st_mode & S_IXUSR) ? "x" : "-");
    printf( (file_stat.st_mode & S_IRGRP) ? "r" : "-");
    printf( (file_stat.st_mode & S_IWGRP) ? "w" : "-");
    printf( (file_stat.st_mode & S_IXGRP) ? "x" : "-");
    printf( (file_stat.st_mode & S_IROTH) ? "r" : "-");
    printf( (file_stat.st_mode & S_IWOTH) ? "w" : "-");
    printf( (file_stat.st_mode & S_IXOTH) ? "x" : "-");
    printf("\t");
}

void printFechaMod(struct stat file_stat){
    struct tm *tm_info = localtime(&file_stat.st_mtime);
    char buffer[20];
    strftime(buffer, 20, "%Y/%m/%d-%H:%M", tm_info);
    printf("%s  ", buffer);
}

void printPropGrupo(struct stat file_stat){
    struct passwd *pw = getpwuid(file_stat.st_uid);
    struct group *gr = getgrgid(file_stat.st_gid);
    printf("\t%s\t%s  ",pw->pw_name,gr->gr_name);
}

void printLink(struct dirent * infofile){
    char linkname[1024];
    ssize_t link = readlink(infofile->d_name,linkname, sizeof(linkname) - 1);

    if (link != -1) {
        linkname[link] = '\0';  
        printf(" --> %s\n",linkname);
    } else {
        printf("\n");
    }
}

void printLink2(char * infofile){
    char linkname[1024];
    ssize_t link = readlink(infofile,linkname, sizeof(linkname) - 1);

    if (link != -1) {
        linkname[link] = '\0';  
        printf(" --> %s\n",linkname);
    } else {
        printf("\n");
    }
}


void listDirRecursively(char *basePath, int showHidden, int showLong, int showLinks, int showAcc) {
    int i;
    char path[1000];
    struct dirent *dp;
    struct stat file_stat;  // Información del archivo
    DIR *dir = opendir(basePath);
    char * nameDir[1000];
    long tamDir[1000];
    int countDir = 0;

    if (!dir)
        return;

    printf("\n************  %s  ************\n", basePath);

    while ((dp = readdir(dir)) != NULL) {
        
        if (strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0)
            continue;
        
        if (!showHidden && dp->d_name[0] == '.') {
            continue;
        }

        // Ruta completa 
        strcpy(path, basePath);
        strcat(path, "/");
        strcat(path, dp->d_name);
    
        if (stat(path, &file_stat) == 0) {
            
            if (showLong) {
                printFechaMod(file_stat);
                printf("  %lu  (%lu)",file_stat.st_nlink, file_stat.st_ino);
                printPropGrupo(file_stat);
                printPermisos(file_stat);
                printf("%ld\t%s",file_stat.st_size,dp->d_name);
                if (link) {
                    printLink(dp);                   
                } else {
                    printf("\n");
                }


            }else if (showAcc) {
                printFechaMod(file_stat);
                printf("  %ld  %s", file_stat.st_size, dp->d_name);
                if (link) {
                    printLink(dp);                   
                } else {
                    printf("\n");
                }  
            }else if (showLinks) {
                printf("%ld  %s", file_stat.st_size, dp->d_name); 
                printLink(dp);                       
            } else {
                printf("%ld\t%s\n", file_stat.st_size, dp->d_name);
            }  
            
            if (S_ISDIR(file_stat.st_mode)) {
                nameDir[countDir] = strdup(dp->d_name);
                tamDir[countDir] = file_stat.st_size;
                countDir++;
            }
        } else {
            perror("Error al obtener la información del archivo");
        }
    }

    for (int i = 0; i < countDir; i++) {
        strcpy(path, basePath);
        strcat(path, "/");
        strcat(path, nameDir[i]);

        
        listDirRecursively(path, showHidden, showLong, showLinks, showAcc);

        free(nameDir[i]);  
    }

    closedir(dir);
}

void revlistDirRecursively(char *basePath, int showHidden, int showLong, int showLinks, int showAcc) {
    char path[1000];
    struct dirent *dp;
    struct stat file_stat;  
    DIR *dir = opendir(basePath);
    struct stat lista_stat[1000];
    char * nameDir[1000];
    int countDir = 0;

    if (!dir)
        return;

    
    
    while ((dp = readdir(dir)) != NULL) {
        
        if (strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0)
            continue;
        
        if (!showHidden && dp->d_name[0] == '.') {
            continue;
        }

        // Ruta completa
        strcpy(path, basePath);
        strcat(path, "/");
        strcat(path, dp->d_name);

        
        if (stat(path, &file_stat) == 0) {
            
            if (S_ISDIR(file_stat.st_mode)) {
                lista_stat[countDir] = file_stat;
                nameDir[countDir] = strdup(dp->d_name);
                countDir++;

                revlistDirRecursively(path, showHidden, showLong, showLinks, showAcc);                
            }
        } else {
            perror("Error al obtener la información del archivo");
        }
    }

    rewinddir(dir);  // Volver al inicio del directorio
    printf("\n*************  %s  *************\n", basePath);

    while ((dp = readdir(dir)) != NULL) {
        
        if (strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0)
            continue;

        if (!showHidden && dp->d_name[0] == '.') {
            continue;
        }

        // Ruta completa
        strcpy(path, basePath);
        strcat(path, "/");
        strcat(path, dp->d_name);

        if (stat(path, &file_stat) == 0) {
            
            if (!S_ISDIR(file_stat.st_mode)) {
                if (showLong) {
                    printFechaMod(file_stat);
                    printf("  %lu  (%lu)", file_stat.st_nlink, file_stat.st_ino);
                    printPropGrupo(file_stat);
                    printPermisos(file_stat);
                    printf("%ld\t%s", file_stat.st_size, dp->d_name);
                    if (showLinks) {
                        printLink(dp);                   
                    } else {
                        printf("\n");
                    }
                } else if (showAcc) {
                    printFechaMod(file_stat);
                    printf("  %ld  %s\n", file_stat.st_size, dp->d_name);
                } else if (showLinks) {
                    printf("%ld  %s", file_stat.st_size, dp->d_name);
                    printLink(dp);
                } else {
                    printf("%ld\t%s\n", file_stat.st_size, dp->d_name);
                }
            }
        } else {
            perror("Error al obtener la información del archivo");
        }
    }

    
    for(int i = 0; i < countDir; i++) {
        if (showLong) {
            printFechaMod(lista_stat[i]);
            printf("  %lu  (%lu)", lista_stat[i].st_nlink, lista_stat[i].st_ino);
            printPropGrupo(lista_stat[i]);
            printPermisos(lista_stat[i]);
            printf("%ld\t%s", lista_stat[i].st_size, nameDir[i]);
            if (showLinks) {
                printLink2(nameDir[i]);                   
            } else {
                printf("\n");
            }
        } else if (showAcc) {
            printFechaMod(lista_stat[i]);
            printf("  %ld  %s\n", lista_stat[i].st_size, nameDir[i]);
        } else if (showLinks) {
            printf("%ld  %s", lista_stat[i].st_size, nameDir[i]);
            printLink2(nameDir[i]);
        } else {
            printf("%ld\t%s\n", lista_stat[i].st_size, nameDir[i]);
        }
        free(nameDir[i]);
    }

    closedir(dir);  
}

void delrecDir(char *path) {
    struct dirent *dp;
    DIR *dir = opendir(path);
    char fullPath[1024];

    if (!dir) {
        perror("Error al abrir el directorio");
        return;
    }

    while ((dp = readdir(dir)) != NULL) {
        // Ignorar "." y ".."
        if (strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0)
            continue;

        // Crear la ruta completa del archivo/directorio actual
        snprintf(fullPath, sizeof(fullPath), "%s/%s", path, dp->d_name);

        struct stat info;
        if (stat(fullPath, &info) == 0) {
            if (S_ISREG(info.st_mode)) {
                // Eliminar archivos
                if (remove(fullPath) != 0) {
                    perror("Error al eliminar el archivo");
                }
            } else if (S_ISDIR(info.st_mode)) {
                // Llamada recursiva para subdirectorios
                delrecDir(fullPath);
            }
        }
    }

    closedir(dir);

    // Eliminar el directorio una vez vaciado
    if (rmdir(path) == 0) {
        printf("Directorio %s eliminado con éxito\n", path);
    } else {
        perror("Error al eliminar el directorio");
    }
}

void do_AllocateMalloc(char *arg[], mtList *mL) {
    char * memAd;
    mtItemL mItem;
    if (arg[0] == NULL) {
        mPrintList("malloc",*mL);
    } else {
        memAd = malloc(atoi(arg[0]));
        if (memAd == NULL) {
            perror("No se pudo reservar memoria");
        } else if (atoi(arg[0]) == 0) {
            perror("No se pueden reservar bloques de 0 bytes");
        } else {
            mItem.size = atoi(arg[0]);
            mItem.memAd = memAd;
            strcpy(mItem.type, "malloc");
            strcpy(mItem.other1, "");
            mItem.other2 = -1;
            mItem.fecha = time(NULL);
            mInsertElement(mItem, mL);
            printf("Asignados %s bytes en %p\n", arg[0], mItem.memAd);
        }
    }

}

void * MapearFichero (char * fichero, int protection, mtList *mL, ftList *fL) {
    int df, map=MAP_PRIVATE,modo=O_RDONLY;
    struct stat s;
    void *p;
    mtItemL mItem;
    ftItemL fItem;
    char aux[100];

    if (protection&PROT_WRITE)
          modo=O_RDWR;
    if (stat(fichero,&s)==-1 || (df=open(fichero, modo))==-1)
          return NULL;
    if ((p=mmap (NULL,s.st_size, protection,map,df,0))==MAP_FAILED)
           return NULL;
    mItem.size = s.st_size;
    mItem.memAd = p;
    strcpy(mItem.type, "mmap");
    strcpy(mItem.other1, fichero);
    mItem.other2 = df;
    mItem.fecha = time(NULL);
    mInsertElement(mItem, mL);
    
    fItem.descriptor = df;
    fItem.OpMode = (mode_t) modo;
    sprintf(aux,"Mapeo de %s",fichero);
    strcpy(fItem.fname, aux);
    fInsertElement(fItem, fL);
    
    return p;
}

void do_AllocateMmap(char *arg[], mtList *mL, ftList *fL) { 
     char *perm;
     void *p;
     int protection=0;
     
     if (arg[0]==NULL) {
        mPrintList("mmap", *mL); 
        return;
     }
     if ((perm=arg[1])!=NULL && strlen(perm)<4) {
            if (strchr(perm,'r')!=NULL)protection|=PROT_READ; 
            if (strchr(perm,'w')!=NULL) protection|=PROT_WRITE;
            if (strchr(perm,'x')!=NULL) protection|=PROT_EXEC;
     }
     if ((p=MapearFichero(arg[0],protection, mL, fL))==NULL)
             perror ("Imposible mapear fichero");
     else
             printf ("fichero %s mapeado en %p\n", arg[0], p);
}

void * ObtenerMemoriaShmget (key_t clave, size_t tam, mtList *mL) {
    void * p;
    int aux,id,flags=0777;
    struct shmid_ds s;
    mtItemL mItem;

    if (tam)     /*tam distito de 0 indica crear */
        flags=flags | IPC_CREAT | IPC_EXCL; /*cuando no es crear pasamos de tamano 0*/
    if (clave==IPC_PRIVATE)  /*no nos vale*/
        {errno=EINVAL; return NULL;}
    if ((id=shmget(clave, tam, flags))==-1)
        return (NULL);
    if ((p=shmat(id,NULL,0))==(void*) -1){
        aux=errno;
        if (tam)
             shmctl(id,IPC_RMID,NULL);
        errno=aux;
        return (NULL);
    }
    shmctl (id,IPC_STAT,&s); /* si no es crear, necesitamos el tamano, que es s.shm_segsz*/
 /* Guardar en la lista   InsertarNodoShared (&L, p, s.shm_segsz, clave); */
    mItem.size = s.shm_segsz;
    mItem.memAd = p;
    strcpy(mItem.type, "shared");
    strcpy(mItem.other1, "");
    mItem.other2 = clave;
    mItem.fecha = time(NULL);
    mInsertElement(mItem, mL);
    
    return (p);
}

void do_AllocateCreateshared (char *tr[], mtList *mL) {
   key_t cl;
   size_t tam;
   void *p;

   if (tr[0]==NULL || tr[1]==NULL) {
		mPrintList("shared", *mL);
		return;
   }
  
   cl=(key_t)strtoul(tr[0],NULL,10);
   tam=(size_t) strtoul(tr[1],NULL,10);
   if (tam==0) {
	printf ("No se asignan bloques de 0 bytes\n");
	return;
   }
   if ((p=ObtenerMemoriaShmget(cl,tam, mL))!=NULL)
		printf ("Asignados %lu bytes en %p\n",(unsigned long) tam, p);
   else
		printf ("Imposible asignar memoria compartida clave %lu:%s\n",(unsigned long) cl,strerror(errno));
}

void do_AllocateShared (char *tr[], mtList *mL) {
   key_t cl;
   size_t tam;
   void *p;

   if (tr[0]==NULL) {
		mPrintList("shared", *mL);
		return;
   }
  
   cl=(key_t)strtoul(tr[0],NULL,10);

   if ((p=ObtenerMemoriaShmget(cl,0, mL))!=NULL)
		printf ("Asignada memoria compartida de clave %lu en %p\n",(unsigned long) cl, p);
   else
		printf ("Imposible asignar memoria compartida clave %lu:%s\n",(unsigned long) cl,strerror(errno));
}

void do_DeallocateMalloc (char *arg[], mtList *mL) {
    mtPosL pos;
    char * memAd;

    if (arg[0] == NULL) {
        mPrintList("malloc",*mL);
    } else {
        pos = mFindItem("malloc", atoi(arg[0]), NULL, *mL);
        if (pos == NULL) {
            perror("No hay bloque de ese tamano asignado con malloc");
        } else {
            memAd = pos->data.memAd;
            free(memAd);
            mRemoveElement(pos,mL);
        }
    }
}

void do_DeallocateMmap(char *arg[], mtList *mL, ftList *fL) {
    mtPosL pos;
    ftPosL pos2;
    char * memAd;
    int size;

    if (arg[0] == NULL) {
        mPrintList("mmap",*mL);
    } else {
        pos = mFindItem("mmap", NULL, arg[0], *mL);
        if (pos == NULL) {
            printf("Fichero %s no mapeado\n", arg[0]);
        } else {
            memAd = pos->data.memAd;
            size = pos->data.size;
            if (munmap(memAd, size) == -1) {
                perror("Error al eliminar el map");
            } else {
                pos2 = fFindItem(pos->data.other2,*fL);
                if (pos2 != NULL) {
                    if (close(pos2->data.descriptor) != -1) {
                        fRemoveElement(pos2, fL);
                    }
                }
                mRemoveElement(pos, mL);
            }
        }
    }
}

void do_DeallocateDelkey (char *args[]) {
   key_t clave;
   int id;
   char *key=args[0];

   if (key==NULL || (clave=(key_t) strtoul(key,NULL,10))==IPC_PRIVATE){
        printf ("      delkey necesita clave_valida\n");
        return;
   }
   if ((id=shmget(clave,0,0666))==-1){
        perror ("shmget: imposible obtener memoria compartida");
        return;
   }
   if (shmctl(id,IPC_RMID,NULL)==-1)
        perror ("shmctl: imposible eliminar memoria compartida\n");
}

void do_DeallocateShared(char *tr[], mtList *mL) {
    mtPosL pos;
    char * memAd;

    if (tr[0] == NULL) {
        mPrintList("shared",*mL);
    } else {
        pos = mFindItem("shared", atoi(tr[0]), NULL, *mL);
        if (pos == NULL) {
            perror("No hay bloque de esa clave mapeado en el proceso");
        } else {
            memAd = pos->data.memAd;
            shmdt(memAd);
            mRemoveElement(pos,mL);
        }
    }
}

void do_DeallocateGenerico(char *arg[], mtList *mL, ftList *fL) {
    mtString type = "";
    mtPosL pos = NULL;
    char * tr[10];
    
    tr[0] = malloc(sizeof(tr)); 
    pos = mFindMemAd(arg,*mL);
    if (pos == NULL) {
        perror("Direccion de memoria no encontrada");
    } else {
        strcpy(type, pos->data.type);
        if (strcmp(type,"malloc") == 0) {
            sprintf(tr[0], "%d", pos->data.size); 
            do_DeallocateMalloc(tr, mL);
        } else if (strcmp(type,"shared") == 0) {
            sprintf(tr[0], "%d", pos->data.other2);
            do_DeallocateShared(tr, mL);
        } else if (strcmp(type,"mmap") == 0) {
            sprintf(tr[0], "%s", pos->data.other1);
            do_DeallocateMmap(tr, mL, fL);
        }
    }
    free(tr[0]);
}

void LlenarMemoria(void *p, size_t cont, unsigned char byte) {
  unsigned char *arr=(unsigned char *) p;
  size_t i;
  for (i=0; i<cont;i++) {
    	arr[i]=byte;
  }
}

void do_MemoryFuncs() {
    printf("Funciones programa  %p   %p   %p\n", &authors, &date, &pid);
    printf("Funciones libreria  %p   %p   %p\n", &printf, &strcmp, &localtime);
}

void do_MemoryVars() {
    static int varStatic1, varStatic2, varStatic3;
    static int iniStatic1 = 10, iniStatic2 = 20, iniStatic3 = 30;
    
    int auto1 = 1, auto2 = 2, auto3 = 3;

    printf("Variables Externas %20p%17p%17p\n", &extern1, &extern2, &extern3 );
    printf("Variables Externas Ini %16p%17p%17p\n", &externIni1, &externIni2, &externIni3);
    printf("Variables Estaticas %19p%17p%17p\n", &varStatic1, &varStatic2, &varStatic3);
    printf("Variables Estaticas Ini %15p%17p%17p\n", &iniStatic1, &iniStatic2, &iniStatic3);
    printf("Variables Automaticas %17p%17p%17p\n", &auto1, &auto2, &auto3);
}

void Do_pmap(void) { 
    pid_t pid;       /*hace el pmap (o equivalente) del proceso actual*/
    char elpid[32];
    char *argv[4]={"pmap",elpid,NULL};
   
    sprintf (elpid,"%d", (int) getpid());
    if ((pid=fork())==-1){
        perror ("Imposible crear proceso");
        return;
        }
    if (pid==0){
        if (execvp(argv[0],argv)==-1)
            perror("cannot execute pmap (linux, solaris)");
            
        argv[0]="procstat"; argv[1]="vm"; argv[2]=elpid; argv[3]=NULL;   
        if (execvp(argv[0],argv)==-1)/*No hay pmap, probamos procstat FreeBSD */
            perror("cannot execute procstat (FreeBSD)");
            
        argv[0]="procmap",argv[1]=elpid;argv[2]=NULL;    
            if (execvp(argv[0],argv)==-1)  /*probamos procmap OpenBSD*/
            perror("cannot execute procmap (OpenBSD)");
            
        argv[0]="vmmap"; argv[1]="-interleave"; argv[2]=elpid;argv[3]=NULL;
        if (execvp(argv[0],argv)==-1) /*probamos vmmap Mac-OS*/
            perror("cannot execute vmmap (Mac-OS)");      
        exit(1);
    }
    waitpid (pid,NULL,0);
}

ssize_t LeerFichero(char *f, void *p, size_t cont) {
    struct stat s;
    ssize_t  n;  
    int df,aux;

    if (stat (f,&s)==-1 || (df=open(f,O_RDONLY))==-1)
        return -1;     
    if (cont==-1)   /* si pasamos -1 como bytes a leer lo leemos entero*/
        cont=s.st_size;
    if ((n=read(df,p,cont))==-1){
        aux=errno;
        close(df);
        errno=aux;
        return -1;
    }
    close (df);
    return n;
}

ssize_t EscribirFichero(char *f, void *p, size_t cont) {
    struct stat s;
    ssize_t  n;  
    int df,aux;

    if (df=open(f,O_RDONLY) !=-1)
        return -1;     

    df = creat(f, 0777);

    if ((n=write(df,p,cont))==-1){
        aux=errno;
        close(df);
        errno=aux;
        return -1;
    }
    close (df);
    return n;
}

ssize_t EscribirFichero2(char *f, void *p, size_t cont) {
    struct stat s;
    ssize_t  n;  
    int df,aux;

    if (stat (f,&s)==-1 || (df=open(f,O_RDWR))==-1) // Abrir con permisos de escritura
        return -1;     
    if (cont==-1)   /* si pasamos -1 como bytes a leer lo leemos entero*/
        cont=s.st_size;
    if ((n=write(df,p,cont))==-1){
        aux=errno;
        close(df);
        errno=aux;
        return -1;
    }
    close (df);
    return n;
}

void Recursiva(int n) {
    char automatico[TAMANO];
    static char estatico[TAMANO];

    printf ("parametro:%3d(%p) array %p, arr estatico %p\n",n,&n,automatico, estatico);

    if (n>0)
        Recursiva(n-1);
}