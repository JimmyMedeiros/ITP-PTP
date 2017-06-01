#include <stdio.h>
#include <stdlib.h>

void getHeader (FILE *imagem, char *formato, int* tamanho_x, int* tamanho_y){
	/* Pegar as informações do cabeçalho */
	char c = 'a';
	fgets (formato, 100, imagem);
	c = fgetc (imagem);
	if (c == '#')
		while (c != '\n')
			c = fgetc (imagem);
	else
		fseek ( imagem , -1 , SEEK_CUR );
	fscanf(imagem, "%d %d", tamanho_x, tamanho_y);
}
	/* Armazena os bits de cada caracter 
	char c = 'a', bits[8],
	while ((c = fgetc (texto)) != EOF) {
		printf("%c", c);
		for (i = 0; i < 8; ++i)
		{
			bits[7-i] = c%2;
			c/= 2;
		}
	}*/

int main(int argc, char const *argv[])
{
	FILE *imagem, *texto, *teste;
	// char c = 'a', bits[8], 
	char formato[3];
	int i, j, k; 
	int tamanho_x, tamanho_y;
	
	/* Abrir os arquivos passados pelo terminal */
	if ((imagem = fopen(argv[argc - 1], "r+")) == NULL)
		perror("O Seguinte erro ocorre:\n");

	if ((texto = fopen(argv[argc - 4], "r")) == NULL)
		perror("O Seguinte erro ocorre:\n");
	/* Arquivo teste para matriz */
	if ((teste = fopen("teste.txt", "w")) == NULL)
		perror("O Seguinte erro ocorre:\n");

	getHeader (imagem, formato, &tamanho_x, &tamanho_y);
	printf("Fomarto: %s\nTamanho x: %d\nTamanho y: %d\nQuantidade de linhas: %d\n", formato, tamanho_x, tamanho_y, tamanho_x*tamanho_y*3);

	/* Alocação da matriz */
	int ***matriz = (int***)malloc(tamanho_y*sizeof(int**));
	for (i = 0; i < tamanho_y; ++i)
		matriz[i] = (int**)malloc(tamanho_x*sizeof(int*));
	for (i = 0; i < tamanho_y; ++i)
		for (j = 0; j < tamanho_x; ++j)
			matriz[i][j] = (int*)malloc(3*sizeof(int));

	/* Pegar as informações da matriz */
	int range = 1;
	fscanf(imagem, "%d", &range);
	for (i = 0; i < tamanho_y; ++i)
		for (j = 0; j < tamanho_x; ++j)
			for (k = 0; k < 3; ++k){
				fscanf(imagem, "%d", &matriz[i][j][k]);
				matriz[i][j][k] /= 2;
			}
	rewind (imagem);
	getHeader (imagem, formato, &tamanho_x, &tamanho_y);
	// getHeader aponta para o final da linha

	/* Colocando as informações da matriz em arquivo */
	fprintf(imagem, "\n%d\n", range); // Então é necessário dar um salto

	for (i = 0; i < tamanho_y; ++i)
		for (j = 0; j < tamanho_x; ++j)
			for (k = 0; k < 3; ++k){
				fprintf(teste, "%d\n", matriz[i][j][k]);
				fprintf(imagem, "%d\n", matriz[i][j][k]);
			}

	/* Liberando espaço */
	for (i = 0; i < tamanho_y; ++i)
		for (j = 0; j < tamanho_x; ++j)
			free(matriz[i][j]);
		free(matriz[i]);
	free(matriz);
	return 0;
}
