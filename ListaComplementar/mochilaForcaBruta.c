/*Considere n itens a serem levados para uma viagem, dentro de uma mochila de capacidade b. Cada item x_j tem um peso a_j e um valor c_j. Implemente uma função, utilizando força-bruta, que calcule o valor máximo de objetos que podem ser carregados dentro da mochila.

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

int mochila_fb(int p[], int c[], int n, int b, int i, int custo){
    int c1, c2;

    if(i >= n){ //ate todos os itens serem percorridos
        if(b < 0) // nada foi add
            return 0;
        else
            return custo;
    }
    else{
        c1 = mochila_fb(p, c, n, b, i + 1, custo); //peso, valor, n item, capacidade
        c2 = mochila_fb(p, c, n, b - p[i], i + 1, custo + c[i]); // peso, valor, n item, att capacidade-peso item,i, attcusto
        return(c1 > c2) ? c1 : c2;
    }
}

int main() {
    int b, n, i, *p, *c;

    scanf("%d", &b); // capacidade
    scanf("%d", &n); // numero de itens

    p = malloc(sizeof(int) * n);
    c = malloc(sizeof(int) * n);

    for(i = 0; i < n; i++){
        scanf("%d %d", &p[i], &c[i]); // peso e valor de cada item
    }

    printf("%d", mochila_fb(p, c, n, b, 0, 0));

    free(p);
    free(c);

    return 0;
}
