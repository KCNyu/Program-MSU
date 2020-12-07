/*================================================================
* Filename:test3.cpp
* Author: KCN_yu
* Createtime:Sun 29 Nov 2020 05:47:08 PM CST
================================================================*/

#include <iostream>
#include <stdlib.h>
#include <cstring>
using namespace std;

class mystring{
private:
    char *p;
    int size;
public:
    mystring(const char* str);
    mystring(const mystring &a);
    ~mystring(){ delete []p; }
    mystring& operator=(const mystring &a);
    void print(){ cout << p << endl; }
};
mystring::mystring(const char* str){
    p = new char[(size = strlen(str))+1];
    strcpy(p,str);
}
mystring::mystring(const mystring &a){
    p = new char[(size = a.size)+1];
    strcpy(p,a.p);
}
mystring& mystring::operator=(const mystring &a){
    if(this == &a) return *this;
    delete []p;
    p = new char[(size = a.size)+1];
    strcpy(p,a.p);
    return *this;
}
int main(int argc, char *argv[])
{
    mystring a("hello world");
    a.print();
    mystring b = a;
    b.print();
    mystring c(a);
    c.print();
    return 0;
}
