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

    std::function<void()> _task;

public:
    Timer(const std::function<void()> &task, const bool isMPI = false) : _task(task), _isMPI(isMPI)
    {
    }
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
    void run()
    {
        start();
        _task();
        end();
        if (_isMPI)
        {
            auto duration = _mpi_end - _mpi_start;
            std::cout << "MPI time : " << duration << std::endl;
        }
        else
        {
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(_end - _start);
            std::cout << "time : " << duration.count() / 1000000.0 << std::endl;
        }
    }
};