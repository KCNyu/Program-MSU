/*************************************************************************
	> File Name: test12.c
	> Author: 
	> Mail: 
	> Created Time: Mon 07 Oct 2019 05:30:27 PM CST
 ************************************************************************/

#include<stdio.h>
int main()
{
    int i,n,A[100],k = 0;
    scanf("%d",&n);
    while(n != 1)
    {
        for(i = 2; i <= n; i++)
        {
            if(n%i == 0)
            {
                A[k] = i;
                k++;
                n /= i;
                break;
            }
        }
    }
    for(i = 0; i < k; i++)
        printf("%d ",A[i]);
    printf("\n");
    return 0;
}
