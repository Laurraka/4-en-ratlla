#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Minimax.h"
#include "ordinador.h"
#include "algoritme.h"
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

void Torn(int *n_torn, char *tauler, char dificultat){
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
        CrearNivell(arrel, nivell, dificultat);
        int index=MiniMax(arrel);
        RecorreArbre(arrel);
        Tirada(2,index+1,tauler);
        ImprimirTauler(tauler);
        AlliberarNivell(arrel, nivell);
    }
}

int Amunt(char *tauler, int recompte, int ValorCasella, int fila, int col){
    if(fila-1>=0 && ValorCasella!=0 && tauler[(fila-1)*N+col]==ValorCasella && recompte<4){
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

int AmuntEsquerra(char *tauler, int recompte, int ValorCasella, int fila, int col){
    if(fila-1>=0 && col-1>=0 && ValorCasella!=0 && tauler[(fila-1)*N+(col-1)]==ValorCasella && recompte<4){
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

int AmuntDreta(char *tauler, int recompte, int ValorCasella, int fila, int col){
    if(fila-1>=0 && col+1<N && ValorCasella!=0 && tauler[(fila-1)*N+(col+1)]==ValorCasella && recompte<4){
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

int Dreta(char *tauler, int recompte, int ValorCasella, int fila, int col){
    if(col+1<N && ValorCasella!=0 && tauler[(fila)*N+(col+1)]==ValorCasella && recompte<4){
        recompte++;
        Dreta(tauler, recompte, tauler[(fila)*N+(col+1)], fila, col+1);
    }
    else if(recompte==4){
        printf("4 en linia\n");
        return 1;
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
            if(Amunt(tauler,recompte,tauler[i*N+j], i, j)==1 || AmuntEsquerra(tauler,recompte,tauler[i*N+j], i, j)==1
               || AmuntDreta(tauler,recompte,tauler[i*N+j], i, j)==1 || Dreta(tauler,recompte,tauler[i*N+j], i, j)==1){
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
    printf("En quina dificultat vols jugar? Facil, mitjana o dificil? (f/m/d):");
    char dificultat;
    scanf("%c", &dificultat);

    char *TaulerReal = malloc(N*N*sizeof(char));

    FILE *fitxer;
    fitxer = fopen("tauler_artificial.txt", "r");
    for(int i=0; i<N; i++) {
        for(int j=0; j<N; j++) {
            fscanf(fitxer, "%i", &(TaulerReal[i*N+j]));
        }
    }
    fclose(fitxer);

    //Omplim de zeros el TaulerReal
    //for(int i=0; i<N; i++){
        //for(int j=0; j<N; j++){
            //TaulerReal[i*N+j]=0;
        //}
    //}
    ImprimirTauler(TaulerReal);
    int n_torn;
    n_torn=1;
    while(ComprovGuanyador(TaulerReal)==0){
        if(ComprovPle(TaulerReal)==1){
            printf("Empat\n");
        }
        else{
            Torn(&n_torn, TaulerReal, dificultat);
            n_torn++;
        }
    }
    printf("Ha guanyat el jugador %i", 2-(n_torn+1)%2);
    return 0;
}
