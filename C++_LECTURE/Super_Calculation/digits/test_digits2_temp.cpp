/*================================================================
* Filename:test_digits2.cpp
* Author: KCN_yu
* Createtime:Mon 02 Mar 2020 05:43:30 PM CST
================================================================*/

#include <iostream>
#include <stdlib.h>
using namespace std;

int main()
{
    int count = 0;
    int sum = 0;
    for(int i = 0; i <= 18; i++){
        for(int c = 0; c <= 9; c++){
            for(int d = 0; d <= 9; d++){
                if( i == c+d) count++;
            }
        }
        cout << "count = " << count << endl;
        sum += count;
        count = 0;
    }
    cout << "sum = " << sum << endl;
    return 0;
}
