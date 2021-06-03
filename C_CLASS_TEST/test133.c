#include <stdio.h>
#include <math.h>
int pow_number(int x, int y)
{
	int a = x;
	if (y == 0)
		return 1;

	while(y != 1)
	{
		x *= a;
		y--;
	}
	return x;
}
int judgedigit(int x)
{
	int i = 0,a = x,k;
	while(x != 0)
	{
		x /= 10;
		i++;
	}
	k = a / (pow_number(10,i-1));
	return k;
}
void startingdigit(int A[],int length)
{
	int i,j,tmp,a1,a2;
	for(i = 0; i < length-1; i++)
	{
		for(j = 0; j < length-i-1; j++)
		{
			a1 = judgedigit(A[j]);
			a2 = judgedigit(A[j+1]);
			if(a1 > a2)
			{
				tmp = A[j];
				A[j] = A[j+1];
				A[j+1] = tmp;
			}
		}
	}
	return;
}
int main()
{
	int A[5],i;
	for(i = 0; i < 5; i++)
		scanf("%d",&A[i]);
	startingdigit(A,5);
	for(i = 0; i < 5; i++)
		printf("%d ",A[i]);
	printf("\n");
	return 0;
}
