#pragma once

#include <omp.h>
#include <iostream>

#include "solver.hpp"
#include "printer.hpp"

using namespace std;

struct Cube
{
    double *data;
    int N;

    Cube() : N(0), data(nullptr) {}
    Cube(int N) : N(N)
    {
        data = new double[(N + 1) * (N + 1) * (N + 1)];
        for (int i = 0; i < (N + 1) * (N + 1) * (N + 1); i++)
        {
            data[i] = 0;
        }
    }
    Cube &operator=(Cube &&c)
    {
        if (this != &c)
        {

            delete[] data;
            data = c.data;
            N = c.N;
            c.data = nullptr;
            c.N = 0;
        }
        return *this;
    }
    ~Cube()
    {
        delete[] data;
    }
    inline double &operator()(int i, int j, int k) const
    {
        return data[i * (N + 1) * (N + 1) + j * (N + 1) + k];
    }
};

class SerialSolver : public Solver
{
private:
    Cube *u;

    inline double laplacian(Cube &c, int i, int j, int k) const
    {
        return (c(i + 1, j, k) - 2 * c(i, j, k) + c(i - 1, j, k)) / (task.g.hx * task.g.hx) +
               (c(i, j + 1, k) - 2 * c(i, j, k) + c(i, j - 1, k)) / (task.g.hy * task.g.hy) +
               (c(i, j, k + 1) - 2 * c(i, j, k) + c(i, j, k - 1)) / (task.g.hz * task.g.hz);
    }
    void boundary_init(Cube &c, double t)
    {
#pragma omp parallel for
        for (int i = 0; i <= task.N; i++)
        {
#pragma omp parallel for
            for (int j = 0; j <= task.N; j++)
            {
                c(i, j, 0) = task.f(i * task.g.hx, j * task.g.hy, 0, t);
            }
        }

#pragma omp parallel for
        for (int i = 0; i <= task.N; i++)
        {
#pragma omp parallel for
            for (int j = 0; j <= task.N; j++)
            {
                c(i, j, task.N) = task.f(i * task.g.hx, j * task.g.hy, task.d.Lz, t);
            }
        }
    }
    void bounday_iterate(int n)
    {
#pragma omp parallel for
        for (int i = 1; i < task.N; i++)
        {
#pragma omp parallel for
            for (int j = 1; j < task.N; j++)
            {
                double l = (u[loop(n - 1)](i + 1, j, 0) - 2 * u[loop(n - 1)](i, j, 0) + u[loop(n - 1)](i - 1, j, 0)) / (task.g.hx * task.g.hx) +
                           (u[loop(n - 1)](i, j + 1, 0) - 2 * u[loop(n - 1)](i, j, 0) + u[loop(n - 1)](i, j - 1, 0)) / (task.g.hy * task.g.hy) +
                           (u[loop(n - 1)](i, j, 0 + 1) - 2 * u[loop(n - 1)](i, j, 0) + u[loop(n - 1)](i, j, 0 + task.N - 1)) / (task.g.hz * task.g.hz);
                u[loop(n)](i, j, 0) = 2 * u[loop(n - 1)](i, j, 0) -
                                      u[loop(n - 2)](i, j, 0) +
                                      task.f.a_2 * task.g.tau * task.g.tau * l;
            }
        }

#pragma omp parallel for
        for (int i = 1; i < task.N; i++)
        {
#pragma omp parallel for
            for (int j = 1; j < task.N; j++)
            {
                double l = (u[loop(n - 1)](i + 1, j, task.N) - 2 * u[loop(n - 1)](i, j, 0) + u[loop(n - 1)](i - 1, j, 0)) / (task.g.hx * task.g.hx) +
                           (u[loop(n - 1)](i, j + 1, task.N) - 2 * u[loop(n - 1)](i, j, 0) + u[loop(n - 1)](i, j - 1, 0)) / (task.g.hy * task.g.hy) +
                           (u[loop(n - 1)](i, j, task.N - task.N + 1) - 2 * u[loop(n - 1)](i, j, 0) + u[loop(n - 1)](i, j, task.N - 1)) / (task.g.hz * task.g.hz);
                (u[loop(n)])(i, j, task.N) = 2 * u[loop(n - 1)](i, j, task.N) -
                                             u[loop(n - 2)](i, j, task.N) +
                                             task.f.a_2 * task.g.tau * task.g.tau * l;
            }
        }
    }
    double getError()
    {
        if (Printer::verbose)
        {
            Printer::open_csv();
        }

        double e = 0;

#pragma omp parallel for reduction(max : e) if (!Printer::verbose)
        for (int i = 0; i <= task.N; i++)
        {
#pragma omp parallel for reduction(max : e) if (!Printer::verbose)
            for (int j = 0; j <= task.N; j++)
            {
#pragma omp parallel for reduction(max : e) if (!Printer::verbose)
                for (int k = 0; k <= task.N; k++)
                {
                    double numerical = u[loop(task.steps)](i, j, k);
                    double analytical = task.f(i * task.g.hx, j * task.g.hy, k * task.g.hz, task.g.tau * task.steps);
                    double error = abs(numerical - analytical);

                    e = max(e, error);

                    if (Printer::verbose)
                    {
                        Printer::save_csv("analytical", i * task.g.hx, j * task.g.hy, k * task.g.hz, analytical);
                        Printer::save_csv("numerical", i * task.g.hx, j * task.g.hy, k * task.g.hz, numerical);
                        Printer::save_csv("error", i * task.g.hx, j * task.g.hy, k * task.g.hz, error);
                    }
                }
            }
        }

        if (Printer::verbose)
        {
            Printer::close_csv();
        }

        return e;
    }
    void init()
    {
        boundary_init(u[0], 0);
        boundary_init(u[1], task.g.tau);

#pragma omp parallel for
        for (int i = 1; i < task.N; i++)
        {
#pragma omp parallel for
            for (int j = 1; j < task.N; j++)
            {
#pragma omp parallel for
                for (int k = 1; k < task.N; k++)
                {
                    u[0](i, j, k) = task.f(i * task.g.hx, j * task.g.hy, k * task.g.hz, 0);
                }
            }
        }
#pragma omp parallel for
        for (int i = 1; i < task.N; i++)
        {
#pragma omp parallel for
            for (int j = 1; j < task.N; j++)
            {
#pragma omp parallel for
                for (int k = 1; k < task.N; k++)
                {
                    u[1](i, j, k) = u[0](i, j, k) + task.f.a_2 * task.g.tau * task.g.tau / 2.0 * laplacian(u[0], i, j, k);
                }
            }
        }
    }
    int loop(int n) const
    {
        return n % 3;
    }
    void iterate(int n)
    {
#pragma omp parallel for
        for (int i = 1; i < task.N; i++)
        {
#pragma omp parallel for
            for (int j = 1; j < task.N; j++)
            {
#pragma omp parallel for
                for (int k = 1; k < task.N; k++)
                {
                    (u[loop(n + 1)])(i, j, k) = 2 * u[loop(n)](i, j, k) -
                                                u[loop(n - 1)](i, j, k) +
                                                task.f.a_2 * task.g.tau * task.g.tau * laplacian(u[loop(n)], i, j, k);
                }
            }
        }

        bounday_iterate(n + 1);
    }

public:
    SerialSolver(Task task) : Solver(task)
    {
        u = new Cube[3];
        u[0] = Cube(task.N);
        u[1] = Cube(task.N);
        u[2] = Cube(task.N);
    }
    void run() override
    {
        init();

        for (int n = 1; n < task.steps; n++)
        {
            iterate(n);
        }

        Printer::print("error", getError());
    }
    ~SerialSolver() override
    {
        delete[] u;
    }
};