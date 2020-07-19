#include <stdio.h>
int main()
{
	int a,a1,a2,a3,max;
	printf("please input a number: \n");
	scanf("%d",&a);
	a1 = a/100;
	a2 = (a/10) % 10;
	a3 = a%10;

	printf("sum  = %d\n",a1 + a2 + a3);
	printf("product = %d\n",a1 * a2 * a3);

	if (a1 > a2)
	max = a1;
	else
	max = a2;
	if (a3 > max)
	max = a3;
	
	printf("max = %d\n",max);
	return 0;
}
