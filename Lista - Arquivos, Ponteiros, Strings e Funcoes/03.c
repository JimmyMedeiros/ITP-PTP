#include <stdio.h>
#include <stdlib.h>

void swap(int* x, int* y){
	int temp;
	temp = *x;
	*x = *y;
	*y = temp;
}

int main(int argc, char const *argv[])
{
	int a, b;
	scanf("%d %d", &a, &b);
	printf("Valor de a: %d. Valor de b: %d\n", a, b);
	printf("Depois do swap:\n");
	swap(&a, &b);
	printf("Valor de a: %d. Valor de b: %d\n", a, b);

	return 0;
}