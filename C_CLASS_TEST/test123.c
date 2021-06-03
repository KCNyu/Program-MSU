#include <stdio.h>
#include <stdlib.h>
/*int main()
{
	int n[5],i;
	for(i = 0; i != 5; i++)
		scanf("%d",&n[i]);
	for(i = 4; i != -1; i--)
	       printf("%d ",n[i] * 2);
	printf("\n");
	return 0;
}*/
int randomInt(n)
{
	return rand()%n;
}
int findMax(int a[])
{	
	int i,max;
	for(i = 0; i < 5; i++)
	{
		if(a[i] < 0)
			a[i] = -a[i];
	}
	max = a[0];
	for(i = 0; i < 5; i++)
	{
		if(a[i] > max)
			max = a[i];
	}
	return max;
}
void changeMin2Max(int a[],int n)
{
	int i,min,max,min_index = 0,max_index = 0;
	min = a[0];
	max = a[0];
	srand(time(NULL));
	for(i = 0; i != n; i++)
	{
		a[i] = randomInt(100);
		printf("%d ",a[i]);
	}
	printf("\n");
	for(i = 0; i < n; i++)
	{
		if(a[i] < min)
		{
			min = a[i];
			min_index = i;
		}
		if(a[i] > max)
		{
			max = a[i];
			max_index = i;
		}
	}
	a[min_index] = max;
	for(i = 0; i < n; i++)
		printf("%d ",a[i]);
	printf("\n");
	return;
}
int main()
{
	int n,a[100] = {0},i,j,length = 0,tmp;
	printf("input number: ");
	scanf("%d",&n);
	while(n != 0)
	{
		a[length] = n%10;
		n /= 10;
		length++;
	}
	for(i = 0; i < length - 1; i++)
	{
		for(j = 0; j < length - 1 - i; j++)
		{
			if (a[j] > a[j+1])
			{
				tmp = a[j];
				a[j] = a[j+1];
				a[j+1] = tmp;
			}
		}
	}
	for(i = 0; i < length; i++)
		printf("%d",a[i]);
	printf("\n");
	return 0;
}

