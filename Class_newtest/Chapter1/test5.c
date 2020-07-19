#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int Judge_parallelogram(float x1,float y1,float x2,float y2)
{
	if(x1 == x2)
		if(y1 == y2)
			return 1;
	if(x1 == y1)
		if(x2 == y2)
			return 1;
	if(x1 == y2)
		if(y1 == x2)
			return 1;
	return 0;
}
int judge_number(float x,float y)
{
	if(x > 0)
		if(y > 0)
			return 1;
		else
			return 4;
	if(x < 0)
		if(y > 0)
			return 3;
		else 
			return 2;
}
float square(float a,float r)
{
	float square_circle = r*r*3.1415926;
	float square_square = a*a;
	if(square_circle > square_square)
		return square_circle;
	else
		return square_square;
}
int function_M(float x,float y)
{
	if (y == 5*x + 1)
		return 1;
	else 
		return 0;
}
float Equation_root1(float a,float b,float c)
{
	if(b*b-4*a*c >= 0)
		return (-b+sqrt(b*b-4*a*c))/(2*a);
	else
		return 0;
}
float Equation_root2(float a,float b,float c)
{
	if(b*b-4*a*c >= 0)
		return (-b-sqrt(b*b-4*a*c))/(2*a);
	else
		return 0;
}
void Sort_array_increment(double a,double b,double c)
{
	double A[3] = {a, b, c},temp;

	int i,j;
	for(i = 0;i < 2;i++)
		for(j = 0; j < 2 - i; j++)
			if(A[j] > A[j+1])
			{
				temp = A[j];
				A[j] = A[j+1];
				A[j+1] = temp;
			}
	for(i = 0; i < 3; i++)
		printf("%lf ",A[i]);
	printf("\n");
	return;
}
void Sort_array_decrement(double a,double b,double c)
{
	double A[3] = {a, b, c},temp;

	int i,j;
	for(i = 0;i < 2;i++)
		for(j = 0; j < 2 - i; j++)
			if(A[j] < A[j+1])
			{
				temp = A[j];
				A[j] = A[j+1];
				A[j+1] = temp;
			}
	for(i = 0; i < 3; i++)
		printf("%lf ",A[i]);
	printf("\n");
	return;
}
void Equation_solution(float a1,float b1,float c1,float a2,float b2,float c2)
{
	if (a1*b2 - b1*a2 == 0)
		printf("don't have answer\n");
	printf("x = %f\ny = %f\n",(b2*c1-b1*c2)/(a1*b2-b1*a2),(a1*c2-c1*a2)/(a1*b2-b1*a2));
	return;

}
