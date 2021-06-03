#include <stdio.h>
int main()
{
	int a,i;
	printf("input a number: \n");
	scanf("%d",&a);
	i = 1;

	while (i <= a)
	{
		printf("%d: %d %d\n",i ,i*i, i*i*i);	
		i++;
	}

	return 0;
}
