/*************************************************************************
	> File Name: Combination.cpp
	> Author: 
	> Mail: 
	> Created Time: Wed 16 Oct 2019 01:05:05 AM CST
 ************************************************************************/

#include<iostream>
#define N 10
using namespace std;
bool Brr[N];
void InputBrr(){
    for(int i = 0; i < N; i++)
        Brr[i] = true;
}
void PrintBrr(){
    for(int i = 0; i < N; i++)
        cout << Brr[i] << " ";
    cout << endl;
}
void CombiPrint(int M, int K){
    if(M <= 0){
        PrintBrr();
        return;
    }
    if(K > 0){
        Brr[M-1] = true;
        CombiPrint(M-1,K-1);
    }
    if(K < M){
        Brr[M-1] = false;
        CombiPrint(M-1,K);
    }
}
int main()
{
    InputBrr();
    int n;
    cin >> n;
    CombiPrint(N,n);
    return 0;
}
