#include <stdio.h>
int main()
{
	char str[] = "i love you!";
	char *target = str;
	int count = 0;

	while(*target++ != '\0')
	{
		count++;
	}
	printf("count = %d\n",count);
	return 0;
}	
