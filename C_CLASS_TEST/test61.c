#include <stdio.h>
int function(int x)
{
	int f;
	if (x >= -2 && x <= 2)
	f = x*x;
	if (x >= 2)
	f = x*x+4*x+5;
	if (x < 2)
	f = 4;

	return f;
}
int main()
{	
	int x,max,i = 0; 
	printf("input number: ");
	do
	{
		scanf("%d",&x);
		if (i == 0)
		max = function(x);
		else if (function(x) > max)
		max = function(x);

		i++;
	}while(x != 0);

	printf("max = %d\n",max);

	return 0;
}
