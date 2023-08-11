/*Implemente o algoritmo de Dijkstra. A função deve receber um grafo representado por uma lista de adjacência e construir uma árvore de caminhos mínimos, que deve ser construída a partir do vértice "0".

Para a implementação, considere o grafo representado por lista de adjacências, conforme as estruturas apresentadas abaixo:

typedef struct {
   int V; // número de vértices
   int A; // número de arestas
   Lista **adj; // lista de adjacências
}GrafoLA;

typedef struct Cell Cell;

struct Cell{
    int key;
    Cell *next;
};


typedef struct{
    Cell *head;
}Lista;
Input Format

A primeira linha contém o número de vértices. A segunda linha contém a quantidade de arestas (A). Para cada uma das "A" próximas linhas devem der lidos dois números inteiros. sendo os 2 primeiros, a aresta, e o último, o peso da aresta.

Constraints

.

Output Format

Imprimir a árvore de caminhos mínimos. Cada linha deve ser impressa no seguinte formato: "v_i: pai[v_i]".

Para o vértice da árvore que não tiver "pai", deve ser impresso o caractere "-" (traço/sinal de menos). Como o algoritmo deve ser iniciada a partir do vértice "0", então a primeira linha sempre será "0: -"

Sample Input 0

6
12
0 1 10
0 2 5
1 2 2
1 3 1
2 1 3
2 3 9
2 4 2
3 4 4
3 5 2
4 0 7
4 3 6
4 5 5
Sample Output 0

0: -
1: 2
2: 0
3: 1
4: 2
5: 3
Explanation 0

Na linha 3 da entrada, 0 e 1 forma uma aresta e o valor 10 é o respectivo peso dessa aresta.*/


#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>
typedef struct Cell Cell;
typedef struct FilaE FilaE;

struct Cell{
    int key;
    Cell *next;
};


typedef struct{
    Cell *head;
}Lista;

typedef struct {
   int V; 
   int A; 
   int *nafila; 
   int *pai;
   int *key;
   int **peso;
   Lista **adj; 
}GrafoLA;

struct FilaE{
    Cell *inicio;
    Cell *fim;
};

Cell* criar_celula(int key){
    Cell *c = (Cell*) malloc(sizeof(Cell));
    c->key = key;

    c->next = NULL;

    return c;
}

FilaE* criar_filaE(){
    FilaE *f = (FilaE*) malloc(sizeof(FilaE));
    
    f->inicio = NULL;
    f->fim = NULL;
    
    return f;
}

Lista* criar_lista(){
    Lista* l = (Lista*) malloc(sizeof(Lista));

    l->head = NULL;

    return l;
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
        
        item = aux->key;

        free(aux);
    }

    return item;
}


void imprimir_fila(FilaE* f){
    Cell *aux;

    if (!filaE_vazia(f)){
        aux = f->inicio;

        while (aux != NULL){
            printf("%d ", aux->key);
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



int lista_vazia(Lista *l){
    return (l == NULL) || (l->head == NULL);
}


int procurar(int key, Lista *l){
    Cell *aux=NULL;

    if (l != NULL){
        aux = l->head;

        while ((aux != NULL) && (key < aux->key))
            aux = aux->next;
    }

    if ((aux != NULL) && (key == aux->key))
        return 1;
    else
        return 0;
}


void inserir_na_lista(int key, Lista *l){
    Cell *auxA, *auxP;
    Cell* c;

    if (lista_vazia(l)){
        if (l == NULL)
            l = criar_lista();

        l->head = criar_celula(key);
    }else{
        c = criar_celula(key);

        if (l->head->key >= key){
           c->next = l->head;


           l->head = c;
        }else{
            auxA = l->head;
            auxP = auxA;

            while ((auxP != NULL) && (auxP->key < key)){
                auxA = auxP;
                auxP = auxP->next;
            }

            auxA->next = c;
            c->next = auxP;
        }
    }
}


int remover_na_lista(int key, Lista *l){
    Cell *auxA, *auxP;

    if (!lista_vazia(l)){
        auxA = l->head;

        if(auxA->key == key)
            l->head = l->head->next;
        else{
            auxP = auxA;

            while((auxA != NULL) && (key < auxA->key)){
                auxP = auxA;
                auxA = auxA->next;
            }

            if (auxA->key == key)
                auxP->next = auxA->next;
            else
                auxA = NULL;
        }

        if (auxA != NULL)
            free(auxA);

        return 1;
    }

        return 0;
}


void imprimir(Lista *l){
    Cell *aux;

    if (!lista_vazia(l)){
        aux = l->head;

        while (aux != NULL){
            printf("%d\n", aux->key);

            aux = aux->next;
        }
    }
}


int liberar_lista(Lista *l){
    Cell *aux;

    if ((l != NULL) && !lista_vazia(l)){

        while(l->head != NULL){
            aux = l->head;

            l->head = aux->next;

            free(aux);
        }

        free(l);

        return 1;
    }

    return 0;
}


//grafo
static Lista** iniciar_LA(int n){ 
    int i;
    Lista **adj = (Lista**) malloc(n * sizeof(Lista*));

    for (i = 0; i < n; i++)
        adj[i] = criar_lista();

    return adj;
}


GrafoLA* iniciar_grafoLA(int v, int aresta){
    int i;
    
    GrafoLA* G = (GrafoLA*) malloc(sizeof(GrafoLA));

    G->V = v;
    G->A = aresta;
    
    G->nafila= (int*)malloc(sizeof(int)*v);
    G->pai= (int*)malloc(sizeof(int)*v);
    G->key= (int*)malloc(sizeof(int)*v);
    
    G->adj = iniciar_LA(G->V);
    
    G->peso = (int**)malloc(sizeof(int*)*v);
    
    for (i=0; i<v; i++){
        G->peso[i]= (int*)malloc(sizeof(int)*v);
    }

    return G;
}


int aresta_existeLA(GrafoLA* G, int v1, int v2){
    if ((G!= NULL) && (G->adj[v1]->head != NULL))
        return procurar(v2, G->adj[v1]);

    return 0;
}


void inserir_arestaLA(GrafoLA* G, int v1, int v2, int peso){
    if (!aresta_existeLA(G, v1, v2)){
        inserir_na_lista(v2, G->adj[v1]);
        inserir_na_lista(v1, G->adj[v2]);
        G->peso[v1][v2]=peso;
        G->peso[v2][v1]=peso;
    }
}


void remover_arestaLA(GrafoLA* G, int v1, int v2){
    if (aresta_existeLA(G, v1, v2)){
        remover_na_lista(v2, G->adj[v1]);
        remover_na_lista(v1, G->adj[v2]);
        G->A--;

    }
}


void imprimir_arestasLA(GrafoLA* G){
    int i;
    Cell *aux;

    if (G != NULL)
        for (i = 0; i < G->V; i++){
            aux = G->adj[i]->head;

            while (aux != NULL){
                printf("(%d, %d)\n", i, aux->key);

                aux = aux->next;
            }

        }
}


void liberarGLA(GrafoLA* G){
    int i;

    if (G != NULL){
        for (i = 0; i < G->V; i++)
            liberar_lista(G->adj[i]);

        free(G);
    }
}
int extract_min(FilaE *f, GrafoLA *G){
    int vM;
    Cell *aux, *auxM;
    
    auxM= f->inicio;
    aux= auxM->next;
    
    while(aux!=NULL){
        if(G->key[aux->key]< G->key[auxM->key])
            auxM =aux;
        
        aux=aux->next;
    }
    
    
    if(auxM != f->inicio){
        vM = f->inicio->key;
        f->inicio->key = auxM->key;
        auxM->key = vM;
    }

    //antes disso fila prioridades com os menores na frente
    return desenfileirar(f);
} //ate aqui serve pro prox alg



void Dijkstra (GrafoLA *G){
    int i, v, u;
    FilaE *f= criar_filaE();
    
  
        for(i=0; i< G->V; i++){
            G->pai[i]= -1;
            G->key[i]=INT_MAX;
            G->nafila[i]= 1;
            enfileirar(i,f);
        }
        
        G->key[0]=0; //r=0
        
        while (!filaE_vazia(f)){
            u= extract_min(f, G);
            G->nafila[u]=0;
            
            Cell * aux= G->adj[u]->head; // lista de adj de u
            while(aux!=NULL){
                v=aux->key;
                //dijkstra add relaxacao
                if((G->nafila[v])&&(G->peso[u][v] + G->key[0] < G->key[v])){
                    G->key[v]= G->peso[u][v]+ G->key[0];
                    G->pai[v]=u;
                }
                 aux = aux->next;
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


int main() {
    int nV, nA;
    int vert1, vert2, peso, i, j;
    
    scanf("%d", &nV);
    scanf("%d", &nA);
    
    GrafoLA* G=iniciar_grafoLA(nV, nA);
        
    for (i=0; i<nA; i++){
       
     scanf("%d %d %d", &vert1, &vert2, &peso);
     inserir_arestaLA(G, vert1, vert2, peso);
        
    }
    
    
   Dijkstra(G);
         
    
    
    return 0;
}

