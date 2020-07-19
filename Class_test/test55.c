#include <stdio.h>
int main()
{
	int i,n,a = 1;
	printf("input number: ");
	scanf("%d",&n);
	for(i = 1; i <= n; i++)
	{
		a = a * i ;
	}
	printf("%d\n",a);
	return 0;
}
