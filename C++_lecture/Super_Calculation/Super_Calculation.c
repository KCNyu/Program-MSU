#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int len1,len2,len_max;
void input(int n1[],int n2[])
{
	int i;
	char s1[100],s2[100];
	printf("input two numbers:");
	scanf("%s%s",s1,s2);
	len1 = strlen(s1);
	len2 = strlen(s2);
	for(i = 0; i < len1; i++)
		n1[len1-i-1] = s1[i] - '0';
	for(i = 0; i < len2; i++)
		n2[len2-i-1] = s2[i] - '0';
		len_max = len2;
	if(len1 > len2)
	{
		for(i = len2; i < len1; i++)
			n2[i] = 0;
		len_max = len1;
	}
	if(len1 < len2)
	{
		for(i = len1; i < len2; i++)
			n1[i] = 0;
		len_max = len2;
	}
	return;
}
void addition(int n1[],int n2[])
{
	int i,flag = 0,sum,n_add[len_max+1],len_add;
	for(i = 0; i < len_max; i++)
	{
		sum = n1[i] + n2[i];
		n_add[i] = (sum + flag)%10;
		flag = (sum + flag)/10;
	}
	
	if(flag == 1)
	{
		n_add[len_max] = 1;
		len_add = len_max;
	}
	else
		len_add = len_max-1;
	printf("sum = ");
	for(i = len_add; i >= 0; i--)
		printf("%d",n_add[i]);
	printf("\n");
	return;	
}
void multiplication(int n1[],int n2[])
{
	int i,j,len_mult = len1+len2, flag = 0;
	int n_product[len_mult];
	for(i = 0; i < len_mult; i++)
		n_product[i] = 0;
	for(i = 0; i < len1; i++)
		for(j = 0; j < len2; j++)
		{
			n_product[i+j] = n1[i] * n2[j] + n_product[i+j];
			n_product[i+j+1] = n_product[i+j]/10 + n_product[i+j+1];
			n_product[i+j] = n_product[i+j]%10;
		}
	printf("product =");
	for(i = len_mult-1; i >= 0; i--)
	{
		if(n_product[len_mult-1] == 0 && flag == 0)
		{
			flag = 1;
			continue;
		}
		printf("%d",n_product[i]);
	}
	printf("\n");
	return;
}
int main()
{
	int n1[100], n2[100];
	input(n1,n2);
	addition(n1,n2);
	multiplication(n1,n2);
	return 0;
}

