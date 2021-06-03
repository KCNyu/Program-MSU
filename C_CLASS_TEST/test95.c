#include <stdio.h>
#include <stdlib.h>
int randomInt(int n)
{
	return rand()%n - 12;
}

int main()
{
	int a[12], i, sum = 0;
	float avg;
	srand(time(NULL));
	for(i = 0; i < 12; i++)
		a[i] = randomInt(25);
	for(i = 0; i < 12; i++)
		printf("a[%d] = %d ",i,a[i]);
	printf("\n");
	for (i = 0; i < 12; i++)
	{
		sum += a[i];
	}
	printf("avg = %f\n",sum/12.0);	
	return 0;
}
