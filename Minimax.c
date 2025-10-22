#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 8
#define NIVELL 2

typedef struct node{
     struct node * *fills;
     int n_fills;
     char tauler[N][N];
     double valor;
} Node;

double min_llista(double *llista, int mida) {
    double min = llista[0];
    for (int i=1; i<mida; i++) {
        if (llista[i]<min) {
            min = llista[i];
        }
    }
    return min;
}

double max_llista(double *llista, int mida) {
    double max = llista[0];
    for (int i=1; i<mida; i++) {
        if (llista[i] > max) {
            max = llista[i];
        }
    }
    return max;
}

void PujarValors(Node *pare, int nivell_actual, int nivell_max){
    if(nivell_actual<nivell_max){
        for(int i=0; i<pare->n_fills; i++){
            PujarValors(pare->fills[i], nivell_actual+1, nivell_max);
        }
    }
    else{
        double *valors_fills=malloc(pare->n_fills*sizeof(double));
        for(int i=0; i<pare->n_fills; i++){
            valors_fills[i]=pare->fills[i]->valor;
        }
        if(nivell_actual%2==1){
            pare->valor=min_llista(valors_fills, pare->n_fills);
        }
        else{
            pare->valor=max_llista(valors_fills, pare->n_fills);
        }
    }
}

int MiniMax(Node *arrel){
    int nivell_max=NIVELL-1;
    while(nivell_max>=1){
        PujarValors(arrel, 0, nivell_max);
        nivell_max--;
    }

    //Seleccionem columna amb la puntuació més alta
    int index=0;
    for (int i=1; i<arrel->n_fills; i++) {
        if (arrel->fills[i]->valor > arrel->fills[index]->valor) {
            index=i;
        }
    }
    return index;
}
