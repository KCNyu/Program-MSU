#include <stdio.h>
#include <stdlib.h>
float power1(float a,int n)
{
	float t = a;
	if(n <= 0 && a == 0)
	{
		printf("no\n");	
		return 0;
	}
	int i;
	if(n > 0)
	{	for(i = 1; i < n; i++)
			a *= t;
		return a;
	}
	if(n == 0)
		return 1;
	if(n < 0 && a != 0)
	{
		for(i = 0; i < -n+1; i++)
			a /= t;
		return a;
	}
}
int main()
{
	float x,y;
	int k;
	printf("input x:");
	scanf("%f",&x);
	printf("input y:");
	scanf("%f",&y);
	if(x >= 1)
	{
		k = 1;
		while(!(power1(y,k-1) <= x && x < power1(y,k)))
			k++;
		printf("k = %d\n",k);
	}
	if(x < 1)
	{
		k = -1;
		while(!(power1(y,k-1) <= x && x < power1(y,k)))
			k--;
		printf("k = %d\n",k);
	}
	return 0;
}


