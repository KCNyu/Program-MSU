#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 10
int main()
{
	int i,A[N], count_0 = 0;
	srand(time(NULL));
	for(i = 0; i < N; i++)
		A[i] = rand()%2;
	for(i = 0; i < N; i++)
		printf("%d ",A[i]);
	printf("\n");
	for(i = 0; i < N; i++)
	{	
		if(A[i] == 0)
			count_0++;
	}
	for(i = 0; i < N; i++)
	{
		if(i < count_0)
			A[i] = 0;
		else
			A[i] = 1;
	}
	for(i = 0; i < N; i++)
		printf("%d ",A[i]);
	printf("\n");
	return 0;
}
