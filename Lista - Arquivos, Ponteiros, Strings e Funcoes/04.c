#include <stdio.h>
#include <stdlib.h>

void calcular_IMC(float peso, float altura){
	float imc;
	imc = peso/(altura*altura);
	if (imc < 17)
		printf("Muito abaixo do peso\n");
	else if (imc <= 18.49)
		printf("Abaixo do peso\n");
	else if (imc <= 24.99)
		printf("Peso normal\n");
	else if (imc <= 29.99)
		printf("Acima do peso\n");
	else if (imc <= 34.99)
		printf("Obesidade I\n");
	else if (imc <= 39.99)
		printf("Obesidade II (severa)\n");
	else 
		printf("Obesidade III (mórbida)\n");
}

int main(int argc, char const *argv[])
{
	float p, a;
	printf("Digite seu peso e sua altura:\n");
	
	while (scanf("%f %f", &p, &a)!=EOF){
		calcular_IMC(p, a);
	}

	return 0;
}