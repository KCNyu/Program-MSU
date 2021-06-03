#include <stdio.h>
int main()
{
	int a, b,i = 0;
	printf("input number: \n");
	scanf("%d%d",&a,&b);
	while (a != 0 && b != 0)
	{
		if (a > b)
		a = a % b;
		else
		b = b % a;

		i++;
	}
	printf("%d\n%d\n",a + b,i);
	
	return 0;
}
