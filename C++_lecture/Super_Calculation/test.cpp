/*************************************************************************
	> File Name: test.cpp
	> Author: 
	> Mail: 
	> Created Time: Sat 12 Oct 2019 01:53:43 PM CST
 ************************************************************************/

#include<iostream>
#define MAXN 10001
using namespace std;
void modRes(int res[], int n) {//从低位开始向高位进位
    for(int i=0;i<n-1;++i) {
        res[i+1] += (res[i]/10);
        res[i] %=10;
    }
}
int main()
{
    int a,b,i;
    int res[MAXN]={0};//存放结果的数组，可以看成一个大数
    cout<<"input a and b:";
    cin>>a>>b;
    res[0]=a;
    for(i=1;i<b;++i) {
        for(int j=0;j<MAXN-1;++j) {
            res[j] *= a;//大数的每一位乘以a
        }
        modRes(res, MAXN);//进位
    }
 
    for(i=MAXN-1;i>=0;--i) {//高位多余的0不需要输出
        if(res[i] != 0) break;
    }
    cout << i << "\n";
    cout<<a<<"^"<<b<<"=";
    for(;i>=0;--i) {//从第一个不是0的高位开始输出
        cout<<res[i];
    }
    cout<<endl;
 
    return 0;
}
