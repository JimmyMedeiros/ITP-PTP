#include <stdio.h>
#include <stdlib.h>
#include <math.h>

enum colors {
	red=0, green, blue
};
typedef struct
{
	unsigned char rgb[3];
}PixelRGB;

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
void alocarMatrizDePixel (PixelRGB*** pixelMatrix, int xSize, int ySize){
	*pixelMatrix = (PixelRGB **) malloc(ySize * sizeof(PixelRGB*));
	for (int i = 0; i < ySize; ++i)
		(*pixelMatrix)[i] = malloc(xSize * sizeof(PixelRGB));
}
void desalocarMatrizDePixel (PixelRGB*** pixelMatrix, int ySize){
	for (int i = 0; i < ySize; ++i)
		free((*pixelMatrix)[i]);
	free(*pixelMatrix);
}
/* Coloca os caracteres na imagem */
PixelRGB** swapLastBit (PixelRGB **pixel, char characater){
	unsigned char r;
	/* Dica: usar um dos operadores OR XOR (^ |) com o resto da divisão */
	for (int i = 0; i < 8; ++i)
	{
		r = characater%2; // armazena cada bit do caracter de trás para frente
		if (r == 1)
		{
			(*(*pixel)).rgb[i%3] = (*(*pixel)).rgb[i%3] | r; // ex: 100101 | 1 = 0
		} else {
			(*(*pixel)).rgb[i%3] = (*(*pixel)).rgb[i%3] ^ 1; // ex: 100101 ^ 1 = 
		}
		if (((i+1)%3) == 0) // pula de pixel quando um é preenchido
			++pixel;
		characater /= 2; // diminui o caracter
	}
	return ++pixel;
}
/* Recupera os caracteres da imagem */
void getMessage (FILE *image, char* word){
	char f[3];
	unsigned char c, letter = 0;
	int i, x, y, r; // Só para armezenar as variáveis do getHeader
	getHeader(image, f, &x, &y, &r);
	for (i = 0; i < 5; ++i){
		for (int j = 0; j < 8; ++j){
			fscanf(image, "%c", &c);
			c %= 2; // pega o último bit
			letter += c * pow(2, j);
		}
		word[i] = letter;
		letter = 0;
	}
	word[i] = '\0';
}

int main(int argc, char const *argv[])
{
	FILE *imagem, *texto, *imagemSaida;
	char formato[3];
	int i, j;
	int tamanho_x, tamanho_y, extensao;
	
	/* Abrir os arquivos passados pelo terminal */
	if ((imagem = fopen(argv[argc - 1], "r")) == NULL)
		perror("O Seguinte erro ocorre:\n");
	if ((imagemSaida = fopen("saida.ppm", "w+")) == NULL)
		perror("O Seguinte erro ocorre:\n");
	if ((texto = fopen(argv[argc - 4], "r")) == NULL)
		perror("O Seguinte erro ocorre:\n");
	
	/* Pega as informações do cabeçário */
	getHeader (imagem, formato, &tamanho_x, &tamanho_y, &extensao);

	/* Aloca a matriz de Pixels */
	PixelRGB **matrizDePixel = NULL;
	alocarMatrizDePixel(&matrizDePixel, tamanho_x, tamanho_y);
	
	/* Pegar as informações da matriz */
	for (i = 0; i < tamanho_y; ++i)
		for (j = 0; j < tamanho_x; ++j)
			fscanf(imagem, "%c%c%c", &matrizDePixel[i][j].rgb[red], &matrizDePixel[i][j].rgb[green], &matrizDePixel[i][j].rgb[blue]);

	/* Alterando a imagem */
	PixelRGB **apontador = matrizDePixel;
	unsigned char c = 'a';
	while ((fscanf(texto, "%c", &c)) != EOF) {
		apontador = swapLastBit(apontador, c);
		// (*(*apontador)).rgb[blue] = c;
		// apontador++;
	}
	/* Colocando as informações da matriz em arquivo de Saída */
	printf("Gerando arquivo de saída\n");
	fprintf(imagemSaida, "%s\n%d %d\n%d\n", formato, tamanho_x, tamanho_y, extensao);
	for (i = 0; i < tamanho_y; ++i)
		for (j = 0; j < tamanho_x; ++j)
			fprintf(imagemSaida, "%c%c%c", matrizDePixel[i][j].rgb[red], matrizDePixel[i][j].rgb[green], matrizDePixel[i][j].rgb[blue]);

	/* Pegando a mensagem */
	char letra[10];
	getMessage (imagemSaida, letra);
	printf("%s\n", letra);

	/* Liberando espaço */
	desalocarMatrizDePixel(&matrizDePixel, tamanho_y);
	return 0;
}