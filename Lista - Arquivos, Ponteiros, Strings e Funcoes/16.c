#include <stdio.h>
#include <string.h>

int find_substr(const char *string1, const char *string2){
	int i, j, len_str1 = strlen(string1);
	j = 0;
	for (i = 0; i < len_str1; ++i)
	{
		if (string1[i] == string2[0])
		{
			while (string1[i+j] == string2[j]){
				++j;
			}
			if (string2[j] == '\0')
			{
				return i;
			}
		}
	}
	return -1;
}

int main(int argc, char const *argv[])
{
	char *palavra1, *palavra2;
	palavra1 = "paralelepípedo";
	palavra2 = "lele";

	int n = find_substr(palavra1, palavra2);
	printf("palavra2 encontrada em: %d\n", n);

	return 0;
}