/*************************************************************************
	> File Name: Basic_sort.cpp
	> Author: <F5>
	> Mail: 
	> Created Time: Fri 11 Oct 2019 11:59:06 PM CST
 ************************************************************************/

#include<iostream>
#define N 10
using namespace std;
void InputArray(int A[]){
    for(int i = 0; i < N; i++){
        A[i] = rand()%100;
    }
}
void PrintArray(int A[]){
    for(int i = 0; i < N; i++){
        cout << A[i] << " ";
    }
    cout << "\n";
}
void Bubble_sort(int A[]){
    for(int i = 0;  i < N-1; i++){
        for(int j = 0;  j < N-i-1; j++){
            if(A[j] > A[j+1]){
                int tmp = A[j];
                A[j] = A[j+1];
                A[j+1] = tmp;
            }
        }
    }
}
int main(){
    int A[N];
    srand(time(NULL));
    InputArray(A);
    PrintArray(A);
    Bubble_sort(A);
    PrintArray(A);
}

