#include <stdio.h>
int main()
{
	int x,y = 1,z;
	while(y < 11)
	{
		x = y++;
		z = ++y;
	}
	printf("x = %d\ny = %d\nz = %d\n",x,y,z);
	return 0;
}
