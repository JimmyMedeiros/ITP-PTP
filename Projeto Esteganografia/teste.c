#include <stdio.h>
#include <stdlib.h>

typedef struct
{
	int *red;
	int *green;
	int *blue;
} Pixel;

Pixel readRGBPixel (FILE *img){
	Pixel px;
	fscanf(img, "%p %p %p" px.red, px.green, px.blue);
	return px;
}

int swapLastBit (int *color, char bit){
	if ((*color)%2 != bit) ~(*color);
}

void putMessage (FILE *matrixBegining, char *message){
	Pixel px;
	int i = 0;
	while (message[i] != '\0'){
		
		while (!feof(matrixBegining) && message[i] > 0){
			px = readRGBPixel(matrixBegining);
			// armazenar somente no valor blue
			swapLastBit (px.blue, message[i]%2);
			message[i] /= 2;
		}
		i++;
	}
}

int main(int argc, char const *argv[])
{
	FILE *imagem, *texto;
	char mensagem[100], nomeImagem;
	
	if ((imagem = fopen("teste.ppm", "r+") == NULL))
		perror("O Seguinte erro ocorre:\n");

	if ((texto = fopen("segredo.txt", "r") == NULL))
		perror("O Seguinte erro ocorre:\n");


	return 0;
}