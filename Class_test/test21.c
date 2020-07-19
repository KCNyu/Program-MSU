#include <stdio.h>
int main()
{
	int a,i;
	printf("please input a number: \n");
	scanf("%d",&a);
	i = 0;

	while (a != 0)
	{
		a = a / 10;
		i++ ;
	}
	
	if (i == 3)
	printf("Yes!\n");
	else
	printf("No!\n")	;

	return 0;
}
