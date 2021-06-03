#include <stdio.h>
int main()
{
	int digit[10] = {}, n,i,j,currentDigit;
	
	printf("input number: ");
	scanf("%d",&n);
	while(n)
	{
		currentDigit = n%10;
		digit[currentDigit]++;
		n /= 10;
	}
	for(i = 0; i <= 9 ;i++)
		for(j = 0; j < digit[i]; j++)
			printf("%d ",i);
	printf("\n"); 
	return 0;
}

