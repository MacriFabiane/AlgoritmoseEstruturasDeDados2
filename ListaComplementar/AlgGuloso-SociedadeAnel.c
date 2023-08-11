/*Bilbo teve uma uma missão de levar um anel mágico para ser destruído em um vulcão. Nessa jornada, Bilbo deve percorrer um campo cheio de obstáculos. Esse campo pode ser representado por uma matriz de números inteiros (M), onde cada elemento representa um custo para ser acessado a partir dos elementos na vizinhança. Por exemplo, se M[3][3] = 5, então o custo para o deslocamento de M[2][3], M[3][4], M[4][3], ou M[3][2] para M[3][3] é 5. O Bilbo mora na posição M[0][0], que tem custo zero, pois é de sua casa que ele iniciará a aventura. O vulcão fica em um lugar distante da casa de Bilbo e pelo que se sabe, está localizado na posição M[l - 1][c - 1], onde l é o número de linhas e c é o número de colunas da matriz. Bilbo é um cara preguiçoso e a partir do lugar que ele se enconcontra, vai para o lugar menos custoso, mas ele é persistente e não reconsidera a sua decisão. Implemente uma função gulosa que calcule o custo do caminho do Bilbo até o vulcão.

Input Format

A primeira linha contém a quantidade de linhas (l) e de colunas (c) da matriz. A partir da próxima linha, deve ser lida uma matriz l x c de números inteiros.

Constraints

Na matriz não deve ser permitido delocamento pela diagonal. Por exemplo, se Bilbo estiver na posição M[3][3], ele não pode ir para M[2][2], M[2][4], M[4][4] ou M[4][2] a partir de M[3][3]. Em outras palavras, apenas é possível deslocar para cima, baixo, esquerda ou direita.

Output Format

O custo total do deslocamento de M[0][0] até M[l - 1][c - 1] utilizando solução gulosa. Caso M[l - 1][c - 1] não seja alcançado, imprimir "sem solucao".

Sample Input 0

6 6
0 1 2 3 4 5
2 1 3 2 1 4
1 3 4 5 2 1
1 2 2 6 7 5
3 4 1 3 5 6
1 4 2 1 2 3
Sample Output 0

19*/
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>

int proximo_passo(int **m, int l, int c, int *lp, int *cp){
    int i, menor = INT_MAX; // menor e inicializado com intmax pois e alg gulososo entao e
    int al, ac;
    int ml = *lp;
    int mc = *cp;
    int movX[] = {-1, 0, 1, 0};
    int movY[] = {0, -1, 0, 1};

    for(i = 0; i < 4; i++){
        al = *lp + movX[i]; // al e ac novas coordenadas
        ac = *cp + movY[i];

        if((al >= 0) && (al < l) && (ac >= 0) && (ac < c) && (menor > m[al][ac])){ // ve se as new coord sao validas
            ml = al; //Se a posicao adjacente atual tiver um custo menor que o menor custo encontrado ate o momento, atualiza-se as coordenadas (ml e mc) e o menor custo (menor).
            mc = ac;
            menor = m[ml][mc];
        }
    }
    *lp = ml;  // atualiza-se lp e lc com as coord de menor custo
    *cp = mc;

    return menor; // retorna o menor custo
}

int percurso(int **m, int l, int c, int lp, int cp, int custo){
    int aux;

    if((lp == l - 1) && (cp == c - 1)){ // lp linha prox cp prox
        return custo;
    }
    else{ // caso nao tenha chegado no fim vai marcar a posicao como visitada
        m[lp][cp] = INT_MAX;// colocando o valor maximo na posicao

        aux = proximo_passo(m, l, c, &lp, &cp); // tenta achar o proximo passo com menor custo

        if(aux < INT_MAX){ // se tiver menor custo
            return percurso(m, l, c, lp, cp, custo + m[lp][cp]); // chama de novo percurso com a posicao e custo att
        }
        else{
            return INT_MAX; // Se a prox posicao adjacente tiver um custo igual a INT_MAX, significa que n ha caminho possivel a partir desta posicao, entao a funcao retorna INT_MAX para indicar que nao ha solucao viavel
        }
    }
}

int main() {
    int l, c, **m, i, j, r;

    scanf("%d %d", &l, &c); //linha coluna

    m = (int**)malloc(sizeof(int*) * l); //inicializa as linhas da mat

    for (i = 0; i < l; i++){
        m[i] = (int*)malloc(sizeof(int) * c); // inicializa as colunas da mat

        for (j = 0; j < c; j++){
            scanf("%d", &m[i][j]); //ini elementos da mat
        }
    }

    r = percurso(m, l, c, 0, 0, 0);

    if(r < INT_MAX){
        printf("%d", r); // custo total do deslocamento
    }
    else{
        printf("sem solucao");
    }

    for(i = 0; i < l; i++){
        free (m[i]);
    }
    free(m);

    return 0;
}
