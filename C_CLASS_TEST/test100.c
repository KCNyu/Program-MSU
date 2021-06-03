#include <stdio.h>
#include <stdlib.h>
int randomInt(int n)
{
	return rand()%n;
}
int main()
{
	int a[10],i,k,j;
	srand(time(NULL));
	for(i = 0; i < 10; i++)
		a[i] = randomInt(101);
	for(i = 0; i < 10; i++)
		printf("a[%d] = %d ",i,a[i]);
	printf("\n");
	for(i = 0; i < 9; i++)
	{
		for(j = 0; j < 9-i; j++)
		{
			if ((a[j]%10) > (a[j+1]%10))
			{
				k = a[j];
				a[j] = a[j+1];
				a[j+1] = k;
			}
			if ((a[j]%10) == (a[j+1])%10)
			{
				if (((a[j]/10)%10) > ((a[j+1]/10)%10))
				{
					k = a[j];
					a[j] = a[j+1];
					a[j+1] = k;
				}
			}	
		}
	}
	for(i = 0; i < 10; i++)
	{
		printf("a[%d] = %d ",i,a[i]);
	}
	printf("\n");	
	return 0;
}
