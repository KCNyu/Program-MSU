/*================================================================
* Filename:main.cpp
* Author: KCN_yu
* Createtime:Sun 10 Oct 2021 05:07:10 PM CST
================================================================*/

#include <iostream>
#include "color.h"
using namespace std;

int main()
{
	setColor(F_PURPLE);
	cout << "русский язык" << endl;
	setColor(F_RED);
	cout << "中文" << endl;
}
