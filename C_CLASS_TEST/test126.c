#include <stdio.h>
#include <stdlib.h>
#define N 8
#define M 8
int main()
{
	int a[N][M],i,j,max,max_i = 0;
	srand(time(NULL));
	for(i = 0; i < N; i++)
		for(j = 0; j < M; j++)
			a[i][j] = rand()%10;

	for(i = 0; i < N; i++)
	{
		for(j = 0; j < M; j++)
			printf("%2d ",a[i][j]);
		printf("\n");
	}
	max = a[0][0];
	for(i = 1; i < N; i++)
	{
		if(max < a[i][i])
		{
			max_i = i;
			max = a[i][i];
		}
	}
	printf("max = %d\nmax_i = %d\n",max,max_i);
	return 0;
}
