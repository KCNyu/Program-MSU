#include <stdio.h>
#include <stdlib.h>
int main()
{
	int number,number1,N = 0,i = 0,j,tmp;
	scanf("%d",&number);
	number1 = number;
	while (number1 != 0)
	{
		number1 /= 10;
		N++;
	}
	int a[N];
	while (number != 0)
	{
		a[i] = number % 10;
		number /= 10;
		i++;
	}
	for(i = 0; i < N-1; i++)
	{
		for(j = 0; j < N-i-1; j++)
		{
			if(a[j] > a[j+1])
			{
				tmp = a[j];
				a[j] = a[j+1];
				a[j+1] = tmp;
			}
		}
	}
	for(i = 0; i < N; i++)
		printf("%d",a[i]);
	printf("\n");
	return 0;
}
