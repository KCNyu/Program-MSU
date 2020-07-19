#include <stdio.h>
#include <math.h>
int main()
{
	float a,b,c,d,s;
	s = 1;
	a = 2;
	b = 3;
	c = 3;
	d = 1;
	while (fabs((d*a)/(b*c))> 0.001)
	{	
		s = s + (d*a)/(b*c);
		a = a + 2;
		d = (-1)*d;
		b = b + 2;
		c = c * 3;	
	}
	printf("s = %f\n",s);
	return 0;
}
