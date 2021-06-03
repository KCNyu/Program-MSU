#include <stdio.h>
int main()
{
	int n, i;
	printf("please write the number of the string: ");
	scanf("%d",&n);
	char a[n + 1];
	printf("please write the string: ");
	getchar();
	for (i = 0; i < n; i++)
	{
		scanf("%c", &a[i]);
	}
	a[n] = '\0';
	printf("the string which you write is: %s\n",a);
	return 0;
}
	
