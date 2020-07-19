#include <stdio.h>
#include <stdlib.h>
#define N 2
#define M 2
char randomsymbol()
{
	return rand()%26 + 'A';
}
int randomInt(int n)
{
	return rand()%n;
}
/*int main()
{
	int a[N][M],i,j,quantity_symbol[26] = {0};
	srand(time(NULL));
	for(i = 0; i < N; i++)
		for(j = 0; j < M; j++)
			a[i][j] = randomsymbol();

	for(i = 0; i < N; i++)
	{
		for(j = 0; j < M; j++)
		{
			printf("%c ",a[i][j]);
			quantity_symbol[a[i][j] - 'A']++;
		}
		printf("\n");
	}
	for(i = 0; i < 26; i++)
		printf("%c -- %d\n",'A'+i,quantity_symbol[i]);
	return 0;
}*/

/*int main()
{
	int a[N][M],i,j;
	srand(time(NULL));
	for(i = 0; i < N; i++)
		for(j = 0; j < M; j++)
			a[i][j] = randomInt(9)+1;
	for(i = N-2; i >= 1; i--)
		for(j = 0; j < i; j++)
			a[i][M-j-2] = 0;
	for(i = 0; i < N; i++)
	{
		for(j = 0; j < M; j++)
		{
			printf("%2d",a[i][j]);
		}
		printf("\n");
	}
	return 0;
}*/

int main()
{
	int a[N][M],i,j,k;
	srand(time(NULL));
	for(i = 0; i < N; i++)
		for(j = 0; j < M; j++)
			scanf("%d",&a[i][j]);
/*	for(i = 0; i <= N/2; i++)
	{
		for(j = M/2-i; j < M/2+i+1; j++)
			a[i][j] = 0;
		for(k = i+1; k < M-i-1; k++)
			a[i+N/2+1][k] = 0;
	}*/
	for(i = 0; i < N; i++)
	{
		for(j = 0; j < M; j++)
		{
			printf("%2d",a[i][j]);
		}
		printf("\n");
	}
	return 0;
}
