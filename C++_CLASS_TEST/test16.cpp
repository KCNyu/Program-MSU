/*================================================================
 * Filename:test16.cpp
 * Author: KCN_yu
 * Createtime:Wed 13 Jan 2021 03:46:32 PM CST
 ================================================================*/

#include <iostream>
#include <stdlib.h>
using namespace std;

char c;
void A();
void B();
void gc(){
    cin >> c;
}
void S(){
    A();
    B();
}
void A(){
    cout << "c = " << c << endl;
    if(c == 'a') gc();
    else if(c == 'c'){
        gc();
        A();
    }
    else throw c;
}
void B(){
    cout << "c = " << c << endl;
    if(c == 'b'){
        gc();
        A();
    }
    else throw c;
}
int main ( ) {
    try {
        gc ();
        S ();
        if (c != '@') throw c;
        cout << "SUCCESS !!!" << endl;
        return 0;
    }
    catch ( char c ) {
        cout << "ERROR on lexeme" << c << endl;
        return 1;
    }
}
