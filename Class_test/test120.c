#include <stdio.h>
#include <string.h>
#define N 80
int randomInt(int n)
{
	return rand()%n;
}
int randomInt_even(int n)
{
	int number;
	do
	{
		number = rand()%n;
	}while(number%2 != 0);
	return number;

}
int stringLenth(char str[])
{
	int count = 0;
	while (str[count] != '\0')
		count++;
	return count;
}
/*int main()
{
	char s[N],count = 0;
	scanf("%[^\n]s",s);
	printf("%s, %s, %s%d\n",s,s,s,stringlenth(s));
	
	return 0;
}*/
char randomSymbol()
{
	char c;
	c = randomInt(52);
	if (c > 25)
		c = c - 25 + 'a';
	else
		c = c + 'A';
	return c;
}
/*int main()
{
	char s[11];
	int count = 0,i;
	srand(time(NULL));
	for(i = 0; i < 10; i++)
	{
		if (i%2 == 0)
			s[i]=randomSymbol();
		else
			s[i] = '0' + randomInt_even(10);
	}
	s[i] = '\0';
	puts(s);

	return 0;
}*/

/*int main()
{
	char s[N],i,count_s,number;
	scanf("%[^\n]s",s);
	count_s=stringlenth(s);
	for(i = 0; i < count_s - 1; i++)
	{
		if (s[i] == s[count_s - 1])
			printf("%d ",i);
	}
	printf("\n");
	return 0;
}*/

int main()
{
	char s1[N],s2[N];
	int count1[26] = {0},count2[26] = {0},i = 0;
	scanf("%s%s",s1,s2);
	while(s1[i] != '\0')
	{
		count1[ s1[i] - 'a']++;
		i++;
	}
	i = 0;
	while(s2[i] != '\0')
	{
		count2[ s2[i] - 'a']++;
		i++;
	}
	for(i = 0; i < 26; i++)
	{
		if (count1[i] == 1 && count2[i] == 1)
		{
			printf("%c ",'a' + i);
			putchar(' ');
		}
	}
	printf("\n");	
	return 0;
}

/*int main()
{
	char s[N];
	int i,count;
	scanf("%s",s);
	count = stringLenth(s);
	for(i = 0; i < count; i++)
	{
		if (s[i] == 'a')
			s[i] = 'b';
		else if (s[i] == 'b')
            B
			s[i] = 'a';
	}
	puts(s);
	return 0;
}*/

/*int main()
{
	char s[N];
	int i, count, judge = 0;
	scanf("%s",s);
	count = stringLenth(s);
	for (i = 0; i < count/2+1; i++)
	{
		if (s[i] == s[count-i-1])
			judge++;
	}
	if (judge == count/2+1)
		printf("right\n");
	else
		printf("no\n");

	return 0;
} */

/*int main()
{
	char s[N];
	int i,count_big = 0, count_small = 0,count;
	scanf("%s",s);
	count = stringLenth(s);
	for(i = 0; i < count; i++)
	{
		if (s[i] >= 'a' && s[i] <= 'z')
			count_small++;
		if (s[i] >= 'A' && s[i] <= 'Z')
			count_big++;	
	}
	printf("count_small = %d\n",count_small);
	printf("count_big = %d\n",count_big);
	return 0;
}*/


/*int main()
{
	char s[N];
	int i,count,answer[N],ia = 0, num = 0, flag = 0;
	scanf("%[^\n]s",s);
	count = stringLenth(s);
	for(i = 0; i < count; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			num *= 10;
			num += s[i] - '0';
			flag = 1;
		}
		else if (flag != 0)
		{
			answer[ia] = num;
			ia++;
			num = 0;
			flag = 0;
		}
	}
	for(i = 0; i < ia; i++)
	printf("%d ",answer[i]);
	printf("\n");
	return 0;
}*/

