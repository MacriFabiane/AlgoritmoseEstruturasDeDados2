/*Implemente uma função que receba uma árvore binária. A função deverá verificar se árvore é cheia ou não.

Input Format

Na primeira linha deve ser lido o número inteiro N, que é referente à quantidade de nós da árvore binária de busca. Em seguida, em cada linha deve ser lido um número inteiro para ser inserido como nó na árvore (fazer isso até que N números sejam lidos).

Constraints

.

Output Format

Imprimir "sim", caso a árvore esteja cheia. Imprimir "nao", caso contrário.

Sample Input 0

8
10
3
14
1
7
13
4
8
Sample Output 0

nao
Sample Input 1

7
10
4
14
1
7
13
15
Sample Output 1

sim*/
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>

typedef struct Node Node;

struct Node{
    int item;
    struct Node *left;
    struct Node *right;
};


Node* criar(int item){
    Node * tree = (Node *) malloc(sizeof(Node));

    tree->item = item;
    tree->left = NULL;
    tree->right = NULL;

    return tree;
}


Node* pesquisar(int item, Node* tree){
    if (tree != NULL){
        if (item == tree->item)
            return tree;
        else if (item < tree->item)
            return pesquisar(item, tree->left);
        else
            return pesquisar(item, tree->right);
    }else
        return NULL;
}


int min(Node* tree){
    Node* aux = tree;

    if (aux != NULL){
        while (aux->left != NULL)
            aux = aux->left;

        return aux->item;
    }

    return INT_MIN;
}


int max(Node* tree){
    Node* aux = tree;

    if (aux != NULL){
        while (aux->right != NULL)
            aux = aux->right;

        return aux->item;
    }

    return INT_MAX;
}



Node* inserir(int item, Node* tree){
    if (tree == NULL)
        tree = criar(item);
    else if (item < tree->item)
        tree->left = inserir(item, tree->left);
    else if (item > tree->item)
        tree->right = inserir(item, tree->right);

    return tree;
}


Node* remover(int item, Node* tree){
    Node *aux, *auxP, *auxF;

    if (tree != NULL){
        if (item < tree->item)
            tree->left = remover(item, tree->left);
        else if (item > tree->item)
            tree->right = remover(item, tree->right);
        else{
            aux = tree;

            if (aux->left == NULL)
                tree = tree->right;
            else if (aux->right == NULL)
                tree = tree->left;
            else{
                auxP = aux->right;
                auxF = auxP;

                while (auxF->left != NULL){
                    auxP = auxF;
                    auxF = auxF->left;
                }

                if (auxP != auxF){
                    auxP->left = auxF->right;
                    auxF->left = aux->left;
                }

                auxF->right = aux->right;

                tree = auxF;
            }

            free(aux);
        }
    }

    return tree;
}


void imprimirInfix(Node* tree){
    if (tree != NULL){
        imprimirInfix(tree->left);
        printf("%i\n", tree->item);
        imprimirInfix(tree->right);
    }
}


void imprimirPrefix(Node* tree){
    if (tree != NULL){
        printf("%i\n", tree->item);
        imprimirPrefix(tree->left);
        imprimirPrefix(tree->right);
    }
}


void imprimirPosfix(Node* tree){
    if (tree != NULL){
        imprimirPosfix(tree->left);
        imprimirPosfix(tree->right);
        printf("%i\n", tree->item);
    }
}


void liberar_arvore(Node* tree){
    if (tree != NULL){
        liberar_arvore(tree->left);
        liberar_arvore(tree->right);
        free(tree);
    }
}

int altura(Node *tree){
    int e, d; //esquerda direita
    
    if(tree==NULL){
        return -1;
    }
    else{
        e= altura(tree->left) +1 ;
        d= altura(tree->right) +1;
        
        // return ((e > d) ? e : d)+1; //se e > retorna e : caso contrario d sem o +1 do e e d
        return (e > d) ? e : d;
    }
}
int n_nos_abb_cheia(int n){
    return (int) pow(2, n +1)-1; // n = altura pow-dubble
}

int contar_nodes(Node *tree){
    if(tree == NULL)
        return 0;
    else
        return 1 + contar_nodes(tree->left)+contar_nodes(tree->right);
}

int arvore_cheia(Node *tree){
    return contar_nodes(tree) == n_nos_abb_cheia(altura(tree));
}

int main() {
    int n, item;
    Node *tree =NULL;

    scanf("%d", &n);

    while(n>0){
        scanf("%d", &item);

        tree= inserir(item, tree);

        n--;
    }
    
    if(arvore_cheia(tree))
        printf("sim");
    else
        printf("nao");

  
    liberar_arvore(tree);



    return 0;
}