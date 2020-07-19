#include <stdio.h>
#include <string.h>
int main()
{
	char str1[] = "i love you!";
	char str2[] = "i love you!";
	if (!strcmp (str1,str2))
	{
		printf("the same!\n");
	}
	else
	{
		printf("not the same!\n");
	}
	return 0;
}

