#include <stdio.h>
#include <stdlib.h>

void scalar(int *numeros, int tamanho, int escalar){
	int i;
	for (i = 0; i < tamanho; ++i)
	{
		numeros[i] *= escalar;
	}
}

int main(int argc, char const *argv[])
{
	int n, s, i, *vetor;
	scanf("%d %d", &n, &s);
	vetor = malloc(n*sizeof(int));
	for (i = 0; i < n; ++i)
		scanf("%d", &vetor[i]);
	scalar(vetor, n, s);
	for (int i = 0; i < n; ++i)
		printf("%d ", vetor[i]);
	printf("\n");

	free(vetor);

	return 0;
}