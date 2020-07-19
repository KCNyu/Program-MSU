#include <stdio.h>
#include <stdlib.h>
#define N 8
#define M 8
int main()
{
	int a[N][M],i,j,imin = 0,jmin = 0,imax = 0,jmax = 0;
	srand(time(NULL));
	for(i = 0; i < N; i++)
		for(j = 0; j < M; j++)
			a[i][j] = rand()%101 - 50;

	for(i = 0; i < N; i++)
	{
		for(j = 0; j < M; j++)
			printf("%3d ",a[i][j]);
		printf("\n");
	}

	for(i = 0; i < N; i++)
	{
		for(j = 0; j < M; j++)
		{
			if(a[i][j] > a[imax][jmax])
			{
				imax = i;
				jmax = j;
			}
			if(a[i][j] < a[imin][jmin])
			{
				imin = i;
				jmin = j;
	
			}
		}
	}
	printf("min a[%d][%d] = %d\n",imin,jmin,a[imin][jmin]);
	printf("max a[%d][%d] = %d\n",imax,jmax,a[imax][jmax]);
	return 0;
}
