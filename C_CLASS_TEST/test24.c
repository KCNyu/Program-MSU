#include <stdio.h>
int main()
{
	int a,i,k = 0;
	printf("please input a number: \n");
	scanf("%d",&a);

	while (a != 0)
	{
		i = a;
		while (i != 0)		
		{
			if (a%10 == (i / 10) % 10)
			{	
				printf("Yes\n");
                           	k ++;
				return 0;
			}
			i = i/10;
		}	
		a = a / 10;
	}	
	if (k == 0)
	printf("No!\n");
	return 0 ;
}
