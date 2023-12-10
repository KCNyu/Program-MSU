#pragma once

#include <mpi.h>

#include "solver.hpp"
#include "cube.hpp"
#include "printer.hpp"

struct Process
{
    int rank;
    int size;

    Process()
    {
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);
        MPI_Comm_size(MPI_COMM_WORLD, &size);
    }
};

class ParallelSolver : public Solver
{
private:
    Cube *u;

    Process p;

    std::vector<Scale> rank_scales;
    std::vector<Cube> recv_cubes;

    std::vector<std::pair<int, Scale>> wait_send;
    std::vector<std::pair<int, Scale>> wait_recv;

    void split(Scale origin)
    {
        int px, py, pz;
        std::tie(px, py, pz) = Scale::split_triplet(p.size);

        int dx = std::max(1, origin.x_len / px);
        int dy = std::max(1, origin.y_len / py);
        int dz = std::max(1, origin.z_len / pz);

        for (int i = 0, x_l = origin.x_l; i < px; ++i)
        {
            int x_r = (i == px - 1) ? origin.x_r : x_l + dx - 1;

            for (int j = 0, y_l = origin.y_l; j < py; ++j)
            {
                int y_r = (j == py - 1) ? origin.y_r : y_l + dy - 1;

                for (int k = 0, z_l = origin.z_l; k < pz; ++k)
                {
                    int z_r = (k == pz - 1) ? origin.z_r : z_l + dz - 1;

                    rank_scales.push_back(Scale(x_l, x_r, y_l, y_r, z_l, z_r));

                    z_l = z_r + 1;
                }

                y_l = y_r + 1;
            }

            x_l = x_r + 1;
        }
    }
    bool IsInside(int xmin1, int xmax1, int ymin1, int ymax1, int xmin2, int xmax2, int ymin2, int ymax2) const
    {
        return xmin2 <= xmin1 && xmax1 <= xmax2 && ymin2 <= ymin1 && ymax1 <= ymax2;
    }
    void init_send_recv()
    {
        Scale local_scale = rank_scales[p.rank];

        for (int i = 0; i < p.size; i++)
        {
            if (i != p.rank)
            {
                Scale remote_scale = rank_scales[i];

                if (local_scale.x_l == remote_scale.x_r + 1 || remote_scale.x_l == local_scale.x_r + 1)
                {
                    int xSend = local_scale.x_l == remote_scale.x_r + 1 ? local_scale.x_l : local_scale.x_r;
                    int xRecv = remote_scale.x_l == local_scale.x_r + 1 ? remote_scale.x_l : remote_scale.x_r;
                    int y_l, y_r, z_l, z_r;
                    if (IsInside(local_scale.y_l, local_scale.y_r, local_scale.z_l, local_scale.z_r,
                                 remote_scale.y_l, remote_scale.y_r, remote_scale.z_l, remote_scale.z_r))
                    {
                        y_l = local_scale.y_l;
                        y_r = local_scale.y_r;
                        z_l = local_scale.z_l;
                        z_r = local_scale.z_r;
                    }
                    else if (IsInside(remote_scale.y_l, remote_scale.y_r, remote_scale.z_l, remote_scale.z_r,
                                      local_scale.y_l, local_scale.y_r, local_scale.z_l, local_scale.z_r))
                    {
                        y_l = remote_scale.y_l;
                        y_r = remote_scale.y_r;
                        z_l = remote_scale.z_l;
                        z_r = remote_scale.z_r;
                    }
                    else
                    {
                        continue;
                    }
                    wait_send.emplace_back(i, Scale(xSend, xSend, y_l, y_r, z_l, z_r));
                    wait_recv.emplace_back(i, Scale(xRecv, xRecv, y_l, y_r, z_l, z_r));
                    continue;
                }
                if (local_scale.y_l == remote_scale.y_r + 1 or remote_scale.y_l == local_scale.y_r + 1)
                {
                    int ySend = local_scale.y_l == remote_scale.y_r + 1 ? local_scale.y_l : local_scale.y_r;
                    int yRecv = remote_scale.y_l == local_scale.y_r + 1 ? remote_scale.y_l : remote_scale.y_r;
                    int x_l, x_r, z_l, z_r;
                    if (IsInside(local_scale.x_l, local_scale.x_r, local_scale.z_l, local_scale.z_r,
                                 remote_scale.x_l, remote_scale.x_r, remote_scale.z_l, remote_scale.z_r))
                    {
                        x_l = local_scale.x_l;
                        x_r = local_scale.x_r;
                        z_l = local_scale.z_l;
                        z_r = local_scale.z_r;
                    }
                    else if (IsInside(remote_scale.x_l, remote_scale.x_r, remote_scale.z_l, remote_scale.z_r,
                                      local_scale.x_l, local_scale.x_r, local_scale.z_l, local_scale.z_r))
                    {
                        x_l = remote_scale.x_l;
                        x_r = remote_scale.x_r;
                        z_l = remote_scale.z_l;
                        z_r = remote_scale.z_r;
                    }
                    else
                    {
                        continue;
                    }
                    wait_send.emplace_back(i, Scale(x_l, x_r, ySend, ySend, z_l, z_r));
                    wait_recv.emplace_back(i, Scale(x_l, x_r, yRecv, yRecv, z_l, z_r));
                    continue;
                }
                if (local_scale.z_l == remote_scale.z_r + 1 or remote_scale.z_l == local_scale.z_r + 1)
                {
                    int zSend = local_scale.z_l == remote_scale.z_r + 1 ? local_scale.z_l : local_scale.z_r;
                    int zRecv = remote_scale.z_l == local_scale.z_r + 1 ? remote_scale.z_l : remote_scale.z_r;
                    int x_l, x_r, y_l, y_r;
                    if (IsInside(local_scale.x_l, local_scale.x_r, local_scale.y_l, local_scale.y_r,
                                 remote_scale.x_l, remote_scale.x_r, remote_scale.y_l, remote_scale.y_r))
                    {
                        x_l = local_scale.x_l;
                        x_r = local_scale.x_r;
                        y_l = local_scale.y_l;
                        y_r = local_scale.y_r;
                    }
                    else if (IsInside(remote_scale.x_l, remote_scale.x_r, remote_scale.y_l, remote_scale.y_r,
                                      local_scale.x_l, local_scale.x_r, local_scale.y_l, local_scale.y_r))
                    {
                        x_l = remote_scale.x_l;
                        x_r = remote_scale.x_r;
                        y_l = remote_scale.y_l;
                        y_r = remote_scale.y_r;
                    }
                    else
                    {
                        continue;
                    }
                    wait_send.emplace_back(i, Scale(x_l, x_r, y_l, y_r, zSend, zSend));
                    wait_recv.emplace_back(i, Scale(x_l, x_r, y_l, y_r, zRecv, zRecv));
                    continue;
                }
            }
        }
    }
    Cube get_send_cube(Cube &c, Scale remote_scale)
    {
        Cube send_cube(remote_scale);

        // cout << "====================" << endl;
        // cout << "rank " << p.rank << endl;
        // cout << remote_scale;
        // cout << "~~~~~~~~~~~~~~~~~~~~" << endl;
        // cout << c.scale;
        // cout << "====================" << endl;

        // MPI_Barrier(MPI_COMM_WORLD);
        for (int i = remote_scale.x_l; i <= remote_scale.x_r; i++)
        {
            for (int j = remote_scale.y_l; j <= remote_scale.y_r; j++)
            {
                for (int k = remote_scale.z_l; k <= remote_scale.z_r; k++)
                {
                    send_cube(i, j, k) = c(i, j, k);
                }
            }
        }

        return send_cube;
    }
    void send_recv_cube(int n)
    {
        recv_cubes.clear();
        recv_cubes.resize(wait_recv.size());

        std::vector<MPI_Request> requests(2);
        std::vector<MPI_Status> statuses(2);

        // cout << "===rank: " << p.rank << "===" << endl;
        // for (int i = 0; i < wait_send.size(); i++)
        // {
        //     cout << "send to " << wait_send[i].first << " with size " << wait_send[i].second.size << endl;
        // }
        // for (int i = 0; i < wait_recv.size(); i++)
        // {
        //     cout << "recv from " << wait_recv[i].first << " with size " << wait_recv[i].second.size << endl;
        // }
        // cout << "====================" << endl;
        for (int i = 0; i < wait_recv.size(); i++)
        {
            Cube send_cube = get_send_cube(u[loop(n)], wait_send[i].second);
            recv_cubes[i] = Cube(wait_recv[i].second);

            // cout << "rank " << p.rank << " send to " << wait_send[i].first << " with size " << send_cube.scale << endl;
            // cout << "rank " << p.rank << " recv from " << wait_recv[i].first << " with size " << wait_recv[i].second << endl;

            MPI_Isend(send_cube.data, wait_send[i].second.size, MPI_DOUBLE, wait_send[i].first, 0, MPI_COMM_WORLD, &requests[0]);
            MPI_Irecv(recv_cubes[i].data, wait_recv[i].second.size, MPI_DOUBLE, wait_recv[i].first, 0, MPI_COMM_WORLD, &requests[1]);
            MPI_Waitall(2, requests.data(), statuses.data());
        
            // cout << "i == " << i << endl;
        }
    }

    void init_boundary(Cube &c, double t)
    {
        if (c.scale.z_l == 0)
        {
#pragma omp parallel for
            for (int i = c.scale.x_l; i <= c.scale.x_r; i++)
            {
                for (int j = c.scale.y_l; j <= c.scale.y_r; j++)
                {
                    c(i, j, 0) = task.f(i * task.g.hx, j * task.g.hy, 0, t);
                }
            }
        }
        if (c.scale.z_r == task.N)
        {
#pragma omp parallel for
            for (int i = c.scale.x_l; i <= c.scale.x_r; i++)
            {
                for (int j = c.scale.y_l; j <= c.scale.y_r; j++)
                {
                    c(i, j, task.N) = task.f(i * task.g.hx, j * task.g.hy, task.d.Lz, t);
                }
            }
        }
    }
    int loop(int n) const
    {
        return n % 3;
    }
    double actual_u(Cube &c, int i, int j, int k) const
    {
        if (c.scale.x_l <= i && i <= c.scale.x_r &&
            c.scale.y_l <= j && j <= c.scale.y_r &&
            c.scale.z_l <= k && k <= c.scale.z_r)
        {
            return c(i, j, k);
        }

        for (int r_i = 0; r_i < recv_cubes.size(); r_i++)
        {
            Scale remote_scale = recv_cubes[r_i].scale;

            if (remote_scale.x_l <= i && i <= remote_scale.x_r &&
                remote_scale.y_l <= j && j <= remote_scale.y_r &&
                remote_scale.z_l <= k && k <= remote_scale.z_r)
            {
                return recv_cubes[r_i](i, j, k);
            }
        }

        return 0;
    }
    inline double laplacian(Cube &c, int i, int j, int k) const
    {
        double dx = (actual_u(c, i - 1, j, k) - 2 * c(i, j, k) + actual_u(c, i + 1, j, k)) / (task.g.hx * task.g.hx);
        double dy = (actual_u(c, i, j - 1, k) - 2 * c(i, j, k) + actual_u(c, i, j + 1, k)) / (task.g.hy * task.g.hy);
        double dz = (actual_u(c, i, j, k - 1) - 2 * c(i, j, k) + actual_u(c, i, j, k + 1)) / (task.g.hz * task.g.hz);
        return dx + dy + dz;
    }
    void init()
    {
        split(Scale(task.N));
        Scale local_scale = rank_scales[p.rank];
        for (int i = 0; i < 3; i++)
        {
            u[i] = Cube(local_scale);
        }
        init_send_recv();

        init_boundary(u[0], 0);
        init_boundary(u[1], task.g.tau);

        int x_l = std::max(1, u[0].scale.x_l);
        int x_r = std::min(task.N - 1, u[0].scale.x_r);

        int y_l = std::max(1, u[0].scale.y_l);
        int y_r = std::min(task.N - 1, u[0].scale.y_r);

        int z_l = std::max(1, u[0].scale.z_l);
        int z_r = std::min(task.N - 1, u[0].scale.z_r);

#pragma omp parallel for
        for (int i = x_l; i <= x_r; i++)
        {
            for (int j = y_l; j <= y_r; j++)
            {
                for (int k = z_l; k <= z_r; k++)
                {
                    u[0](i, j, k) = task.f(i * task.g.hx, j * task.g.hy, k * task.g.hz, 0);
                }
            }
        }

        send_recv_cube(0);

        // cout << "~~~~~~~~~~~~~~~" << endl;
        // for (int i = 0; i < recv_cubes.size(); i++)
        // {
        //     cout << recv_cubes[i].scale;
        // }
        // cout << "~~~~~~~~~~~~~~~" << endl;

#pragma omp parallel for
        for (int i = x_l; i <= x_r; i++)
        {
            for (int j = y_l; j <= y_r; j++)
            {
                for (int k = z_l; k <= z_r; k++)
                {
                    u[1](i, j, k) = u[0](i, j, k) + task.f.a_2 * task.g.tau * task.g.tau / 2.0 * laplacian(u[0], i, j, k);
                    // if (p.rank == 0)
                    // {
                    //     cout << "i = " << i << " j = " << j << " k = " << k << " u[1] = " << u[1](i, j, k) << endl;
                    // }
                }
            }
        }
    }
    void iterate_boundary(int n)
    {
        init_boundary(u[loop(n)], n * task.g.tau);
    }
    void iterate(int n)
    {
        int x_l = std::max(1, u[loop(n)].scale.x_l);
        int x_r = std::min(task.N - 1, u[loop(n)].scale.x_r);

        int y_l = std::max(1, u[loop(n)].scale.y_l);
        int y_r = std::min(task.N - 1, u[loop(n)].scale.y_r);

        int z_l = std::max(1, u[loop(n)].scale.z_l);
        int z_r = std::min(task.N - 1, u[loop(n)].scale.z_r);

        send_recv_cube(n);

#pragma omp parallel for
        for (int i = x_l; i <= x_r; i++)
        {
            for (int j = y_l; j <= y_r; j++)
            {
                for (int k = z_l; k <= z_r; k++)
                {
                    (u[loop(n + 1)])(i, j, k) = 2 * u[loop(n)](i, j, k) -
                                                u[loop(n - 1)](i, j, k) +
                                                task.f.a_2 * task.g.tau * task.g.tau * laplacian(u[loop(n)], i, j, k);
                }
            }
        }

        iterate_boundary(n + 1);
    }
    double getError()
    {
        double e = 0;

#pragma omp parallel for reduction(max : e)
        for (int i = u[0].scale.x_l; i <= u[0].scale.x_r; i++)
        {
#pragma omp parallel for reduction(max : e)
            for (int j = u[0].scale.y_l; j <= u[0].scale.y_r; j++)
            {
#pragma omp parallel for reduction(max : e)
                for (int k = u[0].scale.z_l; k <= u[0].scale.z_r; k++)
                {
                    double numerical = u[loop(task.steps)](i, j, k);
                    double analytical = task.f(i * task.g.hx, j * task.g.hy, k * task.g.hz, task.g.tau * task.steps);
                    double local_error = abs(numerical - analytical);

                    e = std::max(e, local_error);
                }
            }
        }

        double global_error = 0;
        MPI_Reduce(&e, &global_error, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);

        return global_error;
    }

public:
    ParallelSolver(Task task) : Solver(task)
    {
        u = new Cube[3];
    }

    void run() override
    {
        init();

        for (int n = 1; n < task.steps; n++)
        {
            iterate(n);
        }

        double error = getError();
        if (p.rank == 0)
        {
            Printer::print("error", error);
        }
    }

    ~ParallelSolver() override
    {
        delete[] u;
    }
};