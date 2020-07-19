#include <stdio.h>
int main()
{
	int a,i,sum;
	sum = 0;
	i = 0;
	printf("input a number: \n");
	do
	{
		scanf("%d",&a);
		if (a <= 0)
		printf("input a positive number: \n");
	}
	while(a <= 0);
	
	while(a != 0)
	{
		sum = a % 10 + sum;
		i = (a % 10) * i;
		a = a/10;
	}

	if (i == sum)
	printf("yes\n");
	else 
	printf("no\n");
	return 0;
}	
