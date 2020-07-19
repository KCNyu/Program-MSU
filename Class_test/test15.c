#include <stdio.h>
int main()
{
	int a;
	printf("please input the month: \n");
	scanf("%d",&a);

	if (3 <= a && a <= 5)
	printf("spring!\n");
	if (6 <= a && a<= 8)
	printf("summer!\n");
	if (9 <= a && a<= 11)
	printf("autumn!\n");
	if (a == 12 || (1 <= a && a<= 2))
	printf("winter!\n");

	return 0;
}
