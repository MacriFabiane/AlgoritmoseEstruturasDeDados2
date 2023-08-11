#include <stdio.h>

#define MAX 10

// Solu��o do problema do labirinto por backtracking
int resolver_labirinto(int lab[MAX][MAX], int m, int n, int movX[], int movY[], int li, int ci, int lf, int cf){
	/*
	l, c: posi��o de um passo no labirinto
	*/
	int l, c, i, passos;

	if ((li == lf) && (ci == cf)) return lab[li][ci];

	/*Todos os movimentos a partir da posi��o inicial s�o testados*/
	for (i = 0; i < 4; i++){
		// Posi��o do candidato a pr�ximo passo
		l = li + movX[i];
		c = ci + movY[i];
		//mX[4]={0,0,1,-1} cima baixo frente traz
        //my[4]={1,-1,0,0}


		/*O movimento � verificado e caso seja v�lido, uma solu��o � gerada*/
		if ((l >= 0) && (l < m) && (c >= 0) && (c < n) && (lab[l][c] == -1)){ //-1 significa q aposic��o n foi visitada
			lab[l][c] = lab[li][ci] + 1; // atualizar a quantidade de passos na posi��o l,c

			// Continuar o percurso no labirinto
			passos = resolver_labirinto(lab, m, n, movX, movY, l, c, lf, cf);

			if (passos > 0) return passos;
		}
	}
	return 0;
}


// Outra solu��o do problema do labirinto por backtracking
// Neste caso, a solu��o �tima deve ser encontrada
void resolver_labirinto2(int lab[MAX][MAX], int m, int n, int movX[], int movY[], int li, int ci, int lf, int cf, int *min){
	int l, c, i;

	if ((li == lf) && (ci == cf)){
		if (lab[lf][cf] < *min)
			*min = lab[lf][cf];
	}else{
	/*Todos os movimentos a partir da posi��o inicial s�o testados*/
		for (i = 0; i < 4; i++){
			l = li + movX[i];
			c = ci + movY[i];

			/*O movimento � verificado e caso seja v�lido, uma solu��o � gerada*/
			if ((l >= 0) && (l < m) && (c >= 0) && (c < n) && ((lab[l][c] == -1) || (lab[l][c] > lab[li][ci] + 1))){ //parte depois do ou permite passar pelo mesmo local 2 vezes
				lab[l][c] = lab[li][ci] + 1;                                        // ve se a nova � maior que a atual +1 se for � substituida por lab[li][ci]+1

				resolver_labirinto2(lab, m, n, movX, movY, l, c, lf, cf, min);
			}
		}
	}
}


// Outra solu��o do problema do labirinto por branch-and-bound
void resolver_labirintoBnB(int lab[MAX][MAX], int m, int n, int movX[], int movY[], int li, int ci, int lf, int cf, int *min){
	int l, c, i;

	if ((li == lf) && (ci == cf)){
		if (lab[lf][cf] < *min)
			*min = lab[lf][cf];
	}else{
		/*Todos os movimentos a partir da posi��o inicial s�o testados*/
		for (i = 0; i < 4; i++){
			l = li + movX[i];
			c = ci + movY[i];

			/*O movimento � verificado e caso seja v�lido, uma solu��o � gerada*/
			if ((l >= 0) && (l < m) && (c >= 0) && (c < n) && ((lab[l][c] == -1) || (lab[l][c] > lab[li][ci] + 1))){
				lab[l][c] = lab[li][ci] + 1;

				// Aqui s�o definidos os limitantes
				if (lab[l][c] + abs(l - lf) + abs(c - cf) < *min) //se encontrar o min de passos segue
					resolver_labirintoBnB(lab, m, n, movX, movY, l, c, lf, cf, min);
			}
		}
	}
}


int main(){
	/*
	lab: labirinto
	n, m: n�mero de linhas e de colunas ocupadas na matriz labirinto
	li, ci: posi��o inicial no labirinto
	lf, cf: posi��o final no labirinto
	resp: 1 se um caminho foi encontrado entre (li, ci) e (lf, cf), ou 0, caso contr�rio
	*/

	int lab[MAX][MAX], n, m, li, ci, lf, cf, resp;

	/*Movimentos v�lidos no labirinto

	Exemplo: movX[0] e movY[0] indica que o movimento � para baixo
	*/
	int movX[] = {0, 1, 0, -1}; // Movimentos no eixo x da matriz
	int movY[] = {1, 0, -1, 0}; // Movimentos no eixo y da matriz

	/*inicializar as vari�veis relacionadas ao labirinto*/
	//iniciar_labirinto(lab, m, n, li, ci, lf, cf); // implementar

	lab[ci][cf] = 0; // posi��o inicial no labirinto

	resp = resolver_labirinto(lab, m, n, movX, movY, li, ci, lf, cf);

	if (resp > 0) imprimir_labirinto(lab, m, n);
	eles printf("Solucao nao encontrada!\n");

	return 0;
}
