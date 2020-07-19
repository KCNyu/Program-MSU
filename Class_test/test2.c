#include <stdio.h>
int main()
{
	int a,b,c;
	printf("please input three numbers: \n");
	scanf("%d%d%d",&a,&b,&c);
	printf("%d + %d + %d = %d\n",a,b,c,a + b + c);
	printf("%d * %d * %d = %d\n",a,b,c,a*b*c);
	return 0;
}
