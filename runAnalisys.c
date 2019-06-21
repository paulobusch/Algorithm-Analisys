//===== DEPENDÊNCIAS ======
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <stdarg.h>
#include <stdbool.h>
#include <locale.h>
#include <time.h>

//====== ALGORITMOS ========
#include "algorithms/bubble.h"
#include "algorithms/insertion.h"
#include "algorithms/selection.h"
#include "algorithms/quick.h"
#include "algorithms/merge.h"
#include "algorithms/heap.h"
#include "algorithms/radix.h"

//====== CONSTANTES ========
#define FOLDER_DATA "data"
#define FOLDER_LOG "log"

#define FILE_LOG "log.csv"

#define FILE_ROW 50
#define REPEAT_BY_AVG 10

/* Keys */
#define BUBBLE_SORT    0
#define INSERTION_SORT 1
#define SELECTION_SORT 2
#define QUICK_SORT     3
#define MERGE_SORT     4
#define HEAP_SORT      5
#define RADIX_SORT     6

//======= PROTÓTIPOS ========
char **filesByFolder(char *path, int *qtdFiles);
int  *arrayByFile(char *path, int *qtdArray);
void writeLineFile(char *path,bool rewrite, char *cols,...);

void prepareRegisterAnalisys();
double analiseAlgorithm(int algorithmKey, int *data, int qtdArray);
void registerAnalisys(char *algorithm, char *source, double elapsed);

char *combinePath(char *path, char *file);
char *alocateStr(int len);
char *nameAlgorithm(int algorithmKey);

//======= VARIÁVEIS =========

//========== MAIN ===========
int main(){
    int qtdFiles = 0, idxFile = 0;
    int qtdArray = 0, idxLine = 0;
    int idxAlgor = 0, idxAvg  = 0;
    double cpu_time_usage = 0.0;
    char **files = filesByFolder(FOLDER_DATA, &qtdFiles);
    char *pathLog = combinePath(FOLDER_LOG, FILE_LOG);
    char *algorithm = NULL;

    setlocale(LC_ALL, "Portuguese");

    prepareRegisterAnalisys();
    
    // Repete algoritmo para calculo posterior de média
    while(idxAvg < REPEAT_BY_AVG){
    
        // Itera algoritmos            
        while(idxAlgor <= RADIX_SORT){

            // Itera arquivos
            while(idxFile < qtdFiles){
                int *data = arrayByFile(combinePath(FOLDER_DATA,files[idxFile]), &qtdArray);

                cpu_time_usage = analiseAlgorithm(idxAlgor, data, qtdArray);
                registerAnalisys(nameAlgorithm(idxAlgor), files[idxFile], cpu_time_usage);

                free(data);
                idxFile++;
            }
            idxFile = 0; 
            idxAlgor++;
        }
        idxAlgor = 0;
        idxAvg++;
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

/* Ultimo argumento deve ser NULL */
void writeLineFile(char *path,bool rewrite, char *cols,...){
    FILE *file = NULL;
    char *line = alocateStr(FILE_ROW);
    char *next = cols;
    va_list args;

    // Procura argumentos
    va_start(args, cols);
    
    while(next != NULL){
        strcat(line, next);
        next = va_arg(args, char*);
        if(next != NULL)
            strcat(line, ";");
    } 

    va_end(args);

    // Escreve
    puts(line);
    strcat(line, "\n");

    file = fopen(path, rewrite ? "w" : "a");
    fprintf(file, line);
    fclose(file);
}

char *combinePath(char *path, char *file){
    char *pathFile = alocateStr(FILE_ROW);
    sprintf(pathFile,"%s/%s",path,file);
    return pathFile;
}

char *alocateStr(int len){
    char *str = (char*) malloc(sizeof(char) * len);
    strcpy(str, "");
    return str;
}

//==== SELEÇÃO DE ALGORITMOS ==== 
double analiseAlgorithm(int algorithmKey, int *data, int qtdArray){
    char *algorithm = alocateStr(15);
    clock_t start, end;
    double cpu_time_used;

    //Roda algoritmo
    start = clock();
    switch(algorithmKey){
        case BUBBLE_SORT:
            bubbleSort(data, qtdArray);
            break;
        case INSERTION_SORT:
            insertionSort(data, qtdArray);
            break;
        case SELECTION_SORT:
            selectionSort(data, qtdArray);
            break;
        case QUICK_SORT:
            quickSort(data, 0, qtdArray -1);
            break;
        case MERGE_SORT:
            mergeSort(data, 0, qtdArray);
            break;
        case HEAP_SORT:
            heapSort(data, qtdArray);
            break;
        case RADIX_SORT:
            radixSort(data, qtdArray);
            break;
    }    
    
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    return cpu_time_used;
}

char *nameAlgorithm(int algorithmKey){
    switch(algorithmKey){
        case BUBBLE_SORT:
            return "Bolha";
        case INSERTION_SORT:
            return "Inserção";
        case SELECTION_SORT:
            return "Selection";
        case QUICK_SORT:
            return "Quicksort";
        case MERGE_SORT:
            return "Mergesort";
        case HEAP_SORT:
            return "Heapsort";
        case RADIX_SORT:
            return "Radixsort";
    }  
}

//======= GERAÇÃO DE LOG ======== 
void prepareRegisterAnalisys(){    
    char *pathLog = combinePath(FOLDER_LOG, FILE_LOG);
    writeLineFile(pathLog, true, "ALGORITMO", "ARQUIVO DE DADOS", "TEMPO", NULL);
}

void registerAnalisys(char *algorithm, char *source, double elapsed){
    char *pathLog = combinePath(FOLDER_LOG, FILE_LOG);
    char *strElapsed = alocateStr(10);
    sprintf(strElapsed, "%.3f", elapsed);
    writeLineFile(pathLog, false, algorithm, source, strElapsed, NULL);
}