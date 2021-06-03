#include <stdio.h>
int main()
{
	int n,k,i;
	scanf("%d",&n);
	k = 1;
	i = 0;

	while(k != (n+1))
	{	   
		while( i != k )
		{
			printf("*");
			i++;
		}
		printf("\n");
		k++;
		i = 0;
	
	}
	return 0;
}
		

