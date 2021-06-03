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
		b =( (i/10) % 10 );
		
		if (a < b)	
		{
			k = k - 1;
		}
		i = i / 10;
	}
	if (k >= 0)
	printf("yes\n");
	else
	printf("no\n");
	
	return 0;
}

