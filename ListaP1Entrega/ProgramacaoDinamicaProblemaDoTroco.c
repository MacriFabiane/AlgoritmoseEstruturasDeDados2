/*Dado um conjunto de moedas e um valor de troco que deve ser dado utilizando essas moedas. Em vez de tentarmos obter a quantidade mínima de moedas, dessa vez, o nosso interesse poderia ser definir as formas a quantidade de formas possíveis para devolvermos o troco. Por exemplo, para o troco de valor 5 e o conjunto de moedas {1,2,3,4} existem 6 formas diferentes para retornarmos o troco: {1,1,1,1,1}, {1,1,1,2}, {1,1,3}, {1,4}, {1,2,2}, {2,3}.

Em uma estratégia parecida com a da mochila binária, podemos utilizar a programação dinâmica para encontrarmos a quantidade possíveis de formas para devolvermos o troco a partir de um conjunto de moedas. Implemente uma função, utilizando programação dinâmica, que retorne a quantidade de possibilidades para retornar um valor de troco utilizando um conjunto de moedas.

Input Format

A primeira linha deve conter o valor do troco (T).

A segunda linha deve conter a quantidade de moedas (N).

Na terceira linha, ler o conjunto de N moedas.

Constraints

.

Output Format

Imprimir a quantidade de formas possíveis que o valor do troco T pode ser devolvido a partir do conjunto de moedas.

Sample Input 0

5
4
1 2 3 4
Sample Output 0

6*/
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int possib_troco(int t, int moedas[], int n) {
    int dp[t+1][n+1]; // matriz de possibilidades

    for (int j = 0; j <= n; j++) {
        dp[0][j] = 1; // troco igual a 0 so tem uma maneira de dar o troco q e no dar nada
    }
    for (int i = 1; i <= t; i++) {
        dp[i][0] = 0;// sem moedas sem troco
    }

    for (int i = 1; i <= t; i++) {//troco
        for (int j = 1; j <= n; j++) { //moedas
            if (moedas[j-1] <= i) { //se a moeda  for menor= q o troco da pra usar
                dp[i][j] = dp[i][j-1] + dp[i-moedas[j-1]][j]; //dp[i-coins[j-1]][j] troco - moeda att, e o nro de maneiras de obter a quantia (i - coins[j-1]) usando as primeiras j moedas 
            } else {
                dp[i][j] = dp[i][j-1]; 
            }
        }
    }

    return dp[t][n];
}

int main() {
    int n, t;
    scanf("%d", &t);
    scanf("%d", &n);
    int moedas[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &moedas[i]);
    }
    printf("%d\n", possib_troco(t, moedas, n));  
    return 0;
}

