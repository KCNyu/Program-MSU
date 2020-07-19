/*************************************************************************
	> File Name: Quicksort_temp.c
	> Author: 
	> Mail: 
	> Created Time: Thu 28 Nov 2019 02:17:17 PM CST
 ************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
void quick_sort(int s[], int l, int r)
{
    if (l < r)
    {
        //Swap(s[l], s[(l + r) / 2]); //将中间的这个数和第一个数交换 参见注1
        int i = l, j = r, x = s[l];
        while (i < j)
        {
            while(i < j && s[j] >= x) // 从右向左找第一个小于x的数
                j--;  
            if(i < j) 
                s[i++] = s[j];
            
            while(i < j && s[i] < x) // 从左向右找第一个大于等于x的数
                i++;  
            if(i < j) 
                s[j--] = s[i];
        }
        s[i] = x;
        quick_sort(s, l, i - 1); // 递归调用 
        quick_sort(s, i + 1, r);
    }
}
int main()
{
    srand(time(NULL));
    int A[10];
    for(int i = 0; i < 10; i++)
        A[i] = rand()%10;
    for(int i = 0; i < 10; i++)
        printf("%d ",A[i]);
    printf("\n");
    quick_sort(A,0,9);
    for(int i = 0; i < 10; i++)
        printf("%d ",A[i]);
    printf("\n");
    return 0;
}

