#include <stdio.h>
int main()
{
	int count = 0;
	printf("please write a sentence!");
	while (getchar() != '\n')
	{
		count = count + 1;
	}
	printf("you have written %d words!\n",count);
	
	return 0;

}
