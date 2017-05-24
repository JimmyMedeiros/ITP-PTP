#include <stdio.h>

int main(int argc, char const *argv[])
{
	int i, j, x, fat = 1, primo, is_primo;
	printf("Digite um valor para x\n");
	scanf("%d", &x);

	for (i = 2; i <= x; ++i)
	{
		fat *= i;
	}
	is_primo = 1;
	for (i = 1; i < fat; ++i)
	{
		primo = fat - i;
		for (j = 2; j < (primo/2)+1; ++j)
		{
			if ((primo%j) == 0)
			{
				is_primo = 0;
				break;
			}
		}
		if (is_primo > 0)
		{
			break;
		}
		is_primo = 1;
	}
	printf("Primo encontrado: %d\n", primo);

	return 0;
}