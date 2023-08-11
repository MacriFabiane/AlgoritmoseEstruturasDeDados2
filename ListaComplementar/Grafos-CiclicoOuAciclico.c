/*Implemente uma função para verificar se um grafo é cíclico ou acíclico

Input Format

A primeira linha contém o número de vértices seguido pela respectiva matriz de adjacência.

Constraints

Deve utilizada a estrutura de dados apresentada em sala de aula para matriz de adjacência.

Output Format

imprimir ciclico ou aciclico.

Sample Input 0

4
0 1 1 1
1 0 1 1
1 1 0 0
1 1 0 0
Sample Output 0

ciclico
Sample Input 1

4
0 1 1 0
1 0 0 0
1 0 0 1
0 0 1 0
Sample Output 1

aciclico*/
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

int visitar_vertice(GrafoMA *G, int u){
    int v, b=0;
    
    G->cor[u]=1;//cnza
 
    
    for(v=0; (v<G->V) && (b==0); v++) //b==0 aresta de retorno b muda p 1
        if (G->mat[u][v]!=0 ){//checando adjacentes
            if(G->cor[v]==0){// n visitado
                G->pai[v]= u;
                b = visitar_vertice(G, v); //visita o v
            }
            else if((G->pai[u]!=v)&&(G->cor[v]==1))  // encotrado aresta de retorno
                b=1;
        }
    
    G->cor[u]=2; //preto
   
    return b;
            
}

int ciclico(GrafoMA *G){
    int u, b=0;
    
    for (u=0; u < G->V; u++){
        G->cor[u]=0; //branco
        G->pai[u]= -1;
    }
    
    for(u=0; (u< G->V) && (b==0); u++){
        if (G->cor[u]==0)
            b= visitar_vertice(G, u);
    }
    return b;
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
    
    if (ciclico(G))
        printf("ciclico");
    else
        printf ("aciclico");
    
    
    
    return 0;
}

