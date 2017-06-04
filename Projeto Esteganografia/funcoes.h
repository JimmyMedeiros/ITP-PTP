#ifndef FUNCOES_H
#define FUNCOES_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

enum colors {
	red=0, green, blue, alpha
};
typedef struct
{
	unsigned char rgb[3];
}PixelRGB;

void getHeader (FILE *image, char *formato, int* xSize, int* ySize, int* range);
/* Alocação e desalocação da Matriz */
void alocarMatrizDePixel (PixelRGB*** pixelMatrix, int xSize, int ySize);
void desalocarMatrizDePixel (PixelRGB*** pixelMatrix, int ySize);
/* Coloca os caracteres na imagem */
PixelRGB* swapLastBit (PixelRGB *pixel, char characater);
/* Recupera os caracteres da imagem */
void getMessage (FILE *image, char* word, int wordSize);

#endif