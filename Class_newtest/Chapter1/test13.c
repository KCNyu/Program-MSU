#include <stdio.h>
int gcd(int a, int b)
{
	while(a != 0)
	{
		a = a % b;
		if(a == 0)
			return b;
		b = b % a;
		if(b == 0)
			return a;
	}
}
int main()
{
	int a,b;
	scanf("%d%d",&a,&b);
	printf("%d\n",gcd(a,b));
	return 0;
}

