#include <stdio.h>
#include <string.h>
#define N 80
int stringlen(char str[])
{
	int count = 0;
	while ( str[count] != '\0')
		count++;
	return count;
}
void printstring(char str[])
{
	int i = 0;
	while(str[i] != '\0')
	{
		printf("%c",str[i]);
		i++;
	}
	printf("\n");
	return;
}
/*int main()
{
	char s[N];
	int i,length, count = 0;
	scanf("%[^\n]s",s);
	length = stringlen(s);
	for(i = 0; i < length; i++)
	{
		if(s[i] == 'a' && ( s[i+1] == ' ' || s[i+1] == '\0' ))
			count++;
	}
	printf("found words with 'a' ending - %d\n",count);
	return 0;
}*/

/*int main()
{
	char s[N],new_s[N];
	int i,j,k = 1,newtype = 1;
	scanf("%[^\n]s",s);
	new_s[0] = s[0];
	for(i = 1; s[i] != '\0'; i++)	
	{
		for(j = 0; j < k; j++)
		{
			if(s[i] == new_s[j])
				newtype = 0;
		}
		if (s[i] == ' ')
			newtype = 0;
		if (newtype == 1)
		{
			new_s[k] = s[i];
			k++;
		}
		newtype = 1;
	}
	printstring(new_s);
	return 0;
} */

int main()
{
	char s[N];
	int i, flag = 1, length = 0, max_length,point;

	scanf("%[^\n]s",s);
	for(i = 0; s[i] != '\0'; i++)
	{
		if ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z'))
			length++;
		if (s[i] == ' ' && flag == 1)
		{
			max_length = length;
			point = 0;
			flag = 0;
			length = 0; 
		}
		if ((s[i] == ' ' || s[i+1] == '\0') && flag == 0)
		{	
			if (length > max_length)
			{
				max_length = length;
				point = i;
			}
			length = 0;
		}
	}
	for(i = point - max_length; i <= point; i++)
		printf("%c",s[i]);
	printf("\n");
	return 0;
} 

/*int main()
{
	char s[N];
	int i;
	scanf("%[^\n]s",s);
	for(i = 0; s[i] != '\0'; i++)
	{
		if (s[i] == ' ')
			s[i] = '\n';
	}
	printstring(s);
	return 0;
}*/









