#include <stdio.h>
int main()
{
	int i , j;
	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 10; j++)
		{
			if (j == 3)
			{
				break;
			}
		}
		if (j == 3)
		{
			break;
		}
	}
	printf("%d\n%d\n",i,j);
	return 0;
}
