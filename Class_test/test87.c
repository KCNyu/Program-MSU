#include <stdio.h>
int number_three(int n)
{
	if (n == 0)
	return 0;
	if (n%10 == 3)
	return number_three(n/10) + 1;
	if (n%10 != 3)
	return number_three(n/10);
}
int main()
{
	int n;
	printf("input number: ");
	scanf("%d",&n);
	printf("Answer:%d\n",number_three(n));
	return 0;
}
