/*************************************************************************
	> File Name: Fibonacci.cpp
	> Author: 
	> Mail: 
	> Created Time: Mon 04 Nov 2019 11:51:46 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;
int Fibonacci1(int n){
    int F[n];
    F[0] = 1;
    F[1] = 1;
    for(int i = 2; i < n; i++){
        F[i] = F[i-1] + F[i-2];
    }
    return F[n-1];
}
int Fibonacci2(int n){
    if(n == 1 || n == 2){
        return 1;
    }
    else{
        return Fibonacci2(n-1) + Fibonacci2(n-2);
    } 
}
int Gcd(int m, int n){
    if(m%n == 0){
        return n;
    }
    if(n%m == 0){
        return m;
    }
    if(m > n){
        Gcd(m%n,n);
    }
    else{
        Gcd(n,n%m);
    }
}
int main()
{
    int n;
    cin >> n;
    cout << Fibonacci1(n) << endl;
//    int m, n;
//    cin >> m >> n;
//    cout << Gcd(m,n) << endl;
    return 0;
}
