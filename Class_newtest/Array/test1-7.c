#include <stdio.h>
#include <stdlib.h>
#define N 10
int randomInt(int n)
{
	return rand()%n;
}
void Even_oddindex(int A[],int n)
{
	int i;
	for(i = 0; i < n; i++)
	{
		if(i%2 == 0)
			printf("%d ",A[i]);
	}
	printf("\n");
	for(i = 0; i < n; i++)
	{
		if(i%2 != 0)
			printf("%d ",A[i]);
	}
	return;
}
void judge_biggerright(int A[],int n)
{
	int i,count = 0;
	for(i = 0; i < n-1; i++)
	{
		if(A[i] > A[i+1])
		{
			printf("A[%d] = %d\n",i,A[i]);
			count++;
		}
	}
	printf("count = %d\n",count);
	return;
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
	return ;
}
int judgesorted(int A[],int n)
{
	int i,j,count = 0,max = 0;
	for(i = 0; i < n-1; i++)
	{
		if(A[i] > 0)
		{
			for(j = i; j < n-1; j++)
			{
				if(A[j] <= A[j+1])
					count++;
				else
					break;
					
			}
			if(count > max)
			{
				max = count;
				count = 0;
			}
		}
	}
	return max;
}

int judgeUparray(int A[],int n)
{
	int i,j;
	for(i = 0; i < n-1; i++)
	{
		if(A[i] > A[i+1])
			return 0;
	}
	return 1;
}
void Move_right(int A[],int n)
{
	int i,tmp;
	for(i = n-1; i >= 0; i--)
	{
		tmp = A[i];
		A[i] = A[i-1];
		A[i-1] = tmp;
	}
	return;
}
int SearchMin(int A[],int n)
{
	int min,i,flag = 0;
	for(i = 0; i < n; i++)
	{
		if(A[i] > 0)
		{
			if(flag == 0)
			{
				min = A[i];
				flag = 1;
			}
			else if(A[i] < min)
				min = A[i];
		}
	}
	return min;
}
int More_k(int A[], int n)
{
	int i,k;
	scanf("%d",&k);
	for(i = 0; i < n; i++)
		if(A[i] > k)
			return i;
}
void printarray(int A[],int n)
{
	int i;
	for(i = 0; i < n; i++)
		printf("%d ",A[i]);
	printf("\n");
	return;
}
int SearchMax(int A[],int n)
{
	int i, max = A[0];
	for(i = 1; i < n; i++)
	{
		if(A[i] > max)
			max = A[i];
	}
	return max;
}
void print_betweenMax(int A[],int n)
{
	int index_max1 = 0,index_max2 = 0,max1 = A[0],i;
	for(i = 1; i < n; i++)
	{
		if(A[i] > max1)
		{	
			max1 = A[i];
			index_max1 = i;
		}
		if(A[i] == max1)
			index_max2 = i;
	}
	if(index_max1 == index_max2)
		printf("%d\n",max1);
		return;

	for(i = index_max1+1; i < index_max2;i++)
		printf("%d ",A[i]);
	printf("\n");
	return;
}			
/*int main()
{
	int a[N],i;
	srand(time(NULL));
	for(i = 0; i < N; i++)
		a[i] = randomInt(10);
	printarray(a,N);
	print_betweenMax(a,N);
	return 0;
}
int main()
{
	int a[N],i;
	srand(time(NULL));
	for(i = 0; i < N; i++)
		a[i] = randomInt(10);
	printarray(a,N);
	Even_oddindex(a,N);
	printf("\n");
	return;
}*/
int main()
{
	int a[N],i;
	srand(time(NULL));
	for(i = 0;i < N; i++)
		a[i] = randomInt(10);
	printarray(a,N);
	Move_right(a,N);
	printarray(a,N);
	return 0;
}
	
