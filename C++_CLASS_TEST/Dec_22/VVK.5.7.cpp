/*================================================================
* Filename:VVK.5.7.cpp
* Author: KCN_yu
* Createtime:Wed 23 Dec 2020 01:03:56 AM CST
================================================================*/

#include <iostream>
#include <stdlib.h>
using namespace std;

class Ex {
    int code;
    public:
    Ex(int i) : code(i) {}
    Ex(const Ex& ex) : code(ex.code) {}
    int Get() const { return code; }
};
struct Ex90 : Ex {
    Ex90() : Ex(90) {}
};
void f() {
    throw Ex90();
    cout << "dog" << endl;
}
void t() {
    try { f(); }
    catch(Ex90 &x) {
        cout<< "cat" << endl;
        throw Ex(x.Get() + 1);
        cout << "sheep" << endl;
    }
    catch(Ex &) { cout << "horse" << endl; }
    cout <<"cow" << endl;
}
int main() {
 try { t(); }
 catch(Ex &x) { cout << "elephant " << x.Get() << endl; }
 catch(...) { cout << "wolf" << endl;  }
 return 0;
}

