#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct
{
	int maior;
	int frequencia;
} resposta;

resposta freq_do_maior(int *vetor, int tamanho){
	resposta res;
	int i, max = INT_MIN, cont;
	for (i = 0; i < tamanho; ++i)
	{
		if (vetor[i] > max)
		{
			max = vetor[i];
			cont = 1;
		} else if (vetor[i] == max)
		{
			++cont;
		}
	}
	res.maior = max;
	res.frequencia = cont;
	return res;
}

int main(int argc, char const *argv[])
{
	/*int n;
	scanf("%d", &n);*/
	int vet[] = { 5, 2, 15, 3, 7, 15, 8, 6, 15 };
	resposta a = freq_do_maior(vet, 9);

	printf("maior: %d frequencia: %d\n", a.maior, a.frequencia);

	return 0;
}