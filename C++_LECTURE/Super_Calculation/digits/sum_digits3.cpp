/*================================================================
* Filename:sum_digits3.cpp
* Author: KCN_yu
* Createtime:Mon 02 Mar 2020 05:43:30 PM CST
================================================================*/

#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

int main()
{
    clock_t begintime = clock();
    int count = 0;
    int sum = 0;
    for(int i = 0; i <= 27/2; i++){
        for(int a = 0; a <= 9; a++){
            for(int b = 0; b <= 9; b++){
                    int ab = a+b;
                for(int c = 0; c <= 9; c++){
                    int abc = a+b+c;
                    if(i == abc) count++;
                }
            }
        }
        sum += count*count;
        count = 0;
    }
    sum *= 2;
    clock_t endtime = clock();
    cout << "sum = " << sum << endl;
    cout << "time: " << endtime-begintime << endl;
    return 0;
}
