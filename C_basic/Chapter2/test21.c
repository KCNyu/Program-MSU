#include <stdio.h>
int main()
{
	int i , j;
	for (i = 0, j = 10 ; i < j; i++, j--)
	{
		printf("%d\n",i);
	}
	printf("%d,%d\n",i,j);
	return 0;

}
