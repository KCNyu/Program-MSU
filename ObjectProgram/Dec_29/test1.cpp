/*================================================================
 * Filename:test1.cpp
 * Author: KCN_yu
 * Createtime:Tue 29 Dec 2020 04:12:59 PM CST
 ================================================================*/

#include <iostream>
#include <list>

using namespace std;
int g (list <int> & lst){
        int S=0;
        list<int> :: iterator p = lst.begin();
        while (p != lst.end())
        {
            S += * p;
            cout << "*p = " << *p << endl;
            p++;
            if(p != lst.end()) p++;
        }
        return S;
}
void p (list <int> & lst){
        list<int> :: iterator p = lst.begin();
        while (p != lst.end())
        {
            cout << "*p = " << *p << endl;
            p++;
        }
}
void f (const int x, const list <int> & lst){
        list<int> :: const_iterator p = lst.begin();
        while (p != lst.end())
        {
            if(*p == x){
                cout << "YES!\n";
                return;
            }
            p++;
        }
        cout << "NO!\n";
}
void h (list <int> & lst){
    list<int> :: iterator p = lst.begin();
    lst.insert(p,*p);
    while (p != lst.end()){
        p++;
        if(p == lst.end()) break;
        lst.insert(p,*p);
    }
    for(list<int>::reverse_iterator iter = lst.rbegin(); iter != lst.rend();){
        cout << *(iter++) << endl;
    }
}
int main(int argc, char *argv[])
{
    list<int> l = {1,2,3,4,5,6};
    cout << g(l) << endl;
    f(1,l);
    h(l);
    return 0;
}
