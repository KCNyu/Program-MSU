#include <stdio.h>
#include <stdlib.h>
int randomInt(int n)
{
	return rand()%n - 10;
}

int main()
{
	int a[10], i,min,min_index,max,max_index;
	srand(time(NULL));
	for(i = 0; i < 10; i++)
		a[i] = randomInt(21);
	for(i = 0; i < 10; i++)
		printf("a[%d] = %d ",i,a[i]);
	printf("\n");
	for(i = 0; i < 10; i++)
	{
		if (i == 0)
		{
			min = a[0];
			min_index = 0;
		}
		if (a[i] < min)
		{
			min = a[i];
			min_index = i;
		}
	}
	for(i = 0; i < 10; i++)
	{
		if (i == 0)
		{
			max = a[0];
			max_index = 0;
		}
		if (a[i] > max)
		{
			max = a[i];
			max_index = i;
		}
	}
	printf("min = %d\nmin_index = %d\n",min,min_index);
	printf("max = %d\nmax_index = %d\n",max,max_index);
	return 0;
}
