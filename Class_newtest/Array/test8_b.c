#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 10
float abs1(float x)
{
	if(x < 0)
		return -x;
	else
		return x;
}

int main()
{
	float A[N],r,d,d_min;
	int i,d_index = 0;
	srand(time(NULL));
	scanf("%f",&r);
	for(i = 0; i < N; i++)
		A[i] = rand()%100+0.5;
	for(i = 0; i < N; i++)
		printf("%f ",A[i]);
	printf("\n");
	d_min = abs1(A[0]-r); 
	for(i = 1; i < N; i++)
	{
		d = abs1(A[i]-r);
		if(abs1(d) < d_min)
		{
			d_min = d;
			d_index = i;
		}
	}
	printf("d_min:A[%d] = %f\nd_min = %f\n",d_index,A[d_index],d_min);
	return 0;
}
			
	
