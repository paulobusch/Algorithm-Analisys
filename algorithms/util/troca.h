#ifndef TROCA_H
#define TROCA_H

//====== DEPENDÊNCIAS =======

//======= PROTÓTIPOS ========
void troca(int *a, int *b);

//===== IMPLEMENTAÇÃO =======
void troca(int *a, int *b) {
    int temp;
    temp = *a;
    *a  = *b;
    *b = temp;
}

#endif