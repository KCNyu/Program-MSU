#include <stdio.h>
int main()
{
	int a,b,c,n,i;
	i = 1;
	b = 0;
	printf("input number: ");
	scanf("%d",&n);
	
	while(n != 0)
	{
		a = n%3;
		n = n/3;
		b = b + a*i;
		i = i*10;
	}
	printf("Answer: %d\n",b);
	return 0;
}
