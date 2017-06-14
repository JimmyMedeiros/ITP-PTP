#include <stdio.h>
#include "gif.h"

void print_ctrl_block(CONTROL_BLOCK *cb){
	// Header
	for (int i = 0; i < 3; ++i)
		printf("%c", cb->hdr.signature[i]);
	printf(" Versão: ");
	for (int i = 0; i < 3; ++i){
		printf("%c", cb->hdr.version[i]);
	}printf("\n");
	// Logical Screen Description
	printf("Largura:%u, ", cb->LgScrDsc.width);
	printf("Altura:%u\n", cb->LgScrDsc.height);
	printf("Packed Fields:%u\n", cb->LgScrDsc.pckdFlds);
	int c = cb->LgScrDsc.pckdFlds;
	for (int i = 0; i < 8; ++i){
		printf("%d", c%2);
		c /= 2;
	}
	printf("\nÍndice de cores:%u\n", cb->LgScrDsc.bg_color_index);
	printf("Pixel Aspect Ratio:%d\n", cb->LgScrDsc.pxl_Aspect_Ratio);
	// Color table
	cb->color_table = malloc(256*sizeof(PixelRGB));
	// Graphical Control Extension
	
}
int encipher_GIF(FILE *imagem, FILE *saida, FILE *texto){
	// variáveis
	CONTROL_BLOCK ctrl_block; // 22 bytes
	fread(&ctrl_block, 13, 1, imagem);
	// Color table size
	int ct_size = 256;
	print_ctrl_block(&ctrl_block);
	PixelRGB *pxl = ctrl_block.color_table;
	fread(pxl, 3, ct_size, imagem);
	for (int i = 0; i < ct_size; ++i){
		//printf("%d, %d, %d\n", pxl->rgb[0], pxl->rgb[1], pxl->rgb[2]);
		pxl++;
	}
	// Imagem Descriptor 
	fread(&ctrl_block.GrphCtrlExt, 1, 8, imagem);
	printf("%x\n", ctrl_block.GrphCtrlExt.intro);
	IMAGE_RENDERING img_render;
	fread(&img_render, 1, 10, imagem);
	printf("Largura: %d\n", img_render.desc.width);

	free(ctrl_block.color_table);

	return 0;
}

void decipher_GIF (FILE *img, FILE *textoSaida){
	// TODO
}