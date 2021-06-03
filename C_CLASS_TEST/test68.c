#include <stdio.h>
int factor(int a, int b)
{	
	while( a != 0 && b != 0)
	{
		if (a > b)
		a = a % b;
		else
		b = b % a;
	}
	return (a + b);
}
int main()
{
	int a ,b;
	printf("input two numbers: ");
	scanf("%d%d",&a,&b);
	printf("factor = %d\n",factor(a,b));
	return 0;
}
