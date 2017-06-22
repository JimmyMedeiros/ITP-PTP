#include <stdio.h>
#include "gif.h"

void print_ctrl_block(CONTROL_BLOCK *cb){
	// TODO
}
int encipher_GIF(FILE *imagem, FILE *saida, FILE *texto){
	// variáveis
	CONTROL_BLOCK ctrl_block; // ? bytes
	int ct_size = 256;
	img_Descriptor img_render;
	
	// Informações do Control Block antes da color table
	fread(&ctrl_block, 13, 1, imagem);
	// Verifica se a imagem cabe
	unsigned char color_table_size = ctrl_block.pckdFlds&0xFE;
	if (verify_message_size(color_table_size, 1, texto)){
		return 1;
	}
	// Color table 
	ctrl_block.color_table = malloc(ct_size*sizeof(PixelRGB));
	PixelRGB *pxl = ctrl_block.color_table;
	fread(pxl, 3, ct_size, imagem);
	// A mensagem é cifrada na tabela de cores
	// Colocar a mensagem
	rewind(texto);
	PixelRGB *ptr = pxl;
	char c = 'a';
	while ((fscanf(texto, "%c", &c)) != EOF)
		ptr = swapLastBit(ptr, c);
	swapLastBit(ptr, '\0');// Colocando o sinal de final de texto;

	// Image Descriptor
	fread(&ctrl_block.GrphCtrlExt, 1, 8, imagem);
	// Image Render
	fread(&img_render, 1, 10, imagem);
	
	// Bloco de controle
	fwrite(&ctrl_block, 13, 1, saida);
	// tabela de cores
	fwrite(pxl, 256, 3, saida);
	// Graphic Control Extension
	fwrite(&ctrl_block.GrphCtrlExt, 1, 8, saida);
	// Image Render
	fwrite(&img_render, 1, 10, saida);
	// Esse trecho pega os dados da imagem que estão compactados pelo algoritmo LZW e copia para a imagem de saída
	char img_data, flag = 0;
	while (flag == 0) {
		img_data=getc(imagem);
		fwrite(&img_data, 1, 1, saida);
		flag = feof(imagem);
	}
	
	free(ctrl_block.color_table);

	return 0;
}

void decipher_GIF (FILE *img, FILE *textoSaida){
	// variáveis
	CONTROL_BLOCK ctrl_block; // ? bytes
	//int ct_size = 256;
	
	// Informações do Control Block antes da color table
	fread(&ctrl_block, 13, 1, img);
	// Pegando a color table
	unsigned int color_table_size = (0x02<<(ctrl_block.pckdFlds&0x7))-1;
	printf("%d\n", color_table_size);
	int tamanho_Mensagem = (color_table_size)/3;
	printf("%d\n", tamanho_Mensagem);
	char *letras = NULL;
	letras = (char*)malloc(tamanho_Mensagem * sizeof(char));
	if (letras == NULL)
		fprintf(stderr, "Memória insuficiente\n");
	getMessage (img, letras, tamanho_Mensagem);
	// Colocando a mensagem no texto 
	rewind(textoSaida);
	fprintf(textoSaida, "%s", letras);
	printf("%s\n", letras);
}