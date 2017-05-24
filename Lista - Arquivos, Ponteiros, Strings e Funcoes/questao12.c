#include <stdio.h>


int main(int argc, char const *argv[])
{
	int a, *b, **c , *** d;

	//scanf("%d", &a);

		b = &a,
		c = &b,
		d = &c;

	scanf("%d", &a);

	printf("Valor: %d \nDobro: %d \nTriplo: %d  \nQuadruplo:%d \n", a, (*b + *b) , (**c + **c + **c) ,(***d + ***d + ***d + ***d) );

	return 0;
}