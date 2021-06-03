#include <stdio.h>
int main()
{
	int i;
	i = 0;
	while( i < 100 )
	{
		if(i % 2)
		{
			continue;
		}
	i++;
	printf("%d\n",i);
	}
	return 0;
}
