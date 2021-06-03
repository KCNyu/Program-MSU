#include <stdio.h>
int main()
{
	int a,b,c;
	printf("please input three numbers: \n");
	scanf("%d%d%d",&a,&b,&c);
	
	if (a > b && a > c)
	printf("max = %d\n",a);
	if (b > a && b > c)
	printf("max = %d\n",b);
	if (c > a && c > b)
	printf("max = %d\n",c);

	return 0;
}
