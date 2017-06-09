#include <stdio.h>
#include "bmp.h"

void convert_little_to_big_endian(char* little, char* big){
	for (int i = 0; i < 4; ++i)
	{
		*big = *little;
		little++;
		big++;
	}
}

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

int cifrar_bmp(FILE *imagem, FILE *saida){
	// Variáveis
	BMP_header h;
	BITMAPINFOHEADER dib;
	BGRPixel *pixelArray;
	
	// Lê o cabeçalho BMP do arquivo
	fread(&h, 14, 1, imagem);
	// Lê o cabeçalho DIB do arquivo
	fread(&dib, 40, 1, imagem);
	
	// Aloca e lê os pixels 
	pixelArray = malloc(dib.width * dib.height * sizeof(BGRPixel));
	if (pixelArray == NULL){
		fprintf(stderr, "Não foi possível carregar a imagem. Memória insuficiente\n");
		return 1;
	}
	
	fread(pixelArray, sizeof(BGRPixel), dib.width * dib.height, imagem);

	// Escreve o cabeçalho BMP no arquivo de saída
	fwrite(&h, 14, 1, saida);
	// Escreve o cabeçalho DIB no arquivo de saída
	fwrite(&dib, 40, 1, saida);
	
	BGRPixel *p = pixelArray;
	for (int i = 0; i < dib.width * dib.height; ++i)
	{
		/* inserir código para modificar a imagem */
		p++;
	}

	// escreve os pixels 
	fwrite(pixelArray, sizeof(BGRPixel), dib.width * dib.height, saida);
	
	free(pixelArray);

	return 0;
}