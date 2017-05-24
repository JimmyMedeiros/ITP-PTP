#include <stdio.h>
#include <stdlib.h>

void load (int* vetor, int* tamanho, const char* infile){
	/* abrir o arquivo */
	int i;
	FILE* arquivo;
	arquivo = fopen(infile, "r");
	if (arquivo == NULL) perror ("Erro ao abrir o arquivo");
	else {
		/* contar quantos números existem no arquivo */
		printf("ainda funcionando\n");
		/* E se o tamanho do vetor for maior que a quantidade de números no arquivo?
		E se a quantidade de números no arquivo for maior? */
		for (i = 0; i < *tamanho; ++i)
			fscanf(arquivo, "%d", &vetor[i]);
	}
	fclose(arquivo);
}
int* createIdxCrescente (const int* vetor, const int tamanho){
	/* TÁ TUDO ERRADO! */
	int* index, i, j, temp;
	index = malloc(tamanho*sizeof(int));
	if (index == NULL) perror ("Espaço em memória insuficiente");
	for (i = 0; i < tamanho; ++i)
		index[i] = i;
	for (i = 0; i < tamanho; ++i)
	{
		for (j = i+1; j < tamanho; ++j)
		{
			/* 79  0 27 29  9 51 69 420 666 17 42 13
			saída:
				11 0 10  2  1  6  5   4   3  8  7  9
			Isso significa que o index[11] = 0 

			    0  1  2  3  4  5  6   7   8  9 10 11   i = 0 , j = 1
			    1  0  2  3  4  5  6   7   8  9 10 11   i = 0 , j = 2, 3, 4 ... 11
			    1  0  2  3  4  5  6   7   8  9 10 11   i = 1 , j = 2		*/
			if (vetor[index[i]] > vetor[j])
			{
				temp = index[index[i]];
				index[index[i]] = index[j];
				index[j] = temp;
			}
		}
	}
	for (i = 0; i < tamanho; ++i)
	{
		index[index[i]] = i;
	}
	return index;
}
int* createIdxDecrescente (const int* vetor, const int tamanho){
	int *aux = createIdxCrescente(vetor, tamanho);
	int *index, i;
	index = malloc(tamanho*sizeof(int));
	if (index == NULL) perror ("Espaço em memória insuficiente");
	for (i = 0; i < tamanho; ++i)
		index[i] = aux[tamanho-i-1];

	return index;
}
void print (const int* indice, const int tamanho, const int *vetor){
	for (int i = 0; i < tamanho; ++i)
	{
		for (int j = 0; j < tamanho; ++j)
		{
			/* code */
		}
	}
	printf("\n");
}
/*
void save (const int* indice, const int tamanho, const char* outfile){

}*/

int main(int argc, char const *argv[])
{
	char* nome_do_arquivo = "file.txt";
	int *v, *indice_cresc, *indice_decres, i, t = 12;
	v = malloc(t*sizeof(int));
	indice_cresc = malloc(t*sizeof(int));
	indice_decres = malloc(t*sizeof(int));
	if (v == NULL || indice_cresc == NULL || indice_decres == NULL) perror ("Espaço em memória insuficiente");

	printf("funcionando\n");
	load(v, &t, nome_do_arquivo);
	indice_cresc = createIdxCrescente(v, t);
	indice_decres = createIdxDecrescente(v, t);

	/* Vai imprimir tudo, até os índices não inicializados */
	for (i = 0; i < t; ++i)
		printf("%d ", v[i]);
	printf("\n");
	for (i = 0; i < t; ++i)
	{
		printf("%d ", indice_cresc[i]);
	}
	printf("\n");
	for (i = 0; i < t; ++i)
	{
		printf("%d ", indice_decres[i]);
	}
	printf("\n");
	//print(indice_cresc, t, v);

	free(v);

	return 0;
}