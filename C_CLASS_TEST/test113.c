#include <stdio.h>
#include <stdlib.h>
int randomInt(int n)
{
	return rand()%n;
}
int main()
{
	int a[32],i,j,tmp,nX = -1, R = 32, L = 0, X, c,stepcount = 0;
	srand(time(NULL));
	for(i = 0; i < 32; i++)
		a[i] = randomInt(101);
	for(i = 0; i < 31; i++)
	{
		for(j = 0; j < 31-i; j++)
		{
			if (a[j] < a[j+1])
			{
				tmp = a[i];
				a[j] = a[j+1];
				a[j+1] = tmp;
			}
		}	
	}
	printf("please input a number : ");
	scanf("%d",&X);
	while (R >= L)
	{
		c = (R + L) / 2;
		if (X == a[c])
		{
			nX = c;
			break;
		}
		if (X > a[c])
		{
			R = c - 1;
			stepcount++;
		}
		if (X < a[c])
		{
			L = c + 1;
			stepcount++;
		}
	}
	if(nX < 0)
	printf("Not found!\n");
	else
	printf("a[%d] = %d\n",nX,X);
	printf("stepcount = %d\n",stepcount);
	return 0;
}	

	
