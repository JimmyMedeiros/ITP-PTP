# include <stdio.h>
# define N 3

int main ( int argc , char const * argv [])
{
	int numeros[N] = {1768382797 , 1699618913 , 560034407};
	char *p;
	p = (char*) numeros; /* p recebe o endereço do primeiro elemento do vetor números, ou seja, o endereço que armazena o valor 1768382797 */
	for (int i = 0; i < N*4; ++ i )
	{
		printf ("%c" , *(p++)) /* imprime 1byte de numeros[0] e incrementa 1 no endereço, indo para o segundo byte de numeros[0]. Após percorrer os 4bytes ele vai para numeros[1] e assim por diante até percorrer todos os 12bytes do vetor */;
	}
	return 0;
}