#include <stdio.h>
#include <stdlib.h>
int randomInt(int n)
{
	return rand()%n;
}
int main()
{
	int a[10],i,j,b[10],count = 0,k,isExist;
	srand(time(NULL));
	for(i = 0; i < 10; i++)
		a[i] = randomInt(10);
	for(i = 0; i < 10; i++)
		printf("a[%d] = %d ",i,a[i]);
	printf("\n");
	for(i = 0; i < 10; i++)
	{
		for(j = i + 1; j < 10; j++)
		{
			if(a[i] == a[j])
			{
				isExist = 0;
				for(k = 0; k < count; k++)
					if(b[k] == a[i])
						isExist = 1;
				if(isExist == 0)
				{
					b[count] = a[i];
					count++;
					break;
				}
			}
		}
	}
	for(i = 0; i < count; i++)
	{
		printf("b[%d] = %d ",i,b[i]);
	}
	printf("\n");	
	return 0;
}
