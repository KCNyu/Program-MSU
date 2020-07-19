#include <stdio.h>
int main()
{
	int a,i,k,x = 0;

	printf("input a number: \n");
	do
	{
		scanf("%d",&a);
		if (a <= 0)
		printf("input a positive number: \n");
	}
	while(a <= 0);

	printf("repeat: ");
	while(a != 0)
	{
		k = 0;
		i = a;
		while (i != 0)	
		{	
			if ( a%10 == (i/10)%10 )
			k++;
			
			i = i / 10;	
		}
		if (k == 1)
		{
			printf("%d ",a%10);
	 		x++;
		}
		a = a / 10;
	}	
	
	if (x == 0)
	printf("Not!");

	printf("\n");
	return 0;

}	
