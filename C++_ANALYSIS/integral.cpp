#define GL_SILENCE_DEPRECATION

#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <functional>
#include <GLUT/GLUT.h>
#include <chrono>

using namespace std;
using chrono::duration;
using chrono::duration_cast;
using chrono::high_resolution_clock;

#define derta 0.000001

// function
double f1(double x)
{
    return exp(x) + 2;
}
double f2(double x)
{
    return -1.0 / x;
}
double f3(double x)
{
    return -2.0 * (x + 1) / 3;
}
double derivatives_1(function<double(double)> const &f, double x)
{
    return (f(x + derta) - f(x)) / derta;
}
double derivatives_2(function<double(double)> const &f, double x)
{
    return (derivatives_1(f, x + derta) - derivatives_1(f, x)) / derta;
}
double f_1_2(double x)
{
    return f1(x) - f2(x);
}
double f_1_3(double x)
{
    return f1(x) - f3(x);
}

// Find root
double root_help(function<double(double)> const &F, double a, double b, double eps)
{
    double x0, xn;
    
    if (derivatives_1(F, b) * derivatives_2(F, b) > 0)
    {
        x0 = b;
    }
    else if (derivatives_1(F, a) * derivatives_2(F, a) < 0)
    {
        x0 = a;
    }
    xn = x0 - F(x0) / derivatives_1(F, x0);
    while (fabs(x0 - xn) > eps)
    {
        x0 = xn;
        xn = x0 - F(x0) / derivatives_1(F, x0);
    }
    return x0;
}
double root(double f1(double), double f2(double), double a, double b, double eps)
{
    auto F = [&](double x)
    { return f1(x) - f2(x); };
    return root_help(F, a, b, eps);
}

// Integral
double trapezoid(double a, double b, double f(double))
{
    return (f(a) + f(b)) * (b - a) / 2;
}
double integral_help(double a, double b, double eps, double A, double f(double))
{
    double c = a + (b - a) / 2;
    double L = trapezoid(a, c, f), R = trapezoid(c, b, f);
    if (fabs(L + R - A) <= eps)
        return L + R + (L + R - A);
    return integral_help(a, c, eps, L, f) + integral_help(c, b, eps, R, f);
}
double integral(double f(double), double a, double b, double eps)
{
    return integral_help(a, b, eps, trapezoid(a, b, f), f);
}

double integral_while(double f(double), double a, double b, double eps)
{
    
    double Fn = trapezoid(a, b, f);
    
    double F2n = trapezoid(a, b, f)/2;
    double n = 2;
    double h = (b-a)/n;
    for (int i = 1; i < n; i++)
    {
        F2n += f(a+i*h);
    }
    while(fabs(F2n-Fn) >= eps)
    {
        Fn = F2n;
        
        double ext = 0;
        for (int i = 0; i < n; i++)
        {
            ext += f(a+i*h+h/2);
        }
        ext *= h;
        F2n = (Fn+ext)/2;
        h /= 2;
        n *= 2;
    }
    return F2n;
}
// Test
void test()
{
    auto test_f = [](double x)
    { return pow(x, 3); };
    cout << "=====test=====" << endl;
    cout << derivatives_2(test_f, 3) << endl;
    //cout << integral_while(test_f, 0, 3, 0.0000001) << endl;
    cout << integral(test_f, 0, 3, 0.0000001) << endl;
    cout << endl;
}

// graph

void display()

{
    
    glClearColor(1,1,1,1);                     //设置刷新背景色
    
    glClear(GL_COLOR_BUFFER_BIT);              //刷新背景
    
    
    
    glBegin(GL_LINES);                //画个十字充当坐标系
    
    glColor3f(0,0,0);          //设置当前颜色
    
    glVertex3f(-1,0,0);
    
    glVertex3f(1,0,0);
    
    glVertex3f(0,-1,0);
    
    glVertex3f(0,1,0);
    
    glEnd();
    
    
    
    glBegin(GL_LINE_STRIP);
    
    glColor3f(1,0,0);
    for (float x=-5.00;x<= 5.00;x+=0.01)
        glVertex2f(x/5,f1(x)/10);
    
    glEnd();
    
    glBegin(GL_LINE_STRIP);
    
    glColor3f(0,1,0);
    for (float x=-5.00;x< 0.00;x+=0.01)
        glVertex2f(x/5,f2(x)/10);
    
    
    glEnd();
    
    glBegin(GL_LINE_STRIP);
    
    glColor3f(0,0,1);
    for (float x=-5.00;x<=5.00;x+=0.01)
        
        glVertex2f(x/5,f3(x)/10);
    
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    glColor3f(1,1,0);
    for (float x=-5.00;x< 0;x+=0.01)
    {
        for (float y = -5.00; y <= 5.00; y+=0.01)
        {
            if(y<f1(x)/10&&y>f2(x)/10&&y>f3(x)/10){
                glVertex2f(x/5,y);
            }
        }
    }
    glEnd();
    glFlush();          //更新窗口
    
}

void PrintTime(high_resolution_clock::time_point start_time,
               high_resolution_clock::time_point end_time)
{
    cout << "Time: "
    << duration_cast<duration<double, milli>>(end_time - start_time).count()
    << " ms" << endl;
}

int main(int argc, char *argv[])
{
    
    test();
    
    double eps = 0.0000001;
    
    cout << "======Root======" << endl;
    double Root_1_2 = root(f1, f2, -1, -0.2, eps);
    double Root_1_3 = root(f1, f3, -5, -3, eps);
    double Root_2_3 = root(f2, f3, -3, -1, eps);
    
    cout << "Root_1_2: " << Root_1_2 << endl;
    cout << "Root_1_3: " << Root_1_3 << endl;
    cout << "Root_2_3: " << Root_2_3 << endl;
    cout << endl;
    
    cout << "======Recursive Integral======" << endl;
    auto start_time = high_resolution_clock::now();
    double Square = integral(f_1_3, Root_1_3, Root_2_3, eps) + integral(f_1_2, Root_2_3, Root_1_2, eps);
    auto end_time = high_resolution_clock::now();
    cout << "Square: " << Square << endl;
    PrintTime(start_time, end_time);
    cout << endl;
    
    cout << "======Loop Integral=====" << endl;
    start_time = high_resolution_clock::now();
    Square = integral_while(f_1_3, Root_1_3, Root_2_3, eps) + integral(f_1_2, Root_2_3, Root_1_2, eps);
    end_time = high_resolution_clock::now();
    cout << "Square: " << Square << endl;
    PrintTime(start_time, end_time);
    cout << endl;
    
    cout << "=====End=====" << endl;
    glutInit(&argc, argv);
    
    //设置显示模式，RGB,单缓存
    
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    
    //设置窗体位置
    
    glutInitWindowPosition(1000, 1000);
    
    //设置窗体大小
    
    glutInitWindowSize(400, 400);
    
    //创建窗体但不显示
    
    glutCreateWindow("first");
    
    glutDisplayFunc(&display);
    //显示
    
    glutMainLoop();
    return 0;
}

