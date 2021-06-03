#include <stdio.h>
void string(char c)
{	
	scanf("%c",&c);
       	if (c == '.')
		return;
       	string(c);
        printf("%c",c);
}
int main()
{
	char c;
	string(c);
	printf("\n");
	return 0;
}
