#include <stdio.h>
int main()
{
	float x1,x2,y1,y2,k,b;
	printf("Input x1: \n");
	scanf("%f",&x1);
	printf("Input y1: \n");
	scanf("%f",&y1);
	printf("Input x2: \n");
	scanf("%f",&x2);
	printf("Input y2: \n");
	scanf("%f",&y2);

	k = (y2 - y1)/(x2 - x1);
	b = (y2 -x2 * (y2 - y1)/(x2 - x1));
	printf("the function is :y = %fx+%f\n",k,b);
	
	return 0;
}

