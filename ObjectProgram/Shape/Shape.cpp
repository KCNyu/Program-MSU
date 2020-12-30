/*================================================================
* Filename:Shape.cpp
* Author: KCN_yu
* Createtime:Wed 23 Dec 2020 06:57:33 PM CST
================================================================*/

#include <iostream>
#include <stdlib.h>
#include <cmath>
#include "Shape.h"

using namespace std;

///////////////////////////////////////////////////////////////////////

void Shape::print() const{
    cout << "Area: " << getArea() << " Perim: " << getPerim() << endl;
}

Shape::~Shape(){}

int Shape::count = 0;

///////////////////////////////////////////////////////////////////////

Parallelogram::Parallelogram(double edge1, double edge2, double angle){
    this->edge1 = edge1;
    this->edge2 = edge2;
    this->angle = angle;
    count++;
}

double Parallelogram::getArea() const{
    return edge1*edge2*sin(angle);
}

double Parallelogram::getPerim() const{
    return 2*(edge1+edge2);
}

void Parallelogram::print() const{
    cout << "Parallelogram: ";
    Shape::print();
}
///////////////////////////////////////////////////////////////////////

Rectangle::Rectangle(double width, double height):Parallelogram(width,height,M_PI/2) {}

double Rectangle::getArea() const{
    return edge1*edge2;
}

void Rectangle::print() const{
    cout << "Rectangle: ";
    Shape::print();
}

///////////////////////////////////////////////////////////////////////

Rhombus::Rhombus(double edge,double angle):Parallelogram(edge,edge,angle) {}

double Rhombus::getPerim() const{
    return edge1*4;
}

void Rhombus::print() const{
    cout << "Rhombus: ";
    Shape::print();
}

///////////////////////////////////////////////////////////////////////

Square::Square(double edge):Parallelogram(edge,edge,M_PI/2){}

void Square::print() const{
    cout << "Square: ";
    Shape::print();
}

///////////////////////////////////////////////////////////////////////

Circle::Circle(double r){
    this->r = r;
    count++;
}

double Circle::getArea() const{
    return r*r*M_PI;
}

double Circle::getPerim() const{
    return 2*r*M_PI;
}

void Circle::print() const{
    cout << "Circle: ";
    Shape::print();
}

///////////////////////////////////////////////////////////////////////

Triangle::Triangle(double edge1, double edge2, double edge3){
    this->edge1 = edge1;
    this->edge2 = edge2;
    this->edge3 = edge3;
    count++;
}

double Triangle::getArea() const{
    double p = getPerim()/2;
    return sqrt(p*(p-edge1)*(p-edge2)*(p-edge3));
}

double Triangle::getPerim() const{
    return edge1+edge2+edge3;
}

void Triangle::print() const{
    cout << "Triangle: ";
    Shape::print();
}

///////////////////////////////////////////////////////////////////////

void Shapes(Shape *p[], int n){
    double sum = 0;
    for(int i = 0; i < n; i++){
        cout << "Shape #" << i+1 << ":" << endl;
        p[i]->print(); cout << endl;
        sum += p[i]->getArea();
    }
    cout << "sumArea: " << sum << endl;
}

