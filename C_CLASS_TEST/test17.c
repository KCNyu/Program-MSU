#include <stdio.h>
int main()
{
	int a, b, c;
	printf("please input 3 numbers: \n");
	scanf("%d%d%d",&a,&b,&c);

	if ((a + b) > c && (a + c) > b && (b + c) > a)
	printf("triangle!\n");
	else
	printf("No!\n");

	return 0;
}
