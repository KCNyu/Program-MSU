#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 10
int main()
{
	int i,flag = 1;
	int A[N];
	for(i = 0; i < N; i++)
		scanf("%d",&A[i]);
	for(i = 0; i < N; i++)
	{
		if(A[i] >= A[i+1])
		{
			printf("no\n");
			flag = 0;
			break;
		}
	}
	if(flag == 1)
		printf("yes\n");

	return 0;
}	
			
