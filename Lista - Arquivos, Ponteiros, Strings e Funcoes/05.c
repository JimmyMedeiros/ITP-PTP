#include <stdio.h>
#include <stdlib.h>

float conta_de_energia(int consumo){
	float conta;
	if (consumo <= 45){
		conta = 20;
	} else {
		conta = 20 + (consumo-45)*0.5;
	}
	return conta;
}


int main(int argc, char const *argv[])
{
	float valor_do_consumo;
	printf("Digite o consumo em KwH:\n");
	
	while (scanf("%f", &valor_do_consumo)!=EOF){
		printf("Valor da conta de energia: R$ %.2f\n", conta_de_energia(valor_do_consumo));
	}

	return 0;
}