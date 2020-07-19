#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 7
void Exchange(int A[], int i, int j)
{
	int tmp;
	tmp = A[i];
  	A[i] = A[j];
	A[j] = tmp;
	return;
}
void Heapify(int tree[], int n, int i)
{
	int c1 = i*2+1;
	int c2 = i*2+2;
	int max = i;
	if(c1 < n && tree[c1] > tree[max])
		max = c1;
	if(c2 < n && tree[c2] > tree[max])
		max = c2;
	if(max != i)
	{
		Exchange(tree,max,i);	
		Heapify(tree,n,max);
	}
	return;
}
void Build_heap(int tree[],int n)
{
	int last_node = n - 1;
	int parent = (last_node - 1) / 2;
	int i;
	for(i = parent; i >= 0; i--)
		Heapify(tree,n,i);
	return;
}
void Heapsort(int tree[],int n)
{
	Build_heap(tree,n);
	int i;
	for( i = n - 1; i >= 0; i--)
	{
		Exchange(tree,i,0);
		Heapify(tree,i,0);
	}
	return;
}	
int main()
{
	int tree[N],i;
	srand(time(NULL));
	for(i = 0; i < N; i++)
		tree[i] = rand()%20;
	for(i = 0; i < N; i++)
		printf("%d ",tree[i]);
	printf("\n");
	Heapify(tree,N,0);
	for(i = 0; i < N; i++)
		printf("%d ",tree[i]);
	printf("\n");
	Build_heap(tree,N);
	for(i = 0; i < N; i++)
		printf("%d ",tree[i]);
	printf("\n");
	Heapsort(tree,N);
	for(i = 0; i < N; i++)
		printf("%d ",tree[i]);
	printf("\n");
	return 0;
}
