#include <stdio.h>
#include <math.h>
int class_ride(int x)
{
	int i,s = 1;
	for(i = 1; i <= x ; i++ )
	{
		s = s * i;
	}
	return s;

}
float powFunc(float x, int p)
{
	int i;
	float mult =1;
	for (i = 1 ; i <= p; i++)
	{
		mult *= x;
	}
	return mult;
}
float convertToRadian(float x)
{
	return (3.1415926536 * x)/ 180;
}
float sinFunc(float x)
{
	float xrad = convertToRadian(x);
	float elem = xrad,sum = 0, z = -1;
	int i = 3;
	while (fabs(elem) >= 0.001)
	{
		sum += elem;
		elem = z * powFunc(xrad,i)/class_ride(i);
		i += 2;
		z = -z;
	}
	return sum;
}
int main()
{
	float x;
	printf("input a number: ");
	scanf("%f",&x);
	printf("sin(%f) = %5.3f\n",x,sinFunc(x));
	return 0;
}
