#include <stdio.h>
int main()
{
	int i,a,b,odd,even;

	printf("input a number: \n");
	scanf("%d",&i);
	odd = 0;
	even = 0;
	while (i != 0)
	{
		a = i % 10;
	
		if (a%2 == 0)
		even++ ;
		else
		odd++ ;	
		
		
		i = i/10;
	}
	printf("even = %d\nodd = %d\n",even,odd);
	
	return 0;
}

