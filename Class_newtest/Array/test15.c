#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 10
int main()
{
	int A[N],i,j,tmp;
	srand(time(NULL));
	for(i = 0; i < N; i++)
		A[i] = rand()%10;
	for(i = 0; i < N; i++)
		printf("%d ",A[i]);
	printf("\n");
	for(i = 0; i < N-1; i++)
		for(j = 0; j < N-1-i; j++)
			if(A[j] >= A[j+1])
			{
				tmp = A[j];
				A[j] = A[j+1];
				A[j+1] = tmp;
			}
	int flag = 1,count = 1,B[N];
	B[0] = A[0];
	for(i = 1; i < N; i++)
	{
		for(j = 0; j < count; j++)
			if(A[i] == B[j])
			{
				flag = 0;
				break;
			}
		if(flag)
		{
			B[count] = A[i];
			count++;
		}
		flag = 1;
	}
	for(i = 0; i < count; i++)
		printf("%d ",B[i]);
	printf("\n");
	return 0;
}
	
