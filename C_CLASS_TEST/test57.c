#include <stdio.h>
int main()
{	
	int m,i = 0,a = 0;

	do
	{	
		printf("input number: ");
		scanf("%d",&m);
		switch(m)
		{
		case 1 : printf("this month 31 days\n");i = 0;break;
		case 2 : printf("this month 28 days\n");i = 0;break;
		case 3 : printf("this month 31 days\n");i = 0;break;
		case 4 : printf("this month 30 days\n");i = 0;break;
		case 5 : printf("this month 31 days\n");i = 0;break;
		case 6 : printf("this month 30 days\n");i = 0;break;
		case 7 : printf("this month 31 days\n");i = 0;break;
		case 8 : printf("this month 31 days\n");i = 0;break;
		case 9 : printf("this month 30 days\n");i = 0;break;
		case 10 : printf("this month 31 days\n");i = 0;break;
		case 11 : printf("this month 30 days\n");i = 0;break;
		case 12 : printf("this month 31 days\n");i = 0;break;
		
		default : i++,a++;
		}
	}
	while(i != 0);	
	printf("you try %d times\n",a);
	return 0;
}
