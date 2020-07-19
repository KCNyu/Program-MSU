#include <stdio.h>
int lacked_number(int a[],int n)
{
	int sum_n = n * (n + 1)/2,sum_array = 0, i;
	for (i = 0; i < n; i++)
		sum_array += a[i];
	return sum_n - sum_array;
}	
int main()
{
	int a[10],n = 9,i = 0,element;
	do
	{
		scanf("%d",&element);
		a[i] = element;
		i++;
	}while(element != 0);
	printf("lacked number = %d\n",lacked_number(a,n));
	return 0;
}
