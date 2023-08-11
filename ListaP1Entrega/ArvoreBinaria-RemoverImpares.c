/*Implemente uma função que receba uma árvore binária de busca e remova todos os nós ímpares.

Input Format

Na primeira linha deve ser lido o número inteiro N, que é referente à quantidade de nós da árvore binária de busca. Em seguida, em cada linha deve ser lido um número inteiro para ser inserido como nó na árvore (fazer isso até que N números sejam lidos).

Constraints

.

Output Format

Após a remoção, imprimir o valor da chave de cada nó em uma única linha considerando o percurso pré-ordem.

Sample Input 0

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
Sample Output 0

50 20 32 72*/
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

Node* minValueNode(Node* node)
{
    Node* current = node;
 
    /* loop down to find the lef tmost leaf */
    while (current && current->left != NULL)
        current = current->left;
 
    return current;
}

Node* remover(Node* tree, int item)
{
    // base case
    if (tree == NULL)
        return tree;
 
    // If the key to be deleted
    // is smaller than the tree's
    // key, then it lies in left subtree
    if (item < tree->item)
        tree->left = remover(tree->left, item);
 
    // If the key to be deleted
    // is greater than the tree's
    // key, then it lies in right subtree
    else if (item > tree->item)
        tree->right = remover(tree->right, item);
 
    // if key is same as tree's key,
    // then This is the node
    // to be deleted
    else {
        // node with only one child or no child
        if (tree->left == NULL) {
            Node* temp = tree->right;
            free(tree);
            return temp;
        }
        else if (tree->right == NULL) {
            Node* temp = tree->left;
            free(tree);
            return temp;
        }
 
        // node with two children:
        // Get the inorder successor
        // (smallest in the right subtree)
        Node* temp = minValueNode(tree->right);
 
        // Copy the inorder
        // successor's content to this node
        tree->item = temp->item;
 
        // Delete the inorder successor
        tree->right = remover(tree->right, temp->item);
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
    //coloca -1 nos impares
Node* marca_impar(Node * tree){

    if (tree != NULL){
 
    if(tree->item % 2 != 0){
            tree->item = -1;
    }
        marca_impar(tree->left);
        marca_impar(tree->right);
    }
    return tree;
}
    //tira o -1 da arvore
Node* remove_impar(Node * tree){

    if (tree != NULL){
         tree->left = remove_impar(tree->left);
         tree->right = remove_impar(tree->right);
        
        if(tree->item==-1){
            tree = remover( tree,tree->item);
        }
         
    }
    
    return tree;
}


//implementar uma func que identifique impares, enquanto existir, remove os impares

int main() {
    int n, item;
    Node *tree =NULL;

    scanf("%d", &n);

    while(n>0){
        
        scanf("%d", &item);
        

        tree= inserir(item, tree);
        n--;
    }
    
    tree= marca_impar(tree);
    tree=remove_impar(tree);

    imprimirPrefix(tree);

    liberar_arvore(tree);

    return 0;
}