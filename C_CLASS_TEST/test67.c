#include <stdio.h>
int factor(int x)
{
	int i;
	for (i = 2; i <= x; i++)
	{
		if(x % i == 0)
		return i;
	}
	return 0;
}
int main()
{
	int x,i,a = 0;
	printf("input a number: ");
	scanf("%d",&x);
	printf("%d =",x);

	while (x != 1)
	{
		if (a == 0)
		{
			printf(" %d", factor(x));
			a++;
		}
		else
		printf(" * %d",factor(x));	
	
		i = factor(x);
		x = x/i;
	}
	printf("\n");	
	
	return 0;
}
