/*Implemente uma função que faz o somatório, utilizando divisão e conquista, de todos os elementos de um vetor de números inteiros. Antes da divisão, a partição do vetor analizada deve ser impressa caso a mesma tiver, no mínimo, dois elementos.

Input Format

Na primeira linha deve ser lido o tamanho do vetor.

Na segunda linha deve ser lido o conteúdo do vetor.

Constraints

.

Output Format

Nas primeiras linhas devem ser impressas as partições antes da sua respectiva "divisão".

Na última linha, deve ser impresso o resultado do somatório seguindo o seguinte padrão:

"soma: resultado do somatorio"

Sample Input 0

8
1 2 3 4 5 6 7 8
Sample Output 0

1 2 3 4 5 6 7 8
1 2 3 4
1 2
3 4
5 6 7 8
5 6
7 8
soma: 36*/
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

void somatorio(int v[], int esq, int dir, int* soma, int imp){
    int meio, i;
     
 
    if (esq < dir){
        meio = (esq + dir) / 2;
        
        if(dir-esq >1){
                for(i=esq; i<dir+1; i++){
                    printf("%d ", v[i]);
                } 
            printf("\n");
        }
        
        if(dir-esq==2){
            *soma+=v[imp];
        }
        
        if (dir-esq==1){
           for(i=esq; i<dir+1; i++){
                    printf("%d ", v[i]);
               *soma+=v[i];
                } 
            printf("\n");
         }
        
        
        somatorio(v, esq, meio, soma, imp);    
        somatorio(v, meio + 1, dir, soma, imp);
        
    }
}
   
int main() {
    int n, i, soma=0;
    
    scanf("%d", &n);
    
    int v[n];

    for(i=0; i<n; i++){
        scanf("%d", &v[i]);
    }
    somatorio(v, 0, n-1, &soma, n-1);
    printf("soma: %d", soma);
    
    
    return 0;
}
