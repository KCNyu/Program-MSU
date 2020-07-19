#include <stdio.h>
int main()
{
	int i,sum1 = 0,sum2 = 0;
	for(i = 1; i <= 100; i++)
	{
		if(i%2 == 0)
			sum2 += i;
		else
			sum1 += i;
	}
	printf("sum1 = %d\nsum2 = %d\n",sum1,sum2);
	return 0;
}
