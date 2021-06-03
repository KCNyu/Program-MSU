#include <stdio.h>
int number_0and1(int a[],int n)
{
	int i,count_0 = 0,count_1 = 0,b[10],k = 0,c[n+1];
	for(i = 0; i < n; i++)
		c[i] = a[i];
	if (a[n-1] == 0)
		c[n] = 1;
	if (a[n-1] == 1)
		c[n] = 0;
	if (a[0] == 1)
	{
		b[k] = 0;
		k++;
	}	
		for (i = 0; i < n; i++)
		{
			if (c[i] == 0)
				count_0++;
			if (c[i] == 1)
				count_1++;
			if (c[i] == 0 && c[i+1] == 1)
			{
				b[k] = count_0;
				k++;
				count_0 = 0;
			}
			if (c[i] == 1 && c[i+1] == 0)
			{
				b[k] = count_1;
				k++;
				count_1 = 0;
			}
		}
	for (i = 0; i < k; i++)
		printf("b[%d] = %d ",i,b[i]);
	return 0;
}
int main()
{
	int a[11] = {1,0,0,0,1,1,1,1,1,1,1};
	number_0and1(a,11);
	printf("\n");
	return 0;
}	

