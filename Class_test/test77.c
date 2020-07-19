#include <stdio.h>
int sum(int n)
{
	if(n == 1)
	return 1;
	return sum(n-1) + n;
}
int number1(int n)
{	
	if (n == 0)
	return 0;

	return number1(n/10) + n%10;
}
void number2(int n)
{
	if (n == 0)
		return;
	number2(n/10);
	printf("%d ",n%10);
}
void two_n(int n)
{
	if (n == 0)
		return;
	two_n(n/2);
	printf("%d",n%2);
}
void string(char c)
{
	scanf("%c",&c);
	if (c == '.')
		return;
	string(c);
	printf("%c",c);
}
int judge(int n, int i)
{
	if (n == i)
	return 0;
	if (n%i == 0)
	return 1;
	
	judge(n , (i + 1));
}
int main()
{
	int n;
	scanf("%d",&n);
	if (judge(n,2))
	printf("yes\n");
	else
	printf("no\n");
	return 0;
}
