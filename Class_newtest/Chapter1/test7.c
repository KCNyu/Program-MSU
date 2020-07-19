#include <stdio.h>
double Harmonic_series(int n)
{
	double i,sum = 0;
	for(i = 1; i <= n; i++)
		sum += 1/i;
	return sum;
}
int compare(double a)
{
	int n = 1;
	while(Harmonic_series(n) < a)
	{	
		n++;
	}
	return n;
}
int Fibonacci(int n)
{
	if(n == 1 || n == 2)
		return 1;
	else
		return Fibonacci(n-2)+Fibonacci(n-1);
}
/*int main()
{
	double a;
	scanf("%lf",&a);
	printf("when n = %d Harmoinc series bigger than %lf\nHarmoinc series = %lf\n",compare(a),a,Harmonic_series(compare(a)));
	return 0;
}*/
int main()
{
	int i,n;
	scanf("%d",&n);
	for(i = 1; i <= n; i++)
	{
		printf("%d ",Fibonacci(i));
	}
	printf("\n");
}
