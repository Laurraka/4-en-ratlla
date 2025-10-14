#include <stdio.h>
#include <stdlib.h>

#define N 8

//ALTRES FUNCIONS 26 DE SETEMBRE

typedef struct node{
     struct node * *fills; //array de fills (pointers a nodes)
     int n_fills;
     char tauler[N][N];
     double valor;
} Node;

void ImprimirTauler(char **tauler){
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            if(j<N-1){
                printf("|%i", tauler[i][j]);
            }
            else{
                printf("|%i|", tauler[i][j]);
            }
        }
        printf("\n");
    }
}

void Tirada(int *n_torn, char **tauler){
    printf("Jugador %i, a quina columna vols tirar?", 2-(*n_torn%2));
    int n_columna;
    scanf("%i", &n_columna);
    while(n_columna<1 || N<n_columna || tauler[0][n_columna-1]!=0){
        printf("Columna no valida. Torna a introduir la columna:");
        scanf("%i", &n_columna);
        printf("\n");
    }
    if(*n_torn%2==1){ //Torn persona 1
        int n_fila=N;
        while(tauler[n_fila-1][n_columna-1]!=0){
            n_fila--;
        }
        tauler[n_fila-1][n_columna-1]=1;
        ImprimirTauler(tauler);
    }
    else{ //Torn persona 2
        int n_fila=N;
        while(tauler[n_fila-1][n_columna-1]!=0){
            n_fila--;
        }
        tauler[n_fila-1][n_columna-1]=2;
        ImprimirTauler(tauler);
    }
}

int Amunt(char **tauler, int recompte, int ValorCasella, int fila, int col){
    if(0<fila){
        if(ValorCasella!=0 && tauler[fila-1][col]==ValorCasella){
            recompte++;
            Amunt(tauler, recompte, tauler[fila-1][col], fila-1, col);
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

int AmuntEsquerra(char **tauler, int recompte, int ValorCasella, int fila, int col){
    if(0<fila && 0<col){
        if(ValorCasella!=0 && tauler[fila-1][col-1]==ValorCasella){
            recompte++;
            AmuntEsquerra(tauler, recompte, tauler[fila-1][col-1], fila-1, col-1);
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

int AmuntDreta(char **tauler, int recompte, int ValorCasella, int fila, int col){
    if(0<fila && col<N){
        if(ValorCasella!=0 && tauler[fila-1][col+1]==ValorCasella){
            recompte++;
            AmuntDreta(tauler, recompte, tauler[fila-1][col+1], fila-1, col+1);
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

int Esquerra(char **tauler, int recompte, int ValorCasella, int fila, int col){
    if(0<col){
        if(ValorCasella!=0 && tauler[fila][col-1]==ValorCasella){
            recompte++;
            Esquerra(tauler, recompte, tauler[fila][col-1], fila, col-1);
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

int Dreta(char **tauler, int recompte, int ValorCasella, int fila, int col){
    if(0<col){
        if(ValorCasella!=0 && tauler[fila][col+1]==ValorCasella){
            recompte++;
            Dreta(tauler, recompte, tauler[fila][col+1], fila, col+1);
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

int ComprovGuanyador(char **tauler){
    for(int i=N-1; 0<=i; i--){
        for(int j=0; j<N; j++){
            int recompte;
            recompte=1;
            if(Amunt(tauler,recompte,tauler[i][j], i, j)==1 || AmuntEsquerra(tauler,recompte,tauler[i][j], i, j)==1 || AmuntDreta(tauler,recompte,tauler[i][j], i, j)==1 ||
               Esquerra(tauler,recompte,tauler[i][j], i, j)==1 || Dreta(tauler,recompte,tauler[i][j], i, j)==1){
                return 1;
            }
        }
    }
    return 0;
}

int ComprovPle(char **tauler){
    for(int j=0; j<N; j++){
        if(tauler[0][j]==0){
            return 0;
        }
    }
    return 1;
}

int main(void)
{
    //Creem el tauler real
    char **TaulerReal = malloc(N*sizeof(char *));
    for (int i=0; i<N; i++) {
        TaulerReal[i] = malloc(N*sizeof(char));
    }

    //Omplim de zeros el tauler
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            TaulerReal[i][j]=0;
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
            Tirada(&n_torn, TaulerReal);
            n_torn++;
        }
    }
    printf("Ha guanyat el jugador %i, felicitats !!!!!!!!!!!!", 2-(n_torn+1)%2);
    return 0;
}

