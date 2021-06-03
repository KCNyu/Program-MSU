#include <iostream>
#include "shape.h"
#define pi 3.1415926535
using namespace std;
int shape::n = 0;
circle::circle (double x)
{
	r=x;
	n++;
}
double circle::area ()
{
	return pi*r*r/2;
}
circle::~circle ()
{
	n--;
}
triangle::triangle (double x,double y)
{
	a=x;
	h=y;
	n++;
}
double triangle::area ()
{
	return a*h/2;
}
triangle::~triangle ()
{
	n--;
}
rhombus::rhombus (double x,double y)
{
	a=x;
	h=y;
	n++;
}
void rhombus::get(){
    cout << a << endl;
    cout << h << endl;
}
double rhombus::area ()
{
	return a*h;
}
rhombus::~rhombus ()
{
	n--;
}
square::square(double x):rhombus(x,x){}
int main()
{
	square s(2);
    s.get();
	cout << s.area() << endl;
	return 0;
}
