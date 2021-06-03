#include <stdio.h>
void print_three_n(int n)
{
	if (n == 0)
	return;
        print_three_n(n/3);
        printf("%d",n%3);
}
int main()
{
	int n;
	printf("input number: ");
	scanf("%d",&n);
	print_three_n(n);
	printf("\n");
	return 0;
}
	
