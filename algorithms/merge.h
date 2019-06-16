#ifndef MERGE_H
#define MERGE_H

//====== DEPENDÊNCIAS =======

//======= PROTÓTIPOS ========
void intercala(int v[], int p, int q, int r);
void mergeSort(int v[], int p, int r);

//===== IMPLEMENTAÇÃO =======
void intercala(int v[], int p, int q, int r) {
    int *w;
    w = (int*) malloc( (r-p) * sizeof(int));
    int i=p;
    int j=q;
    int k=0;
    
    while(i<q && j<r) {
        if(v[i] <= v[j])
            w[k++] = v[i++];
        else
            w[k++] = v[j++];
    }

    while(i<q)
        w[k++] = v[i++];

    while(j<r)
        w[k++] = v[j++];

    for(i=p; i<r; ++i)
        v[i] = w[i-p];

    free(w);
}

void mergeSort(int v[], int p, int r) {
    int q;
    if(p<r-1) {
        q = (p+r)/2;
        mergeSort(v, p, q);
        mergeSort(v, q, r);
        intercala(v, p, q, r);
    }
}

#endif
