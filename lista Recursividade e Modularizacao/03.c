#include <stdio.h>

int contarFreq(int n, int k){
	int count = 0;
	if (n == 0)		return 0;

	count += contarFreq(n/10,k);
	if (n%10 == k) return count+1;
	return count;
}

int main(int argc, char const *argv[])
{
	int num = 685256945;
	int c = contarFreq(num, 6);
	printf("%d\n", c);
	return 0;
}