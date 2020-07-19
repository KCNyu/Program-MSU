#include <stdio.h>
int main()
{
	int a,b;
	printf("please input two numbers: \n");
	scanf("%d%d",&a,&b);
	if (a > b)
	{
		printf("%d > %d",a,b);
	}
	else
	{
		printf("%d < %d",a,b);
	}
	return 0;
}
