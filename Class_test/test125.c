#include <stdio.h>
#include <stdlib.h>
#define N 8
#define M 8
int main()
{
	int a[N][M],i,j,maxsum,sum,maxsum_i = 0;
	srand(time(NULL));
	for(i = 0; i < N; i++)
		for(j = 0; j < M; j++)
			a[i][j] = rand()%10;

	for(i = 0; i < N; i++)
	{
		for(j = 0; j < M; j++)
			printf("%3d ",a[i][j]);
		printf("\n");
	}

	for(i = 0; i < N; i++)
	{
		sum = 0;
		for(j = 0; j < M; j++)
			sum += a[i][j];
		if(i == 0)
			maxsum = sum;
		else if(sum > maxsum)
		{
			maxsum = sum;
			maxsum_i = i;
		}
		printf("sum%d = %d\n",i,sum);
	}
	printf("maxsum = %d\nmaxsum_i = %d\n",maxsum,maxsum_i);
	return 0;
}
