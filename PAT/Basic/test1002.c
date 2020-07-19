#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void Readchinese(int n)
{
	switch(n)
	{
		case 0:printf("ling ");break;
		case 1:printf("yi ");break;
		case 2:printf("er ");break;
		case 3:printf("san ");break;
		case 4:printf("si ");break;
		case 5:printf("wu ");break;
		case 6:printf("liu ");break;
		case 7:printf("qi ");break;
		case 8:printf("ba ");break;
		case 9:printf("jiu ");break;
	}
	return;
}
void Readchinese_no(int n)
{
	switch(n)
	{
		case 0:printf("ling");break;
		case 1:printf("yi");break;
		case 2:printf("er");break;
		case 3:printf("san");break;
		case 4:printf("si");break;
		case 5:printf("wu");break;
		case 6:printf("liu");break;
		case 7:printf("qi");break;
		case 8:printf("ba");break;
		case 9:printf("jiu");break;
	}
	return;
}
int main()
{
	char s[100];
	int i,len,sum = 0;
	scanf("%s",s);
	len = strlen(s);
	int n[len];
	for(i = 0; s[i] != '\0'; i++)
		n[i] = s[i] - '0';
	for(i = 0; i < len; i++)
		sum += n[i];
	if(sum >= 100)
	{
		Readchinese(sum/100);
		Readchinese((sum/10)%10);
		Readchinese_no(sum%10);
	}
	else if(sum < 100 && sum > 10)
	{
		Readchinese(sum/10);
		Readchinese_no(sum%10);
	}
	else if(sum < 10)
		Readchinese_no(sum%10);
	printf("\n");
	return 0;
}


