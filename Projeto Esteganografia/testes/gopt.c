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
	char *input_file = NULL;
	char *format = NULL;
	char *image = NULL;
	int index;
	int i;

	opterr = 0;

	while ((i = getopt (argc, argv, "edif:")) != -1){
		switch (i)
			{
			case 'e': eflag = 1; break;
			case 'd': dflag = 1; break;
			case 'i': input_file = optarg; break;
			case 'f': format = optarg; image = optarg; break;
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
	printf ("aflag = %d, bflag = %d, input_file = %s\n", eflag, dflag, input_file);
	printf("formato = %s, imagem: %s\n", image, input_file);

	for (index = optind; index < argc; index++)
		printf ("Non-option argument %s\n", argv[index]);
	return 0;
}
