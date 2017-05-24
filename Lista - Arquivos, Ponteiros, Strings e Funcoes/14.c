#include <stdio.h>
#include <stdlib.h>

void percorrer_espiral(int linhas, int colunas, int **vetor){
	int i, j;
	for (i = 0; i < linhas/2 && i < colunas/2; ++i)
	{
		// imprime a linha de cima → → → > > >
		for (j = i; j < colunas-i; ++j)
			printf("%d ", vetor[i][j]);
		// imprime a linha da direita ↓ ↓ ↓ v v v
		for (j = i+1; j < linhas-i; ++j)
			printf("%d ", vetor[j][colunas - i-1]);
		// imprime a linha de baixo ← ← ← < < <
		for (j = i + 1; j < colunas-i; ++j)
			printf("%d ", vetor[linhas-i-1][colunas-j-1]);
		// imprime a linha da esquerda ↑ ↑ ↑ ^ ^ ^
		for (j = i+1; j < linhas-i-1; ++j)
			printf("%d ", vetor[linhas-j-1][i]);
	}
	if (colunas%2 && linhas > colunas)
	{
		// imprime a linha da direita ↓ ↓ ↓ v v v
		for (j = i; j < linhas-i; ++j)
			printf("%d ", vetor[j][colunas-i-1]);
	}
	if (linhas%2 && linhas <= colunas){
		// imprime a linha de cima → → → > > >
		for (j = i; j < colunas-i; ++j)
			printf("%d ", vetor[i][j]);
	}
	printf("\n");
}
void percorrer_diagonal(int linhas, int colunas, int **vetor){
	int i, j, k;
	
	for (i = 0; i < linhas; ++i)
	{
		for (j = 0; j <= i && j < colunas; ++j)
			printf("%d ", vetor[i-j][j]);
	}
	for (k = 1; k < colunas; ++k)  // Essa linha já garante percorrer a quantidade de diagonais restantes
	{
		for (j = 0; j < linhas && k+j < colunas; ++j)
			printf("%d ", vetor[i-j-1][k+j]);
	}
	printf("\n");
}
int main(int argc, char const *argv[])
{
	int i, j, m, n;
	int **matriz;
	while(scanf("%d %d", &m, &n)!=EOF){
		matriz = (int**) malloc(m*sizeof(int*));
		for (i = 0; i < m; ++i)
			matriz[i] = (int*) malloc(n*sizeof(int));
		for (i = 0; i < m; ++i)
		{
			for (j = 0; j < n; ++j)
				scanf("%d", &matriz[i][j]);
		}
		
		// para o teste1_quesão14 usar essa função:
		//percorrer_diagonal(m, n, matriz);

		// para o teste2_quesão14 usar essa função:
		percorrer_espiral(m, n, matriz);
		
		for (i = 0; i < m; ++i)
			free(matriz[i]);
		free(matriz);
	}
	return 0;
}