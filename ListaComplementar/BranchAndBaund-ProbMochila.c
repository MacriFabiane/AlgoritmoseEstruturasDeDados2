/*Considere n itens a serem levados para uma viagem, dentro de uma mochila de capacidade b. Cada item x_j tem um peso a_j e um valor c_j. Implemente uma função, utilizando branch-and-bound, que calcule o valor máximo de objetos que podem ser carregados dentro da mochila.

Input Format

Na primeira linha deve ser lido um número inteiro que represente a capacidade da mochila.

Na próxima linha, deve ser lido um outro número (N) referente à quantidade de objetos disponíveis.

Em seguida, nas N linhas restantes devem ser lidos o peso e o valor (logo em sequência) de cada objeto.

Constraints

.

Output Format

O valor máximo de objetos que a mochila possa carregar.*/
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
// b = capacidade, p=peso, n=nitens, c=custo
int mochila_bnb(int *p, int *c, int n, int b, int i){ // i qual item esta sendo analisado
    int c1, c2;

    if((b>0) && (i<n)){
        c1= mochila_bnb(p, c,  n,  b, i+1);

        if (b-p[i]>=0)
            c2= c[i] + mochila_bnb(p, c,  n,  b-p[i], i+1);

        else
            c2=0;

        return (c1> c2)? c1 :c2;
    }
    else
        return 0;
}

int main() {
    int i, n, b;
        int *p, *c;

        scanf("%d", &b);
        scanf("%d", &n);

        p= (int*)malloc(sizeof(int)*n);
        c= (int*)malloc(sizeof(int)*n);

        for(i=0; i<n; i++)
            scanf("%d %d", &p[i], &c[i]);

        printf("%d", mochila_bnb(p,c,n,b, 0));

        free(p);
        free(c);
    return 0;
}
