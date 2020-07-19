#include <stdio.h>
int main()
{
	int a,b,c,d,count1,count2;
	printf("input two numbers: \n");
	scanf("%d%d",&a,&b);
	c = a;
	d = b;
	count1 = 0;
	count2 = 0;
	while(a != 0 && b != 0)
	{
		if (a > b)
		a = a - b;
		else
		b = b - a;
		count1 ++;
	}
	
	while (c != 0 && d != 0)
	{		               
		 if (c > d)
		 c = c % d;
		 else
		 d = d % c;						               
		 count2 ++;
	}

	printf("%d\ncount1 = %d\n",a + b,count1);
	printf("%d\ncount2 = %d\n",c + d,count2);
	return 0;
}
