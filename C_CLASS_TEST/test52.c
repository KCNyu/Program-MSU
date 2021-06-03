#include <stdio.h>
int main()
{
	int a,b,i,sum = 0;
	printf("input number: ");
	scanf("%d%d",&a,&b);
	
	for(i = a; i <= b; i++)
	{
		sum += i*i;
	}
	printf("sum = %d\n",sum);
		
	return 0;
}
