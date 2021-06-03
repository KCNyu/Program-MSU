#include <stdio.h>
int primer(int n)
{
	scanf("%d",&n);
	if (n == 0)
	return 0;

	primer(n);	
	
	if (n % 2 != 0)
	printf("%d ",n);	
}
int main()
{
	int n;
	primer(n);
	printf("\n");
	return 0;
}

