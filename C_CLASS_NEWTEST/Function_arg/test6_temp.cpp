/*************************************************************************
	> File Name: test6_temp.cpp
	> Author: 
	> Mail: 
	> Created Time: Sun 20 Oct 2019 10:30:49 PM CST
 ************************************************************************/

#include<iostream>
#include<stdarg.h>
using namespace std;
int max(int n, ...) { // 定参 n 表示后面变参数量，定界用，输入时切勿搞错
va_list ap; // 定义一个 va_list 指针来访问参数表
va_start(ap, n); // 初始化 ap，让它指向第一个变参
int maximum = -0x7FFFFFFF; // 这是一个最小的整数
int temp;
for(int i = 0; i < n; i++) {
temp = va_arg(ap, int); // 获取一个 int 型参数，并且 ap 指向下一个参数。这里取的是整数所以是这样，但是如果是比较字符串则使用的char*，这里需要注意的是short char，他们使用时需要转换成int型，这里也可直接写成int
if(maximum < temp) maximum = temp;
}
va_end(ap); // 善后工作，关闭 ap
return maximum ;
}
// 在主函数中测试 max 函数的行为(C++ 格式)
int main() {
cout << max(3, 10, 20, 40) << endl;
cout << max(6, 20, 40, 10, 50, 30, 40) << endl;
}
