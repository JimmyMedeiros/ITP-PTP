#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <ctype.h>
#include <unistd.h>
#include <getopt.h>

//#include "funcoes.h"
#include "./libraries/ppm.h"
//#include "./libraries/bmp.h"
//#include "./libraries/cipher.h"

int main(int argc, char const *argv[])
{
	/* Trecho de código modificado do exemplo de getopt no site do projeto GNU:
	http://www.gnu.org/software/libc/manual/html_node/Example-of-Getopt.html#Example-of-Getopt */
	// Flags
	int eflag = 0, dflag = 0, sflag = 0;
	// Nome dos arquivos
	char *input_file = NULL, *output_file = NULL, *format = NULL, *image_name = NULL;
	// Variáveis do getopt
	int index, c;
	opterr = 0;
	// Demais variáveis
	char formato[3];
	long int tamanhoMensagem;
	int i, j;

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
		image_name = argv[optind++]; // pega a img como último argumento depois das opções
	for (index = optind; index < argc; index++)
		printf ("Non-option argument %s\n", argv[index]);
	
	// Opção Cifrar
	if (eflag != 0){
		// Abrir os arquivos passados pelo getopt		
		FILE *img, *imgSaida, *texto;
		if ((img = fopen(image_name, "r")) == NULL)
			perror("O Seguinte erro ocorre:\n");
		if ((texto = fopen(input_file, "r")) == NULL)
			perror("O Seguinte erro ocorre:\n");
		
		// Verificar o formato da img e coloca a mensagem
		if (strcmp(format, "ppm") || strcmp(format, "PPM")){
			if ((imgSaida = fopen("saida.ppm", "w")) == NULL)
				perror("O Seguinte erro ocorreu:\n");
			encipher_PPM(img, imgSaida, texto);
		}
		else if (strcmp(format, "bmp") || strcmp(format, "BMP")){
			if ((imgSaida = fopen("saida.bmp", "w")) == NULL)
				perror("O Seguinte erro ocorreu:\n");
			encipher_BMP(img, imgSaida, texto);
		}
		// Fechar arquivos
		fclose(imgSaida);
		fclose(texto);
		fclose(img);
	}
	// Opção Decifrar
	else if (dflag != 0){
		// Abrir os arquivos passados pelo getopt
		FILE *img, *textoSaida;
		if ((img = fopen(image_name, "r")) == NULL)
			perror("O Seguinte erro ocorre:\n");
		if ((textoSaida = fopen("textoSaida.txt", "w")) == NULL)
			perror("O Seguinte erro ocorre:\n");	
		// Pegando a mensagem 
		decipher_PPM (FILE *img, FILE *textoSaida);
		
		fclose(img);
		fclose(textoSaida);
	}
	
	return 0;
}