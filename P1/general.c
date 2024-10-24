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
    } else if (strcmp(trozos[0], "exit") == 0|| strcmp(trozos[0], "bye") == 0|| strcmp(trozos[0], "quit") == 0) {
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