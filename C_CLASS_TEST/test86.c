#include <stdio.h>
int max(int n1, int n2, int n3)
{
	int max1 = n1;
	if (n2 > max1)
	max1 = n2;
	if (n3 > max1)
	max1 = n3;

	return max1;
}
int main()
{
	int n1,n2,n3;
	printf("input 3 numbers: ");
	scanf("%d%d%d",&n1,&n2,&n3);
	printf("Answer = %d\n",max(n1,n2,n3));
	return 0;
}

	
