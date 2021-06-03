#include <stdio.h>
int main()
{
	int i,a,k;

	printf("input a number: \n");
	scanf("%d",&i);
	k = 0;
	while (i != 0)
	{
		a = i % 10;
		if (a == 9)
		{
			k++;
		}
		i = i / 10;
	}
	if (k == 1)
	printf("yes\n");
	else
	printf("no\n");
	
	return 0;
}

