#include <stdio.h>
int main()
{
	int a,i;
	printf("please input a number: \n");
	scanf("%d",&a);

	while (a != 0)
	{
		if (a % 10 == (a / 10) % 10)
		{	
			printf("Yes\n");
			break ;
		}
		a = a / 10;
	}	

	return 0 ;
}
