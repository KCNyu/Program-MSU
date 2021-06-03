#include <stdio.h>
int main()
{
	int i = 1, sum = 0;
	while (i <= 100)
	{
		sum = sum + i;
		i = i + 1;
	}
	printf("sum = %d\n",sum);
	
	return 0;

}

