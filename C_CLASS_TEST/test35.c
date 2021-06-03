#include <stdio.h>
#include <math.h>
int main()
{
	float a,b,c,d,b3,b2,s;
	s = (float)4/3;
	a = 4;
	b = 3;
	c = 9;
	d = -1;
	b3 = 3;
	b2 = 2;
	while (fabs((d*a)/(b*c))> 0.0001)
	{	
		s = s + (d*a)/(b*c);
		a = a + 2;
		d = (-1)*d;
		c = c * 3;
		b = b2 + b3;
		b2 = b3;
		b3 = b;
			
	}
	printf("s = %f\n",s);
	return 0;
}
