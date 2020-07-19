#include <stdio.h>
#include <stdlib.h>
int randomInt(int n)
{
	return rand()%n + 2;
}
int main()
{
	int k,i,j,multiple;
	srand(time(NULL));
	k = randomInt(97);
	printf("k = %d\n",k);
	for(j = 2; j < 10; j++)
	{
		for(i = k; i > 0 ; i--)
		{
			if(i % j == 0)
			{
				multiple = i/j;
				break;
			}
			else
				multiple = 0;
		}
		printf("%d--%d\n",j,multiple);
	}
	return 0;
}
