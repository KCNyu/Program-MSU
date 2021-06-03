#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 10
int Arr[N],nCount;
void Shift(int i,int j)
{
	int tmp = Arr[j],k;
	for(k = j; k >= i+1; k--)
		Arr[k] = Arr[k-1];
	Arr[i] = tmp;
	nCount += j-i+2;
	return;
}
int LinSearch(int Key, int iMax)
{
	int i;
	for(i = 0; i <= iMax; i++)
		if(Arr[i] > Key)
			return i;
	return -1;
}
void SortingDirectInclude()
{
	int i;
	for(i = 1; i < N; i++)
	{
		int J = LinSearch(Arr[i],i-1);
		if(J >= 0)
			Shift(J,i);
	}
	return;
}
void PrintArr()
{
	int i;
	for(i = 0; i < N; i++)
		printf("%d ",Arr[i]);
	printf("\n");
	return;
}
void Sort(int n)
{
    int i,j,tmp;
    for(i = 0; i < n-1; i++)
    {
        for(j = 0; j < n-1-i; j++)
        {
            if(Arr[j] > Arr[j+1])
            {
                tmp = Arr[j];
                Arr[j] = Arr[j+1];
                Arr[j+1] = tmp;
            }
        } 
    }
}
int main()
{
	int i,B[N];
	srand(time(NULL));
	for(i = 0; i < N; i++)
    {
        Arr[i] = rand()%1000;
        B[i] = Arr[i];
    }
	PrintArr();
    nCount = 0;
    Sort(N);
    SortingDirectInclude();
    printf("nCount = %d\n",nCount);

    nCount = 0;
	SortingDirectInclude();
	PrintArr();
	printf("nCount = %d\n",nCount);

    nCount = 0;
    for(i = 0; i < N/5; i++)
        Arr[i] = B[i];
	SortingDirectInclude();
	PrintArr();
	printf("nCount = %d\n",nCount);

    nCount = 0;
    for(i = 4*N/5; i < N; i++)
        Arr[i] = B[i];
	SortingDirectInclude();
	PrintArr();
    A
	printf("nCount = %d\n",nCount);

    return 0;
}



