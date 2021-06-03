#include <stdio.h>
int main()
{
	int a,b,t,i,sum;
	sum = 0;
	printf("input two number: \n");
	scanf("%d%d",&a,&b);

	if (a > b)
	t = a, a = b, b = t;

	while (a <= b)
	{
		i = a * a;
		sum = sum + i;	
		a++;
	}
	printf("%d\n",sum);
	return 0;
}
