#define GL_SILENCE_DEPRECATION
#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <functional>
#include <chrono>
#include <GLUT/GLUT.h>

using namespace std;
using chrono::duration;
using chrono::duration_cast;
using chrono::high_resolution_clock;

#define derta 0.000001

double f(double x)
{
    return 2 * x - 1.0 + 2 * cos(M_PI * x);
}
double derivatives_1(function<double(double)> const &f, double x)
{
    return (f(x + derta) - f(x)) / derta;
}
double derivatives_2(function<double(double)> const &f, double x)
{
    return (derivatives_1(f, x + derta) - derivatives_1(f, x)) / derta;
}
double min_Newton(function<double(double)> const &f, double a, double b, double eps)
{
    double x1 = (a + b) / 2.0;
    double x2 = x1 - derivatives_1(f, x1) / derivatives_2(f, x1);
    while (fabs(x2 - x1) > eps)
    {
        x1 = x2;
        x2 = x1 - derivatives_1(f, x1) / derivatives_2(f, x1);
    }
    return x2;
}
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
        glVertex2f(x/5,f(x)/10);
    
    glEnd();
    
    
    glBegin(GL_LINE_STRIP);
    
    glColor3f(0,1,0);
    glVertex2f(0.896884/5, 1);
    glVertex2f(0.896884/5, -1);
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
void test(double eps)
{
    const auto start_time = high_resolution_clock::now();
    double min_x = min_Newton(f, 0, 2, eps);
    double min = f(min_x);
    const auto end_time = high_resolution_clock::now();
    cout << "min_x = " << min_x << endl;
    cout << "min = " << min << endl;
    PrintTime(start_time, end_time);
}
int main(int argc, char *argv[])
{
    test(0.000001);
    
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
