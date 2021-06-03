#include <stdio.h>
int order(int x)
{
	int i1,i2,a = 0;
	while (x != 0)
	{
		i1 = x % 10;
		i2 = (x / 10) % 10;
		if (i1 < i2)
		{
			a ++;
			return (a == 0);
		}	
		x /= 10;
	}
	return ( a == 0);
}
int main()
{
	int x;
	printf("input a number: ");
	scanf("%d",&x);

	if (order(x))
	printf("%d is order",x);
	else
	printf("%d is not order",x);

	printf("\n");
	return 0;
}

