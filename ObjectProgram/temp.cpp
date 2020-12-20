/*================================================================
* Filename:temp.cpp
* Author: KCN_yu
* Createtime:Fri 18 Dec 2020 06:50:02 PM CST
================================================================*/

#include <iostream>
#include <stdlib.h>
using namespace std;

class A { public:
A () {cout << "Constructor of A\n";}
~A () {cout << "Destructor of A\n";}
};
class Error {};
class Error_of_A : public Error {};
void f () {
    A a;
    throw 1;
    cout << "This message is never printed" << endl;
}
int main () {
try {
    f ();
    throw Error_of_A();
}
catch (int) { cerr << "Catch of int\n"; }
catch (Error_of_A) { cerr << "Catch of Error_of_A \n"; }
catch (Error) { cerr << "Catch of Error\n"; }
return 0;
}
