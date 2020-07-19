#include <stdio.h>
int judge()
{
	char c;
	int count = 0;
	do
	{
		scanf("%c",&c);
		if (c == '(')
		count ++;
		if (c == ')')
		count --;
		if (count < 0)
		return 0;
	}while( c != '.');

	if ( count == 0)
	return 1;
	else
	return 0;
}
int main()
{
	char c;
	printf("input text: ");
	if (judge(c))
	printf("yes\n");
	else
	printf("no\n");
	return 0;
}




