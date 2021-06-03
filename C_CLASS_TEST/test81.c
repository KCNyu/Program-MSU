#include <stdio.h>
int factor(int n,int a)
{
	if (n == 1)
	return 0;
	if (n%a == 0)
	{
		printf("%d ",a);
		factor(n/a,a);
	}
	else
	factor(n,a+1);
}
int main()
{
	int n;
	scanf("%d",&n);
	factor(n,2);
	printf("\n");
	return 0;
}
		
