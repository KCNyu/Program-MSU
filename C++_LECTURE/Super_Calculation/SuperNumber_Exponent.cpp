/*================================================================
* Filename:SuperNumber_Exponent.cpp
* Author: KCN_yu
* Createtime:Sun 22 Mar 2020 11:53:36 AM CST
================================================================*/

#include <iostream>
#include <stdlib.h>
#include <string.h>

#define Maxlen 10000

using namespace std;

class Supernumber{
    private:
        int num[Maxlen];
        int len;
    public:
        Supernumber() {}
        Supernumber(const char* s){ Init(s); }
        Supernumber operator*(const Supernumber& N);
        void Init(const char* s){
            len = strlen(s);
            for(int i = 0; i < strlen(s); i++) num[len-i-1] = s[i] - '0';
        }
        void Print() { int i = 0; while(i < len) cout << num[len-++i]; cout << endl; };
};
Supernumber Supernumber::operator*(const Supernumber& N){
    Supernumber result;
    result.len = len + N.len;
    for(int i = 0; i < result.len; i++) result.num[i] = 0;
    for(int i = 0; i < len; i++)
        for(int j = 0; j < N.len; j++){
            result.num[i+j] = num[i] * N.num[j] + result.num[i+j];
            result.num[i+j+1] = result.num[i+j]/10 + result.num[i+j+1];
            result.num[i+j] = result.num[i+j]%10;
        }
    if(result.num[result.len-1] == 0) result.len--;
    return result;
}
Supernumber Exponent(const Supernumber& N, int X){
    Supernumber result;
    if(X == 0){
        const char* temp = "1";
        result.Init(temp);
        return result;
    }
    if(X == 1) return N;
    result = Exponent(N,X >> 1);
    result = result * result;
    if((X & 0x01) == 1) result = result * N;
    return result;
}
int main(int argc, char *argv[])
{

    const char* s1 = "2426178628472168727198739182214";
    Supernumber N1(s1);

    Supernumber N2 = Exponent(N1,10); N2.Print();

    return 0;
}
