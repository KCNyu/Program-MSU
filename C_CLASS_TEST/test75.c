#include <stdio.h>
int classride(int n)
{
	if (n == 1)
	return 1;

	return classride(n - 1) * n;
}
int main()
{
	int n;
	scanf("%d",&n);
	printf("%d! = %d\n",n,classride(n));

	return 0;
}
