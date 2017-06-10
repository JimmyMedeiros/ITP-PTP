#include <stdio.h>
//#include "cipher.h"
#include "ppm.h"


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
void get_PPM_Header (FILE *image, PPM_Header *hdr){
	/* Pegar as informações do cabeçalho */
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
	swapLastBit(ptr, '\0'); // Colocando o sinal de final de texto;
	
	// Colocando as informações da matriz em arquivo de Saída
	printf("Gerando arquivo de saída\n");
	fprintf(imagemSaida, "%s\n%d %d\n%d\n", header.format, header.xSize, header.ySize, header.color_depth);
	for (i = 0; i < (header.ySize*header.xSize); ++i)
		fprintf(imagemSaida, "%c%c%c", pxlMtrx[i].rgb[red], pxlMtrx[i].rgb[green], pxlMtrx[i].rgb[blue]);
	
	free(pxlMtrx);
	
	return 0;
}
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

void decipher_PPM (FILE *img, FILE *textoSaida){
	fseek(texto, 0L, SEEK_END);
	long int tamanho_Mensagem = ftell(texto);
	// Pegando a mensagem 
	char letras[tamanhoMensagem];
	getMessage (img, letra, tamanho_Mensagem);
	fprintf(textoSaida, "%s", letras);
}