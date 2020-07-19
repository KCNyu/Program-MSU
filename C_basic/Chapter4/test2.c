#include <stdio.h>
int main()
{
	int a;
	int *p = &a;
	printf("please write a number: ");
	scanf("%d",&a);
	printf("a = %d\n",a);

	printf("please write a number again: ");
	scanf("%d",p);
	printf("a = %d\n",a);

	return 0;
}

