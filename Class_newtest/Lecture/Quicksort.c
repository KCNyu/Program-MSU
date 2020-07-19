#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 10
void Exchange(int i, int j,int A[])
{
	int Tmp = A[i];
	A[i] = A[j];
	A[j] = Tmp;
	return;
}

int ForPlaceL(int nL,int nR,int A[])
{
	for(int i = nR; i > nL; i--)
	{
		if(A[i] >= A[nL])
			continue;
		Exchange(nL,i,A);
		return i;
	}
	return nL;
}

int ForPlaceR(int nL,int nR,int A[])
{
	for(int i = nL; i < nR; i++)
	{
		if(A[i] <= A[nR])
			continue;
		Exchange(i,nR,A);
		return i;
	}
	return nR;
}

int ForPlace(int nL, int nR, int A[])
{
	while(1)
	{
		nR = ForPlaceL(nL,nR,A);
		if(nR == nL)
			return nR;
		nL = ForPlaceR(nL,nR,A);
		if(nL == nR)
			return nL;
	}
}

void QuickSort (int nL, int nR, int A[])
{
	if(nL > nR)
		return;
	int n = ForPlace(nL,nR,A);
	QuickSort(nL,n-1,A);
	QuickSort(n+1,nR,A);
}
void QuickSortMain(int A[])
{
	QuickSort(0,N-1,A);
}
void Printarray(int A[],int n)
{
	for(int i = 0; i < n; i++)
		printf("%d ",A[i]);
	printf("\n");
	return;
}
int main()
{
	int A[N];
	srand(time(NULL));
	for(int i = 0; i < N; i++)
        scanf("%d",&A[i]);
    Printarray(A,N);
	QuickSortMain(A);
	Printarray(A,N);
	return 0;
}


