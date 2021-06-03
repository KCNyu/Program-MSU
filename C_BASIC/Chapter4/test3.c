#include <stdio.h>
int main()
{
	char str[128];
	printf("please input the website: ");
	scanf("%s",str);
	printf("the website is %s\n",str);
	printf("str addr = %p\n",str);	
	printf("str addr = %p\n",&str[0]);
	return 0;
}
