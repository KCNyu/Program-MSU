#include <stdio.h>
int main()
{
	char ch;

	printf("how points are you?\n");
	scanf("%c",&ch);

	switch(ch)
	{
		case 'A': printf("your marks are higher than 90!\n");
		case 'B': printf("your marks are between 80 and 90!\n");
        	case 'C': printf("your marks are between 70 and 80!\n");
		case 'D': printf("your marks are between 60 and 70!\n");
		case 'E': printf("your marks are lower than 60!\n");
		default:  printf("please write former marks!\n");
	}

	return 0;
}
