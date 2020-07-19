#include <stdio.h>
int main()
{
	int a,b,c,d,e,more1,more2,less1,less2,max,min;
	printf("please input five numbers: \n");
	scanf("%d%d%d%d%d",&a,&b,&c,&d,&e);
	
	if (a > b)
	more1 = a, less1 = b;
	else
	more1 = b, less1 = a;
	if (d > e)
	more2 = d, less2 = e;
	else
	more2 = e, less2 = d;

	if (c > more1)
	max = c; 
	else
	max = more1;
	if (more2 > max)
	max = more2;
	printf("max = %d\n",max);
	
	if (c < less1)
	min = c; 
	else
	min = less1;
	if (less2 < min)
	min = less2;
	printf("min = %d\n",min);
	
	printf("max + min = %d\n",max + min);

	return 0;

}
