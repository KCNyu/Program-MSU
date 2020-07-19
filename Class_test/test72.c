#include <stdio.h>
int isDight(char c)
{
	if (c >= '0' && c <= '9')
	{
		c = c - '0';
		return c ;
	}	
	return 0;
}
int main()
{
	char c,sum = 0;
	printf("input text: ");
	do
	{
		scanf("%c",&c);
		sum += isDight(c);
	}while( c != '.');
	
	printf("sum = %d\n",sum);

	return 0;
}
