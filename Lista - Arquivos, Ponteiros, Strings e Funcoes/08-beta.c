#include <stdio.h>
#include <stdlib.h>

void load (int* array, int* length, const char* infile){
	int i;
	FILE* arquivo;
	arquivo = fopen(infile, "r");
	if (arquivo == NULL){
		perror ("Erro ao abrir o arquivo");
	} else {		
		if (array == NULL){
			perror ("A função load recebeu um vetor nulo");
		} else {
			for (i = 0; i < (*length); ++i)
				fscanf(arquivo, "%d", &array[i]);
		}	
	}
	fclose(arquivo);
}
int* createIdxCrescente (const int* array, const int length){
	int* index, i, j, temp;
	index = malloc(length*sizeof(int));
	for (i = 0; i < length; ++i)
	{
		index[i] = i;
	}
	
	for (i = 0; i < length-1; ++i)
	{
		for (j = i+1; j < length; ++j)
		{
			if (array[index[i]] > array[index[j]])
			{
				temp = index[i];
				index[i] = index[j];
				index[j] = temp; 
			}
		}
	}

	return index;
}
int* createIdxDecrescente (const int* array, const int length){
	int* index, i, j, temp;
	index = malloc(length*sizeof(int));
	for (i = 0; i < length; ++i)
	{
		index[i] = i;
	}
	
	for (i = 0; i < length-1; ++i)
	{
		for (j = i+1; j < length; ++j)
		{
			if (array[index[i]] < array[index[j]])
			{
				temp = index[i];
				index[i] = index[j];
				index[j] = temp; 
			}
		}
	}

	return index;
}
void print (const int* index, const int length, const int* array){
	int i;
	for (i = 0; i < length; ++i)
		printf("%d ", array[index[i]]);
	printf("\n");
}

void save (const int* index, const int length, int* array, const char* outfile){
	int i;
	FILE* arquivo;
	arquivo = fopen(outfile, "w");
	if (arquivo == NULL){
		perror ("Erro ao abrir o arquivo");
	} else {
		for (i = 0; i < length; ++i)
			fprintf(arquivo, "%d ", array[index[i]]);
		fprintf(arquivo, "\n");
	}
}

int main(int argc, char const *argv[])
{
	/* Declaração de variáveis */
	char* nome_do_arquivo = "questao08.txt";
	int i, tamanho;
	int *vetor = NULL, *indice, *indice_cresc, *indice_decres;
	FILE* arquivo;
	
	/* Inicialização das variáveis */
	arquivo = fopen(nome_do_arquivo, "r");
	if (arquivo == NULL){
		perror ("Erro ao abrir o arquivo");
	} else {
		/* modifica length para retornar o tamanho */
		while (!feof(arquivo)){
			fscanf(arquivo, "%d", &i);
			++(tamanho);
		}
		--(tamanho);// Gabiarra Detected!
	}
	
	vetor = malloc((tamanho-1)*sizeof(int));
	printf("tamanho do vetor = %d\n", tamanho); // ATENÇÃO! Não pode tirar essa linha porque dá erro. É sério, isso não é uma piada, eu só não consegui descobrir ainda qual a magia negra por trás desse printf 
	
	load(vetor, &tamanho, nome_do_arquivo);
	
	if (vetor == NULL){
		perror ("Espaço em memória num tem");
		return 1;
	}
	if (tamanho == 0)
	{
		perror("Arquivo Vazio");
		return 2;
	}
	indice = malloc(tamanho*sizeof(int));
	for (i = 0; i < tamanho; ++i)
		indice[i] = i;
	indice_decres = createIdxDecrescente(vetor, tamanho);
	indice_cresc = createIdxCrescente(vetor, tamanho);
	if (indice_cresc == NULL || indice_decres == NULL){
		perror ("Espaço em memória insuficiente");
		return 1;
	}

	/* imprime o vetor na ordem do arquivo */
	print(indice, tamanho, vetor);
	/* imprime o vetor em ordem crescente */
	print(indice_cresc, tamanho, vetor);
	/* imprime o vetor em ordem decrescente */
	print(indice_decres, tamanho, vetor);
	save(indice_decres, tamanho, vetor, "questao08_saida");


	free(vetor);
	free(indice);
	free(indice_cresc);
	free(indice_decres);
	fclose(arquivo);

	return 0;
}