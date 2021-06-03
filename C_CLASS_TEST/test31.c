#include <stdio.h>
int main()
{
	int a, count;
	printf("input number \n");
	scanf("%d",&a);
	count = 0;
	while(a != 0)
	{
		scanf("%d",&a);
		count++;
	}
	printf("count = %d\n",count);
	return 0;
}
