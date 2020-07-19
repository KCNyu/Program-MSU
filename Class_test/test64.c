#include <stdio.h>
char upChar(char ch)
{
	char newch = ch;
	if(ch >= 'a' && ch <= 'z')
	newch = 'A' + (ch - 'a');
	return newch;
}
int main()
{
	char ch;
	printf("input a string: ");
	do
	{
		scanf("%c",&ch);
		printf("%c",upChar(ch));
	}while( ch != '.');
	
	printf("\n");
	return 0;
}


