#include <stdio.h>
#include "ppm.h"


void get_PPM_Header (FILE *image, PPM_Header *hdr){
	// Pegar as informações do cabeçalho
	char c = 'a';
	fscanf (image, "%s", hdr->format);
	c = fgetc (image);// Pegar o '\n'
	c = fgetc (image);// Pega um char para verificar se tem comentário
	if (c == '#')
		while (c != '\n')// Pega o comentário
			c = fgetc (image);
	else
		fseek ( image , -1 , SEEK_CUR );
	fscanf(image, "%d %d %d%c", &hdr->xSize, &hdr->ySize, &hdr->color_depth, &c); 
	// c armazena a tabulação ('\t')
}
int encipher_PPM(FILE *imagem, FILE *imagemSaida, FILE *texto){
	PPM_Header header;
	get_PPM_Header(imagem, &header);
	int i;
	// Antes de alterar a imagem, verifica se cabe a mensagem 
	fseek(texto, 0L, SEEK_END);
	long int tamanho_Mensagem = ftell(texto), mensagem_Max = ((header.xSize*header.ySize)/3);
	if(tamanho_Mensagem > mensagem_Max){
		fprintf(stderr, "A mensagem do arquivo não cabe na imagem.\nO arquivo deve ter no máximo %ld bytes.\n", mensagem_Max);
		return 1;
	}
	// Aloca a matriz
	PixelRGB *pxlMtrx = NULL;
	pxlMtrx = (PixelRGB*)malloc(header.xSize*header.ySize*sizeof(PixelRGB));
	if (pxlMtrx == NULL)
		fprintf(stderr, "Memória insuficiente.\n");
	// Pegar as informações da matriz
	for (i = 0; i < (header.xSize*header.ySize); ++i)
		fscanf(imagem, "%c%c%c", &pxlMtrx[i].rgb[red], &pxlMtrx[i].rgb[green], &pxlMtrx[i].rgb[blue]);
	// Alterando a imagem
	rewind(texto);
	// Lembrete: colocar esse trecho no arquivo cipher.c
	PixelRGB *ptr = pxlMtrx;
	char c = 'a';
	while ((fscanf(texto, "%c", &c)) != EOF){
		ptr = swapLastBit(ptr, c);
	}
	swapLastBit(ptr, 3); // Colocando o sinal de fim de texto - EOT;
	
	// Colocando as informações da matriz em arquivo de Saída
	printf("Gerando arquivo de saída\n");
	fprintf(imagemSaida, "%s\n%d %d\n%d\n", header.format, header.xSize, header.ySize, header.color_depth);
	for (i = 0; i < (header.ySize*header.xSize); ++i)
		fprintf(imagemSaida, "%c%c%c", pxlMtrx[i].rgb[red], pxlMtrx[i].rgb[green], pxlMtrx[i].rgb[blue]);
	
	free(pxlMtrx);
	
	return 0;
}

void decipher_PPM (FILE *img, FILE *textoSaida){
	// Pegando o cabeçalho 
	PPM_Header hdr;
	get_PPM_Header (img, &hdr);
	
	// Pegando a mensagem
	int tamanho_Mensagem = (hdr.xSize*hdr.ySize)/3;
	char *letras = NULL;
	letras = (char*)malloc(tamanho_Mensagem * sizeof(char));
	if (letras == NULL)
		fprintf(stderr, "Memória insuficiente\n");
	getMessage (img, letras, tamanho_Mensagem);
	// Colocando a mensagem no texto 
	fprintf(textoSaida, "%s", letras);

	free(letras);
}