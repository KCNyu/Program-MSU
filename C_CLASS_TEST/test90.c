#include <stdio.h>
void printSquare(int n)
{
	int i,a = 0;
	while (n >= a)
	{
		for (i = 1;i <= (n-a)/2; i++)
		printf(" ");
		for (i = 1;i <= a+1; i++)
		printf("*");
	
		a = a + 2;
		printf("\n");
	}
	a = a - 2;
	while (a >= 1)
	{
		for (i = 1;i <= (n-a)/2+1; i++)
		printf(" ");
		for (i = 1;i <= a-1; i++)
		printf("*");
	
		a = a - 2;
		printf("\n");
	}
}
int main()
{
	int n;
	printf("input number: ");
	scanf("%d",&n);
	printSquare(n);
	return 0;
}
		

