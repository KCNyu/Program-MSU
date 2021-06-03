#include <stdio.h>
int main()
{
	int a,b;
	printf("please input 2 numbers");
	scanf("%d %d",&a,&b);

	if (a != b)
	{
		if (a > b)
		{
			printf("%d > %d",a,b);
		}
		else
		{
			printf("%d < %d",a,b);
		}

	}
	else
	{
		printf("%d = %d",a,b);
	}

		return 0;
	}
