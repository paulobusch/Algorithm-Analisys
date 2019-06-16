#ifndef BUBBLE_H
#define BUBBLE_H

//====== DEPENDÊNCIAS =======
#include "util/troca.h"

//======= PROTÓTIPOS ========
void bubbleSort(int *vetor, int size);

//===== IMPLEMENTAÇÃO =======
void bubbleSort(int *vetor, int size) {
    int i, j;

    for(i=0; i<size-1; i++) {
        for(j=0; j<size-i-1; j++) {
            if(vetor[j] > vetor[j+1]) {
                troca(&vetor[j], &vetor[j+1]);
            }
        }        
    }
}

#endif