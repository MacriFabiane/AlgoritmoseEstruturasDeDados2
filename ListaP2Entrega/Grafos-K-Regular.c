/*Implemente uma função para verificar se um grafo representado por listas de ajacência é k-regular. Se o grafo for k-regular, a função deve retornar o valor de k. Se o grafo não for k-regular, a função deve retornar 0.

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

Imprimir "grafo k-regular com k=valor" caso o grafo seja regular ou imprimir "grafo nao k-regular", caso contrário.

Sample Input 0

8
1 3 -1
0 2 -1
1 -1
0 4 5 -1
3 5 6 -1
3 4 6 7 -1
4 5 7 -1
5 6 -1
Sample Output 0

grafo nao k-regular
Sample Input 1

6
1 2 3 -1
0 2 3 -1
0 1 4 -1
1 4 5 -1
2 3 5 -1
0 3 4 -1
Sample Output 1

grafo k-regular com k=3*/
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
typedef struct Cell Cell;

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
   Lista **adj; 
}GrafoLA;


Lista* criar_lista(){
    Lista* l = (Lista*) malloc(sizeof(Lista));

    l->head = NULL;

    return l;
}


Cell* criar_celula(int key){
    Cell *c = (Cell*) malloc(sizeof(Cell));
    c->key = key;

    c->next = NULL;

    return c;
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

int Kregular (GrafoLA * G){
    int i, k=0,cont;
    Cell * aux;
    
    aux = G->adj[0]->head;

    while (aux!= NULL) {
        k++; // ve o grau do primeiro vertice
        aux = aux->next;
    }

    for (i=1; i<G->V; i++){
        aux=G->adj[i]->head;
        cont=0;
        
        while (aux!=NULL){
            cont++;
            aux=aux->next;
        }
        if(cont!=k){ //ve se o grau dos subsequentes sao diferentes do primeiro
          return 0;
        }

    }
    
    return k;
}

int main() {
    int nV;
    int vert, i, k;
    
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
    
    k= Kregular(G);
    if(k!=0){
        printf("grafo k-regular com k=%d", k);
    }
    else
        printf("grafo nao k-regular");
    
    
    
      
    return 0;
}
