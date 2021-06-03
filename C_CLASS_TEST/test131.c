#include <stdio.h>
float absfloat(float x)
{
	if (x < 0)
		return -x;
	else
		return x;
}
float multiple(float x,int n)
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
	return (32*multiple(x,5)-160*multiple(x,4)+288*multiple(x,3)-224*multiple(x,2)+70*x-6);
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
float Findroot(float xl,float xr,float eps)
{
	int countstep = 0;
	float xm;
	while(absfloat(xr-xl) > eps)
	{
		xm = (xl+xr)/2;
		countstep++;
		if(signF(xm) == 0)
		{
			printf("Find the root %f for %d steps\n",xm,countstep);
			return xm;
		}
		if(signF(xm) != signF(xl))
			xr = xm;
		else
			xl = xm;
	}
	printf("Find the root %f for %d steps\n",xm,countstep);
	return (xl+xr)/2;
}
int main()
{
	Findroot(-0.1,0.3,0.00001);
	Findroot(0.3,0.7,0.00001);
	Findroot(0.7,1.2,0.00001);
	Findroot(1.2,1.7,0.00001);
	Findroot(1.7,2,0.00001);
	return 0;
}





