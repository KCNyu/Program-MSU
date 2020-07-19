#include <stdio.h>
int main()
{
	int n,count = 0;
	scanf("%d",&n);
	while(n != 1)
	{
		if(n%2 == 0)
		{
			n = n/2;
			count++;
		}
		else
		{
			n = (3*n+1)/2;
			count++;
		}
	}
	printf("%d",count);
	return 0;
}


