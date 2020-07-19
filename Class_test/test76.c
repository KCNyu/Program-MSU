#include <stdio.h>
void printN(int i,int n)
{
	if (i == n)
	{
		printf("%d ",i);
		return;
	}
	if (i > n)
	{
		printf("%d ",i);
		printN(i-1 , n);
	}
	else
	{
		printf("%d ",i);
		printN(i+1 , n);
	}
}
int main()
{
	int i,n;
	scanf("%d%d",&i,&n);
	printN(i,n);
	printf("\n");
	return 0;
}
