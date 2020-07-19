#include <stdio.h>
int main()
{
	int i,a,b,k;

	printf("input a number: \n");
	scanf("%d",&i);
	k = 0;
	while (i != 0)
	{
		a = i % 10;
		printf("%d",a);
		i = i / 10;
	}	
	return 0;
}

