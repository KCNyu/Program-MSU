/*================================================================
* Filename:main.cpp
* Author: KCN_yu
* Createtime:Tue 05 Jan 2021 02:11:58 AM CST
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
