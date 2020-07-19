#include <stdio.h>
int main()
{
	int array[4][5] = {0};
	printf("sizeof int : %ld\n",sizeof(int));
	printf("array: %p\n",array);
	printf("array+1: %p\n",array + 1);
	return 0;
}
