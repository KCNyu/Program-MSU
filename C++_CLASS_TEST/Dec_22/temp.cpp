/*================================================================
 * Filename:temp.cpp
 * Author: KCN_yu
 * Createtime:Wed 30 Dec 2020 02:27:41 PM CST
 ================================================================*/

#include <iostream>
#include <stdlib.h>
using namespace std;

class Base {
    virtual void f ( ) {}
};
class Derived1: public Base {
};
class Derived2: public Base {
};
int main ( ) {
    /*
    int i;
    Base *p, b_ob;
    Derived1 ob1;
    Derived2 ob2;
    cout << "Тип i - " << typeid ( i ) . name ( ) << endl;
    p = & b_ob;
    cout << "p указывает на объект типа " << typeid ( * p ) . name ( ) << endl;
    p = & ob1;
    cout << "p указывает на объект типа " << typeid ( * p ) . name ( ) << endl;
    p = & ob2;
    cout << "p указывает на объект типа " << typeid ( * p ) . name ( ) << endl;
    if ( typeid (ob1) == typeid (ob2) )
        cout << "Тип объектов ob1 и ob2 одинаков\n";
    else
        cout << "Тип объектов ob1 и ob2 не одинаков\n";
    */
    Base * bp, b_ob;
    Derived1 * dp, d_ob;
    bp = & d_ob;
    dp = dynamic_cast <Derived1 *> (bp);
    if (dp)
        cout << "Приведение типов прошло успешно\n";
    bp = &b_ob;
    dp = dynamic_cast <Derived1 *> (bp);
    if (!dp)
        cout << "Приведения типов не произошло\n";
    return 0;
}
