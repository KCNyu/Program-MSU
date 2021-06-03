#include <stdio.h>
int main()
{
	int a,b,c,d,e,max,min;
	printf("please input five numbers: \n");
	scanf("%d%d%d%d%d",&a,&b,&c,&d,&e);

	if (a > b)
	max = a,min = b;
	else 
	max = b,min = a;

	if (c > max)
	max = c;
	if (c < min)
	min = c;	
	if (d > max)
	max = d;
	if (d < min)
	min = d;
	if (e > max)
	max = e;
	if (e < min)
	min = e;
	
	printf("max = %d\nmin = %d\nmax + min = %d\n",max,min,max + min);

	return 0;
}
