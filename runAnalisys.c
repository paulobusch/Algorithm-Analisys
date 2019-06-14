#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

//====== CONSTANTES ========
#define FOLDER_DATA "data"
#define FOLDER_LOG "log"

#define FILE_LOG "log.csv"

#define FILE_ROW 30

//======= PROTÓTIPOS ========
char **filesByFolder(char *path, int *qtdFiles);
char **infoByFile(char *path, int *qtdRows);

//======= VARIÁVEIS =========


//======= MAIN ==========
int main(){
    int qtdFiles = 0; 
    int idxFile = 0;
    char **files = filesByFolder(FOLDER_DATA, &qtdFiles);
    
    while(idxFile < qtdFiles){
        puts(files[idxFile]);
        idxFile++;
    }

    return 0;
}

//========== PASTAS ===========  
char **filesByFolder(char *path, int *qtdFiles){
    DIR *dir = NULL;
    struct dirent *inf = NULL;
    char **files = (char**) malloc(sizeof(char*));
    int coutFiles = 0;
    dir = opendir(path);

    if(dir == NULL){      
        return NULL;
    }
    
    for(*qtdFiles = 0; (inf = readdir(dir)) != NULL; *qtdFiles++){
        files = (char**) realloc(files, (*qtdFiles +1) * sizeof(char**));
        files[*qtdFiles] = inf->d_name;
    }

    closedir(dir);

    return files;
}

//========== ARQUIVOS =========== 
char **infoByFile(char *path, int *qtdRows){
    FILE *file = fopen(path, "r");
    char **rows = (char**) malloc(sizeof(char*));
    int contRows = 0;

    if(file == NULL){

        return NULL;
    }

    while(fgets(rows[contRows], FILE_ROW, file) != NULL)
        puts(rows[contRows]);

    fclose(file);
    return rows;
}