/*================================================================
* Filename:elec_counter.cpp
* Author: KCN_yu
* Createtime:Mon 30 Nov 2020 06:06:50 PM CST
================================================================*/

#include <iostream>
#include <stdlib.h>

using namespace std;

#define MAX 256

class elec_counter
{
private:
    int dim;
    int num;
public:
    elec_counter() { dim = MAX; num = 0; }
    elec_counter(int n) { dim = n; num = 0; }
    void print() { cout << num << endl; }
    void add(int n){
        if(n+num > dim)
            num = 0;
        else
            num += n;
    }
};
int main(int argc, char *argv[])
{
    elec_counter a;
    a.add(5);
    a.print();
    a.add(252);
    a.print();
    return 0;
}
