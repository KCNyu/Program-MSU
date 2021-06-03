#include <stdio.h>
int main()
{
	int i, num;
	_Bool flag = 1;

	printf("please write a number!");
	scanf("%d",&num);

	for ( i = 2; i <= num / 2; i++)
	{
		if (num % i == 0)
		{
			flag = 0;
		}
	}
	if (flag)
	{
		printf("%d is a prime number!\n",num);
	}
	else
	{
		printf("%d is a composite number!\n",num);
	}

	return 0;

}

