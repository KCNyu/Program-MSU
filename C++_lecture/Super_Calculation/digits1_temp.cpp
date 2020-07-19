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
    int a,b,c,d,e,f,count = 0;
    for(a = 0; a <= 9; a++){
        for(b = 0; b <= 9; b++){
            for(c = 0; c <= 9; c++){
                for(d = 0; d <= 9; d++){
                    for(e = 0; e <= 9; e++){
                        for(f = 0; f <= 9; f++){
                            if(a == b+c+d+e+f){
                                cout << a << b << c << d << e << f << endl;
                                count++;
                                continue;
                            }
                            if(b == a+c+d+e+f){
                                count++;
                                cout << a << b << c << d << e << f << endl;
                                continue;
                            }
                            if(c == b+a+d+e+f){
                                count++;
                                cout << a << b << c << d << e << f << endl;
                                continue;
                            }
                            if(d == b+c+a+e+f){
                                count++;
                                cout << a << b << c << d << e << f << endl;
                                continue;
                            }
                            if(e == b+c+d+a+f){
                                count++;
                                cout << a << b << c << d << e << f << endl;
                                continue;
                            }
                            if(f == b+c+d+e+a){
                                count++;
                                cout << a << b << c << d << e << f << endl;
                                continue;
                            }
                            if(a+b == c+d+e+f){
                                count++;
                                cout << a << b << c << d << e << f << endl;
                                continue;
                            }
                            if(a+c == b+d+e+f){
                                count++;
                                cout << a << b << c << d << e << f << endl;
                                continue;
                            }
                            if(a+d == b+c+e+f){
                                count++;
                                cout << a << b << c << d << e << f << endl;
                                continue;
                            }
                            if(a+e == b+c+d+f){
                                count++;
                                cout << a << b << c << d << e << f << endl;
                                continue;
                            }
                            if(a+f == b+c+d+e){
                                count++;
                                cout << a << b << c << d << e << f << endl;
                                continue;
                            }
                            if(b+c == a+d+e+f){
                                count++;
                                cout << a << b << c << d << e << f << endl;
                                continue;
                            }
                            if(b+d == a+c+e+f){
                                count++;
                                cout << a << b << c << d << e << f << endl;
                                continue;
                            }
                            if(b+e == a+c+d+f){
                                count++;
                                cout << a << b << c << d << e << f << endl;
                                continue;
                            }
                            if(b+f == a+c+d+e){
                                count++;
                                cout << a << b << c << d << e << f << endl;
                                continue;
                            }
                            if(c+d == b+a+e+f){
                                count++;
                                cout << a << b << c << d << e << f << endl;
                                continue;
                            }
                            if(c+e == b+a+d+f){
                                count++;
                                cout << a << b << c << d << e << f << endl;
                                continue;
                            }
                            if(c+f == b+a+d+e){
                                count++;
                                cout << a << b << c << d << e << f << endl;
                                continue;
                            }
                            if(d+e == b+c+a+f){
                                count++;
                                cout << a << b << c << d << e << f << endl;
                                continue;
                            }
                            if(d+f == b+c+a+e){
                                count++;
                                cout << a << b << c << d << e << f << endl;
                                continue;
                            }
                            if(e+f == b+c+d+a){
                                count++;
                                cout << a << b << c << d << e << f << endl;
                                continue;
                            }
                            if(a+b+c == d+e+f){
                                count++;
                                cout << a << b << c << d << e << f << endl;
                                continue;
                            }
                            if(a+b+d == c+e+f){
                                count++;
                                cout << a << b << c << d << e << f << endl;
                                continue;
                            }
                            if(a+b+e == c+e+f){
                                count++;
                                cout << a << b << c << d << e << f << endl;
                                continue;
                            }
                            if(a+b+f == c+d+e){
                                count++;
                                cout << a << b << c << d << e << f << endl;
                                continue;
                            }
                            if(a+c+d == b+e+f){
                                count++;
                                cout << a << b << c << d << e << f << endl;
                                continue;
                            }
                            if(a+c+e == b+d+f){
                                count++;
                                cout << a << b << c << d << e << f << endl;
                                continue;
                            }
                            if(a+c+f == b+d+e){
                                count++;
                                cout << a << b << c << d << e << f << endl;
                                continue;
                            }
                            if(a+d+e == b+c+f){
                                count++;
                                cout << a << b << c << d << e << f << endl;
                                continue;
                            }
                            if(a+d+f == b+c+e){
                                count++;
                                cout << a << b << c << d << e << f << endl;
                                continue;
                            }
                            if(a+e+f == b+c+d){
                                count++;
                                cout << a << b << c << d << e << f << endl;
                                continue;
                            }
                            if(b+c+d == a+e+f){
                                count++;
                                cout << a << b << c << d << e << f << endl;
                                continue;
                            }
                            if(b+c+e == a+d+f){
                                count++;
                                cout << a << b << c << d << e << f << endl;
                                continue;
                            }
                            if(b+c+f == a+d+e){
                                count++;
                                cout << a << b << c << d << e << f << endl;
                                continue;
                            }
                            if(b+d+e == c+a+f){
                                count++;
                                cout << a << b << c << d << e << f << endl;
                                continue;
                            }
                            if(b+d+f == a+c+e){
                                count++;
                                cout << a << b << c << d << e << f << endl;
                                continue;
                            }
                            if(b+e+f == a+c+d){
                                count++;
                                cout << a << b << c << d << e << f << endl;
                                continue;
                            }
                            if(c+d+e == b+a+f){
                                count++;
                                cout << a << b << c << d << e << f << endl;
                                continue;
                            }
                            if(c+d+f == a+b+e){
                                count++;
                                cout << a << b << c << d << e << f << endl;
                                continue;
                            }
                            if(c+e+f == b+d+a){
                                count++;
                                cout << a << b << c << d << e << f << endl;
                                continue;
                            }
                            if(d+e+f == b+c+a){
                                count++;
                                cout << a << b << c << d << e << f << endl;
                                continue;
                            }
                        }
                    }
                }
            }
        }
    }
    cout << "count = "<< count << endl;
    return 0;
}
