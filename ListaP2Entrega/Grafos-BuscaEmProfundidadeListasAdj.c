/*Implemente o algoritmo de busca em profundidade para grafos. Para a representação do grafo, você pode usar matriz ou lista de adjacências. A aplicação do algoritmo deve começar pelo vértice 0.

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

A primeira linha contém o número de vértices seguida pela respectiva lista de adjacência. Cada uma das seguintes linhas será referente a um vértice v_i, onde os vértices adjacentes devem ser lidos. Para cada linha, enquanto o número "-1" (menos um) não for lido, um vértice adjacente deve ser lido. Por exemplo, suponha que o i-ésimo vértice seja adjacente aos vértices 2 e 5, então a leitura deve seguir o seguinte formato:

2 5 -1

Caso o vértice não tenha adjacentes, basta ler -1 (menos 1). Exemplo:

-1

Constraints

.

Output Format

Na primeira linha deve ser impressa a seguinte sequência de caracteres: "v d f p".

Para cada uma das próximas linhas, imprimir um vértice (em ordem crescente), o momento da sua descoberta, o momento da sua finalização e o seu respectivo pai.

Para cada vértice que não tem pai, deve ser impresso "-" em sua respectiva linha.

Sample Input 0

4
1 3 -1
2 3 -1
-1
2 -1
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
   int *pi, *cor, *d, *f;
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


GrafoLA* iniciar_grafoLA(int v){
    GrafoLA* G = (GrafoLA*) malloc(sizeof(GrafoLA));

    G->V = v;
    G->A = 0;
    
    G->cor=malloc(sizeof(int)*v);
    G->pi=malloc(sizeof(int)*v);
    G->d=malloc(sizeof(int)*v); // momento da descoberta
    G->f=malloc(sizeof(int)*v); //momento da finalizacao
    
    G->adj = iniciar_LA(G->V);

    return G;
}


int aresta_existeLA(GrafoLA* G, int v1, int v2){
    if ((G!= NULL) && (G->adj[v1]->head != NULL))
        return procurar(v2, G->adj[v1]);

    return 0;
}


void inserir_arestaLA(GrafoLA* G, int v1, int v2){
    if (!aresta_existeLA(G, v1, v2)){
        inserir_na_lista(v2, G->adj[v1]);
        inserir_na_lista(v1, G->adj[v2]);
        G->A++;
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
static int valida_vertice(GrafoLA* G, int v){
    return (v >= 0) && (v < G->V);
}
void visitar_vertice(GrafoLA *G, int u, int *tempo){
    int v;
    
    G->cor[u]=1;//cnza
    *tempo= *tempo +1;
    G->d[u]=*tempo;
    
    Cell * aux= G->adj[u]->head; // lista de adj de u
    while(aux!=NULL){
        v=aux->key; // v vai ser o adj
        if (G->cor[v]==0){//checando adjacentes n visitados
            G->pi[v]=u;
            visitar_vertice(G, v, tempo); //visita o v
        }
        aux=aux->next;
    }
    
    G->cor[u]=2; //preto
    *tempo= *tempo +1;
    G->f[u]=*tempo;
            
}
void busca_profundidade(GrafoLA *G){
    int u, tempo=0;
    
    for (u=0; u < G->V; u++){
        G->cor[u]=0; //branco
        G->pi[u]= -1;
    }
    
    for(u=0; u< G->V; u++){
        if (G->cor[u]==0)
            visitar_vertice(G, u, &tempo);
    }
}

void imprimir_resultados(GrafoLA *G){
    int v;
    
    printf("v d f p\n");
    
    for(v=0; v< G->V; v++){
        printf("%d %d %d ", v, G->d[v], G->f[v]);
        
        if(G->pi[v]>=0)
            printf("%d\n", G->pi[v]);
        else
            printf ("-\n");
    }
}

int main() {
    int nV;
    int vert, i;
    
    scanf("%d", &nV);
    GrafoLA* G=iniciar_grafoLA(nV);
        
    for (i=0; i<nV; i++){
       
     scanf("%d", &vert);
     while(vert !=-1){
        
        if (vert == -1) {
            break; 
        }

        inserir_na_lista(vert, G->adj[i]); 
        scanf("%d", &vert);
        }
        
    }
    
    
    
    busca_profundidade(G);
    imprimir_resultados(G);
    
    
    return 0;
}

