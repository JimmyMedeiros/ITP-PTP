#include <stdio.h>
#include <stdlib.h>

int sort_marbles(int *vetor, int tamanho){
	int temp, i, j, c = 0;
	for (i = 0; i < tamanho; ++i)
	{
		if (vetor[i] == 0){
			j = i + 1;
			while (vetor[j] == 0 && j < tamanho)
				j++;
			temp = vetor[i];
			vetor[i] = vetor[j];
			vetor[j] = temp;
		}
	}
	for (i = 0; i < tamanho; ++i){
		printf("%d ", vetor[i]);
		if (vetor[i] == 1)
			c++;
	}
	printf("\n");

	return c;
}


int main(int argc, char const *argv[])
{
	int n, i, *v;
	scanf("%d", &n);
	v = malloc(n*sizeof(int));
	for (i = 0; i < n; ++i)
		scanf("%d", &v[i]);
	//sort_marbles(v, n);
	
	printf("%d\n", sort_marbles(v,n));
	free(v);

	return 0;
}