#include <stdio.h>
int main()
{
	int i;

	printf("how old are you?");
	scanf("%d", &i);

	if (i >= 18)
	{
		printf("left!\n");
	}

	return 0;

}
