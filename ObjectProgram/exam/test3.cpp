#include <iostream>
#include <stdlib.h>
using namespace std;
class U {
    public: virtual int f (int y) { cout << "U::f" << endl; return 0; }
            void g () { f (1); cout << "U::g" << endl; }
            virtual void h () { g (); cout << "U::h" << endl; }
};
class S: public U {
    public: int f (double y) { cout << "S::f" << endl; return 2; }
            virtual void g () { f (1); cout << "S::g" << endl; }
            virtual void h () { g(); cout << "S::h" << endl; }
};
int main( ){
    U u; S s; U *p = &s;
    p -> f (1.5);
    p -> g ();
    p -> h ();
}
