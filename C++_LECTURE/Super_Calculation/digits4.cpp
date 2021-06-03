/*************************************************************************
	> File Name: digits1.cpp
	> Author: 
	> Mail: 
	> Created Time: Thu 17 Oct 2019 03:23:28 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;
int main()
{
    int a,b,c,d,a1,b1,c1,d1,count = 0;
    for(a = 0; a <= 9; a++){
        for(b = -9; b <= 9; b++){
            for(c = -9; c <= 9; c++){
                for(d = -9; d <= 9; d++){
                    if(a == b+c+d){
                        a1 = abs(a);
                        b1 = abs(b);
                        c1 = abs(c);
                        d1 = abs(d);
                        cout << a1 << b1 << c1 << d1 << endl;
                        count++;
                    }       
                }
            }
        }
    }
    cout << "count = "<< count << endl;
}
