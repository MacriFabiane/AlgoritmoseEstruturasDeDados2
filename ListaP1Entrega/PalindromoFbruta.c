/*Implemente uma função que receba, pelo menos, uma string como parâmetro. A função deverá procurar, utilizando a estratégia de força-bruta, o maior
palíndromo possível dentro da string e imprimí-lo na saída.

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


void maior_palindromo(char str[]) {
    int n = strlen(str),ini= 0, i, j, k;
    int maior = 1;//comeca em 1 pq qualquer letra serve

    // Ve se a string e um palindromo por completo tipo arara
    for (i = 0, j = n - 1; i < j; i++, j--) { // i<j ignora a letra do meio se for impar
        if (str[i] != str[j]) {
            break;
        }
    }
    if (i >= j) { //>= pq se for impar i> e = se for par
        printf("%s", str);
        return;
    }

    // caso pali tamanho impar
    for (k = 1; k < n; k++) { //comeca em 1 e termina em n-1 pra ter margem
        for (i = k - 1, j = k + 1; i >= 0 && j < n; i--, j++) { //i vai analizar uma casa antes de k e j uma depois, assim por diante
            if (str[i] != str[j]) {
                break;
            }
        }
        if (j - i - 1 > maior) {//j-1-i define o tam do palindromo encontrado
            maior = j - i - 1;
            ini = i + 1; // posicao inicial
        }
    }

    // pali tamanho par
    for (k = 1; k < n; k++) {
        for (i = k - 1, j = k; i >= 0 && j < n; i--, j++) {//comeca analisando um par sem excluir o k já que j=k
            if (str[i] != str[j]) {
                break;
            }
        }
        if (j - i - 1 > maior) {
            maior = j - i - 1;
            ini = i + 1;
        }
    }

    for (int i = ini; i < ini + maior; i++) {
    printf("%c", str[i]);
  }

}

int main() {
    char str[50];

    scanf("%s", str);

    maior_palindromo(str);

    return 0;
}
