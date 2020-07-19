#include <stdio.h>
int main()
{
	int a,b,t;
	printf("input two number: \n");
	scanf("%d%d",&a,&b);

	if (a > b)
	t = a, a = b, b = t;

	while (a <= b)
	{
		printf("%d: %d %d\n",a ,a*a, a*a*a);	
		a++;
	}

	return 0;
}
