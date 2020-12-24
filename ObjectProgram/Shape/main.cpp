/*================================================================
* Filename:main.cpp
* Author: KCN_yu
* Createtime:Wed 23 Dec 2020 11:01:37 PM CST
================================================================*/

#include <iostream>
#include <cmath>
#include "Shape.h"

using namespace std;

int main(int argc, char *argv[])
{
    Rectangle r1(1,2);

    Rhombus r2(3,M_PI/6);

    Square s(5);

    Circle c(3);

    Triangle t(3,4,5);

    Shape * arr[] = { (Shape*)&r1, (Shape*)&r2, (Shape*)&s, (Shape*)&c, (Shape*)&t };
    Shapes(arr,sizeof(arr)/sizeof(Shape*));

    cout << "Shape::count: " << Shape::count << endl;
    return 0;
}
