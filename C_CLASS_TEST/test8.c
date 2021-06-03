#include <stdio.h>
int main()
{
	int a[4];
	int i = 0, min = 0, max = 0;
	printf("please write four numbers: \n");
	for (i = 0; i < 5; i++)
	{
		scanf("%d",&a[i]);
	}
	min = a[0];
	for (i = 1; i < 5; i++)
	{
		if (min > a[i])
		{
			min = a[i];
		}
	}
	printf("min = %d\n",min);
	max = a[0];
	for (i = 1; i < 5; i++)
	{
		if (max < a[i])
		{
			max = a[i];
		}
	}
	
	printf("max = %d\n",max);
	printf("max + min = %d + %d = %d\n",max,min,max + min);
		
	return 0;
}

