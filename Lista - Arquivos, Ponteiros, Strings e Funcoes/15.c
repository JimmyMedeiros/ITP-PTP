#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[])
{
	FILE *arquivo;
	char nome_do_arquivo[100], palavra[100], palavra_do_arquivo[100];
	int cont;

	printf("Escreva o nome do arquivo: \n");
	scanf("%s", nome_do_arquivo);
	if((arquivo = fopen (nome_do_arquivo, "r"))==NULL){
		perror("Arquivo não pôde ser aberto");
		return 1;
	}
	printf("Escreva a palavra para procurar no arquivo: \n");
	scanf("%s", palavra);
	

	while(fscanf(arquivo, " %s", palavra_do_arquivo)!=EOF){
		char c = palavra_do_arquivo[strlen(palavra_do_arquivo)-1];
		if (c == '!' || c == '?' || c == '.' || c  == ',')
		{
			palavra_do_arquivo[strlen(palavra_do_arquivo)-1] = '\0';
		}
		if (strcmp(palavra, palavra_do_arquivo)==0)
		{
			++cont;
		}
	}
	printf("A palavra \"%s\" aparece %d vezes no arquivo %s\n", palavra, cont, nome_do_arquivo);

	fclose(arquivo);

	return 0;
}