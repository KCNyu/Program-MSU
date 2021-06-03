#include <stdio.h>
int main()
{
	int i,n,n_square = 1;
	scanf("%d",&n);
	for(i = 1; i <= n; i++)
	{		
		printf("%d^2 = %d\n",i,n_square);
		n_square = n_square + +i+i + 1;
	}
	return 0;
}
