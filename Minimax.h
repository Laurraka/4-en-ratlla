#define N 8
#define NIVELL 2

typedef struct node{
     struct node * *fills;
     int n_fills;
     char tauler[N][N];
     double valor;
} Node;

double min_llista(double *llista, int mida);
double max_llista(double *llista, int mida);
void PujarValors(Node *pare, int nivell_actual, int nivell_max);
int MiniMax(Node *arrel);
