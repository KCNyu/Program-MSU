/*================================================================
* Filename:Array.cpp
* Author: KCN_yu
* Createtime:Thu 16 Apr 2020 01:03:57 PM CST
================================================================*/

#include <iostream>
#include <stdlib.h>
using namespace std;

class Array{
    protected:
        int nDim;
    private:
        int* Arr;
    public:
        Array(int nDim);
        ~Array() { delete[] Arr; }
        void Set(int nX, int N) { Arr[nX] = N; }
        int Get(int nX) { return Arr[nX]; }
    protected:
        void Print(int nBeg, int nEnd);
    public:
        void Print(){ Print(0,nDim-1); }
};
Array::Array(int nDim){
    this->nDim = nDim;
    Arr = new int[nDim];
    for(int i = 0; i < nDim; i++) Set(i,-1);
}
void Array::Print(int nBeg, int nEnd){
    for(int i = nBeg; i < nEnd; i++) cout << Arr[i] << " ";
}
