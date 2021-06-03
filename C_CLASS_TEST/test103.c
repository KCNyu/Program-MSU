#include <stdio.h>
#include <stdlib.h>
int randomInt(int n)
{
	return rand()%n;
}
int main()
{
	int a[10],b[10],k = 0,i,j;
	srand(time(NULL));
	for(i = 0; i < 10; i++)
		a[i] = randomInt(1000);
	for(i = 0; i < 10; i++)
		printf("a[%d] = %d ",i,a[i]);
	printf("\n");
	for(i = 0; i < 10; i++)
	{
		if (((a[i]/10)%10) == 0)
		{
			b[k] = a[i];
			k++;
		}
	}
	for(j = 0; j < k; j++)
	{
		printf("b[%d] = %d ",j,b[j]);
	}
	printf("\n");	
	return 0;
}
