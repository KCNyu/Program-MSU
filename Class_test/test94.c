#include <stdio.h>
#include <stdlib.h>
int randomInt(int n)
{
	return rand()%n - 100;
}

int main()
{
	int a[10], i, sum = 0;
	srand(time(NULL));
	for(i = 0; i < 10; i++)
		a[i] = randomInt(201);
	for(i = 0; i < 10; i++)
		printf("a[%d] = %d ",i,a[i]);
	printf("\n");
	for (i = 0; i < 10; i++)
	{
		if (a[i] > 0)
		sum += a[i];
	}
	printf("sum = %d\n",sum);	
	return 0;
}
