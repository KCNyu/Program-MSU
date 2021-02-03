/*================================================================
* Filename:test3.cpp
* Author: KCN_yu
* Createtime:Wed 20 Jan 2021 04:07:06 PM CST
================================================================*/

#include <iostream>
#include <stdlib.h>
using namespace std;

class A{
    public:
        A() { cout << "A()"; }
        A(const A& s) { cout << "A(const A&)";}
        ~A(){ cout << "~A()"; }

};
int main(int argc, char *argv[])
{
    try{throw  *new A ;}
    catch(A a){ A b; }
    catch(int){ cout << "~A()"; }
    catch(...){ cout << "A() ~A() ~A() ~A()";}
    return 0;
}
