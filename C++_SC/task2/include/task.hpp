#pragma once

#include <cmath>
#include <vector>

struct Domain
{
    double Lx;
    double Ly;
    double Lz;

    Domain(double Lx, double Ly, double Lz) : Lx(Lx), Ly(Ly), Lz(Lz) {}
};

struct Grid
{
    double hx;
    double hy;
    double hz;

    double tau;

    Grid(Domain d, int N, double T, double K)
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

    enum class Type
    {
        FIRST,
        PERIODIC
    };
    std::vector<Type> types;

    Function(Domain d) : d(d)
    {
        a_t = sqrt(1.0 / (d.Lx * d.Lx) + 1.0 / (d.Ly * d.Ly) + 4.0 / (d.Lz * d.Lz));
        a_2 = 1.0 / (M_PI * M_PI);

        types = {Type::FIRST, Type::FIRST, Type::PERIODIC};
    }

    double operator()(double x, double y, double z, double t) const
    {
        return sin(M_PI * x / d.Lx) * sin(M_PI * y / d.Ly) * sin(2 * M_PI * z / d.Lz) * cos(a_t * t + 2 * M_PI);
    }
};

struct Task
{
    Domain d;
    Grid g;
    Function f;

    int N;
    int steps;

    Task(double Lx, double Ly, double Lz, int N, double T, double K, int steps) : d(Domain(Lx, Ly, Lz)),
                                                                                  g(Grid(d, N, T, K)),
                                                                                  f(Function(d)),
                                                                                  N(N),
                                                                                  steps(steps)
    {
    }
};