/*================================================================
* Filename:test_digits3.cpp
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
    for(int i = 0; i <= 27; i++){
        for(int a = 0; a <= 9; a++){
            for(int b = 0; b <= 9; b++){
                    int ab = a+b;
                for(int c = 0; c <= 9; c++){
                    int abc = a+b+c;
                    if(i == abc) count++;
                }
            }
        }
        cout << "count_" << i << " = " << count << endl;
        sum += count*count;
        count = 0;
    }
    cout << "sum = " << sum << endl;
    return 0;
}
