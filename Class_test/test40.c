#include <stdio.h>
int main()
{
	char a;
	int i = 0;
	printf("please input char: ");

	do
	{
		scanf("%c",&a);
		i++ ;
	}
	while( a != '.');
	
	printf("%d\n",i);

}
	
