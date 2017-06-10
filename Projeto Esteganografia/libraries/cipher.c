#include <stdio.h>
#include "cipher.h"

/* Coloca os caracteres na imagem */
PixelRGB* swapLastBit (PixelRGB *pixel, char character){
	unsigned char r;
	/* Dica: usar um dos operadores OR XOR (^ |) com o resto da divisão */
	for (int i = 0; i < 8; ++i){
		r = character%2; // armazena cada bit do caracter de trás para frente
		if ((*pixel).rgb[i%3]%2 != r){ // verifica se o último bit é igual
			if (r == 1)
				(*pixel).rgb[i%3] = (*pixel).rgb[i%3] | r; // ex: 100101 ^ 1 = 1 
			else 
				(*pixel).rgb[i%3]--; // ex: 100101 ^ 1 = 0
		}
		if (((i+1)%3) == 0) // pula de pixel quando um é preenchido
			++pixel;
		character /= 2; // diminui o caracter
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
			//printf("%d", c);
			letter += c * pow(2, j);
		}
		fscanf(image, "%c", &c); // pega o valor blue que sobrou
		word[i] = letter;
		++i;
	}
	word[i-1] = '\0';
}