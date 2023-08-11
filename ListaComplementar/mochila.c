#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>


# força-bruta
int mochila_fb(int c[], int p[], int n, int b, int i, int max){
    int c1, c2;

    if (i >= n){
        if (b < 0)
            return 0;
        else
            return max;
    }else{
        c1 = mochila_fb(c, p, n, b, i + 1, max); //ignora o item na posição 1

        c2 = mochila_fb(c, p, n, b - p[i], i + 1, max + c[i]); // atualiza a capacidade b, e o custo da mochila c[i]

        return c1 > c2 ? c1 : c2;

    }
}

//não gera soluções invalidas
# backtracking
int mochila_bkt(int c[], int p[], int n, int b, int i, int max){
    int c1, c2;

    if (b < 0)//capacidade foi extrapolada
        return 0;
    else if (i < n){ // itens não foram totalmente explorados
        c1 = mochila_bkt(c, p, n, b, i + 1, max);

        c2 = mochila_bkt(c, p, n, b - p[i], i + 1, max + c[i]);//p[i] peso c[i] custo

        return c1 > c2 ? c1 : c2;
    }else
        return max;
}


# branch-and-bound
int mochila_bnb(int c[], int p[], int n, int b, int i){
    int c1, c2;

    if ((i < n) && (b > 0)){
        c1 = mochila_bnb(c, p, n, b, i + 1);

        if (b - p[i] >= 0) // verifica se add outro item n vai extrapolar e n perde tempo fazendo a chamada
            c2 = c[i] + mochila_bnb(c, p, n, b - p[i], i + 1);
        else
            c2 = 0;

        return c1 > c2 ? c1 : c2;
    }

    return 0;
}






int mochila(int c[], int p[], int n, int b){
    return mochila_bkt(c, p, n, b, 0);
}




int main() {
    int b, n, i;
    scanf("%d", &b);
    scanf("%d", &n);
    int p[n], v[n];

    for(i=0; i<n; i++){
         scanf("%d %d", &p[i], &v[i]);
    }



    printf("%d ", mochila_fb(v, p, n, b));
}
