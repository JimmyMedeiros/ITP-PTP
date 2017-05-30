#include <stdio.h>

int fat (int n){
	if (n == 1 || n == 0)
		return 1;
	return n*fat(n-1);
}

int fatQuad (int n){
	return fat(2*n) / fat(n);
}

int main(int argc, char const *argv[])
{
	int num = 4;
	int f = fatQuad (num);
	printf("%d\n", f);
	return 0;
}