#include <stdio.h>
#include "funcoes.h"

void getHeader (FILE *image, char *formato, int* xSize, int* ySize, int* range){
	/* Pegar as informações do cabeçalho */
	char c = 'a';
	fscanf (image, "%s", formato);
	c = fgetc (image);// pegar o '\n'
	c = fgetc (image);
	if (c == '#')
		while (c != '\n')
			c = fgetc (image);
	else
		fseek ( image , -1 , SEEK_CUR );
	fscanf(image, "%d %d %d%c", xSize, ySize, range, &c); // c armazena a tabulação ('\t')
}
/* Alocação e desalocação da Matriz */
void alocarMatrizDePixel (PixelRGB** pixelMatrix, int xSize, int ySize){
	*pixelMatrix = (PixelRGB *) malloc(xSize * ySize * sizeof(PixelRGB));
}
/*void desalocarMatrizDePixel (PixelRGB** pixelMatrix, int ySize){
	for (int i = 0; i < ySize; ++i)
		free((*pixelMatrix)[i]);
	free(*pixelMatrix);
}*/

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
/* Recupera os caracteres da imagem */
void getMessage (FILE *image, char* word, int wordSize){
	char f[3];
	unsigned char c = 0, letter = 0;
	int i, x, y, r; // Só para armezenar as variáveis do getHeader
	getHeader(image, f, &x, &y, &r);
	for (i = 0; i < wordSize; ++i){
		for (int j = 0; j < 8; ++j){
			fscanf(image, "%c", &c);
			c %= 2; // pega o último bit
			//printf("%d", c);
			letter += c * pow(2, j);
		}
		fscanf(image, "%c", &c); // pega o valor blue que sobrou
		word[i] = letter;
		letter = 0;
	}
	word[i] = '\0';
}