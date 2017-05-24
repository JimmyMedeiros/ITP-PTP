#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* criado por Gleydvan */

void scalar(int *first, int *last, int valor){
	
	while (first <= last){
		(*first) *= valor;
		first++;
	}

}

int main(int argc, char const *argv[]){

	int n, i;
	int *inicio, *fim;

	printf("Digite a quantidade de numeros inteiros a serem armazenados: \n");
	scanf("%d", &n);

	int *inteiros;
	inteiros = calloc(n+1, sizeof(int));
	if(inteiros == NULL){
		printf("Memoria insuficiente. \n");
		return 1;
	}

	printf("Digite os %d numeros: \n", n);
	for (i = 0; i < n; ++i){
		scanf("%d", &inteiros[i]);
	}

	inicio = inteiros;
	fim = &inteiros[n-1];

	negate(inicio, fim);


	printf("Numeros com sinal invertido:\n");
	for(i = 0; i < n; ++i){
		printf("%d ", inteiros[i]);
	}

	free(inteiros);
	return 0;
}
