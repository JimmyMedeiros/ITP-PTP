#include <stdio.h>
 
int main() {
 
    int i, j;
	char T;
	double soma = 0, count = 0.0, matriz[12][12];
	scanf("%c", &T);
	for (i = 0; i < 12; ++i)
	{
		for (j = 0; j < 12; ++j)
		{
			scanf("%lf", &matriz[i][j]);
			if (j < i && j > 11-i)
			{
				soma += matriz[i][j];
				count++;
			}
		}
	}
	if (T == 'S')
	{
		printf("%.1lf\n", soma);
	}
	else if (T == 'M'){
		printf("%.1lf\n", soma/count);
	}
 
    return 0;
}