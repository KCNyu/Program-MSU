#include <cstdlib>
#include <iostream>
using namespace std;

class T {
public:
  int a;
  T() { a = 0; }
};

class sp {
  T *p;
  int *pc;

public:
  sp() {
    p = new T;
    pc = new int(1);
  }

  ~sp() {
    if (*pc > 1)
      (*pc)--;
    else {
      delete p;
      delete pc;
    }
  }

  sp(const sp &x) {
    this->p = x.p;
    (*x.pc)++;
    this->pc = x.pc;
  }

  sp &operator=(const sp &y) {
    if (this == &y)
      return *this;
    (*pc)--;
    if (*pc == 0) {
      delete p;
      delete pc;
    }
    p = y.p;
    pc = y.pc;
    (*pc)++;
    return *this;
  }

  T *operator->() { return p; }
  void print() { cout << *pc << endl; }
};

int main() {
  sp pp1, pp2, pp3(pp2);
  pp1->a = 2;
  pp1.print();
  pp2.print();
  pp3.print();
  cout << "--------------" << endl;
  cout << pp1->a << endl;
  cout << pp2->a << endl;
  cout << pp3->a << endl;

  pp2 = pp1;
  pp1 = pp3;
  pp2 = pp1;
  cout << pp2->a << endl;
  cout << "--------------" << endl;
  pp1.print();
  pp2.print();
  pp3.print();
}
