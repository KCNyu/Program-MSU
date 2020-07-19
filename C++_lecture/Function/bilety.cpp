/*================================================================
* Filename:bilety.cpp
* Author: KCN_yu
* Createtime:Mon 23 Mar 2020 01:42:16 PM CST
================================================================*/

#include <iostream>
#include <stdlib.h>
using namespace std;

class Bilety{
    private:
        int Max;
        int Arr[100];
    public:
        Bilety() {}
        void Init0() { for(int i = 0; i < Max; i++) Arr[i] = 0; }
        void Init() { Max = 10; for(int i = 0; i < Max; i++) Arr[i] = 1; }
        void Print(){ for(int i = 0; i < Max; i++) cout << i << " : " << Arr[i] << endl; }
        Bilety operator*(const Bilety& B);
};
Bilety Bilety::operator*(const Bilety& B){
    Bilety BBB;
    BBB.Max = Max+B.Max-1;
    BBB.Init0();
    for(int i = 0; i < Max; i++)
        for(int j = 0; j < B.Max; j++)
            BBB.Arr[i+j] += Arr[i]*B.Arr[j];
    return BBB;
}
Bilety My_pow(Bilety& B, int X){
    Bilety result;
    if(X == 0){
        result.Init0();
        return result;
    }
    if(X == 1) return B;
    result = My_pow(B, X >> 1);
    result = result * result; // result^2;
    if((X & 0x01) == 1)
        result = result * B;
    return result;
}
int main(int argc, char *argv[])
{
    Bilety BBB1;BBB1.Init();//BBB1.Print();
    Bilety BBB2;BBB2.Init();//BBB2.Print();

    Bilety BBB3 = My_pow(BBB1,10);
    BBB3.Print();
    return 0;
}
