#include <stdio.h>
#include <math.h>

double calcularSoma(int n){ // double porque a função pow retorna double
	double soma = 0; // variável para armezenar a soma
	if (n == 0) return 1.0; // caso base
	soma += 1.0/pow(2, n);
	soma += calcularSoma(n-1); // entra na recursão para somar 1/2^(n-1) 
	return soma;
}

int main(int argc, char const *argv[])
{
	double d = calcularSoma(20);
	printf("%lf\n", d);
	return 0;
}
