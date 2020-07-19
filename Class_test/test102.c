#include <stdio.h>
#include <stdlib.h>
int randomInt(int n)
{
	return rand()%n;
}

int main()
{
	int a[10],i,k,isSort,j = 0;
	srand(time(NULL));
	for(i = 0; i < 10; i++)
		a[i] = randomInt(101);
	for(i = 0; i < 10; i++)
		printf("a[%d] = %d ",i,a[i]);
	printf("\n");
	do
	{
		isSort = 1;
		for(i = 0; i < 9-j; i++)
		{
			if ((a[i]) > (a[i+1]))
			{
				k = a[i];
				a[i] = a[i+1];
				a[i+1] = k;
				isSort = 0;
			}
		}
		j++;
	}while(isSort == 0);
	for(i = 0; i < 10; i++)
	{
		printf("a[%d] = %d ",i,a[i]);
	}
	printf("\n");	
	return 0;
}
