#include <stdio.h>

int main()
{	
	int n1,n2,i;
	printf("input number: ");
	scanf("%d%d",&n1,&n2);
	for (i = n1; i <= n2; i++ )
	{		
		printf("%d*%d*%d = %d\n",i,i,i,i*i*i);
	}
	return 0;
}
