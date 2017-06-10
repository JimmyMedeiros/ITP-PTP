#include <stdio.h>
#include "bmp.h"

// Função útil para verificar se a imagem foi lida corretamente
void print_deb_header (BITMAPINFOHEADER dib){
	/* Imprimir informações */
	printf("Largura: %d, altura: %d\n", dib.width, dib.height);
	printf("Planos de cores: %u\n", dib.planes);
	printf("Profundidade de cor: %d\n", dib.bitCount);
	printf("Tipo de compressão: %d\n", dib.compression);
	printf("Tamanho da imagem RAW: %d\n", dib.sizeImage);
	printf("Resolução horizontal: %d\n", dib.xPelsPerMeter);
	printf("Resolução vertical: %d\n", dib.yPelsPerMeter);
	printf("Número de cores na paleta de cores: %d\n", dib.clrUsed);
	printf("Cores importantes: %d\n", dib.clrImportant);
}

int encipher_BMP(FILE *imagem, FILE *saida, FILE *texto){
	// Variáveis
	BMP_header hdr;
	BITMAPINFOHEADER dib;
	PixelRGB *pixelArray;
	// Lê o cabeçalho BMP do arquivo
	fread(&hdr, 14, 1, imagem);
	// Lê o cabeçalho DIB do arquivo
	fread(&dib, 40, 1, imagem);
	// Aloca e lê os pixels 
	pixelArray = malloc(dib.width * dib.height * sizeof(BGRPixel));
	if (pixelArray == NULL){
		fprintf(stderr, "Não foi possível carregar a imagem. Memória insuficiente\n");
		return 1;
	}
	fread(pixelArray, sizeof(BGRPixel), dib.width * dib.height, imagem);
	// Colocar a mensagem
	rewind(texto);
	PixelRGB *ptr = pixelArray;
	char c = 'a';
	while ((fscanf(texto, "%c", &c)) != EOF)
		ptr = swapLastBit(ptr, c);
	swapLastBit(ptr, '\0'); // Colocando o sinal de final de texto;
	
	// Escreve o cabeçalho BMP no arquivo de saída
	fwrite(&hdr, 14, 1, saida);
	// Escreve o cabeçalho DIB no arquivo de saída
	fwrite(&dib, 40, 1, saida);
	// Escreve os pixels 
	fwrite(pixelArray, sizeof(BGRPixel), dib.width * dib.height, saida);
	
	free(pixelArray);

	return 0;
}

void decipher_BMP (FILE *img, FILE *textoSaida){
	// Variáveis
	BMP_header hdr;
	BITMAPINFOHEADER dib;
	// Lê o cabeçalho BMP do arquivo
	fread(&hdr, 14, 1, img);
	// Lê o cabeçalho DIB do arquivo
	fread(&dib, 40, 1, img);
	
	// Pegando a mensagem
	int tamanho_Mensagem = (dib.width*dib.height)/3;
	char *letras = NULL;
	letras = (char*)malloc(tamanho_Mensagem * sizeof(char));
	if (letras == NULL)
		fprintf(stderr, "Memória insuficiente\n");
	getMessage (img, letras, tamanho_Mensagem);
	// Colocando a mensagem no texto 
	fprintf(textoSaida, "%s", letras);

	free(letras);
}