#include <stdio.h>
int main()
{
	int a[5], i,min,min_index;
	printf("please input five numbers: ");
	for(i = 0; i < 5; i++)
	{
		scanf("%d",&a[i]);
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
	printf("min = %d\nmin_index = %d\n",min,min_index);
	return 0;
}
