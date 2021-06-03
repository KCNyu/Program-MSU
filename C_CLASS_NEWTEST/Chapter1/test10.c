#include <stdio.h>
int Finaldigit(int n)
{
	return (n%10);
}
int abs(int n)
{
	if(n >= 0)
		return n;
	else
		return -n;
}
int lengthnumber(int n)
{
	int length = 0;
	while(n != 0)
	{
		n /= 10;
		length++;
	}
	return length;
}
int main()
{
	int i,n,length,digit;
	scanf("%d",&n);
	printf("input a digit:");
	scanf("%d",&digit);
	n = abs(n);
	length = lengthnumber(n);
	for(i = 0;i < length; i++)
	{
		if(digit == Finaldigit(n))
		{
			printf("have this digit in the number\n");
			return 0;
		}
		n /= 10;
	}
	printf("doesn't have this digit in the number\n");
	return 0;
}
