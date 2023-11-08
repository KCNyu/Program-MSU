#pragma once

#include "solver.hpp"

class ParallelSolver : public Solver
{
public:
    ParallelSolver(Task task) : Solver(task)
    {
    }

    void run() override
    {
    }

    ~ParallelSolver() override {}
};