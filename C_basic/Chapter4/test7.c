#include <stdio.h>
#include <string.h>
int main()
{
	char *str = "i love fish.com!";
	int i, length;

	length = strlen(str);

	for (i = 0; i < length; i++)
	{
		printf("%c",str[i]);
	}
	printf("\n");
	
	return 0;
}
