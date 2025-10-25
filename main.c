#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Minimax.h"
#include "main.h"

void ImprimirTauler(char *tauler){
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            if(j<N-1){
                printf("|%i", tauler[i*N+j]);
            }
            else{
                printf("|%i|", tauler[i*N+j]);
            }
        }
        printf("\n");
    }
}

void CopiaTauler(char *origen, char *desti){
        for(int i=0; i<N; i++){
            for(int j=0; j<N; j++){
               *(desti+i*N+j) = *(origen+i*N+j);
            }
        }
}

void Tirada(int fitxa, int n_columna, char *tauler){
    int n_fila=N;
    while(tauler[(n_fila-1)*N+(n_columna-1)]!=0){
        n_fila--;
    }
    tauler[(n_fila-1)*N+(n_columna-1)]=fitxa;
}

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

Node* CrearNode(Node *pare, int n_columna){ //cada posició de l'array de fills és un node apuntador
    Node *f=malloc(sizeof(Node));
    CopiaTauler(&(pare->tauler[0][0]),&(f->tauler[0][0]));

    //Tirem fitxa ordinador
    Tirada(2, n_columna, &(f->tauler[0][0]));

    //Assignem valor al node
    f->valor=rand();

    return f;
}

void CrearNivell(Node *pare, int nivell){
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
        pare->fills[i]=CrearNode(pare,columnes_disponibles[i]);
    }

    if(nivell<NIVELL){
        for(int i=0; i<pare->n_fills; i++){
            CrearNivell(pare->fills[i], nivell);
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

void Torn(int *n_torn, char *tauler){
    if(*n_torn%2==1){ //Torn persona (jugador 1)
        printf("A quina columna vols tirar?");
        int n_columna;
        scanf("%i", &n_columna);
        while(n_columna<1 || N<n_columna || tauler[n_columna-1]!=0){
            printf("Columna no valida. Torna a introduir la columna:");
            scanf("%i", &n_columna);
            printf("\n");
        }
        Tirada(1, n_columna, tauler);
        ImprimirTauler(tauler);
    }
    else{ //Torn ordinador (jugador 2)
        printf("Torn ordinador\n");
        Node *arrel= malloc(sizeof(Node));
        CopiaTauler(tauler, &(arrel->tauler[0][0]));
        int nivell=0;
        arrel->valor=2;
        CrearNivell(arrel, nivell);
        int index=MiniMax(arrel);
        Tirada(2,index+1,tauler);
        ImprimirTauler(tauler);
        AlliberarNivell(arrel, nivell);
    }
}

int Amunt(char *tauler, int recompte, int ValorCasella, int fila, int col){
    if(0<fila){
        if(ValorCasella!=0 && tauler[(fila-1)*N+col]==ValorCasella){
            recompte++;
            Amunt(tauler, recompte, tauler[(fila-1)*N+col], fila-1, col);
        }
        else if(recompte==4){
            printf("4 en linia\n");
            return 1;
        }
        else{
            return 0;
        }
    }
    else{
        return 0;
    }
}

int AmuntEsquerra(char *tauler, int recompte, int ValorCasella, int fila, int col){
    if(0<fila && 0<col){
        if(ValorCasella!=0 && tauler[(fila-1)*N+(col-1)]==ValorCasella){
            recompte++;
            AmuntEsquerra(tauler, recompte, tauler[(fila-1)*N+(col-1)], fila-1, col-1);
        }
        else if(recompte==4){
            printf("4 en linia\n");
            return 1;
        }
        else{
            return 0;
        }
    }
    else{
        return 0;
    }
}

int AmuntDreta(char *tauler, int recompte, int ValorCasella, int fila, int col){
    if(0<fila && col<N){
        if(ValorCasella!=0 && tauler[(fila-1)*N+(col+1)]==ValorCasella){
            recompte++;
            AmuntDreta(tauler, recompte, tauler[(fila-1)*N+(col+1)], fila-1, col+1);
        }
        else if(recompte==4){
            printf("4 en linia\n");
            return 1;
        }
        else{
            return 0;
        }
    }
    else{
        return 0;
    }
}

int Esquerra(char *tauler, int recompte, int ValorCasella, int fila, int col){
    if(0<col){
        if(ValorCasella!=0 && tauler[fila*N+(col-1)]==ValorCasella){
            recompte++;
            Esquerra(tauler, recompte, tauler[fila*N+(col-1)], fila, col-1);
        }
        else if(recompte==4){
            printf("4 en linia\n");
            return 1;
        }
        else{
            return 0;
        }
    }
    else{
        return 0;
    }
}

int Dreta(char *tauler, int recompte, int ValorCasella, int fila, int col){
    if(0<col){
        if(ValorCasella!=0 && tauler[fila*N+(col+1)]==ValorCasella){
            recompte++;
            Dreta(tauler, recompte, tauler[fila*N+(col+1)], fila, col+1);
        }
        else if(recompte==4){
            printf("4 en linia\n");
            return 1;
        }
        else{
            return 0;
        }
    }
    else{
        return 0;
    }
}

int ComprovGuanyador(char *tauler){
    for(int i=N-1; 0<=i; i--){
        for(int j=0; j<N; j++){
            int recompte;
            recompte=1;
            if(Amunt(tauler,recompte,tauler[i*N+j], i, j)==1 || AmuntEsquerra(tauler,recompte,tauler[i*N+j], i, j)==1 || AmuntDreta(tauler,recompte,tauler[i*N+j], i, j)==1 ||
               Esquerra(tauler,recompte,tauler[i*N+j], i, j)==1 || Dreta(tauler,recompte,tauler[i*N+j], i, j)==1){
                return 1;
            }
        }
    }
    return 0;
}

int ComprovPle(char *tauler){
    for(int j=0; j<N; j++){
        if(tauler[j]==0){
            return 0;
        }
    }
    return 1;
}

int main(void)
{
    srand(time(NULL));
    char *TaulerReal = malloc(N*N*sizeof(char));
    //Omplim de zeros el TaulerReal
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            TaulerReal[i*N+j]=0;
        }
    }
    ImprimirTauler(TaulerReal);
    int n_torn;
    n_torn=1;
    while(ComprovGuanyador(TaulerReal)==0){
        if(ComprovPle(TaulerReal)==1){
            printf("Empat\n");
        }
        else{
            Torn(&n_torn, TaulerReal);
            n_torn++;
        }
    }
    printf("Ha guanyat el jugador %i", 2-(n_torn+1)%2);
    return 0;
}
