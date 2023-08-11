/*Implemente uma função que receba uma árvore binária de busca. A função deverá imprimir o percurso da árvore nas seguintes forma: pré-ordem, ordem simétrica e pós-ordem.

Input Format

Na primeira linha deve ser lido o número inteiro N, que é referente à quantidade de nós da árvore binária de busca. Em seguida, em cada linha deve ser lido um número inteiro para ser inserido como nó na árvore (fazer isso até que N números sejam lidos).

Constraints

.

Output Format

Nas três linhas, imprimir o seguinte percurso em sequência: pré-ordem, ordem simétrica e pós-ordem.

Sample Input 0

7
4
2
6
1
3
5
7
Sample Output 0

4 2 1 3 6 5 7
1 2 3 4 5 6 7
1 3 2 5 7 6 4
Sample Input 1

10
41
20
11
29
32
65
50
91
72
99
Sample Output 1

41 20 11 29 32 65 50 91 72 99 
11 20 29 32 41 50 65 72 91 99 
11 32 29 20 50 72 99 91 65 41*/
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
        printf("%i ", tree->item);
        imprimirInfix(tree->right);
    }
}


void imprimirPrefix(Node* tree){
    if (tree != NULL){
        printf("%i ", tree->item);
        imprimirPrefix(tree->left);
        imprimirPrefix(tree->right);
    }
}


void imprimirPosfix(Node* tree){
    if (tree != NULL){
        imprimirPosfix(tree->left);
        imprimirPosfix(tree->right);
        printf("%i ", tree->item);
    }
}


void liberar_arvore(Node* tree){
    if (tree != NULL){
        liberar_arvore(tree->left);
        liberar_arvore(tree->right);
        free(tree);
    }
}

int main() {
    int n, item;
    
    Node *tree = NULL;
    
    scanf("%d", &n);
    
    while(n>0){
        scanf("%d", &item);
        
        tree = inserir(item, tree);
        n--;
    }
    imprimirPrefix(tree);
    printf("\n");
    imprimirInfix(tree);
    printf("\n");
    imprimirPosfix(tree);
     
    liberar_arvore(tree);
    return 0;
}
