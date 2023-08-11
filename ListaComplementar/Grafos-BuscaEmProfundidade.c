/*Implemente o algoritmo de busca em profundidade para grafos representados por matriz de adjacências. A aplicação do algoritmo deve começar pelo vértice 0.

Input Format

A primeira linha contém o número de vértices seguido pela respectiva matriz de adjacência.

Constraints

Deve utilizada a estrutura de dados apresentada em sala de aula para matriz de adjacências.

Output Format

Na primeira linha deve ser impressa a seguinte sequência de caracteres: "v d f p".

Para cada uma das próximas linhas, imprimir um vértice (em ordem crescente), o momento da sua descoberta, o momento da sua finalização e o seu respectivo pai.

Para cada vértice que não tem pai, deve ser impresso "-" em sua respectiva linha.

Sample Input 0

4
0 1 0 1
0 0 1 1
0 0 0 0
0 0 1 0
Sample Output 0

v d f p
0 1 8 -
1 2 7 0
2 3 4 1
3 5 6 1*/
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

typedef struct GrafoMA GrafoMA;

struct GrafoMA{
   int V, A;
   int **mat;
    int *cor, *pai, *d, *f;
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

    G->V = v;
    G->A = 0;
    G->mat = iniciar_MA(G->V);
    
    G->cor=(int*)malloc(v*sizeof(int));
     G->pai=(int*)malloc(v*sizeof(int));
     G->d=(int*)malloc(v*sizeof(int));
     G->f=(int*)malloc(v*sizeof(int));

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

void visitar_vertice(GrafoMA *G, int u, int *tempo){
    int v;
    
    G->cor[u]=1;//cnza
    *tempo= *tempo +1;
    G->d[u]=*tempo;
    
    for(v=0; v<G->V; v++)
        if (G->mat[u][v]!=0 && (G->cor[v]==0)){//checando adjacentes n visitados
            G->pai[v]=u;
            visitar_vertice(G, v, tempo); //visita o v
        }
    
    G->cor[u]=2; //preto
    *tempo= *tempo +1;
    G->f[u]=*tempo;
            
}

void busca_profundidade(GrafoMA *G){
    int u, tempo=0;
    
    for (u=0; u < G->V; u++){
        G->cor[u]=0; //branco
        G->pai[u]= -1;
    }
    
    for(u=0; u< G->V; u++){
        if (G->cor[u]==0)
            visitar_vertice(G, u, &tempo);
    }
}

void imprimir_resultados(GrafoMA *G){
    int v;
    
    printf("v d f p\n");
    
    for(v=0; v< G->V; v++){
        printf("%d %d %d ", v, G->d[v], G->f[v]);
        
        if(G->pai[v]>=0)
            printf("%d\n", G->pai[v]);
        else
            printf ("-\n");
    }
}


int main() {
    int i, j, V;
    GrafoMA *G;
    
    scanf("%d", &V);
    
    G=iniciar_grafoMA(V);
    
    for(i=0; i<V; i++){
        for(j=0; j<V; j++){
            scanf("%d", &G->mat[i][j]);
        }
    }
    
    busca_profundidade(G);
    imprimir_resultados(G);
    
    
    return 0;
}
