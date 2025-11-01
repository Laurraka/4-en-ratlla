#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Minimax.h"
#include "ordinador.h"
#include "algoritme.h"
#include "main.h"

int CalculaNumFills(char *tauler){
    int num_fills;
    num_fills=0;
    for(int j=0; j<N; j++){
        if(tauler[j]==0){
            num_fills++;
        }
    }
    return num_fills;
}

Node* CrearNode(int nivell, Node *pare, int n_columna, char dificultat){ //cada posició de l'array de fills és un node apuntador
    Node *f=malloc(sizeof(Node));
    CopiaTauler(&(pare->tauler[0][0]),&(f->tauler[0][0]));

    //Tirem fitxa ordinador
    Tirada(2-((nivell+1)%2), n_columna, &(f->tauler[0][0]));

    //Assignem valor al node
    f->valor=algoritme(&(f->tauler[0][0]), dificultat);

    return f;
}

void CrearNivell(Node *pare, int nivell, char dificultat){
    nivell++;
    pare->n_fills=CalculaNumFills(&(pare->tauler[0][0]));
    int *columnes_disponibles=malloc((pare->n_fills)*sizeof(int));
    int index=0;
    for(int j=0; j<N; j++){
        if(pare->tauler[0][j]==0){
            columnes_disponibles[index]=j+1;
            index++;
        }
    }

    pare->fills = malloc(pare->n_fills * sizeof(Node *));
    for(int i=0; i<pare->n_fills; i++){
        pare->fills[i]=CrearNode(nivell,pare,columnes_disponibles[i],dificultat);
    }

    if(nivell<NIVELL){
        for(int i=0; i<pare->n_fills; i++){
            CrearNivell(pare->fills[i], nivell, dificultat);
        }
    }
    return ;
}

void RecorreArbre(Node *arrel) {
    int comptador=1;
    printf("%i-%f\n",comptador,arrel->valor);
    for(int i=0 ; i<arrel->n_fills ; i++) {
        comptador++;
        printf("  %i-%f\n",comptador,arrel->fills[i]->valor);
        for(int j=0; j<arrel->fills[i]->n_fills ; j++) {
            comptador++;
            printf("    %i-%f\n",comptador,arrel->fills[i]->fills[j]->valor);
        }
    }
}

void AlliberarNivell(Node *pare, int nivell){
    nivell++;
    if(nivell<NIVELL){
        for(int i=0; i<pare->n_fills; i++){
            AlliberarNivell(pare->fills[i], nivell);
            free(pare->fills[i]);
        }
    }
    else{
        for(int i=0; i<pare->n_fills; i++){
            free(pare->fills[i]);
        }
    }
}
