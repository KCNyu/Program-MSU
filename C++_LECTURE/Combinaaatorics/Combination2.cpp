/*************************************************************************
	> File Name: Combination1.cpp
	> Author: 
	> Mail: 
	> Created Time: Fri 15 Nov 2019 03:02:51 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;
#define N 5
bool Brr[N] = {1};
void CombiInit(int M, int K){
    for (int i = 0; i < M; i++)
        Brr[i] = i < K;
}
bool CombiNext(){
    int nC = 0;
    for(int i = 0; i <= N-2; i++){
        if(!Brr[i])continue;
        if(!Brr[i+1]){
            Brr[i+1] = true;
            CombiInit(i+1,nC);
            return true;
        }
        nC++;
    }
    return false;
}
int main()
{
    CombiNext();
    for(int i = 0; i < N; i++){
        cout << Brr[i] << endl;
    }
    return 0;
}
