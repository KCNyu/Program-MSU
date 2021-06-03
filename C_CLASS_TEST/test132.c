#include <stdio.h>
int main()
{
	char s[52],input_string[80];
	int i,a,N;
	for(i = 0; i < 52; i++)
	{
		s[i] = 'a' + i;
		if (i > 25)
			s[i] = 'a' + (i - 26);
	}
	printf("input the string:");
	scanf("%s",&input_string);
	printf("input the number:");
	scanf("%d",&N);
	for(i = 0; input_string[i] != '\0'; i++)
	{
		for(a = 0; a < 26; a++)
		{
			if(input_string[i] == s[a])
			{
				printf("%c",s[a+N]);
				break;
			}
		}
	}
	printf("\n");
	return 0;
}


