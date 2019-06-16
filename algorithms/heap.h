#ifndef HEAP_H
#define HEAP_H

//====== DEPENDÊNCIAS =======

//======= PROTÓTIPOS ========
void heapSort(int vetor[], int size);

//===== IMPLEMENTAÇÃO =======
void heapSort(int vetor[], int size) {
   int i = size / 2, pai, filho, t;
   while(true) {
      if (i > 0) {
          i--;
          t = vetor[i];
      } else {
          size--;
          if (size == 0) return;
          t = vetor[size];
          vetor[size] = vetor[0];
      }
      pai = i;
      filho = i * 2 + 1;
      while (filho < size) {
          if ((filho + 1 < size)  &&  (vetor[filho + 1] > vetor[filho]))
              filho++;
          if (vetor[filho] > t) {
             vetor[pai] = vetor[filho];
             pai = filho;
             filho = pai * 2 + 1;
          } else {
             break;
          }
      }
      vetor[pai] = t;
   }
}

#endif