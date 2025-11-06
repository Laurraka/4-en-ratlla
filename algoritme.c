#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Minimax.h"
#include "ordinador.h"
#include "algoritme.h"

int algoritme(char *tauler, char dificultat){
    if(dificultat=='f'){
        return rand();
    }
    else if(dificultat=='m'){
        return algoritme_mitja(tauler);
    }
    else if(dificultat=='d'){
        return 2;
    }
}

int algoritme_mitja(char *tauler){
    if (OrdinadorGuanyador(tauler)==1) return 1000;
    else if(RivalGuanyador(tauler)==1) return -1000;
    else return (rand() % 1999) - 999;
}

int OrdinadorGuanyador(char *tauler){
    for(int i=N-1; 0<=i; i--){
        for(int j=0; j<N; j++){
            int recompte;
            recompte=1;
            if(tauler[i*N+j]==2){
                if(AmuntAlgoritme(tauler,recompte,2, i, j)==1 || AmuntEsquerraAlgoritme(tauler,recompte,2, i, j)==1 ||
                    AmuntDretaAlgoritme(tauler,recompte,2, i, j)==1 || DretaAlgoritme(tauler,recompte,2, i, j)==1){
                    return 1;
                }

            }
        }
    }
    return 0;
}

int RivalGuanyador(char *tauler){
    for(int i=N-1; 0<=i; i--){
        for(int j=0; j<N; j++){
            int recompte;
            recompte=1;
            if(tauler[i*N+j]==1){
                if(AmuntAlgoritme(tauler,recompte,1, i, j)==1 || AmuntEsquerraAlgoritme(tauler,recompte,1, i, j)==1 ||
                    AmuntDretaAlgoritme(tauler,recompte,1, i, j)==1 || DretaAlgoritme(tauler,recompte,1, i, j)==1){
                    return 1;
                }

            }
        }
    }
    return 0;
}

int DretaAlgoritme(char *tauler, int recompte, int ValorCasella, int fila, int col){
    if((col+1)<N && ValorCasella!=0 && tauler[(fila)*N+col+1]==ValorCasella && recompte<4){
        recompte++;
        DretaAlgoritme(tauler, recompte, tauler[(fila)*N+col+1], fila, col+1);
    }
    else if(recompte==4){
        return 1;
    }
    else{
        return 0;
    }
}

int AmuntAlgoritme(char *tauler, int recompte, int ValorCasella, int fila, int col){
    if(fila-1>=0 && ValorCasella!=0 && tauler[(fila-1)*N+col]==ValorCasella && recompte<4){
        recompte++;
        AmuntAlgoritme(tauler, recompte, tauler[(fila-1)*N+col], fila-1, col);
    }
    else if(recompte==4){
        return 1;
    }
    else{
        return 0;
    }
}

int AmuntEsquerraAlgoritme(char *tauler, int recompte, int ValorCasella, int fila, int col){
    if(fila-1>=0 && (col-1)>=0 && ValorCasella!=0 && tauler[(fila-1)*N+(col-1)]==ValorCasella && recompte<4){
        recompte++;
        AmuntEsquerraAlgoritme(tauler, recompte, tauler[(fila-1)*N+(col-1)], fila-1, col-1);
    }
    else if(recompte==4){
        return 1;
    }
    else{
        return 0;
    }
}

int AmuntDretaAlgoritme(char *tauler, int recompte, int ValorCasella, int fila, int col){
    if(fila-1>=0 && (col+1)<N && ValorCasella!=0 && tauler[(fila-1)*N+(col+1)]==ValorCasella && recompte<4){
        recompte++;
        AmuntDretaAlgoritme(tauler, recompte, tauler[(fila-1)*N+(col+1)], fila-1, col+1);
    }
    else if(recompte==4){
        return 1;
    }
    else{
        return 0;
    }
}
