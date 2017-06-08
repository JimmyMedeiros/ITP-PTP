#include <stdio.h>
#include <stdlib.h>

/* OBS: procurar saber mais sobre #pragma pack () */
/* 14 bytes */
#pragma pack (2)
typedef struct
{
	char type[2];// Tipo de bitmap (BM, BA, CI, CP, IC, PT)
	unsigned int size;// O tamanho do arquivo
	char reserved1[2];
	char reserved2[2];
	unsigned int offset; // Indica o começo do array de pixels
}BMP_header;
/* 40 bytes */
#pragma pack (2)
typedef struct {
	unsigned int size;// o tamanho do dib
	unsigned int width; // Largura da imagem em pixels
	unsigned int height; // Altura da imagem em pixels
	unsigned short planes; // O número de plano de cores (deve ser 1)
	unsigned short bitCount; // A profundidade de cor, ou seja, bits por pixel
	unsigned int compression; // Tipo de compressão (0 quando não tem compressão)
	unsigned int sizeImage; // Tamanho da imagem RAW (0 quando não tem compressão)
	unsigned int xPelsPerMeter; // Resolução horizontal
	unsigned int yPelsPerMeter; // Resolução vertical
	unsigned int clrUsed; // Número de cores na paleta de cores (valor default 0 para 2^n)
	unsigned int clrImportant; // Número de cores importantes (0 quando todas são importantes)
} BITMAPINFOHEADER;
/* 24 bits ou 3 bytes */
typedef struct 
{
	unsigned char blue;
	unsigned char green;
	unsigned char red;
}BGRPixel;

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

int main(int argc, char const *argv[])
{
	// Variáveis
	FILE *imagem, *saida;
	BMP_header h;
	BITMAPINFOHEADER dib;
	BGRPixel *pixelArray;
	
	// Abre a imagem
	if ((imagem = fopen("imd.bmp", "r"))==NULL)
		fprintf(stderr, "Erro ao abrir o arquivo\n");
	if ((saida = fopen("saida.bmp", "w"))==NULL)
		fprintf(stderr, "Erro ao abrir o arquivo\n");

	// Lê o cabeçalho BMP do arquivo
	fread(&h, 14, 1, imagem);
	// Lê o cabeçalho DIB do arquivo
	fread(&dib, 40, 1, imagem);
	
	// Aloca e lê os pixels 
	pixelArray = malloc(dib.width * dib.height * sizeof(BGRPixel));
	if (pixelArray == NULL)
		fprintf(stderr, "Não foi possível carregar a imagem. Memória insuficiente\n");
	
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
	fclose(imagem);
	fclose(saida);

	return 0;
}