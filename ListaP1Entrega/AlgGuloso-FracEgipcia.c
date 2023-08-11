/*Uma fra��o pode representada pela soma de um conjunto de fra��es unit�rias, onde o numerador � igual a 1 (um). Exemplos:

8/11 � equivamente a 1/2 + 1/5 + 1/37 + 1/4070.

7/3 � equivamente a 2 + 1/3.

Essas fra��es unit�rias podem ser geradas utilizando uma estrat�gia gulosa. Dado dois n�meros inteiros: n (numerador) e d (demoninador).

Se d > n, o denominador da maior fra��o unit�ria � dada da seguinte forma: 1 / (d / n + 1). Ap�s, pode ser feita uma chamada recursiva, cuja fra��o de entrada deve ser equivalente a (n / d) - (1 / (d / n + 1)), que � igual a uma outra fra��o: (n * (d / n + 1) - d) / (d * (d / n + 1)). Por exemplo, para o 8/11, a primeira fra��o unit�ria � 1 / (d / n + 1) = 1 / (11 / 8 + 1) = 1/2. Em seguida, pode ser feita uma chamada recursiva para 8/11 - 1/2 = 5/22, ou seja, (8 * (11/8 + 1) - 11) / ((11/8 + 1) * 11) = 5/22.

Se d < n, o resultado � um n�mero inteiro mais uma fra��o resultante da chamada recursiva para seguinte fra��o: (n % d) / d. Por exemplo, para 7/3, o numerador � maior, ou seja, primeiro dever� ser impresso a parte inteira da divis�o (2). Em seguinda, fazer uma chamada recursiva para (n % d) / n = (7 % 3) / 3 = 1/3.

Os crit�rios de parada s�o:

d % n == 0

n % d == 0

Implemente uma fun��o que receba, pelo menos, dois n�meros inteiros que represente uma fra��o. A fun��o dever� imprimir o somat�rio de fra��es unit�rias e/ou n�meros inteiros cujo resultado � a fra��o de entrada.

Input Format

Ler dois n�meros inteiros: numerador seguido do denominador.

Constraints

.

Output Format

Imprimir o somat�rio.*/
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

void frac_egipt(int n, int d){// n=numerador, d= denominador
    int aux;

    if((n>0) && (d>0)){
        if((d%n)==0)
            printf("1/%d", d/n);
        else if (n%d==0){
            printf("%d", n/d);
        }
        else if (n>d){
            printf("%d +", n/d);
            frac_egipt(n % d, d);
        }
        else{
            aux = d / n + 1;

            printf("1/%d + ", aux);

            frac_egipt(n* aux - d, d*aux);
        }
    }

}

int main() {
    int n, d;

    scanf("%d %d", &n, &d);

    frac_egipt(n, d);

    return 0;
}
