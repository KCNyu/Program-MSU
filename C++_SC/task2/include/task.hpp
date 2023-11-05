#pragma once

#include <cmath>

struct Domain
{
    double Lx;
    double Ly;
    double Lz;

    Domain(double Lx, double Ly, double Lz) : Lx(Lx), Ly(Ly), Lz(Lz) {}
};

struct Grid
{
    Domain d;

    int N;

    double hx;
    double hy;
    double hz;

    double tau;

    Grid(Domain d, int N, double T, double K) : d(d), N(N)
    {
        hx = d.Lx / N;
        hy = d.Ly / N;
        hz = d.Lz / N;

        tau = T / K;
    }
};

struct Function
{
    Domain d;
    double a_t;
    double a_2;

    Function(Domain d) : d(d)
    {
        a_t = sqrt(1.0 / (d.Lx * d.Lx) + 1.0 / (d.Ly * d.Ly) + 4.0 / (d.Lz * d.Lz));
        a_2 = 1.0 / (M_PI * M_PI);
    }

    double operator()(double x, double y, double z, double t) const
    {
        return sin(M_PI * x / d.Lx) * sin(M_PI * y / d.Ly) * sin(2 * M_PI * z / d.Lz) * cos(a_t * t + 2 * M_PI);
    }
};

struct Task
{
    Grid g;
    Function f;
    int steps;

    Task(double Lx, double Ly, double Lz, int N, double T, double K, int steps) : g(Domain(Lx, Ly, Lz), N, T, K), f(Domain(Lx, Ly, Lz)), steps(steps) {}
};