#include <stdio.h>
int pow2(int x )
{
	int sum = 0,i,a,m = 1;
	for (i = 1 ; i <= x ; i++)	
	{
		m = m*2;
		sum = sum + m;
	}
	sum = sum + 1;

	return sum;
}
int pow1(int x)
{
	int i,m = 1;
	for (i = 1; i <= (x-1); i++ )
	{
		m = m*2;
	}
	return m;
}
int sum(int x)
{
	int i,sum = 0;
	for (i = 1; i <= x ; i++)
	{
		sum = sum + i;
	}
	return sum;
}
int main()
{
	int x;
	printf("input number: ");
	scanf("%d",&x);
	printf("m = %d\n",pow1(x));
	
	return 0;
}
