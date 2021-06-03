#include <stdio.h>

int main()
{	
	int n,i;
	printf("input number: ");
	scanf("%d",&n);
	for (i = n; i >= 1; i-=2)
	{		
		printf("%d ",i);
	}
	printf("\n");		
	return 0;
}
