#include <stdio.h>
int judge1(char c)
{
	int count1 = 0;
	if ( c == '(')
	count1++;

	return count1;
}
int judge2(char c)
{
	int count2 = 0;
	if ( c == ')')
	count2++;

	return count2;
}
int main()
{
	char c,sum1 = 0,sum2 = 0;
	printf("input text: ");
	do
	{
		scanf("%c",&c);
		sum1 += judge1(c);
		sum2 += judge2(c);
	}while(c != '.');

	if (sum1 == sum2)
	printf("yes\n");
	else
	printf("no\n");

	return 0;
}
