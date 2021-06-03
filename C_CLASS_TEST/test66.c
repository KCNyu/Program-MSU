#include <stdio.h>
int factor()
{
	int x,i,a = 0;
	printf("input a number: ");
	scanf("%d",&x);
	printf("%d =",x);
	while(x != 0)
	{		
		for (i = 2; i <= x; i++)
		{
			if ( x % i == 0 && a == 0 )
			{
				printf(" %d",i);
				a++;
				break;
			}
			if (x % i == 0 && a != 0 )
			{
				printf(" * %d",i);
				break;
			}
		}
		x = x / i;
	}
	printf("\n");
	return 0;
}
int main()
{
	int x;
	factor(x);
	return 0;
}
