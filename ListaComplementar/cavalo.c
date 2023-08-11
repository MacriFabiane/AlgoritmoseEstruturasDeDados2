#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//vedtor global movimento cavalo

int movX[] = {-1, -2, -2, -1,  1,  2,  2,  1};
int movY[] = { 2,  1, -1, -2, -2, -1,  1,  2};


// verificar se a posi��o (l, c) � v�lida no tabuleiro e se foi visitada
int validar_passo(int **mat, int n, int l, int c){
    return ((l >= 0) && (l < n) && (c >= 0) && (c < n) && (mat[l][c] < 0));
}


// Fun��o que tenta encontrar uma solu��o para o problema do passeio do cavalo
int movimento_cavalo(int **mat, int n, int l, int c, int mov){
    int i, pc, pl;

    mat[l][c] = mov;

    // Verifica se a solu��o foi encontrada
    if (mov == n * n)
        return 1;

    // Testar todos os movimentos poss�veis do cavalo a partir da posi��o (l, c)
    for (i = 0; i < 8; i++){
        pl = l + movX[i];
        pc = c + movY[i];

	// Se o passo � v�lido, fazer chamada recursiva para o pr�ximo movimento
        if (validar_passo(mat, n, pl, pc)){
            if (movimento_cavalo(mat, n, pl, pc, mov + 1))
                return 1;
        }
    }

    mat[l][c] = -1;

    return 0;
}


// fun��o para imprimir matriz
void imprimir(int **mat, int n){
    int i, j;

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++)
            printf("%d ", mat[i][j]);

        printf("\n");
    }
}


// fun��o para inicializar uma matriz n x n
int** iniciar_mat(int n){
    int i, j;
    int **mat = (int**) malloc(sizeof(int*) * n);

    for (i = 0; i < n; i++){
        mat[i] = (int*) malloc(sizeof(int) * n);

        for (j = 0; j < n; j++)
            mat[i][j] = -1;
    }

    return mat;
}


int main() {
    int n = 8, l = 0, c = 0;
    int **mat = iniciar_mat(n);

    mat[l][c] = 0;


    if (movimento_cavalo(mat, n, l, c, 1))
        imprimir(mat, n);


    free(mat);


    return 0;
}
