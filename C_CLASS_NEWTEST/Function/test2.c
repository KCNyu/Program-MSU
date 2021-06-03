#include <stdio.h>
void PrintPrime(int n){
    int i,j,A[n],P[n];
	for(i = 0; i < n; i++)
		A[i] = 1;
	for(i = 2; i < n; i++)
		for(j = 2*i; j < n; j += i)
			A[j] = 0;
    int k = 0;
    for(i = 2; i < n; i++){
        if(A[i]){
            P[k] = i;
            k++;
        }
    }
    for(i = 0; i < k; i++){
        if((P[i]+2) == P[i+1]){
            printf("%d %d\n",P[i],P[i+1]);
        }
    }
}
int main()
{
	int n,i,j;
	scanf("%d",&n);
    PrintPrime(n);
	return 0;
}

