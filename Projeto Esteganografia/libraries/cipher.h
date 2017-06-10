#ifndef CIPHER_H
#define CIPHER_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct{
	unsigned char rgb[3];
}PixelRGB;

void encipher(void *array);

void decipher(void *array, void *output);

#endif