#include <stdio.h>
int main()
{
	int a[] = {1, 2, 3, 4, 5};
	int *p = a;
	printf("p -> %p, p+1 -> %p, p+2 -> %p\n",p,(p+1),(p+2));
	printf("*p = %d, *(p+1) = %d, *(p+2) = %d\n",*p,*(p+1),*(p+2));
	return 0;
}
