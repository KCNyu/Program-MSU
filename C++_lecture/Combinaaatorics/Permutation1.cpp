/*************************************************************************
	> File Name: Permutation.cpp
	> Author: 
	> Mail: 
	> Created Time: Wed 16 Oct 2019 12:19:08 AM CST
 ************************************************************************/

#include<iostream>
#define N 10
int Arr[N];
using namespace std;
void PermuInit(){
    for(int i = 0; i < N; i++)
        Arr[i] = i;
}
void PrintArr(){
    for(int i = 0; i < N; i++)
        cout << Arr[i] << ' ';
    cout << endl;
}
void Swap(int *px, int *py){
    int temp;
    temp = *px;
    *px = *py;
    *py = temp;
}
void PermuPrint(int M){
    if (M <= 1)
        PrintArr();
    else{
        for(int i = M-1; i >= 0; i--){
            Swap(&Arr[i],&Arr[M-1]);
            PermuPrint(M-1);
            Swap(&Arr[i],&Arr[M-1]);
        }
    }
}
int main()
{
    PermuInit();
    int n;
    cin >> n;
    PermuPrint(n);
    return 0;
}
