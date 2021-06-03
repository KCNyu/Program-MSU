#include <stdio.h>
#include <stdlib.h>
int main()
{
	float a;
	printf("input a:");
	scanf("%f",&a);
	float t = a;
	int n;
	printf("input n:");
	scanf("%d",&n);
	if( n <= 0 && a == 0)
	{
		printf("no\n");	
		return 0;
	}
	int i;
	if(n > 0)
	{	for(i = 1; i < n; i++)
			a *= t;
		printf("%f^%d = %f\n",t,n,a);
	}
	if(n == 0)
		printf("%f^%d = 1\n",t,n);
	if(n < 0 && a != 0)
	{
		for(i = 0; i < -n+1; i++)
			a /= t;
		printf("%f^%d = %f\n",t,n,a);
	}

	return 0;
}
