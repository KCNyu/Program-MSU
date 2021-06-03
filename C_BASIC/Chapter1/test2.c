#include <stdio.h>
int main()
{
	int a;
	char b;
	float c;
	double d;

	a = 520;
	b = 'f';
	c = 3.14;
	d = 3.1415926535;

	printf("大家%d\n",a);
	printf("i love you%c\n",b);
	printf("圆周率是:%.2f\n",c);
	printf("精确到小数点后九位的圆周率是：%.9f\n",d);

	return 0;
}



