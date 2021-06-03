#include <stdio.h>
#include <stdlib.h>
int randomInt(int n)
{
	return rand()%n - 12;
}

int main()
{
	int a[12], i,k;
	srand(time(NULL));
	for(i = 0; i < 12; i++)
		a[i] = randomInt(25);
	for(i = 0; i < 12; i++)
		printf("a[%d] = %d ",i,a[i]);
	printf("\n");
	for (i = 0; i < 2; i++)
	{
		k = a[i];
		a[i] = a[3-i];
		a[3-i] = k;
	}
	for (i = 4; i < 6; i++)
	{
		k = a[i];
		a[i] = a[11-i];
		a[11-i] = k;
	}
	for (i = 8; i < 10; i++)
	{
		k = a[i];
		a[i] = a[19-i];
		a[19-i] = k;
	}
	for(i = 0; i < 12; i++)
	{
		printf("a[%d] = %d ",i,a[i]);
	}
	printf("\n");	
	return 0;
}
