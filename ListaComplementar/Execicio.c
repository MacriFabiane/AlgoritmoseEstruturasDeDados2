#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
int contarPalavraString (char string[])
{
	
	int i=0, contPalavra=0;
	if(string[i]!=' ')
	{
		contPalavra++;
 		i++;
	}
	
	while (string[i]!='\0')
	{
		if (string[i]==' ' && string[i-1]!=' ')
		{
			contPalavra++;
		}
		i++;
	}
	
	return(contPalavra);	
}
void mostrarMatrizInteiro (int lin, int col, int matriz[][col])
{
	int i=0, j=0;
	
	for (i=0; i<lin; i++)
	{
		for(j=0; j<lin; j++)
		{
			printf("%d\t", matriz[i][j]);
		}
		printf ("\n");
	}
}
int contVogaisConsoantes (int mat[][col], int lin, int col, char string[]){
	int i = 0, contV =0, contC=0;
	
	int i=0, contPalavra=0;
	if(string[i]!=' ')
	{
		contPalavra++;
		if (string[i]=='a'||string[i]=='A'|| string[i]=='e'||string[i]=='E'|| string[i]=='i'||string[i]=='I'|| string[i]=='o'||string[i]=='O'|| string[i]=='u'||string[i]=='U') 
		{
			contV++;
		} 
		else {
			contC++;
		}
 		i++;
 		mat[i][0]=contV;
 		mat[0][i]= =contC;
	}
	
	while (string[i]!='\0')
	{
		if (string[i]==' ' && string[i-1]!=' ')
		{
			contPalavra++;
			if (string[i]=='a'||string[i]=='A'|| string[i]=='e'||string[i]=='E'|| string[i]=='i'||string[i]=='I'|| string[i]=='o'||string[i]=='O'|| string[i]=='u'||string[i]=='U') 
		{
			contV++;
		} 
		else {
			contC++;
		}
		mat[i][0]=contV;
 		mat[0][i]= =contC;
		}
		i++;
	}
	}
void vetorLetras(int vet0[], int tam, char string[]){
        int i = 0, j = 0, countLetras = 0;
        int vet[tam];
		 
        while (string[i] != '\0')
        {
            if (string[i] != ' ')
            {
                countLetras++;
                if (string[i+1] == ' ' || string[i+1] == '\0')
                {
                    vet[j] = countLetras;
                    countLetras = 0;
                    j++;
                }
            }
            i++;
        }
        for(i=0; i<tam; i++){
       	    vet0[i]=vet[i];
        	printf("%d\t", vet[i]);
		}
		 
    }

int main (){
	
	char str[100];
	int contPalavra=0, i=0;
	
	do{
	
	printf("Informe uma string com no maximo 10 palavras e 100 caracteres: ");
	gets(str);
	contPalavra=contarPalavraString(str);
	 
	 if (contPalavra > 10){
	 	printf("Voce deve informar no maximo 10 palavras");
	 }
}while (contPalavra > 10);
printf ("Quantidade de palavras na string: %d\n", contPalavra);
	int vet0[contPalavra];
	 for (i=0; i<10; i++){
        	vet0[i]=0;
	}

	printf("Quantidade de letras por palavra: \n");
	
    vetorLetras(vet0, contPalavra, str);
    
    int mat[10][2];
    
	

	
	return 0;
}
