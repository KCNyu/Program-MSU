#include <stdio.h>
int print_square(int n,int k)
{
	int i;
	for (i = 1; i <= k; i++)
	{
		if (i <= n-k)
		printf(" ");
		if (i > n-k)
		printf("*");
	}
	if (k == n)
	return 0;
	printf("\n");
	print_square(n,k+1);
}
int print_square1(int n,int k)
{
	int i;
	for (i = 1; i <= k; i++)
	{
		if(i <= n-k)
		printf(" ");
		if(i > n-k)
		printf("*");
	}
	if (k == n/2+1)
	return 0;
	printf("\n");
	print_square1(n,k-1);
}
int main()
{
	int n;
	printf("input number: ");
	scanf("%d",&n);
	print_square(n,n/2+1);
	printf("\n");
	print_square1(n,n-1);
	printf("\n");
	return 0;
}
