#include <stdio.h>
int main()
{	
	int a,b,k;
	printf("input number: ");
	scanf("%d",&a);
	printf("input power: ");
	scanf("%d",&b);
	k = a;
	while (b != 1)
	{
		a = a * k;
		b--;
	}	
	printf("Answer:%d\n",a);

	return 0;
}
