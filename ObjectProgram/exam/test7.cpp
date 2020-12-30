
#include <iostream>
using namespace std;
class A {
    public: A () { cout << 1 << endl; }
};
class B: public A {
    public: B (int n) { try { if (n == 0) throw *this;
                if (n > 11) throw 11; }
            catch (int) { cout << 2 << endl; }
            catch (B&) { cout << 3 << endl; throw; }
            cout << 4 << endl; }
            B (B&) {cout << 5 << endl;}
            ~B () {cout << 6 << endl;}
};
int main() { try { B b(0); B c (3); }
    catch (...) { cout << 7 << endl; }
    cout << 8 << endl;
}
