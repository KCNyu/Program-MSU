#include <stdio.h>
#include <stdlib.h>
int randomInt(int n)
{
	return rand()%n;
}
int main()
{
	int a[10],b[10],i,j,tmp_Max,iMax = 0,countMax = 0;
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
		tmp_Max = 1;
		for(j = i + 1; j < 10; j++)
		{
			if (a[i] == a[j])
				tmp_Max++;
		}
		if (tmp_Max > countMax)
		{
			iMax = i;
			countMax = tmp_Max;
		}	
	}
	printf("a[%d] = %d count = %d",iMax,a[iMax],countMax);
	printf("\n");	
	return 0;
}
