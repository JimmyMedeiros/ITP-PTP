#include <stdio.h>
#include <math.h>

/* size = 10
	somaVetor(vetor)
*/
int somaVetor(int* array, int size){
	int sum = 0;
	if (size == 1) // Se o tamnho for igual 1 significa que é o último elemento do vetor
	{
		return *array; // retorna o conteúdo dessa posição
	}
	sum += *array; // Soma o conteúdo da posição da iteração atual (a cada iteração recursiva com size!=1)
	sum += somaVetor((array)+1, size - 1); // soma o valor retornado pela recursão 
	return sum; //retorna a soma
}

int main(int argc, char const *argv[])
{
	int tamanho = 10;
	int vetor[] = {1,2,3,4,5,6,7,8,9,10};
	int soma = somaVetor(vetor, tamanho);
	printf("%d\n", soma);
	return 0;
}
