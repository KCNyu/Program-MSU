#include <stdio.h>

int main()
{	
	float i,n,sum = 0;
	printf("input number: ");
	scanf("%f",&n);
	for (i = 1; i <= n; i += 0.1)
	{		
		sum += i*i;
	}
	printf("sum = %f\n",sum);
	return 0;
}
