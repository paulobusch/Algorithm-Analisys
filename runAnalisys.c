#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <time.h>

//====== CONSTANTES ========
#define FOLDER_DATA "data"
#define FOLDER_LOG "log"

#define FILE_LOG "log.csv"

#define FILE_ROW 30

//======= PROTÓTIPOS ========
char **filesByFolder(char *path, int *qtdFiles);
int  *arrayByFile(char *path, int *qtdArray);

void startAnalisys(char *file, char *header);
void stopAnalisys(char *file, char *header);

char *combinePath(char *path, char *file);

//======= VARIÁVEIS =========
clock_t start, end;
double cpu_time_used;

//======= MAIN ==========
int main(){
    int qtdFiles = 0, idxFile = 0;
    int qtdArray = 0, idxLine = 0;
    char **files = filesByFolder(FOLDER_DATA, &qtdFiles);
    
    while(idxFile < qtdFiles){
        startAnalisys(files[idxFile], "Iniciado Leitura");
        arrayByFile(combinePath(FOLDER_DATA,files[idxFile]), &qtdArray);
        stopAnalisys(files[idxFile], "Parado Leitura");
        printf(" Valores: %d", qtdArray);
        idxFile++;
    }

    return 0;
}

//========== PASTAS ===========  
char **filesByFolder(char *path, int *qtdFiles){
    DIR *dir = NULL;
    struct dirent *inf = NULL;
    char **files = (char**) malloc(sizeof(char*));
    char *file = (char*) malloc(sizeof(char) * FILE_ROW);
    dir = opendir(path);

    if(dir == NULL)
        return NULL;

    *qtdFiles = 0;
    while((inf = readdir(dir)) != NULL){
        strcpy(file,inf->d_name);
        if(strcmp(file, ".")!=0 && strcmp(file, "..")!=0){
            files = (char**) realloc(files, (*qtdFiles +1) * sizeof(char**));
            files[*qtdFiles] = (char*) malloc(sizeof(char) * FILE_ROW);
            strcpy(files[*qtdFiles],file);
            (*qtdFiles)++;
        }
    }

    closedir(dir);

    return files;
}

//========== ARQUIVOS =========== 
int *arrayByFile(char *path, int *qtdArray){
    int *array = NULL;
    FILE *file = fopen(path, "r");

    if(file == NULL)
        return NULL;

    *qtdArray = 0;
    while(!feof(file)){
        (*qtdArray)++;
        array = (int*) realloc(array, (*qtdArray) * sizeof(int));
        fscanf(file, "%d", &array[*qtdArray -1]);
    }

    fclose(file);
    return array;
}

char *combinePath(char *path, char *file){
    char *pathFile = (char*) malloc(sizeof(char) * FILE_ROW);
    sprintf(pathFile,"%s/%s",path,file);
    return pathFile;
}

//======= GERAÇÃO DE LOG ======== 
void startAnalisys(char *file, char *header){
    start = clock();
}

void stopAnalisys(char *file, char *header){
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("\nArquivo: %s Tempo: %.2fs", file, cpu_time_used);
}