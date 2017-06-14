#include <stdio.h>
#include "cipher.h"

/* Coloca os caracteres na imagem */
PixelRGB* swapLastBit (PixelRGB *pixel, char character){
	// A operação '&' com 0xFE (11111110) zera o bit menos significativo 
	for (int i = 0; i < 8; ++i){
		(*pixel).rgb[i%3] = ((*pixel).rgb[i%3]&0xFE)^character%2;
		// pula de pixel quando um é preenchido
		if (((i+1)%3) == 0)
			++pixel;
		// Passa o próximo bit para o final do byte
		character >>= 1; 
	}
	return ++pixel;
}

// Recupera os caracteres da imagem 
void getMessage (FILE *image, char* word, int wordSize){
	// Pega a Mensagem até encontrar um EOT ou até a capavidade máxima da imagem
	int i = 0; 
	unsigned char c = 0, letter = 0;
	while (letter != 3 && i < wordSize){
		letter = 0;
		for (int j = 0; j < 8; ++j){
			fscanf(image, "%c", &c);
			c %= 2; // pega o último bit
			letter += (c <<= j); // coloca o bit em seu devido lugar
		}
		fscanf(image, "%c", &c); // pega o valor blue que sobrou
		word[i] = letter;
		++i;
	}
	word[i-1] = '\0';
}