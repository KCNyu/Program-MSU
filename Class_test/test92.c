#include <stdio.h>
#include <stdlib.h>
int randomInt(int n)
{
	return rand()%n - 10;
}

int main()
{
	int a[10], i,max2,max2_index,max,max_index;
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
			max = a[0];
			max_index = 0;
		}
		if (a[i] > max)
		{
			max = a[i];
			max_index = i;
		}
	}
	for(i = 0; i < 10; i++)
	{
		if (i == 0)
		{
			max2 = a[0];
			max2_index = i;
		}
		if (a[i] > max2 && a[i] < max)
		{
			max2 = a[i];
			max2_index = i;
		}
	}
	printf("max = %d\nmax_index = %d\n",max,max_index);
	printf("max2 = %d\nmax2_index = %d\n",max2,max2_index);
	return 0;
}
