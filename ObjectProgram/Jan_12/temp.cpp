/*================================================================
* Filename:temp.cpp
* Author: KCN_yu
* Createtime:Sat 16 Jan 2021 04:20:04 PM CST
================================================================*/

#include <iostream>
#include <stdlib.h>
using namespace std;
union data{
    int n;
    char c;
};
char p(data t){
    return t.n;
}
void put(data t, int v){
    cout << "i am int" << endl;
    t.n = v;
    cout << t.c << endl;
    cout << t.n << endl;
}
void put(data t, char v){
    cout << "i am char" << endl;
    t.c = v;
    cout << t.c << endl;
    cout << t.n << endl;
}
int main(int argc, char *argv[])
{
    data t;
    char a = 49;
    cout << (char)97<< endl;
    t.c = 97;
    cout << p(t) << endl;
    put(t,100);
    cout << a << endl;
    char c1 = 'a';
    char c2 = 'b';
    cout << (c1*c2) << endl;

    int f = 1+1;
    cout << f;
    return 0;
}
