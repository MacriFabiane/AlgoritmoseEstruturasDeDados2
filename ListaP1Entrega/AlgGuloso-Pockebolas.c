/*Em dias de folga, um grupo de treinadores pokemon deixam seus monstrinhos livres de suas pokebolas. Em alguns casos, cada pokemon devem retornar a uma pokebola o mais r�pido poss�vel, ou seja, eles se deslocam para a pokebola mais pr�xima. Para simplificar a representa��o desse problema, dados N pokemons e N pokebolas, onde cada pokebola comporta apenas um pokemon. Suponha que cada pokemon desloque em linha reta para chegar na pokebola e o deslocamento de uma posi��o x para x + 1 leva 1 segundo. Por exemplo, se um pokemon est� na posi��o 2 e a pokebola na posi��o 7, ent�o o pokemon precisa de 5 segundos para chegar na pokebola. Caso a posi��o do pokemon e da pokebola sejam iguais, n�o � necess�rio fazer o deslocamento. Implemente uma fun��o, utilizando a estrat�gia gulosa, para o retorno dos pokemons �s pokebolas de forma em que o tempo para �ltimo pokemon entrar na pokebola seja minimizado.

Input Format

Na primeira linha deve ser lido um n�mero inteiro N.

Na segunda linha deve ser lido a posi��o de cada um dos N pokemons.

Na terceira linha deve ser lido a posi��o de cada uma das N pokebolas.

Constraints

.

Output Format

Imprimir o tempo m�nimo para que todos os pokemons estejam na pokebola.

Sample Input 0

10
-85 78 -16 23 -45 -70 -99 -112 20 0
2 18 -29 14 73 -50 -19 34 -67 90
Sample Output 0

56
Sample Input 1

8
-10 -79 -79 67 93 -85 -28 -94
-2 9 69 25 -31 23 50 78
Sample Output 1

102*/
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include<limits.h>
void insertsort(int v[], int n){
    int i, x, j;

    for (i = 1; i < n; i++){
        x = v[i];

        for (j = i - 1; (j >= 0) && (x  < v[j]); j--)
            v[j + 1] = v[j];

        v[j + 1] = x;
    }
}

void menor_tempo(int *pk, int *pp, int n){
    int i, xn, menor = 0;

    insertsort(pp, n);
    insertsort(pk, n);

    for(i = 0; i < n; i++){
                xn= abs (pk[i]-pp[i]);
                if(xn > menor){
                    menor = xn;
            }
    }


        printf("%d\n", menor);
}

int main() {

    int n, *pk, *pp, i;

    scanf ("%d", &n);

    pk= (int*)malloc(sizeof(int)*n);
    pp= (int*)malloc(sizeof(int)*n);

    for(i=0; i<n; i++){
        scanf("%d", &pk[i]);
    }

      for(i=0; i<n; i++){
        scanf("%d", &pp[i]);
    }

    menor_tempo(pk, pp, n);

    free(pk);
    free(pp);

    return 0;
}
