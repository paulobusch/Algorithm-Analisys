#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

//====== CONSTANTES ========
#define FOLDER_DATA "data"
#define FOLDER_LOG "log"

#define FILE_LOG "log.csv"

//======= PROTÓTIPOS ========
char **filesByFolder(char *path);

//======= VARIÁVEIS =========
DIR *dir;
struct dirent *inf;
int idx;

//======= MAIN ==========
int main(){
    char **files = filesByFolder(FOLDER_DATA);
    for(idx = 0; files[idx] != NULL; idx++)
        puts(files[idx]);

    return 0;
}

char **filesByFolder(char *path){
    char **files = (char**) malloc(sizeof(char*));
    dir = opendir(path);
    if(dir == NULL) return NULL;
    
    for(idx = 0; (inf = readdir(dir)) != NULL; idx++){
        files = (char**) realloc(files, (idx +1) * sizeof(char**));
        files[idx] = inf->d_name;
    }

    closedir(dir);
}