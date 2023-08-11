/*Implemente uma função, utilizando divisão e conquista, que calcule a potência de um número inteiro

Input Format

Devem ser lidos, na primeira linha, dois números inteiros ("a" e "b") que sejam >=0.

Constraints

.

Output Format

Um número inteiro resultante da operação "a^b" ("a" elevado a "b")

Sample Input 0

2 3
Sample Output 0

8
Sample Input 1

3 4
Sample Output 1

81*/
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int pot(int a, int n){
    int x;

    if (n == 0){
        return 1; // a^0 =1
    }
    else if (n == 1){
        return a; // a^1=a
    }
    else if (n % 2 == 0){ // se par
        x = pot(a, n / 2);
        return x * x;
    }
    else{ //se impar
        x = pot(a, (n - 1) / 2);
        return a * x * x;
    }
}

int main() {
    int a, b;

    scanf("%d %d", &a, &b); //leitura

    printf("%d", pot(a, b));

    return 0;
}
