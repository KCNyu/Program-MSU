#include <stdio.h>
int main()
{
	char a[] = "FishC";
	char *p = a;
	printf("*p = %c, *(p+1) = %c, *(p+2) = %c\n",*p,*(p+1),*(p+2));
	return 0;
}
