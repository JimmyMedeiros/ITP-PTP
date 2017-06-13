#include <stdio.h>
#include "png.h"

int encipher_PNG(FILE *imagem, FILE *saida, FILE *texto){
	// Variáveis
	IHDR ihdr;
	IEND iend;
	// Ler o cabeçalho PNG 
	fread(&ihdr, 13, 1, imagem);
	fread(&iend, 4, 1, imagem);
	// Alocar e ler os pixels 
	printf("%c%c%c%c\n", iend[0], iend[1], iend[2], iend[3]);
	// Colocar a mensagem
	/*rewind(texto);
	PixelRGB *ptr = pixelArray;
	char c = 'a';
	while ((fscanf(texto, "%c", &c)) != EOF)
		ptr = swapLastBit(ptr, c);
	swapLastBit(ptr, '\0'); // Colocando o sinal de final de texto;
	
	// Escrever o arquivo de saída
	
	free(pixelArray);*/

	return 0;
}

void decipher_BMP (FILE *img, FILE *textoSaida){
	// Variáveis

	// Ler o cabeçalho PNG
	
	// Pegando a mensagem
	//int tamanho_Mensagem = (largura * altura)/3;
	/*char *letras = NULL;
	letras = (char*)malloc(tamanho_Mensagem * sizeof(char));
	if (letras == NULL)
		fprintf(stderr, "Memória insuficiente\n");
	getMessage (img, letras, tamanho_Mensagem);
	// Colocando a mensagem no texto 
	fprintf(textoSaida, "%s", letras);

	free(letras);*/
}