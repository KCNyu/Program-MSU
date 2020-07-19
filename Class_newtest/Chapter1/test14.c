#include <stdio.h>
int main()
{
	int n,k,integer_part;
	scanf("%d%d",&n,&k);
	while(n > k)
	{
		n -= k;
		integer_part++;
	}
	printf("integer part = %d\nremainder part = %d\n",integer_part,n);
	return 0;
}

		
