/*************************************************************************
	> File Name: Permutation.cpp
	> Author: 
	> Mail: 
	> Created Time: Wed 16 Oct 2019 12:19:08 AM CST
 ************************************************************************/

#include<iostream>
#define N 3
int Arr[N];
bool bRight[N];
using namespace std;
void PermuInit(){
    for(int i = 0; i < N; i++)
        Arr[i] = i;
    for(int i = 0; i < N; i++)
        bRight[i] = true;
}
int Where(int nMin){
    for(int i = 0; i < N; i++)
        if(Arr[i] == nMin)
            return i;
    return -1;
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
bool PermuNext(int nBeg, int nMin){
    if(nMin >= N-1)
        return false;
    int nEnd = nBeg + N - nMin - 1;
    int nWhere = Where(nMin);
    if(bRight[nMin]){
        if(nWhere+1 <= nEnd){
            Swap(&Arr[nWhere],&Arr[nWhere+1]);
            return true;
        }
        bRight[nMin] = false;
        return PermuNext(nBeg,nMin+1);
    }
    else{
        if(nWhere-1 >= nBeg){
            Swap(&Arr[nWhere],&Arr[nWhere-1]);
            return true;
        }
        bRight[nMin] = true;
        return PermuNext(nBeg+1,nMin+1);
    }
}
void Permu(){
    PermuInit();
    while(1){
        PrintArr();
        if(!PermuNext(0,0))
            break;
    }
}
int main()
{
    Permu();
    return 0;
}
