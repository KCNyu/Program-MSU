#include <stdio.h>
#include <math.h>
int main()
{
	int i, j, k;

	i = 1 + 2;
	j = 1 + 2 * 3;
	k = i + j + -1 + pow(2,3);

	printf("i = %d\n",i);
	printf("j = %d\n",j);
	printf("k = %d\n",k);
	
	return 0;
}
