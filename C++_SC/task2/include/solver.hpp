#pragma once

#include "task.hpp"
#include <vector>
#include <iostream>

using namespace std;

using cube = vector<vector<vector<double>>>;

class Solver
{
    Task task;

    vector<cube> u;

public:
    Solver(Task task) : task(task)
    {
        reserve();
    }
    void reserve()
    {
        u.resize(3);

        for (int n = 0; n < 3; n++)
        {
            u[n].resize(task.g.N + 1);

            for (int i = 0; i <= task.g.N; i++)
            {
                u[n][i].resize(task.g.N + 1);

                for (int j = 0; j <= task.g.N; j++)
                {
                    u[n][i][j].resize(task.g.N + 1);
                }
            }
        }
    }
    double laplacian(cube &c, int i, int j, int k)
    {
        return (c[i + 1][j][k] - 2 * c[i][j][k] + c[i - 1][j][k]) / (task.g.hx * task.g.hx) +
               (c[i][j + 1][k] - 2 * c[i][j][k] + c[i][j - 1][k]) / (task.g.hy * task.g.hy) +
               (c[i][j][k + 1] - 2 * c[i][j][k] + c[i][j][k - 1]) / (task.g.hz * task.g.hz);
    }
    void boundary(cube &c, double t)
    {
#pragma omp parallel for collapse(2)
        for (int i = 0; i <= task.g.N; i++)
        {
            for (int j = 0; j <= task.g.N; j++)
            {
                c[i][j][0] = task.f(i * task.g.hx, j * task.g.hy, 0, t);
                c[i][j][task.g.N] = task.f(i * task.g.hx, j * task.g.hy, task.g.d.Lz, t);
            }
        }
    }
    double getError()
    {
        double error = 0;
        for (int i = 0; i <= task.g.N; i++)
        {
            for (int j = 0; j <= task.g.N; j++)
            {
                for (int k = 0; k <= task.g.N; k++)
                {
                    // cout << u[loop(task.steps)][i][j][k] << " " << task.f(i * task.g.hx, j * task.g.hy, k * task.g.hz, task.g.tau * task.steps) << endl;
                    error = max(error, abs(u[loop(task.steps)][i][j][k] - task.f(i * task.g.hx, j * task.g.hy, k * task.g.hz, task.g.tau * task.steps)));
                }
            }
        }

        return error;
    }
    void init()
    {
        boundary(u[0], 0);
        boundary(u[1], task.g.tau);

#pragma omp parallel for collapse(3)
        for (int i = 1; i < task.g.N; i++)
        {
            for (int j = 1; j < task.g.N; j++)
            {
                for (int k = 1; k < task.g.N; k++)
                {
                    u[0][i][j][k] = task.f(i * task.g.hx, j * task.g.hy, k * task.g.hz, 0);
                }
            }
        }
        for (int i = 1; i < task.g.N; i++)
        {
            for (int j = 1; j < task.g.N; j++)
            {
                for (int k = 1; k < task.g.N; k++)
                {
                    u[1][i][j][k] = u[0][i][j][k] + task.g.tau * task.g.tau / 2.0 * laplacian(u[0], i, j, k);
                }
            }
        }
    }
    const int loop(int n)
    {
        return n % 3;
    }
    void iterate(int n)
    {
#pragma omp parallel for collapse(3)
        for (int i = 1; i < task.g.N; i++)
        {
            for (int j = 1; j < task.g.N; j++)
            {
                for (int k = 1; k < task.g.N; k++)
                {
                    u[loop(n + 1)][i][j][k] = 2 * u[loop(n)][i][j][k] - u[loop(n - 1)][i][j][k] + task.f.a_2 * task.g.tau * task.g.tau * laplacian(u[loop(n)], i, j, k);
                }
            }
        }

        boundary(u[loop(n + 1)], (n + 1) * task.g.tau);
    }
    void run()
    {
        init();

        for (int n = 1; n < task.steps; n++)
        {
            iterate(n);
        }

        cout << "error : " << getError() << endl;
    }
};