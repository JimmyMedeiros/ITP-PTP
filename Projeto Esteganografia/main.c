#include <stdio.h>
#include "funcoes.h"

int main(int argc, char const *argv[])
{
	FILE *imagem, *texto, *imagemSaida, *textoSaida;
	char formato[3];
	int i, j;
	int tamanho_x, tamanho_y, extensao;
	
	/* Abrir os arquivos passados pelo terminal */
	if ((imagem = fopen(argv[argc - 1], "r")) == NULL)
		perror("O Seguinte erro ocorre:\n");
	if ((imagemSaida = fopen("saida.ppm", "w+")) == NULL)
		perror("O Seguinte erro ocorre:\n");
	if ((texto = fopen(argv[argc - 4], "r")) == NULL)
		perror("O Seguinte erro ocorre:\n");
	if ((textoSaida = fopen("textoSaida.txt", "w")) == NULL)
		perror("O Seguinte erro ocorre:\n");

	/* Pega as informações do cabeçário */
	getHeader (imagem, formato, &tamanho_x, &tamanho_y, &extensao);

	/* Aloca a matriz de Pixels */
	PixelRGB **matrizDePixel = NULL;
	alocarMatrizDePixel(&matrizDePixel, tamanho_y, tamanho_x);
	
	/* Pegar as informações da matriz */
	for (i = 0; i < tamanho_y; ++i)
		for (j = 0; j < tamanho_x; ++j)
			fscanf(imagem, "%c%c%c", &matrizDePixel[j][i].rgb[red], &matrizDePixel[j][i].rgb[green], &matrizDePixel[j][i].rgb[blue]);

	/* Alterando a imagem */
	PixelRGB **apontador = matrizDePixel;
	unsigned char c = 'a';
	while ((fscanf(texto, "%c", &c)) != EOF) {
		apontador = swapLastBit(apontador, c);
		// (*(*apontador)).rgb[blue] = c;
		// apontador++;
	}
	swapLastBit(apontador, '\0'); // Colocando o sinal de final de texto;

	/* Colocando as informações da matriz em arquivo de Saída */
	printf("Gerando arquivo de saída\n");
	fprintf(imagemSaida, "%s\n%d %d\n%d\n", formato, tamanho_x, tamanho_y, extensao);
	for (i = 0; i < tamanho_y; ++i)
		for (j = 0; j < tamanho_x; ++j)
			fprintf(imagemSaida, "%c%c%c", matrizDePixel[j][i].rgb[red], matrizDePixel[j][i].rgb[green], matrizDePixel[j][i].rgb[blue]);

	/* Pegando a mensagem */
	rewind(imagemSaida);
	char letra[200];
	getMessage (imagemSaida, letra, 200);
	fprintf(textoSaida, "%s", letra);

	/* Liberando espaço e fechando arquivos */
	desalocarMatrizDePixel(&matrizDePixel, tamanho_y);
	fclose(imagem);
	fclose(texto);
	fclose(imagemSaida);
	return 0;
}