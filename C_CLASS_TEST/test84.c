#include <stdio.h>
int main()
{
	int a[5],i;
	float sum = 0;
	printf("please input five numbers: ");
	for(i = 0; i < 5; i++)
	{
		scanf("%d",&a[i]);
		sum += a[i];
	}
	printf("average = %f\n",sum/5);
	return 0;
}
