#include <stdio.h>
int main()
{
	int i;
	printf("how old are you?\n");
	scanf("%d",&i);

	if (i >= 18)
	{
		printf("left!\n");
	}
	
	else
	{
		printf("get out!\n");
	}

	return 0;

}
