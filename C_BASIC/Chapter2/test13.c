#include <stdio.h>
int main()
{
	char hasBF;

	printf("do you have boyfriend?(Y/N)");
	scanf("%c",&hasBF);

	if (hasBF == 'Y')
	{
		printf("good job!\n");
	}
	else
	{
		printf("i love you!\n");
	}

	return 0;

}
