/*================================================================
* Filename:temp.cpp
* Author: KCN_yu
* Createtime:Tue 06 Apr 2021 06:22:56 PM CST
================================================================*/

#include <iostream>
using namespace std;

int SumDel(int N, int i){
    if(N <= i) return N;
    if(N%i == 0) return i+SumDel(N/i,i);
    else return SumDel(N,i+1);
}
int S(int N){
    return SumDel(N,2);
}
int main(int argc, char *argv[])
{
    cout << S(1164724681) << endl;
    return 0;
}
