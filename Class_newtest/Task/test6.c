/*************************************************************************
	> File Name: test6.c
	> Author: 
	> Mail: 
	> Created Time: Thu 07 Nov 2019 02:20:07 PM CST
 ************************************************************************/

#include<stdio.h>
int Search(int *A, int n, int x){
    int left = 0,right = n-1;
    while(left <= right)
    {
        int mid = (left+right)/2;
        if(x == A[mid] && (x != A[mid-1] || mid == 0)){
            return mid;
        }
        if(x > A[mid])
            left = mid+1;
        else
            right = mid-1;
    }
    return -1;
}
int main()
{
    int n,i;
    printf("input n:");
    scanf("%d",&n);
    
    int A[n];
    for(i = 0; i < n; i++)
        scanf("%d",&A[i]);
    
    int x;
    printf("input x:");
    scanf("%d",&x);
    
    printf("%d\n",Search(A,n,x));
    return 0;
}
