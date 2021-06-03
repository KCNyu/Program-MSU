#include <stdio.h>
int main()
{
	int a, count;
	printf("input number \n");
	scanf("%d",&a);
	count = 0;
	while(a != 0)
	{		
		if (a%2 == 0)
		count++;	
		scanf("%d",&a);
	}
	printf("count = %d\n",count);
	return 0;
}
