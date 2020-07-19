#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define N 80
/*int main()
{

	char s[N];
	int i,count = 0;
	scanf("%s",s);
	for (i = 0; s[i] != '\0'; i++);

	if (s[i - 4] == '.')
		strcpy(s+i-4,".html");
	else
		strcat(s,".html");
	puts(s);
	putchar('\n');
	return 0;
}*/

/*int main()
{
	char s1[N],s2[N];
	scanf("%s%s",s1,s2);
	printf("hello,%s %s\n",s1,s2);
	return 0;
}*/

/*int main()
{
	int x = 7,*px,a[5] = {10,20,30,40,50},i;
	printf("x = %d address x = %p\n",x,&x);
	px = &a[0];
	px = px + 2;
	*px = 25;
	for(i = 0;a[i] != '\0'; i++)
		printf("a[%d] (addr %p) = %d\n",i,&a[i],a[i]);
	return 0;
}*/

/*int main()
{
	int i;
	char s[10] = "abcdef",*p;
	p = strchr(s,'c');
	printf("%c [add %p] nomer = %d\n",*p,p,p-s);
	for(i = 0; s[i] != '\0'; i++)
		printf("%c [add %p] nomer = %d\n",s[i],&s[i],i);
	return 0;
}*/

/*int main()
{
	char s[N],out[N] = {0},*p;	
	int i;
	scanf("%[^\n]s",s);
	printf("addr (s) = %p\n",s);
	for(i = 0; s[i] != '\0'; i++)
		printf("s[%d] = %c addr = %p\n",i,s[i],&s[i]);
	p = strstr(s,"ling");
	printf("addr (ling) = %p\n",p);
	printf(" (p-s) = %d\n",p-s);
	strncpy(out,s,p-s);
	strcat(out,"cao!!!");

	puts(out);
	printf("\n");
	return 0;	
}*/

/*int main()
{
	char s[N],out[N] = {0},*p;
	int i,number = 0,count = 0;
	scanf("%[^\n]s",s);
	p = strstr(s,"ling");
	while(p != NULL)
	{	
		for(i = p - s; i <= p-s+3; i++)
			s[i] = ' ';
		if(count != 0)
		{
			strncat(out,s+number+1,p-s-number-1);
			strcat(out,"cao");
		}
		if(count == 0)
		{
			strncat(out,s+number,p-s-number);
			strcat(out,"cao");
			count++;
		}
		number = p-s+3;
		p = strstr(s,"ling");
	}
	strncat(out,s+number+1,100);
	puts(out);
	return 0;
}*/

/*int main()
{
	char s[N],out[N] = {0},*p;
	int i,number = 0,count = 0;
	scanf("%[^\n]s",s);
	p = strstr(s,"cao");
	while(p != NULL)
	{	
		for(i = p - s; i <= p-s+2; i++)
			s[i] = ' ';
		if(count != 0)
		{
			strncat(out,s+number+1,p-s-number-1);
			strcat(out,"ling");
		}
		if(count == 0)
		{
			strncat(out,s+number,p-s-number);
			strcat(out,"ling");
			count++;
		}
		number = p-s+2;
		p = strstr(s,"cao");
	}
	strncat(out,s+number+1,100);
	puts(out);
	return 0;
}*/
	
/*int main()
{
	char s[N],out[N] = {0},*p;
	scanf("%[^\n]s",s);
	p = strstr(s,"ling");
	printf("%d\n",p-s);
	strncpy(out,s,10);
	
	puts(out);
}*/

void swapChar(char s[])
{
	int i,j,count = 0;
	char tmp;
	for(i = 0; s[i] != '\0'; i++)
	{
		for(j = i + 1; s[j] != '\0'; j++)
		{
			if(s[j] != ' ')
			{
				tmp = s[i];
				s[i] = s[j];
				s[j] = tmp;
				i = j;
				break;
			}
		}
	}
	return;
}
int main()
{
	char s[N];
	scanf("%[^\n]s",s);
	swapChar(s);
	puts(s);
	return 0;
}

	


























