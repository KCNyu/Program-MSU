#include <stdio.h>
int main()
{
	char a = 'F';
	int f = 123;
	char *pa = &a;
	int *pf = &f;

	printf("a = %c\n", *pa);
	printf("f = %d\n", *pf);

	*pa = 'c';
	*pf = *pf + 1;
	printf("now, a = %c\n", *pa);
	printf("now, f = %d\n", *pf);

	printf("sizeof pa = %d\n", sizeof(pa));
	printf("sizeof pa = %d\n", sizeof(pf));

	printf("the addr of a is: %p\n", pa);
	printf("the addr of f is: %p\n", pf);

	return 0;
}
