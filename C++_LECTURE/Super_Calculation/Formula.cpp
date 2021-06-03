/*************************************************************************
	> File Name: Formula.cpp
	> Author:
	> Mail:
	> Created Time: Sat 12 Oct 2019 02:19:37 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;
void Carry(int A[]){
    for(int i = 0; i < 32; i++){
        A[i+1] += (A[i]/256);
        A[i] %= 256;
    }
}
void Init(int A[]){
    A[0] = 1;
    for(int i = 1; i < 33; i++) A[i] = 0;
}
int Compare(int A[], int k){
    Init(A);
    int N_k = 0;
    while(A[32] < 1){
        for(int i = 0; i < 33; i++){
            A[i] *= k;
        }
        Carry(A);
        N_k++;
    }
    return N_k-1;
}
int main()
{
    int A[33];
    //Определите N ^ k из k = 0 и сохраните его в массиве в 256;
    cout << "N3 = " << Compare(A,3) << endl;
    cout << "N5 = " << Compare(A,5) << endl;
    cout << "N7 = " << Compare(A,7) << endl;
    return 0;
}
