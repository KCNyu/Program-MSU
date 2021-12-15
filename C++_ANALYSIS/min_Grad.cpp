#define GL_SILENCE_DEPRECATION
#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <functional>
#include <chrono>
#include <GLUT/GLUT.h>
#include <iomanip>

using namespace std;
using chrono::duration;
using chrono::duration_cast;
using chrono::high_resolution_clock;

#define derta 0.000001

double y1(double x, double c)
{
    return 0.1 * (10 * x * x - sqrt(10) * sqrt(c - x * x + 2 * x - 1));
}
double y2(double x, double c)
{
    return 0.1 * (10 * x * x + sqrt(10) * sqrt(c - x * x + 2 * x - 1));
}
double f(double x, double y)
{
    return 10 * pow(y - x * x, 2) + pow(1 - x, 2);
}
double derivatives_x(function<double(double, double)> const &f, double x, double y)
{
    return (f(x + derta, y) - f(x, y)) / derta;
}
double derivatives_y(function<double(double, double)> const &f, double x, double y)
{
    return (f(x, y + derta) - f(x, y)) / derta;
}
double falpha(double x, double y, double alpha)
{
    double dx = derivatives_x(f, x, y);
    double dy = derivatives_y(f, x, y);
    x -= alpha * dx;
    y -= alpha * dy;
    return f(x, y);
}
double gold(double fx(double, double, double alpha), double x, double y)
{
    double epsilon = 0.001, f_min, tau = 0.618;
    double a_gss = 0, b_gss = 1, f_lambda = 0, f_mu = 0;
    double lambda = a_gss + (1.0 - tau) * (b_gss - a_gss), mu = a_gss + tau * (b_gss - a_gss);
    f_lambda = fx(x, y, lambda);
    f_mu = fx(x, y, mu);
    for (int i = 0; fabs(mu - lambda) > epsilon; i++)
    {
        if (f_lambda < f_mu)
        {
            b_gss = mu;
            mu = lambda;
            f_mu = f_lambda;
            lambda = a_gss + (1.0 - tau) * (b_gss - a_gss);
            f_lambda = fx(x, y, lambda);
        }
        else
        {
            a_gss = lambda;
            lambda = mu;
            f_lambda = f_mu;
            mu = a_gss + tau * (b_gss - a_gss);
            f_mu = fx(x, y, mu);
        }
    }
    f_min = fx(x, y, 0.5 * (lambda + mu));

    return (lambda + mu) / 2;
}

double min_Grad(function<double(double, double)> const &f, double a, double b, double eps)
{
    double alpha;
    pair<double, double> x = {a, b};
    pair<double, double> dx = {derivatives_x(f, x.first, x.second), derivatives_y(f, x.first, x.second)};

    double f_old = f(x.first, x.second);

    double f_result;
    while (true)
    {
        alpha = gold(falpha, x.first, x.second);
        // cout << "alpha = " << alpha << endl;
        x.first -= alpha * dx.first;
        x.second -= alpha * dx.second;
        f_result = f(x.first, x.second);
        if (fabs(f_result - f_old) <= eps)
        {
            break;
        }
        dx.first = derivatives_x(f, x.first, x.second);
        dx.second = derivatives_y(f, x.first, x.second);
        f_old = f_result;
    }
    cout << fixed << setprecision(3) << "min_x = " << x.first << " min_y = " << x.second << endl;
    cout << "f_result = " << f_result << endl;
    return f_result;
}
void display()

{

    glClearColor(1, 1, 1, 1); //设置刷新背景色

    glClear(GL_COLOR_BUFFER_BIT); //刷新背景

    glBegin(GL_LINES); //画个十字充当坐标系

    glColor3f(0, 0, 0); //设置当前颜色

    glVertex3f(-5, 0, 0);

    glVertex3f(5, 0, 0);

    glVertex3f(0, -5, 0);

    glVertex3f(0, 5, 0);

    glEnd();

    for (float i = 0.1; i <= 10; i += 0.5)
    {
        glBegin(GL_LINE_STRIP);
        glColor3f(1, 0, 0);
        for (float x = -5; x <= 5; x += 0.001)
            glVertex2f(x, y1(x, i));
        glEnd();

        glBegin(GL_LINE_STRIP);
        glColor3f(1, 0, 0);
        for (float x = -5; x <= 5; x += 0.001)
            glVertex2f(x, y2(x, i));
        glEnd();
    }
    glFlush(); //更新窗口
}
void PrintTime(high_resolution_clock::time_point start_time,
               high_resolution_clock::time_point end_time)
{
    cout << "Time: "
         << duration_cast<duration<double, milli>>(end_time - start_time).count()
         << " ms" << endl;
}
//转换坐标系
void init(void)
{
    //设置显示窗口的背景为白色。参数顺序为：红、绿、蓝、透明度。
    glClearColor(1.0, 1.0, 1.0, 0.0);
    //设置投影类型：正投影
    glMatrixMode(GL_PROJECTION | GL_MODELVIEW);
    gluOrtho2D(-5, 5, -5, 5);
}

int main(int argc, char *argv[])
{
    min_Grad(f, 0, 0, 0.00000001);

    glutInit(&argc, argv);

    //设置显示模式，RGB,单缓存

    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);

    //设置窗体位置

    glutInitWindowPosition(1000, 1000);

    //设置窗体大小

    glutInitWindowSize(400, 400);

    //创建窗体但不显示

    glutCreateWindow("first");
    init();
    glutDisplayFunc(&display);
    //显示

    glutMainLoop();
    return 0;
}