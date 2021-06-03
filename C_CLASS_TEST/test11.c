#include <stdio.h>
int main()
{
	int a,b,c,d,e,max,min;
	printf("please input five numbers: \n");
	scanf("%d%d%d%d%d",&a,&b,&c,&d,&e);

	max = (a > b) ? a : b;
	min = (a < b) ? a : b;

	max = (c > max) ? c : max;
	min = (c < min) ? c : min;

	max = (d > max) ? d : max;
	min = (d < min) ? d : min;	
	
	max = (e > max) ? e : max;
	min = (e < min) ? e : min;

	printf("max = %d\nmin = %d\nmax + min = %d\n",max,min,max + min);
	return 0;
}
