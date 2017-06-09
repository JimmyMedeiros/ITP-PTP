#ifndef PPM_H
#define PPM_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

enum colors {
	red=0, green, blue, alpha
};
enum formats
{
	ppm=0, bmp
};
typedef struct
{
	unsigned char rgb[3];
}PixelRGB;
typedef struct
{
	char format[3];
	int xSize;
	int ySize;
	int color_depth; // OBS: a profundidade de cada valor RGB, e não do pixel em si
}PPM_Header;

void get_PPM_Header (FILE *image, char *formato, int* xSize, int* ySize, int* range);
/* Alocação e desalocação da Matriz */
void alocarMatrizDePixel (PixelRGB** pixelMatrix, int xSize, int ySize);
// void desalocarMatrizDePixel (PixelRGB** pixelMatrix, int ySize);
/* Coloca os caracteres na imagem */
//char* swapLastBit (char* pointer, char characacter);
PixelRGB* swapLastBit (PixelRGB *pixel, char characater);
/* Recupera os caracteres da imagem */
void getMessage (FILE *image, char* word, int wordSize);

#endif