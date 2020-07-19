#include <stdio.h>
int two_n(int n)
{	
	if (n == 0)
	return 0;	
	if (n%2 == 0)
	return two_n(n/2);	
	if (n%2 == 1)
	return two_n(n/2) + 1;
}
void print_two_n(int n)
{
	if (n == 0)
	return;
        print_two_n(n/2);
        printf("%d",n%2);
}
int main()
{
	int n;
	printf("input a number: ");
	scanf("%d",&n);
	print_two_n(n);
	printf("\n%d\n",two_n(n));

	return 0;
}
