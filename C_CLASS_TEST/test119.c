#include <stdio.h>
int main()
{
	char q[80];
	int i;
	printf("input string\n");
	scanf("%s",q);
	i = 0;
	while(q[i] != '\0')
	{
		if (q[i] == 'a')
			q[i] = 'b';
		i++;
	}
	printf("reslut: %s\n",q);
	return 0;
}
	
