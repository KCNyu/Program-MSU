#include <stdio.h>
int judge_array(int a[], int n)
{
	int i,j;
	for (i = 0; i < n; i++)
	{
		for (j = i+1; j < n; j++)
		{
			if (a[i] == a[j])
				return 1;
		}
	}
	return 0;
}
int main()
{
	int a[5] = {1,2,3,5,4};
	if (judge_array(a,5))
		printf("right\n");
	else
		printf("wrong\n");
	return 0;
}
