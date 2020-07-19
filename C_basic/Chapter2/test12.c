#include <stdio.h>
int main()
{
	char isRain, isFree;

	printf("Free?(Y/N)");
	scanf("%c",&isFree);

	getchar();

	printf("Rain?(Y/N)");
	scanf("%c",&isRain);

	if (isFree == 'Y' && isRain == 'Y')
	{
		printf("please bring umbrella!\n");
	}
	else if (isFree == 'N')
	{
		printf("get out!\n");
	}
	else
	{
		printf("good luck!\n");
		
	}

	return 0;

}
