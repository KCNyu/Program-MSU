#include <stdio.h>
int main()
{
	int a, b, c;
	a =( b = 3,(c = b + 4) + 5);
	printf("a = %d, b = %d, c = %d\n",a, b, c);

	return 0;
}
