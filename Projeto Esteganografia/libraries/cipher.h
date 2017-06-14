#ifndef CIPHER_H
#define CIPHER_H

#include <stdio.h>
#include <stdlib.h>
//#include <math.h>

typedef struct{
	unsigned char rgb[3];
}PixelRGB;

PixelRGB* swapLastBit (PixelRGB *pixel, char character);

void getMessage (FILE *image, char* word, int wordSize);

#endif