/*Considere n itens a serem levados para uma viagem, dentro de uma mochila de capacidade b. Cada item x_j tem um peso a_j e um valor c_j. Implemente uma função, utilizando programação dinâmica, que calcule o valor máximo de objetos que podem ser carregados dentro da mochila.

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

#define max(a,b) a > b? a : b

int mochila (int p[], int c[], int n, int b){
    int i, j, mat [b+1][n+1]; // coluna item

    for (i =0; i<=b; i++)
        mat[i][0]=0;
    //coluna peso item
    for(j=1; j<=n; j++){
        //linha capacidade
        for(i=0; i<=b; i++ ){
            if(i - p[j-1]<0) //capacidade estrapolada  j-1 pois ignoramos a primeira coluna que vai ser 0
                mat[i][j]= mat[i][j-1]; // se estrapolada volta pra casa anterior
            else
                mat [i][j]=max(mat[i][j-1], c[j-1]+mat[i - p[j - 1]][j-1]);

        }
    }
    return mat[b][n]; // ultima linha/coluna tem melhor result
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

    printf("%d", mochila(p,c,n,b));

    free(p);
    free(c);

    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    return 0;
}
