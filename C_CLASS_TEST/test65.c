#include <stdio.h>
int class_ride(int x)
{
	int i,s = 1;
	for(i = 1; i <= x ; i++ )
	{
		s = s * i;
	}
	return s;

}
int main()
{
	int x;
	printf("input number: ");
	scanf("%d",&x);
	printf("class ride = %d\n",class_ride(x));
	return 0;
}
