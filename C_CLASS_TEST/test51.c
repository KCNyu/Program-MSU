#include <stdio.h>

int main()
{	
	int n,i,a0 = 0,a1 = 1,c;
	printf("input number: ");
	scanf("%d",&n);
	for (i = 1; i <= n; i++)
	{
		printf("%d ",a1);
		c = a1;
		a1 = a0 + a1;
		a0 = c;
	}
	printf("\n");	
	return 0;
}
