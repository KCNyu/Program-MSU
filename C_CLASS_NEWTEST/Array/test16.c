#include <stdio.h>
#define N 10
int main()
{
	int i,j,count = 1,flag = 1,A[N];
	srand(time(NULL));
	for(i = 0; i < N; i++)
		A[i] = rand()%10;
	for(i = 0; i < N; i++)
		printf("%d ",A[i]);
	printf("\n");
	int B[N];
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

