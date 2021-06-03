#include <stdio.h>
#include <stdlib.h>
int randomInt(int n)
{
	return rand()%n - 10;
}

int main()
{
	int a[10], i,k;
	srand(time(NULL));
	for(i = 0; i < 10; i++)
		a[i] = randomInt(21);
	for(i = 0; i < 10; i++)
		printf("a[%d] = %d ",i,a[i]);
	printf("\n");
	for (i = 0; i < 3; i++)
	{
		k = a[i];
		a[i] = a[4-i];
		a[4-i] = k;
	}
	for (i = 5; i < 8; i++)
	{
		k = a[i];
		a[i] = a[14-i];
		a[14-i] = k;
	}
	for(i = 0; i < 10; i++)
		printf("a[%d] = %d ",i,a[i]);
	printf("\n");	
	return 0;
}
