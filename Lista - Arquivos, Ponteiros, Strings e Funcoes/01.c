#include <stdio.h>
#include <stdlib.h>

void negate(int *numeros, int tamanho){
	int i;
	for (i = 0; i < tamanho; ++i)
	{
		numeros[i] *= -1;
	}
}

int main(int argc, char const *argv[])
{
	int n, i, *vetor;
	scanf("%d", &n);
	vetor = malloc(n*sizeof(int));
	for (i = 0; i < n; ++i)
		scanf("%d", &vetor[i]);
	negate(vetor, n);
	for (int i = 0; i < n; ++i)
		printf("%d ", vetor[i]);
	printf("\n");

	free(vetor);

	return 0;
}