#include <stdio.h>
#include <stdlib.h>

#include <ctype.h>
#include <unistd.h>
#include <getopt.h>

#include "funcoes.h"
#include "./libraries/ppm.h"
#include "./libraries/bmp.h"
#include "./libraries/cipher.h"

int main(int argc, char const *argv[])
{
	/* Trecho de código modificado do exemplo de getopt no site do projeto GNU:
	http://www.gnu.org/software/libc/manual/html_node/Example-of-Getopt.html#Example-of-Getopt */
	int eflag = 0;
	int dflag = 0;
	int sflag = 0;
	char *input_file = NULL;
	char *output_file = NULL;
	char *format = NULL;
	char *image = NULL;
	int index;
	int c;
	opterr = 0;

	while ((c = getopt (argc, argv, "edi:f:o:s")) != -1){
		switch (c)
			{
			case 'e': 
				if (dflag !=0) fprintf(stderr, "-e option is not allowed along with -c option.\n");
				else eflag = 1; 
				break;
			case 'd': 
				if (dflag !=0) fprintf(stderr, "-d option is not allowed along with -e option.\n");
				else dflag = 1; 
				break;
			case 'i': 
				input_file = optarg; 
				break;
			case 'f': 
				format = optarg;
				break;
			case 'o':
				if (dflag !=0) fprintf(stderr, "-o option is not allowed along with -s option.\n");
				else output_file = optarg;
				break;
			case 's':
				sflag = 1;
				break;
			case '?':{
				if (optopt == 'i')
					fprintf (stderr, "Option -%c requires an argument.\n", optopt);
				else if (isprint (optopt))
					fprintf (stderr, "Unknown option `-%c'.\n", optopt);
				else{
					fprintf (stderr, "Unknown option character `\\x%x'.\n", optopt);
					return 1;
				}
			}
			default:
				abort ();
		}
	}
	if (optind < argc)
		image = argv[optind++]; // pega a imagem como último argumento depois das opções
	for (index = optind; index < argc; index++)
		printf ("Non-option argument %s\n", argv[index]);

	char formato[3];
	int i, j;
	
	// Opção Cifrar
	if (eflag != 0)
	{
		// Abrir os arquivos passados pelo getopt		
		FILE *imagem, *imagemSaida, *texto;
		if ((imagem = fopen(image, "r")) == NULL)
			perror("O Seguinte erro ocorre:\n");
		if ((texto = fopen(input_file, "r")) == NULL)
			perror("O Seguinte erro ocorre:\n");
		if ((imagemSaida = fopen("saida.ppm", "w+")) == NULL)
			perror("O Seguinte erro ocorre:\n");

		// Verificar o formato da imagem
		
		// Fechar arquivos
		fclose(imagemSaida);
		fclose(texto);
	} 
	// Opção Decifrar
	else if (dflag != 0)
	{
		// Abrir os arquivos passados pelo getopt
		FILE *textoSaida;
		if ((textoSaida = fopen("textoSaida.txt", "w")) == NULL)
			perror("O Seguinte erro ocorre:\n");
		/* Pegando a mensagem */
		rewind(imagemSaida);
		char letra[tamanhoMensagem];
		getMessage (imagemSaida, letra, tamanhoMensagem);
		fprintf(textoSaida, "%s", letra);
	}
	int tamanho_x, tamanho_y, extensao;

	/* Pega as informações do cabeçário */
	getHeader (imagem, formato, &tamanho_x, &tamanho_y, &extensao);

	/* Aloca a matriz de Pixels */
	PixelRGB *matrizDePixel = NULL;
	alocarMatrizDePixel(&matrizDePixel, tamanho_x, tamanho_y);
	if (matrizDePixel == NULL)
		fprintf(stderr, "Memória insuficiente.\n");

	/* Pegar as informações da matriz */
	for (i = 0; i < (tamanho_y * tamanho_x); ++i)
		fscanf(imagem, "%c%c%c", &matrizDePixel[i].rgb[red], &matrizDePixel[i].rgb[green], &matrizDePixel[i].rgb[blue]);

	/* Antes de alterar a imagem, verifica se cabe a mensagem */
	fseek(texto, 0L, SEEK_END);
	long int tamanhoMensagem = ftell(texto), MensagemMax = ((tamanho_x*tamanho_y)/3);
	if(tamanhoMensagem > MensagemMax){
		fprintf(stderr, "A mensagem do arquivo \"%s\" não cabe na imagem.\nO arquivo deve ter no máximo %ld bytes.\n", nomeTexto, MensagemMax);
		return 1;
	}
	
	/* Alterando a imagem */
	rewind(texto);
	PixelRGB *apontador = matrizDePixel;
	char c = 'a';
	while ((fscanf(texto, "%c", &c)) != EOF){
		apontador = swapLastBit(apontador, c);
	}
	swapLastBit(apontador, '\0'); // Colocando o sinal de final de texto;
	
	/* Colocando as informações da matriz em arquivo de Saída */
	printf("Gerando arquivo de saída\n");
	fprintf(imagemSaida, "%s\n%d %d\n%d\n", formato, tamanho_x, tamanho_y, extensao);
	for (i = 0; i < tamanho_y; ++i)
		for (j = 0; j < tamanho_x; ++j){
			fprintf(imagemSaida, "%c%c%c", matrizDePixel[i*tamanho_x + j].rgb[red], matrizDePixel[i*tamanho_x + j].rgb[green], matrizDePixel[i*tamanho_x + j].rgb[blue]);
		}

	/* Liberando espaço e fechando arquivos */
	free(matrizDePixel);
	fclose(imagem);
	return 0;
}