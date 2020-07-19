#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 5
int SearchMax(int A[],int n)
{
	int i,max = A[0],max_index = 0;
	for(i = 1; i < N; i++)
	{
		if(A[i] > max)
		{
			max = A[i];
			max_index = i;
		}
	}
	return max_index;
}
int SearchMin(int A[],int n)
{
	int i, min = A[0],min_index = 0;
	for(i = 1; i < N; i++)
	{
		if(A[i] < min)
		{
			min = A[i];
			min_index = i;
		}
	}
	return min_index;
}
int main()
{
	int i,A[N],max,max_index,min,min_index,B[N];
	srand(time(NULL));
	for(i = 0; i < N; i++)
	{
		A[i] = rand()%100;
		printf("%d ",A[i]);
	}
	printf("\n");
	min_index = SearchMin(A,N);
	min = A[min_index];
	for(i = 0; i < N-1; i++)
	{
		max_index = SearchMax(A,N);
		B[i] = max_index;
		A[max_index] = min;
	}
	B[N-1] = min_index;
	for(i = 0; i < N; i++)
		printf("%d ",B[i]);
	printf("\n");
	return 0;
}


	
