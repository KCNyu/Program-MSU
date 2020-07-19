#include <stdio.h>
float abs1(float x)
{
	if(x < 0)
		return -x;
	else
		return x;
}
float power1(float x, int n)
{
	float k = x;
	int i;
	for(i = 1; i < n; i++)
		x *= k;
	return x;
}	
int main()
{
	float eps = 0.00001,x1 = 2.0,x2 = 2.25;
	float i = 3;
	while(abs1(x1-x2) >= eps)
	{
		x1 = power1((1+1/i),i);
		x2 = power1((1+1/(i+1)),i+1);
		i++;
	}
	printf("x1 = %f\nx2 = %f\n",x1,x2);
	return 0;
}
