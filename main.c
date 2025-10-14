#include <stdio.h>
#include <stdlib.h>

#define N 8

typedef struct node{
     struct node * *fills; //array de fills (pointers a nodes)
     int n_fills;
     char tauler[N][N];
     double valor;
} Node;

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

    //if(nivell<2){
        //f->n_fills=CalculaNumFills(f->tauler);
        //f->fills=malloc(f->n_fills*sizeof(Node*));
    //}
    //else{
        //No creo fills
        //f->n_fills=0;
        //f->fills=NULL;
    //}
    return f;
}

void CrearArbre(Node *arrel){
    arrel->n_fills=CalculaNumFills(&(arrel->tauler[0][0]));
    int *columnes_disponibles=malloc((arrel->n_fills)*sizeof(int));
    int index=0;
    for(int j=0; j<N; j++){
        if(arrel->tauler[0][j]==0){
            columnes_disponibles[index]=j+1;
            index++;
        }
    }

    arrel->fills = malloc(arrel->n_fills * sizeof(Node *));
    for(int i=0; i<arrel->n_fills; i++){
        arrel->fills[i]=CrearNode(arrel,columnes_disponibles[i]);
        printf("Tauler despres de tirar el fill %i\n", i+1);
        ImprimirTauler(&(arrel->fills[i]->tauler[0][0]));
        free(arrel->fills[i]);
    }
    return ;
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
        CrearArbre(arrel);
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
