#include <stdio.h>
#include "funcoes.h"

int main(int argc, char const *argv[])
{
	FILE *imagem, *texto, *imagemSaida, *textoSaida;
	char formato[3];
	char const *nomeTexto = argv[argc - 4], *nomeImagem = argv[argc - 1];
	int i, j;
	int tamanho_x, tamanho_y, extensao;
	
	/* Abrir os arquivos passados pelo terminal */
	if ((imagem = fopen(nomeImagem, "r")) == NULL)
		perror("O Seguinte erro ocorre:\n");
	if ((imagemSaida = fopen("saida.ppm", "w+")) == NULL)
		perror("O Seguinte erro ocorre:\n");
	if ((texto = fopen(nomeTexto, "r")) == NULL)
		perror("O Seguinte erro ocorre:\n");
	if ((textoSaida = fopen("textoSaida.txt", "w")) == NULL)
		perror("O Seguinte erro ocorre:\n");

	/* Pega as informações do cabeçário */
	getHeader (imagem, formato, &tamanho_x, &tamanho_y, &extensao);

	/* Aloca a matriz de Pixels */
	PixelRGB *matrizDePixel = NULL;
	alocarMatrizDePixel(&matrizDePixel, tamanho_x, tamanho_y);
	if (matrizDePixel == NULL)
		fprintf(stderr, "Memória insuficiente.\n");

	/* Pegar as informações da matriz */
	for (i = 0; i < (tamanho_y * tamanho_x); ++i)
		fscanf(imagem, "%c%c%c", &matrizDePixel[i].rgb[red], &matrizDePixel[i].rgb[green], &matrizDePixel[i].rgb[blue]);

	/* Antes de alterar a imagem, verifica se cabe a mensagem */
	fseek(texto, 0L, SEEK_END);
	long int tamanhoMensagem = ftell(texto), MensagemMax = ((tamanho_x*tamanho_y)/3);
	if(tamanhoMensagem > MensagemMax){
		fprintf(stderr, "A mensagem do arquivo \"%s\" não cabe na imagem.\nO arquivo deve ter no máximo %ld bytes.\n", nomeTexto, MensagemMax);
		return 1;
	}
	
	/* Alterando a imagem 
	unsigned char c;
	char* apontador;
	fscanf(texto, "%c", &c);
	for (i = 0; i < tamanho_y && c != EOF; ++i){
		PixelRGB *apontador = &(matrizDePixel[i][0]); // pega matrizDePixel[0]
		for (j = 0; i < (tamanho_x/3) && c != EOF; ++i){
			apontador = swapLastBit(apontador, c);
			fscanf(texto, "%c", &c);
		}
	}
	while ((fscanf(texto, "%c", &c)) != EOF) {
		apontador = swapLastBit(apontador, c);
		// (*(*apontador)).rgb[blue] = c;
		// apontador++;
	}
		// swapLastBit(apontador, '\0'); // Colocando o sinal de final de texto;*/
	
	/* Alterando a imagem */
	rewind(texto);
	PixelRGB *apontador = matrizDePixel;
	char c = 'a';
	while ((fscanf(texto, "%c", &c)) != EOF){
		apontador = swapLastBit(apontador, c);
	}
	swapLastBit(apontador, '\0'); // Colocando o sinal de final de texto;
	
	/* Colocando as informações da matriz em arquivo de Saída */
	printf("Gerando arquivo de saída\n");
	fprintf(imagemSaida, "%s\n%d %d\n%d\n", formato, tamanho_x, tamanho_y, extensao);
	for (i = 0; i < tamanho_y; ++i)
		for (j = 0; j < tamanho_x; ++j){
			fprintf(imagemSaida, "%c%c%c", matrizDePixel[i*tamanho_x + j].rgb[red], matrizDePixel[i*tamanho_x + j].rgb[green], matrizDePixel[i*tamanho_x + j].rgb[blue]);
		}

	/* Pegando a mensagem */
	rewind(imagemSaida);
	char letra[521];
	getMessage (imagemSaida, letra, 521);
	fprintf(textoSaida, "%s", letra);

	/* Liberando espaço e fechando arquivos */
	free(matrizDePixel);
	fclose(imagem);
	fclose(texto);
	fclose(imagemSaida);
	return 0;
}