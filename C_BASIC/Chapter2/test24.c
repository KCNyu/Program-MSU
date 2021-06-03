#include <stdio.h>
int main()
{
	long long i, num;
	_Bool flag = 1;

	printf("please write a number!\n");
	scanf("%lld",&num);

	for (i = 2; i < num / 2; i ++)
	{
		if (num % i == 0)
		{
			flag = 0;
			break;
		}

	}
	if (flag)
	{
		printf("%lld is a primer number!",num);
	}
	else
	{
		printf("%lld is not a primer number!",num);
	}
	return 0;
}
