#ifndef RADIX_H
#define RADIX_H

//====== DEPENDÊNCIAS =======
#include <stdlib.h>

//======= PROTÓTIPOS ========
void radixSort(int vetor[], int size);

//===== IMPLEMENTAÇÃO =======
void radixSort(int vetor[], int size) {
    int i;
    int *b;
    int maior = vetor[0];
    int exp = 1;

    b = (int*)calloc(size, sizeof(int));

    for (i = 0; i < size; i++) {
        if (vetor[i] > maior)
    	    maior = vetor[i];
    }

    while (maior/exp > 0) {
        int bucket[10] = { 0 };
    	for (i = 0; i < size; i++)
    	    bucket[(vetor[i] / exp) % 10]++;
    	for (i = 1; i < 10; i++)
    	    bucket[i] += bucket[i - 1];
    	for (i = size - 1; i >= 0; i--)
    	    b[--bucket[(vetor[i] / exp) % 10]] = vetor[i];
    	for (i = 0; i < size; i++)
    	    vetor[i] = b[i];
    	exp *= 10;
    }

    free(b);
}

#endif