#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main()
{
	int n,i;
	printf("input n:");
	scanf("%d",&n);
	int A[n];
	for(i = 0; i < n; i++)
		scanf("%d",&A[i]);
	int x,left = 0,right = n,flag = 0,mid = (left+right)/2;
	printf("input x:");
	scanf("%d",&x);
	if(x == A[0])
	{
		printf("x = A[0]\n");
		return 0;
	}
	while( mid != 0)
	{
		mid = (left+right)/2;
		if(x == A[mid])
		{
			printf("x = A[%d]\n",mid);
			flag = 1;
			break;
		}
		if(x > A[mid])
			left = mid;
		else
			right = mid;
		mid = (left+right)/2;
	}
	if(flag != 1)
		printf("no\n");
	return 0;
}	
			
