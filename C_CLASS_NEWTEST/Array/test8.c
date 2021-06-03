#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 10
int abs(int x)
{
	if(x < 0)
		return -x;
	else
		return x;
}

int main()
{
	int i,A[N],r,d,d_min,d_index = 0;
	srand(time(NULL));
	scanf("%d",&r);
	for(i = 0; i < N; i++)
		A[i] = rand()%100;
	for(i = 0; i < N; i++)
		printf("%d ",A[i]);
	printf("\n");
	d_min = abs(A[0]-r); 
	for(i = 1; i < N; i++)
	{
		d = abs(A[i]-r);
		if(abs(d) < d_min)
		{
			d_min = d;
			d_index = i;
		}
	}
	printf("d_min:A[%d] = %d\nd_min = %d\n",d_index,A[d_index],d_min);
	return 0;
}
			
	
