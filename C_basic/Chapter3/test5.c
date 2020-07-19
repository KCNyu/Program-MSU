#include <stdio.h>
#include <string.h>
int main()
{
	char str1[] = "To be or not to ge";
	char str2[40];
	strncpy(str2,str1,5);
	str2[5] = '\0';	
	printf("%s\n",str2);
	return 0;
}
