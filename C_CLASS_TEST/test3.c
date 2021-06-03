#include <stdio.h>
int main()
{
	int a,b,c;
	printf("please input three numbers: \n");
	scanf("%d%d%d",&a,&b,&c);
	printf("%d + %d + %d = %d\n",a,b,c,a + b + c);
	printf("%d * %d * %d = %d\n",a,b,c,a*b*c);
	double d = (double) (a + b + c)/3;
	printf("(%d + %d + %d)/3 = %f\n",a,b,c,d);
	return 0;
}
