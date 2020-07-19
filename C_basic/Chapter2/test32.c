#include <stdio.h>
int main()
{
	int result, i;
	result = 0;
	i = 0;
	while (i <= 100)
	{
		result += i;
		i++;
	}
	printf("result = %d\n i = %d\n",i,result);
	return 0;
}

