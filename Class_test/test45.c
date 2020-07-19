#include <stdio.h>
int main()
{
	int a,b,c,d,max,min;
	printf("input number: ");
	scanf("%d",&a);
	max = a%10;
	min = a%10;
	while(a != 0)
	{	
		if (a%10 > max)
		max = a%10;
		if (a%10 < min)
		min = a%10;
		a = a/10;
	}
	printf("answer: %d\n",max+min);
	return 0;
}
