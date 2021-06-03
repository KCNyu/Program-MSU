/*************************************************************************
	> File Name: test4.c
	> Author: 
	> Mail: 
	> Created Time: Sat 19 Oct 2019 10:28:52 AM CST
 ************************************************************************/

#include<stdio.h>
int IsSort(int *a, int *end){
    return a < end ? (*a <= *(a+1)) && IsSort(a+1,end) : 1;
}
int Judge(int *Arr,int i){    
    if(*(Arr+i) > *(Arr+i-1)){
        return Judge(Arr,i-1);
    }
    if(i == 0){
        return 1;
    }
    return -1;
}
int main()
{
    int A[5] = {1,2,3,4,5};
    printf("%d\n",IsSort(A,A+4));
    return 0;
}
