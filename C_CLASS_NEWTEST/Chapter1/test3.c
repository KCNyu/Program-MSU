#include <stdio.h>
#include <stdlib.h>
#include <math.h>
double function1(double x)
{
	return sqrt(x*x-4.0)/(x-8);
}
int main()
{
	double x;
	printf("input x = ");
	scanf("%lf",&x);
	printf("y = %lf\n",function1(x));
	return 0;
}

