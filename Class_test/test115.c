#include <stdio.h>
#include <stdlib.h>
int randomInt(int n)
{
	return rand()%n;
}

void sortUparray(int A[],int n)
{
	int i,j,tmp;
	for(i = 0; i < n-1; i++)
	{
		for(j = 0; j < n-1-i; j++)
		{
			if (A[j] > A[j+1])
			{
				tmp = A[j];
				A[j] = A[j+1];
				A[j+1] = tmp;
			}
		}	
	}
	return;
}
void printarray(int A[],int n)
{
	int i;
	for(i = 0; i < n; i++)
		printf("a[%d] = %d ",i,A[i]);
	printf("\n");
	return;
}
void sortarray_even_uneven(int a[],int n)
{
	int i,b[n],k = 0;
	for(i = 0; i < n; i++)
	{
		if (a[i] % 2 == 0)
		{
			b[k] = a[i];
			k++;
		}
	}
	for(i = 0; i < n; i++)
	{
		if (a[i] % 2 != 0)
		{
			b[k] = a[i];
			k++;
		}
	}
	for(i = 0; i < n; i++)
		a[i] = b[i];
	return;
}
int element_array(int a[], int n)
{
	int b[n],c[n],i,j,k = 0,k_count,count_element,type = 0,newtype = 1,max_times = 1,max_index = 0;
	for(i = 0; i < n; i++)
	{
		count_element = 1;
		if(i != 0)
		{
			for (k_count = 0; k_count < k; k_count++)
			{
				if (a[i] == b[k_count])
				{
					newtype = 0;
					break;
				}
			}
		}
		if (newtype != 0)
			type = 0 ;
		for(j = i + 1; j < n; j++)
		{
			if(a[i] == a[j])
			count_element++;
		}
		c[k] = count_element++;
		if(type == 0)
		{
			b[k] = a[i];
			k++;
			type = 1;
		}
		newtype = 1;
	}
	for(i = 0; i < k; i++)
		printf("%d -- %d ",b[i],c[i]);
	printf("\n");
	return 0;
}			
int main()
{
	int n,i = 0,j,a[10];
	scanf("%d",&n);
	while(n != 0)
	{
		a[i] = n%10;
		n /= 10;
		i++ ;
	}
	sortUparray(a,i);
	for(j = 0; j < i; j++)
	printf("%d",a[j]);
	printf("\n");
	return 0;
}
