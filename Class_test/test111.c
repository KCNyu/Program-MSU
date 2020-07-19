#include <stdio.h>
#include <stdlib.h>
int randomInt(int n)
{
	return rand()%n;
}
int main()
{
	int a[10],b[10],c[10],i,j,k = 0,k_count,count_element,type = 0,newtype = 1;
	srand(time(NULL));
	for(i = 0; i < 10; i++)
		a[i] = randomInt(11);
	for(i = 0; i < 10; i++)
		printf("a[%d] = %d ",i,a[i]);
	printf("\n");
	
	for(i = 0; i < 10; i++)
	{
		count_element = 1;
		if(i != 0)
		{
			for (k_count = 0; k_count < k; k_count++)
			{
				if (a[i] == b[k_count])
				{
					newtype = 0;
					break;
				}
			}
		}
		if (newtype != 0)
			type = 0 ;
		for(j = i + 1; j < 10; j++)
		{
			if(a[i] == a[j])
			count_element++;
		}
		c[k] = count_element++;
		if(type == 0)
		{
			b[k] = a[i];
			k++;
			type = 1;
		}
		newtype = 1;
	}
	
	for(i = 0; i < k; i++)
		printf("b[%d] = %d ",i,b[i]);
	printf("\n");
	for(i = 0; i < k; i++)
		printf("c[%d] = %d ",i,c[i]);
	printf("\n");
	return 0;
}
