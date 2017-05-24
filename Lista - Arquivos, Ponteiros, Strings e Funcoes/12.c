#include <stdio.h>

int main(int argc, char const *argv[])
{
	int a, *b, **c, ***d;
	b = &a;
	c = &b;
	d = &c;
	printf("Digite um número: \n");
	scanf("%d", b);

	printf("Número: %d \nDobro: %d\nTriplo: %d\nQuádruplo: %d\n", a, (*b)+a, (*(*c))+a+a, (*(*(*d)))+a+a+a);

	return 0;
}