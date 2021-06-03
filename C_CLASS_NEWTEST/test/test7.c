#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define  N 10
int main()
{
	int a[N],b[N],c[N],i,j,k = 0,k_count,count_element,type = 0,newtype = 1;
	srand(time(NULL));
	for(i = 0; i < N; i++)
		a[i] = rand()%20;
	for(i = 0; i < N; i++)
		printf("%d ",a[i]);
	printf("\n");
	
	for(i = 0; i < N; i++)
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
        if(newtype == 0){
            newtype = 1;
            continue;
        }
		for(j = i + 1; j < N; j++)
		{
			if(a[i] == a[j])
			count_element++;
		}
		c[k] = count_element;
		if(newtype == 1)
		{
			b[k] = a[i];
			k++;
		}
		newtype = 1;
	}
	for(i = 0; i < k; i++)
		printf("%d:%d ",b[i],c[i]);
	printf("\n");
	return 0;
}
