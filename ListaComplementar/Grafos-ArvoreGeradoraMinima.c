/*Implemente o algoritmo de Prim. A função deve receber um grafo representado por uma matriz de adjacência e construir uma árvore geradora mínima. Caso desejar, neste exercício é permitida a conversão da matriz de adjacência para lista de adjacência. Por fim, a árvore geradora mínima deve ser construída a partir do vértice "0".

Input Format

A primeira linha contém o número de vértices seguido pela respectiva matriz de adjacência.

Constraints

Deve utilizada a estrutura de dados apresentada em sala de aula para matriz de adjacência.

Output Format

Imprimir a árvore geradora mínima. Cada linha deve ser impressa no seguinte formato: "v_i: pai[v_i]".

Para o vértice da árvore que não tiver "pai", deve ser impresso o caractere "-" (traço/sinal de menos). Como o algoritmo deve ser iniciada a partir do vértice "0", então a primeira linha sempre será "0: -"

Sample Input 0

9
0 4 0 0 0 0 0 8 0
4 0 8 0 0 0 0 11 0
0 8 0 7 0 4 0 0 2
0 0 7 0 9 14 0 0 0
0 0 0 9 0 10 0 0 0
0 0 4 14 10 0 2 0 0
0 0 0 0 0 2 0 1 6
8 11 0 0 0 0 1 0 7
0 0 2 0 0 0 6 7 0
Sample Output 0

0: -
1: 0
2: 1
3: 2
4: 3
5: 2
6: 5
7: 6
8: 2*/
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>

typedef struct Cell Cell;


typedef struct FilaE FilaE;

struct Cell{
    int item;
    Cell *next;
};


struct FilaE{
    Cell *inicio;
    Cell *fim;
};


Cell* criar_celula(int key){
    Cell *c = (Cell*) malloc(sizeof(Cell));
    c->item = key;

    c->next = NULL;

    return c;
}


FilaE* criar_filaE(){
    FilaE *f = (FilaE*) malloc(sizeof(FilaE));
    
    f->inicio = NULL;
    f->fim = NULL;
    
    return f;
}


int filaE_vazia(FilaE* f){
    return (f == NULL) || (f->inicio == NULL);
}


void enfileirar(int key, FilaE* f){
    Cell *aux;

    if (f == NULL)
        f = criar_filaE();

    aux = criar_celula(key);

    if (f->inicio == NULL)
        f->inicio = f->fim = aux;
    else{
        f->fim->next = aux;
        f->fim = f->fim->next;
    }

}


int desenfileirar(FilaE* f){
    Cell *aux;
    int item = INT_MIN;

    if (!filaE_vazia(f)){
        aux = f->inicio;

        f->inicio = aux->next;
        
        item = aux->item;

        free(aux);
    }

    return item;
}


void imprimir_fila(FilaE* f){
    Cell *aux;

    if (!filaE_vazia(f)){
        aux = f->inicio;

        while (aux != NULL){
            printf("%d ", aux->item);
            aux = aux->next;
        }
        
        printf("\n");
    }
}


int liberar_filaE(FilaE* f){
    if (!filaE_vazia(f)){
        while (f->inicio != NULL)
            desenfileirar(f);

        free(f);

        return 1;
    }

    return 0;
}

typedef struct GrafoMA GrafoMA;

struct GrafoMA{
   int V, A;
   int **mat;
   int *nafila; 
    int *pai;
    int *key;
};

static int** iniciar_MA(int n){
    int i, j;
    int **mat = (int**) malloc(n * sizeof(int*));

    for (i = 0; i < n; i++)
        mat[i] = (int*) calloc(n, sizeof(int));

    return mat;
}


static int valida_vertice(GrafoMA* G, int v){
    return (v >= 0) && (v < G->V);
}


GrafoMA* iniciar_grafoMA(int v){
    GrafoMA* G = (GrafoMA*) malloc(sizeof(GrafoMA));

    // int *nafila; 
    // int *pai;
    // int *key;
    
    G->V = v;
    G->A = 0;
    G->mat = iniciar_MA(G->V);
    
    G->nafila= (int*)malloc(sizeof(int)*v);
    G->pai= (int*)malloc(sizeof(int)*v);
    G->key= (int*)malloc(sizeof(int)*v);

    return G;
}


int aresta_existe(GrafoMA* G, int v1, int v2){
    return (G != NULL) && valida_vertice(G, v1) && valida_vertice(G, v2) && (G->mat[v1][v2] != 0);
}


void inserir_aresta(GrafoMA* G, int v1, int v2){
    if (!aresta_existe(G, v1, v2)){
        G->mat[v1][v2] = G->mat[v2][v1] = 1;
        G->A++;
    }
}

void remover_aresta(GrafoMA* G, int v1, int v2){
    if (aresta_existe(G, v1, v2)){
        G->mat[v2][v1] = G->mat[v1][v2] = 0;
        G->A--;
    }
}

void imprimir_arestas(GrafoMA* G){
    int i, j;

    for (i = 1; i < G->V; i++)
        for (j = 0; j < i; j++)
            if (G->mat[i][j] == 1)
                printf("(%d, %d)\n", i, j);
}


void liberarGMA(GrafoMA* G){
    if (G != NULL){
        free(G->mat);
        free(G);
    }
}

int extract_min(FilaE *f, GrafoMA *G){
    int vM;
    Cell *aux, *auxM;
    
    auxM= f->inicio;
    aux= auxM->next;
    
    while(aux!=NULL){
        if(G->key[aux->item]< G->key[auxM->item])
            auxM =aux;
        
        aux=aux->next;
    }
    
    if(auxM != f->inicio){
        vM = f->inicio->item;
        f->inicio->item = auxM->item;
        auxM->item = vM;
    }
    //antes disso fila prioridades com os menores na frente
    return desenfileirar(f);
} //ate aqui serve pro prox alg

void prim (GrafoMA *G, int s){
    int i, v, u;
    FilaE *f= criar_filaE();
    
    if(valida_vertice(G, s)){
        for(i=0; i< G->V; i++){
            G->pai[i]= -1;
            G->key[i]=INT_MAX;
            G->nafila[i]= 1;
            enfileirar(i,f);
        }
        
        G->key[0]=0;
        
        while (!filaE_vazia(f)){
            u= extract_min(f, G);
            G->nafila[u]=0;
            
            for(v=0; v< G->V; v++){
                if((G->mat[u][v]!=0)&&(G->nafila[v])&&(G->mat[u][v]< G->key[v])){
                    G->key[v]= G->mat[u][v];
                    G->pai[v]=u;
                }
            }
        }
        liberar_filaE(f);
        
        for(v=0; v < G->V; v++){
            printf("%d: ", v);
            
            if(G->pai[v] < 0)
                printf("-\n");
            else
                printf("%d\n", G->pai[v]);
        }
    }
}

int main() {
    int i, j, V, s;
    GrafoMA *G;
    
    scanf("%d", &V);
    
    G= iniciar_grafoMA(V);
    
    for(i=0; i<V; i++)
        for(j=0; j<V; j++)
            scanf("%d", &G->mat[i][j]);
    
    scanf("%d", &s);
    
    prim(G,s);
        
        
    return 0;
}
