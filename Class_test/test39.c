#include <stdio.h>
int main()
{
	int a,i,sum,k;
	sum = 0;
	i = 1;
	printf("input a number >= 10: \n");
	do
	{
		scanf("%d",&a);
		if (a <= 10)
		printf("input a number >= 10: \n");
	}
	while(a <= 10);
	
	while(  a != 10)
	{	
		k = a;
		
		while( k != 0)
		{
			sum = k % 10 + sum;
			i = (k % 10) * i;
			k = k/10;

		}
		
		if (i == sum)
		printf("%d\n",a);
	
		sum = 0, i = 1;
		
		a--;
	}	
 

	return 0;
}	
