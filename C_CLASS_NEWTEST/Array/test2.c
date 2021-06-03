#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 10
int main()
{
	int i,A[N],flag = 0;
	srand(time(NULL));
	for(i = 0; i < N; i++)
		A[i] = rand()%10;
	for(i = 0; i < N; i++)
		printf("%d ",A[i]);
	printf("\n");
	for(i = 0; i < N; i++)
	{
		if(A[i] > A[1] && A[i] < A[N-1])
		{
		 	printf("A[%d] = %d\n",i,A[i]);
			flag = 1;
			break;
		}
	}
	if(flag != 1)
		printf("don't exist this element\n");
	return 0;
}
