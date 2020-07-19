#include <stdio.h>
int main()
{
	int i,a,b,max,min;

	printf("input a number: \n");
	scanf("%d",&i);
	max = min = i%10;
	while (i != 0)
	{
		a = i % 10;
	
		if (a > max)	
		max = a;
		if (a < min)
		min = a;
		
		i = i/10;
	}
	printf("max = %d\nmin = %d\n",max,min);
	
	return 0;
}

