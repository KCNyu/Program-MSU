#include <stdio.h>
int main()
{
	int a = 5, b = 3;

	printf("%d\n", 1 < 2);
	printf("%d\n", a > b);
	printf("%d\n", a <= 1 + b);
	printf("%d\n", 'a' + 'b' <= 'c');
	printf("%d\n", (a=3) > (b=5));

	return 0;

}	
