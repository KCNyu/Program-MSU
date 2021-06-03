#include <stdio.h>
int main()
{
	int a,sum,i;
	printf("please input a number: \n");
	scanf("%d",&a);
	sum = 0;
	while (a != 0)
	{
		i = a % 10 ;
		a = a / 10 ;
		sum = sum + i;
	}	
	printf("%d\n",sum);

	return 0 ;
}
