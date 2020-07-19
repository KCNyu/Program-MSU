#include <stdio.h>
int main()
{
	char a;
	int sum = 0;
	printf("please input char: ");

	do
	{
		scanf("%c",&a);
		if (a >= '0' && a <= '9')
		{
			a = a - '0';
			sum = sum + a;
		}
	}		
	while( a != '.');
	
	printf("%d\n",sum);

}
	
