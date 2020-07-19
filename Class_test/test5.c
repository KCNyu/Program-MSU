#include <stdio.h>
int main()
{
	int a;
	printf("please input a number: \n");
	scanf("%d",&a);
	a = a / 10;
	a = a % 10;
	printf("answer = %d",a);
	return 0;
}

