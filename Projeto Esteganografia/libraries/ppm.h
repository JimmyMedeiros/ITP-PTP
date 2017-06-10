#ifndef PPM_H
#define PPM_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "cipher.h"

enum colors {
	red=0, green, blue
};

typedef struct{
	char format[3];
	int xSize;
	int ySize;
	int color_depth; // OBS: a profundidade de cada valor RGB, e não do pixel em si
}PPM_Header;

PixelRGB* swapLastBit (PixelRGB *pixel, char character);

void get_PPM_Header (FILE *image, PPM_Header *hdr);

int encipher_PPM(FILE *imagem, FILE *imagemSaida, FILE *texto);

void getMessage (FILE *image, char* word, int wordSize);

void decipher_PPM (FILE *img, FILE *textoSaida);

#endif