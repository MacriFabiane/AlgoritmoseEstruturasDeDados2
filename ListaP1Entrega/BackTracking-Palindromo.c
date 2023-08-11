/*mplemente uma função que receba, pelo menos, uma string como parâmetro. A função deverá procurar, utilizando a estratégia de backtracking ou branck-and-bound, o maior palíndromo possível dentro da string e imprimí-lo na saída.

Input Format

Leia uma string.

Constraints

.

Output Format

Imprima o maior palíndromo encontrado dentro da string.

Sample Input 0

caaabbaabc
Sample Output 0

aabbaa
Sample Input 1

abc
Sample Output 1

a*/
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
void maior_palindromobtk(char str[], int ini, int fim, int *maior, int *inipali) {

    // analisar caso em que foi per corrido tudo  e nao achado nada
    if(ini>fim){
         return;
      }
    //analisar o caso de ter palindromos

    if(str[ini]==str[fim]){
        int ePalindromo = 1;
        //verifica se a subs strings sao palindromos
        for(int i=ini+1, j=fim-1; i<=j; i++, j--) {//inicializa aqui i e j
            if(str[i] != str[j]) {
                ePalindromo = 0;
                break;
            }
        }

        if (ePalindromo && fim - ini+1 > *maior) {
             *maior = (fim - ini+1);
             *inipali = ini; // posicao inicial
        }
        }

        maior_palindromobtk(str,ini+1, fim, maior, inipali);
        maior_palindromobtk(str, ini, fim-1, maior, inipali);  //faz 2 caminhos/galhos um q anda so o ini e outro so fim

    }

void imprime (char str[], int ini, int tam) {
    for (int i = ini; i <ini + tam; i++) {
        printf("%c", str[i]);
    }
}
int main() {
    char str[50];
    int n, maior=1, inipali=0;


    scanf("%s", str);

    n=strlen(str);
    maior_palindromobtk(str,0, n-1, &maior, &inipali);
    imprime(str, inipali, maior);



    return 0;
}
