#include <stdio.h>
int function(int x ,int y)
{
	int i = 1,a,b = 0;
	while (x != 0)
	{
		a = x%y;
		x = x/y;
		b = b + a*i;
		i = i*10;
	}
	return b;
}
int main()
{
	int x,y;
	printf("input x and y : ");
	scanf("%d%d",&x,&y);
	printf("%d\n",function(x,y));
	return 0;
}
