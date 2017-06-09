#ifndef BMP_H
#define BMP_H

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
/* 40 bytes 
Este trecho foi baseado no formato padrão de leitura do 
DIB do Windows para o formato BITMAPINFOHEADER */
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
typedef struct {
	unsigned char blue;
	unsigned char green;
	unsigned char red;
}BGRPixel;

void convert_little_to_big_endian(char* little, char* big);

void print_deb_header (BITMAPINFOHEADER dib);

int cifrar_bmp(FILE *imagem, FILE *saida);

#endif