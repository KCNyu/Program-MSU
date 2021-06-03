#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define nDim 50
int Arr(nDim)

void RndArr()
{
	for(int i = 0; i < nDim; i++)
		Arr[i] = rand()%1000;
}

void PrintArr()
{
	for(int i = 0; i < nDim; i++)
		printf("%d ",Arr[i]);
}

void Exchange(int i, int j)
{
	int Tmp = Arr[i];
	Arr[i] = Arr[j];
	Arr[j] = Tmp;
}

bool Ordering (int i,int j)
{
	if (Arr[i] <= Arr[j])
		Exchange(i,j);
	return ture;
}
void Shift(int i, int j)
{
	int Tmp = Arr[j];
	if (j > i)
		for (int k = j; )
