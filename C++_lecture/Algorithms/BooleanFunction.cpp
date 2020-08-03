/*================================================================
* Filename:BooleanFunction.cpp
* Author: KCN_yu
* Createtime:Sat 18 Jul 2020 02:17:06 PM CST
================================================================*/

#include <iostream>
#include <stdlib.h>
#include <stdarg.h>
using namespace std;
#define nDIM 256

class BooleanFunction{
    private:
        int dim;
        int* value;
        bool BooleanTable[5];
    public:
        BooleanFunction();
        BooleanFunction(string s){ dim = s.size(); Init(dim); for(int i = 0; i < dim; i++) value[i] = s[i] - '0'; Result(); }
        virtual ~BooleanFunction(){}
        void Init(int len){ dim = len; value = new int[dim]; }
        void JudgeExist();
        int GetCount(int num);
        bool JudgeT0(){ return value[0] == 0; }
        bool JudgeT1(){ return value[dim-1] == 1; }
        bool JudgeS();
        bool JudgeM();
        bool JudgeL();
        void Result();
        void Print(){ Result(); cout << "T0 T1 S  M  L" << endl; for(int i = 0; i < 5; i++) cout << BooleanTable[i] << "  "; cout << endl; }
        void Print_value(){ for(int i = 0; i < dim; i++) cout << value[i] << ' '; cout << endl; }
        bool GetInverse(int i){ return !BooleanTable[i]; }
};
bool BooleanFunction::JudgeS(){
    if(dim == 1) return false;
    for(int i = 0; i < dim/2; i++)
        if(value[i] == value[dim-i-1])
                return false;
    return true;
}
bool BooleanFunction::JudgeM(){
    int mid = dim/2;
    for(int i = mid; i >= 1; i /= 2)
        for(int j = 0; j < dim; j += 2*i)
            for(int k = j; k < i+j; k++)
                if(value[k] > value[k+i])
                    return false;
    return true;
}
int BooleanFunction::GetCount(int num){
    int count = 0;
    while(num > 0){
        if(num%2 == 1) count++;
        num >>= 1;
    }
    return count;
}
bool BooleanFunction::JudgeL(){
    if(dim >= 2){
        int flag0 = value[0];
        int flag1 = value[1];
        for(int i = 2; i < dim; i++){
            int count = GetCount(i);
            if(count%2 == 0 && value[i] != flag0) return false;
            if(count%2 == 1 && value[i] != flag1) return false;
        }
    }
    return true;
}
void BooleanFunction::JudgeExist(){
Deduplication:
    int mid = dim/2;
    int temp[mid];
    for(int i = mid; i >= 1; i /= 2){
        int flag = 0;
        int t = 0;
        for(int j = 0; j < dim; j += 2*i){
            for(int k = j; k < i+j; k++){
                if(value[k] == value[k+i]){
                    temp[t++] = value[k];
                    flag++;
                }
            }
        }
        if(flag == mid){
            dim = mid;
            for(int m = 0; m < dim; m++) value[m] = temp[m];
            goto Deduplication;
        }
    }
}
void BooleanFunction::Result(){
    JudgeExist();
    BooleanTable[0] = JudgeT0();
    BooleanTable[1] = JudgeT1();
    BooleanTable[2] = JudgeS();
    BooleanTable[3] = JudgeM();
    BooleanTable[4] = JudgeL();
}
bool Judge(int count, ...){

    bool Sum[5] = {0};
    va_list ap;
    va_start(ap,count);
    while(count--){
        BooleanFunction temp = va_arg(ap,BooleanFunction);
        for(int i = 0; i < 5; i++) Sum[i] += temp.GetInverse(i);
    }
    va_end(ap);
    for(int i = 0; i < 5; i++) if(!Sum[i]) return false;
    return true;
}

int main(int argc, char *argv[])
{
    BooleanFunction f1("10");
    f1.Print();
    BooleanFunction f2("00101011");
    f2.Print();
    BooleanFunction f3("0111");
    f3.Print();
    cout << Judge(3,f1,f2,f3) << endl;
    return 0;
}
