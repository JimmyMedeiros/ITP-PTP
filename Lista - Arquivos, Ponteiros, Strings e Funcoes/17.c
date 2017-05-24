#include <stdio.h>

int main(int argc, char const *argv[])
{
	int n, i, fatorial = 1, soma = 0;
	scanf("%d", &n);
	for (i = 2; i <= n; ++i)
	{
		fatorial *= i;
	}

	while(fatorial > 0){
		soma += fatorial%10;
		fatorial /= 10;
	}
	printf("%d\n", soma);

	return 0;
}