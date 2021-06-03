#include <stdio.h>
float average(float x , float y)
{
	return (x + y)/2;
}
int main()
{
	float a,b;
	scanf("%f%f",&a,&b);
	printf("%f\n",average(a,b));
	return 0;
}
