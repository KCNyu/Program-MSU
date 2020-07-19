#include <stdio.h>
#include <stdlib.h>
int randomInt(int n)
{
	return rand()%n;
}
int main()
{
	int a[10],b[10],i,j,count = 0,isExist;
	srand(time(NULL));
	for(i = 0; i < 10; i++)
	{
		a[i] = randomInt(11);
	}
	for(i = 0; i < 10; i++)
		printf("a[%d] = %d ",i,a[i]);
	printf("\n");
	for(i = 0; i < 10; i++)
	{
		isExist = 0;
		for(j = 0; j < 10; j++)
		{
			if (i != j)
			{	
				if (a[i] == a[j])
				{	
					isExist = 1;
					break;
				}
			}
		}
		if (isExist == 0)
		{
			b[count] = a[i];
			count++;
		}
	}
	for(i = 0; i < count; i++)
		printf("b[%d] = %d ",i,b[i]);
	printf("\n");	
	return 0;
}
