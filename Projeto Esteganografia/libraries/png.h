#ifndef PNG_H
#define PNG_H

#include <stdio.h>
#include <stdlib.h>
#include "cipher.h"

#pragma pack (1)
// 13 bytes
typedef struct{
	unsigned int width;
	unsigned int height;
	unsigned char bit_depth; // bits por componente de cor
	unsigned char color_type; // indica se bloco PLTE vai existir e qual seu tipo
	unsigned char compression_method;
	unsigned char filter_method;
	unsigned char interlace_method;
}IHDR;

typedef struct{
	char identifier[4];
}IEND;
/* Se color_type do IHDR for 3: obrigatório
						2 ou 6: opcional
						0 ou 4: proibido
*/ 
typedef struct{
	// Armazena o mapa de cores
}PLTE;

int encipher_PNG(FILE *imagem, FILE *saida, FILE *texto);

void decipher_PNG (FILE *img, FILE *textoSaida);

#endif