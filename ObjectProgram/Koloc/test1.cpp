/*================================================================
 * Filename:test1.cpp
 * Author: KCN_yu
 * Createtime:Tue 19 Jan 2021 04:17:40 PM CST
 ================================================================*/

#include <iostream>
#include <stdlib.h>
#include <list>
using namespace std;

class Parser {
    static list<char>
        result; // результат перевода исходной цепочки
    static char c; //текущий символ(лексема)
    static void gc() { cin >> c; }
    // получить следующий символ-лексему
    class S {
        public:
            S() {
                if (c == 'a') {
                    gc();
                    A();
                    if (c == 'b') {
                        gc();
                        B();
                    } else
                        throw c;
                } else
                    throw c;
            }
            ~S() { result.push_front('S'); }
    };
    class A {
        public:
            A() {
                if (c == 'a') {
                    gc();
                    A();
                }
            }
            ~A() { result.push_front('A'); }
    };
    class B {
        public:
            B() {
                if (c == 'b')
                    gc();
                else
                    throw c;
            }
            ~B() { result.push_front('B'); }
    };
    public:
    void analyze() {
        try {
            result.clear();
            gc();
            S();
            if (c != '#')
                throw c;
            cout << "Результат перевода для входной цепочки: ";
            for (list<char>::iterator p=result.begin();p!=result.end();p++) cout<<*p;
            cout << endl;
        }
        catch (char c) {
            cout << "wrong " << c << endl;
        }
    }
}; // end of Parser
char Parser::c;
list<char> Parser::result;
int main(int argc, char *argv[])
{
    Parser p;
    p.analyze();
    return 0;
}
