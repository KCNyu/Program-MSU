#include <stdio.h>
float floatabs(float x)
{
	if (x <= 0)
		return -x;
	else
		return x;
}
float exponent(float x,int n)
{
	float result = x;
	while(n != 1)
	{
		result *= x;
		n--;
	}
	return result;
}
float function(float x)
{
	return (exponent(x,2)+3*x+2);
}
int signF(float x)
{
	if(function(x) > 0)
		return 1;
	if(function(x) < 0)
		return -1;
	if(function(x) == 0)
		return 0;
}
float rootFind(float xl, float xr, float eps)
{
	int stepcount = 0;
	float xm;
	while(floatabs(xr-xl) > eps)
	{
		stepcount++;
		xm =(xr+xl)/2;
		if(signF(xm) == 0)
		{
			printf("Find root for %d steps\n",stepcount);
			return xm;
		}
		if(signF(xl) != signF(xm))
			xr = xm;
		else
			xl = xm;
	}
	printf("Find root for %d steps\n",stepcount);
	return (xl+xr)/2;
}
int main()
{
	float xl,xr,eps;
	printf("input xl xr eps:");
	scanf("%f%f%f",&xl,&xr,&eps);
	printf("Root 1 = %f\n",rootFind(xl,xr,eps));
	return 0;
}
