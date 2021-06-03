#include <stdio.h>
#include <stdlib.h>
int randomInt(int n)
{
	return rand()%n;
}

int main()
{
	int a[10],i,k,isSort,j;
	srand(time(NULL));
	for(i = 0; i < 10; i++)
		a[i] = randomInt(101);
	for(i = 0; i < 10; i++)
		printf("a[%d] = %d ",i,a[i]);
	printf("\n");
	for(i = 0; i < 5; i++)
	{
		isSort = 1;
		for(j = 0; j < 5-i; j++)
		{
			if ((a[j]) > (a[j+1]))
			{
				k = a[j];
				a[j] = a[j+1];
				a[j+1] = k;
				isSort = 0;
			}
		}
		if(isSort)
		break;
	}
	for(i = 5; i < 10; i++)
	{
		isSort = 1;
		for(j = 5; j < 14-i; j++)
		{
			if ((a[j]) < (a[j+1]))
			{
				k = a[j];
				a[j] = a[j+1];
				a[j+1] = k;
				isSort = 0;
			}
		}
		if(isSort)
		break;
	}
	for(i = 0; i < 10; i++)
	{
		printf("a[%d] = %d ",i,a[i]);
	}
	printf("\n");	
	return 0;
}
