#include <stdio.h>
#include <stdlib.h>

int is_amigo(int *a, int *b){
	int i, soma_a = 0, soma_b = 0;
	for (i = 1; i <= ((*b/2)+1) /* só para otimizar, um número não pode ser divisível por outro que seja maior que sua metade */; ++i)
	{
		if (*b%i == 0)
		{
			soma_b += i;
		}
		if (*a%i == 0)
		{
			soma_a += i;
		}
		if (soma_b > *a)
		{
			return 0;
		}
		if (soma_a > *b)
		{
			return 0;
		}
	}
	if (soma_a == *b && soma_b == *a)
	{
		return 1;
	}
	else if (soma_a < *b)
	{
		++(*a);
		*b = *a + 1;
		return 0;
	}
	else {
		return 0;
	}
}

int main(int argc, char const *argv[])
{
	int i, j, limite = 100000;
	for (i = 200; i <= limite; ++i)
	{
		for (j = i+1; j <= limite; ++j)
		{
			if (is_amigo(&i,&j))
			{
				printf("(%d, %d)\n", i, j);
				i = j;
			}
		}
	}

	/*if (is_amigo(284, 220))
	{
		printf("284 e 220 são amigos :D\n");
	} else {
		printf("284 e 220 NÃO são amigos :(\n");
	}*/

	return 0;
}