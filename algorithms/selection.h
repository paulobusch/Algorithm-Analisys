#ifndef SELECTION_H
#define SELECTION_H

//====== DEPENDÊNCIAS =======
#include "util/troca.h"

//======= PROTÓTIPOS ========
void selectionSort(int *vetor, int size);

//===== IMPLEMENTAÇÃO =======
void selectionSort(int *vetor, int size) {
    int i, j, minIdx;

    for(i=0; i<size-1; i++) {
        minIdx = i;
        for(j=i+1; j<size-1; j++) {
            if(vetor[minIdx] > vetor[j]) 
                minIdx = j;
        }

        troca(&vetor[minIdx], &vetor[i]);
    }
}

#endif