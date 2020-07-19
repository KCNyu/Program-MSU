#include <stdio.h>
int main()
{	
	int M,day,total_days = 0,i,current_day;
 	printf("input month: ");
	scanf("%d",&M);
	printf("input day: ");
	scanf("%d",&current_day);
	
	for(i = 1; i < M; i++)
	{	
		switch(M)
		{
			case 2: day = 28;break;
			case 4: case 6: case 9: case 11:day = 30;break;
		
			case 1: case 3: case 5: case 7: case 8: 
			case 10: case 12: day = 31;break;

			default : day = -1;
		}
		total_days += day;
	}

	printf("you still have %d days.\n",365-(total_days + current_day));
	return 0;
}
