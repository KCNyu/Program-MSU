/*================================================================
* Filename:Gravity.cpp
* Author: KCN_yu
* Createtime:Sun 05 Sep 2021 04:07:12 PM CST
================================================================*/

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <omp.h>

using namespace std;
#define gravity 10 // гравитационная постоянная
#define dt 0.1     // шаг по времени
#define N 800      // количество частиц
#define fmax 1     // максимальное значение силы
#define Niter 100  // число итераций
#define LOG_INFO(format, ...)                                                             \
    {                                                                                     \
        time_t t = time(0);                                                               \
        struct tm ttt = *localtime(&t);                                                   \
        fprintf(stdout, "[INFO] [%4d-%02d-%02d %02d:%02d:%02d] [%s] [%s:%d]\n " format "",  \
                ttt.tm_year + 1900, ttt.tm_mon + 1, ttt.tm_mday, ttt.tm_hour,             \
                ttt.tm_min, ttt.tm_sec, __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__); \
    }
struct Particle
{
    double x, y, vx, vy;
};
struct Force
{
    double x, y;
};
Particle p[N];
Force f[N];
double m[N];
void Init()
{
    for (int i = 0; i < N; i++)
    {
        p[i].x = 20 * (i / 20 - 20) + 10;
        p[i].y = 20 * (i % 20 - 10) + 10;
        p[i].vx = p[i].y / 15;
        p[i].vy = -p[i].x / 50;
        m[i] = 100 + i % 100;
        f[i].x = 0;
        f[i].y = 0;
    }
}
void CalcForces1()
{
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
        {
            if (i == j)
                continue;
            double dx = p[j].x - p[i].x, dy = p[j].y - p[i].y,
                   r_2 = 1 / (dx * dx + dy * dy),
                   r_1 = sqrt(r_2),
                   fabs = gravity * m[i] * m[j] * r_2;
            if (fabs > fmax)
                fabs = fmax;
            f[i].x = f[i].x + fabs * dx * r_1;
            f[i].y = f[i].y + fabs * dy * r_1;
        }
}
//Параллельные методы решения гравитационной задачи n тел 3
void MoveParticlesAndFreeForces()
{
    for (int i = 0; i < N; i++)
    {
        double dvx = f[i].x * dt / m[i],
               dvy = f[i].y * dt / m[i];
        p[i].x += (p[i].vx + dvx / 2) * dt;
        p[i].y += (p[i].vy + dvy / 2) * dt;
        p[i].vx += dvx;
        p[i].vy += dvy;
        f[i].x = 0;
        f[i].y = 0;
    }
}
void info(char *s, double time)
{
    cout << setw(30) << left << s << "Time: " << fixed << setprecision(0) << setw(6) << 1000 * time
         << setprecision(12) << "p0: " << setw(12) << p[0].x << ", " << setw(12) << p[0].y << endl;
}
int main()
{
    double tt = 0;
    int Titer = 50;
    for (int kk = 1; kk <= Titer; kk++)
    {
        Init();
        double t = omp_get_wtime();
        for (int i = 0; i < Niter; i++)
        {
            CalcForces1();
            MoveParticlesAndFreeForces();
        }
        t = omp_get_wtime() - t;
        tt += t;
    }
    info("Non-parallel (N*N)", tt / Titer);
    return 0;
}
