/*
Mario Denis Radu Trifu (m.denis.radu@udc.es)
Mario Ozón Casais (mario.ozon@udc.es)
*/

#include "general.h"
#include "comandos.h"
#include "listaArchivo.h"


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

bool procesarEntrada(char * trozos[], tList L, ftList *fL) {
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
        historic(trozos, L, * fL);
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
    }else if (strcmp(trozos[0], "exit") == 0|| strcmp(trozos[0], "bye") == 0|| strcmp(trozos[0], "quit") == 0) {
        deleteList(&L);
        fDeleteList(fL);
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

void * ObtenerMemoriaShmget (key_t clave, size_t tam) {
    void * p;
    int aux,id,flags=0777;
    struct shmid_ds s;

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
    return (p);
}

void * MapearFichero (char * fichero, int protection) {
    int df, map=MAP_PRIVATE,modo=O_RDONLY;
    struct stat s;
    void *p;

    if (protection&PROT_WRITE)
          modo=O_RDWR;
    if (stat(fichero,&s)==-1 || (df=open(fichero, modo))==-1)
          return NULL;
    if ((p=mmap (NULL,s.st_size, protection,map,df,0))==MAP_FAILED)
           return NULL;
/* Guardar en la lista    InsertarNodoMmap (&L,p, s.st_size,df,fichero); */
/* Gurdas en la lista de descriptores usados df, fichero*/
    return p;
}

void do_AllocateMalloc(char *arg[]) {
    char * memAd;
    if (arg[0] == NULL) {
        // {ImprimirListaMmap(&L); return;}
    } else {
        // Insertar en lista
        memAd = malloc(atoi(arg[0]));
        if (memAd == NULL) {
            perror("No se pudo reservar memoria");
        } else {
            printf("Asignados %s bytes en %s", arg[0], memAd);
        }
    }

}

void do_AllocateMmap(char *arg[]) { 
     char *perm;
     void *p;
     int protection=0;
     
     if (arg[0]==NULL)
           // {ImprimirListaMmap(&L); return;}
     if ((perm=arg[1])!=NULL && strlen(perm)<4) {
            if (strchr(perm,'r')!=NULL)protection|=PROT_READ; 
            if (strchr(perm,'w')!=NULL) protection|=PROT_WRITE;
            if (strchr(perm,'x')!=NULL) protection|=PROT_EXEC;
     }
     if ((p=MapearFichero(arg[0],protection))==NULL)
             perror ("Imposible mapear fichero");
     else
             printf ("fichero %s mapeado en %p\n", arg[0], p);
}

void do_AllocateCreateshared (char *tr[]) {
   key_t cl;
   size_t tam;
   void *p;

   if (tr[0]==NULL || tr[1]==NULL) {
		//ImprimirListaShared(&L);
		return;
   }
  
   cl=(key_t)strtoul(tr[0],NULL,10);
   tam=(size_t) strtoul(tr[1],NULL,10);
   if (tam==0) {
	printf ("No se asignan bloques de 0 bytes\n");
	return;
   }
   if ((p=ObtenerMemoriaShmget(cl,tam))!=NULL)
		printf ("Asignados %lu bytes en %p\n",(unsigned long) tam, p);
   else
		printf ("Imposible asignar memoria compartida clave %lu:%s\n",(unsigned long) cl,strerror(errno));
}

void do_AllocateShared (char *tr[]) {
   key_t cl;
   size_t tam;
   void *p;

   if (tr[0]==NULL) {
		//ImprimirListaShared(&L);
		return;
   }
  
   cl=(key_t)strtoul(tr[0],NULL,10);

   if ((p=ObtenerMemoriaShmget(cl,0))!=NULL)
		printf ("Asignada memoria compartida de clave %lu en %p\n",(unsigned long) cl, p);
   else
		printf ("Imposible asignar memoria compartida clave %lu:%s\n",(unsigned long) cl,strerror(errno));
}

