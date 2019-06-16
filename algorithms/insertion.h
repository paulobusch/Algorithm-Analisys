#ifndef INSERTION_H
#define INSERTION_H

//====== DEPENDÊNCIAS =======
#include "util/troca.h"

//======= PROTÓTIPOS ========
void insertionSort(int *vetor, int size);

//===== IMPLEMENTAÇÃO =======
void insertionSort(int *vetor, int size) {
    int i, j, chave;

    for(i=1; i<size; i++) {
        chave = vetor[i];
        j = i-1;
        while(j>=0 && vetor[j] > chave) {
            vetor[j+1] = vetor[j];
            j--;
        }
        vetor[j+1] = chave;
    }
}

#endif