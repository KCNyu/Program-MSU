#include <stdio.h>
int main()
{
	int i,n,a = 0;
	printf("input number: ");
	scanf("%d",&n);
	if (n == 2)
	{
		printf("prime\n");
		return 0;
	}

	if (n == 1)
	{
		printf("not prime and not not prime");
		return 0;
	}

	for(i = 2; i <= (n - 1)/2; i++)
	{
		if (n % i == 0)
		{	
			printf("not prime\n");
			a = 1;
			return 0;
		}
	
	}
	if (a == 0)
	printf("prime\n");
	return 0;
}
