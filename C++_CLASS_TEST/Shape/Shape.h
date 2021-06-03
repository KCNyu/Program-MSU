#ifndef SHAPE_H
#define SHAPE_H

class Shape{
public:
    virtual double getArea() const = 0;
    virtual double getPerim() const = 0;
    virtual void print() const;
    virtual ~Shape();
    static int count;
};

class Parallelogram : public Shape{
protected:
    double edge1;
    double edge2;
    double angle;
public:
    Parallelogram(double edge1 = 0, double edge2 = 0, double angle = 0);
    double getPerim() const;
    virtual double getArea() const;
    virtual void print() const;
};

class Rectangle : virtual public Parallelogram{
public:
    Rectangle(double width = 0, double height = 0);
    virtual double getArea() const;
    virtual void print() const;
};

class Rhombus : virtual public Parallelogram{
public:
    Rhombus(double edge = 0, double angle = 0);
    virtual double getPerim() const;
    virtual void print() const;
};

class Square : public Rhombus, public Rectangle{
public:
    Square(double edge = 0);
    virtual void print() const;
};

class Circle : public Shape{
private:
    double r;
public:
    Circle(double r = 0);
    double getArea() const;
    double getPerim() const;
    virtual void print() const;
};

class Triangle : public Shape{
private:
    double edge1;
    double edge2;
    double edge3;
public:
    Triangle(double edge1 = 0, double edge2 = 0, double edge3 = 0);
    double getArea() const;
    double getPerim() const;
    virtual void print() const;
};

void Shapes(Shape *p[], int n);

#endif /* SHAPE_H */
