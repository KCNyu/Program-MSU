#include <stdio.h>
int main()
{
	int a, b, c;
	printf("please input three numbers: \n");
	scanf("%d%d%d",&a,&b,&c);

	if (a < b && b < c)
	printf("yes\n");
	else
	printf("not\n");
	return 0;
}
