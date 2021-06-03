#include <stdio.h>
int sum_x(int x, int n)
{
	int i,sum = 0,k = x;
	for(i = 0; i <= n; i++)
	{
		if(i == 0)	
		{
			sum += 1;
			continue;
		}
		else
		{
			sum += x;
			x *= k;
		}
	}
	return sum;
}		
int main()
{
	int x,n;
	scanf("%d%d",&x,&n);
	printf("sum_x = %d\n",sum_x(x,n));
	return 0;
}

