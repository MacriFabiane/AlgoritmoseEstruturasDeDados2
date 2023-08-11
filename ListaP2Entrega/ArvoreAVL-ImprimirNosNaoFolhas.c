/*Implemente uma função que receba uma árvore AVL. A função deverá imprimir todos nós que não são folhas.

Input Format

Na primeira linha deve ser lido o número inteiro N, que é referente à quantidade de nós da árvore binária de busca. Em seguida, em cada linha deve ser lido um número inteiro para ser inserido como nó na árvore (fazer isso até que N números sejam lidos).

Constraints

.

Output Format

Imprimir em uma única linha, os nós não folha da árvore, considerando o percurso pré-ordem.

Sample Input 0

10
22
15
12
18
30
34
54
46
62
91
Sample Output 0

22 15 54 34 62*/
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

typedef struct NodeAVL NodeAVL;

struct NodeAVL{
    int item;
    int fb;
    struct NodeAVL *left; 
    struct NodeAVL *right;
};


NodeAVL* criar_AVL(int item){
    NodeAVL * tree = (NodeAVL *) malloc(sizeof(NodeAVL));

    tree->item = item;
        tree->fb = 0;
    tree->left = NULL;
    tree->right = NULL;

    return tree;
}


static NodeAVL* rotateL(NodeAVL *tree){
    NodeAVL *auxA = tree->left, *auxB;

    if (auxA->fb == +1){
        tree->left = auxA->right;
        auxA->right = tree;
        tree->fb = 0;
        tree = auxA;
    }else{
        auxB = auxA->right;
        auxA->right = auxB->left;
        auxB->left = auxA;
        tree->left = auxB->right;
        auxB->right = tree;

        if (auxB->fb == +1)
            tree->fb = -1;
        else
            tree->fb = 0;

        if (auxB->fb == -1)
            auxA->fb = +1;
        else
            auxA->fb = 0;

        tree = auxB;
    }
    
    return tree;
}


static NodeAVL* rotateR(NodeAVL *tree){
    NodeAVL *auxA = tree->right, *auxB;

    if (auxA->fb == -1){
        tree->right = auxA->left;
        auxA->left = tree;
        tree->fb = 0;
        tree = auxA;
    }else{
        auxB = auxA->left;
        auxA->left = auxB->right;
        auxB->right = auxA;
        tree->right = auxB->left;
        auxB->left = tree;

        if (auxB->fb == -1)
            tree->fb = +1;
        else
            tree->fb = 0;

        if (auxB-> fb == +1)
            auxA->fb = -1;
        else
            auxA->fb = 0;

        tree = auxB;
    }
    
    return tree;
}



NodeAVL* inserirAVL(NodeAVL* tree, int value, int *grown){
    NodeAVL *auxA, *auxB;

    if(tree == NULL){
        tree = criar_AVL(value);

        *grown = 1;

    }else if (value < tree->item){
        tree->left = inserirAVL(tree->left, value, grown);

        if (*grown){
            switch (tree->fb){
                case -1: tree->fb = 0; *grown = 0; break;
                case 0: tree->fb = +1; break;
                case +1: tree = rotateL(tree); tree->fb = 0; *grown = 0;
            }
        }
    }else if (value > tree->item){
        tree->right = inserirAVL(tree->right, value, grown);

        if (*grown){
            switch (tree->fb){
                case +1: tree->fb = 0; *grown = 0; break;
                case 0: tree->fb = -1; break;
                case -1: tree = rotateR(tree); tree->fb = 0; *grown = 0;
            }
        }
    }

    return tree;
}
void imprimirPrefixAVL(NodeAVL* tree){
    if (tree != NULL){
        printf("%d ", tree->item);
        imprimirPrefixAVL(tree->left);
        imprimirPrefixAVL(tree->right);
    }
}
void imprimirNaoFolhas(NodeAVL* tree){
    if (tree != NULL){
        if(tree->left!=NULL || tree->right!=NULL){
            printf("%d ", tree->item);
            imprimirNaoFolhas(tree->left);
            imprimirNaoFolhas(tree->right);
        }
    }
    
}

int main() {
    int n, item;
    NodeAVL *tree=NULL;
    int grown=0;
    
    
    scanf("%d", &n);
    while(n>0){
        scanf("%d", &item);
        tree=inserirAVL(tree, item, &grown);
        n--;
    }
    
    imprimirNaoFolhas(tree);
    
    return 0;
}
