#include <stdio.h>
int max(int n)
{
	int max1;
	scanf("%d",&n);
	if (n == 0)
	return 0;
	else
	{
		max1 = max(n);
		if (n > max1)
		return n;
		else
		return max1;
	}
}
int main()
{
	int n;
	printf("%d\n",max(n));
	return 0;
}

