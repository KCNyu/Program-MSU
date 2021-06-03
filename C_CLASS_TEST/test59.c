#include <stdio.h>
int model (int x)
{
	if (x <= 0)
	x = -x;
	
	return x;
}
int maxmium (int x,int y)
{
	if (x > y)
	return x;
	else
	return y;
}
int power (int x,int y)
{
	int i,m = 1;
	for (i = 1; i <= y;i++)
	{		
		m = m * x;
	}
	return m;
}
int main()
{
	int n,n1;
	printf("input two number: ");
	scanf("%d%d",&n,&n1);
	n = power(n,n1);
	printf("%d\n",n);

	return 0;
}
