#ifndef TROCA_H
#define TROCA_H

//====== DEPEND�NCIAS =======

//======= PROT�TIPOS ========
void troca(int *a, int *b);

//===== IMPLEMENTA��O =======
void troca(int *a, int *b) {
    int temp;
    temp = *a;
    *a  = *b;
    *b = temp;
}

#endif