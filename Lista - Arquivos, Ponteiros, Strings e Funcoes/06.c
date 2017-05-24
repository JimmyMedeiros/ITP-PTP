#include <stdio.h>
#include <stdlib.h>

void compacta(int *vetor, int tamanho){
	int c = 0, i;
	for (i = 0; i < tamanho; ++i)
	{
		if (vetor[i] > 0){
			vetor[c] = vetor[i];
			c++;
		}
	}
	for (i = 0; i < c; ++i)
		printf("%d ", vetor[i]);
	printf("\n");
}


int main(int argc, char const *argv[])
{
	int n, i, *v;
	scanf("%d", &n);
	v = malloc(n*sizeof(int));
	for (i = 0; i < n; ++i)
		scanf("%d", &v[i]);
	compacta(v, n);
	for (i = 0; i < n; ++i)
	{
		printf("%d ", v[i]);
	}
	printf("\n");
	free(v);

	return 0;
}