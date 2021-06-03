#include <stdio.h>
#include <stdlib.h>
int randomInt(int n)
{
	return rand()%n - 12;
}

int main()
{
	int a[12], i,b[4];
	srand(time(NULL));
	for(i = 0; i < 12; i++)
		a[i] = randomInt(25);
	for(i = 0; i < 12; i++)
		printf("a[%d] = %d ",i,a[i]);
	printf("\n");
	for(i = 0; i < 4; i++)
		b[i] = a[i+8];
	for(i = 11; i > 3; i --)
		a[i] = a[i-4];
	for(i = 0; i < 4; i++)
		a[i] = b[i];
	for(i = 0; i < 12; i++)
	{
		printf("a[%d] = %d ",i,a[i]);
	}
	printf("\n");	
	return 0;
}
