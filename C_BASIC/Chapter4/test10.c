#include <stdio.h>
int main()
{
	char *p1[3] =
	{
		"a-1",
		"b-2",
		"c-3"
	};
	int i;
	for (i = 0; i < 3; i++)
		printf("%s\n",p1[i]);
	
	return 0;
}
