/*================================================================
* Filename:Queen.cpp
* Author: KCN_yu
* Createtime:Tue 25 Feb 2020 04:07:05 PM CST
================================================================*/

#include <iostream>
#include <stdlib.h>
using namespace std;

int Q[10];
int const size = 8;
int sum = 0;
void solve(int n, int i){
    if(i >= size){
        sum++;
        for (int j = 0; j < n; j++)
            cout << "(" << j+1 << "," << Q[j] << ")";
        cout << endl;
        return;
    }
}
