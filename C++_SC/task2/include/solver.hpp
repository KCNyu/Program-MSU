#pragma once

#include "task.hpp"

class Solver
{
protected:
    Task task;

public:
    Solver(Task task) : task(task) {}
    virtual void run() = 0;
};