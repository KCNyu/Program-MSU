#include <stdio.h>
int number(int n,int a)
{
	int i;
	for (i = 1; i <= a; i++)
	{
		printf("%d ",a);
		n--;
		if (n == 0)
		return 0;
	}
	number(n,a+1);
}
int main()
{
	int n;
	printf("input a number: ");
	scanf("%d",&n);
	number(n,1);
	printf("\n");
	return 0;
}
