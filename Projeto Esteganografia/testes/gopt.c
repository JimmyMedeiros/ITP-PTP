#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>

int main (int argc, char **argv)
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
	int i;

	opterr = 0;

	while ((i = getopt (argc, argv, "edi:f:o:s")) != -1){
		switch (i)
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
	
	return 0;
}
