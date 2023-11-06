#pragma once

#include <chrono>
#include <functional>
#ifdef USE_MPI
#include <mpi.h>
#endif
#include <iostream>

class Timer
{
private:
    std::chrono::steady_clock::time_point _start;
    std::chrono::steady_clock::time_point _end;

    bool _isMPI;
    double _mpi_start;
    double _mpi_end;

public:
    Timer(const bool isMPI = false) : _isMPI(isMPI) {}
    void start()
    {
        if (_isMPI)
        {
#ifdef USE_MPI
            _mpi_start = MPI_Wtime();
#endif
        }
        else
        {
            _start = std::chrono::steady_clock::now();
        }
    }
    void end()
    {
        if (_isMPI)
        {
#ifdef USE_MPI
            _mpi_end = MPI_Wtime();
#endif
        }
        else
        {
            _end = std::chrono::steady_clock::now();
        }
    }
    void run(const std::function<void()> &task)
    {
        start();
        task();
        end();
        if (_isMPI)
        {
#ifdef USE_MPI
            auto duration = _mpi_end - _mpi_start;
            double max_duration;
            MPI_Reduce(&duration, &max_duration, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);

            int rank;
            MPI_Comm_rank(MPI_COMM_WORLD, &rank);
            if (rank == 0)
            {
                std::cout << "MPI time : " << max_duration << std::endl;
            }
#endif
        }
        else
        {
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(_end - _start);
            std::cout << "time : " << duration.count() / 1000000.0 << std::endl;
        }
    }
};