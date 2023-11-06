#include "parser.hpp"
#include "task.hpp"
#include "solver.hpp"
#include "timer.hpp"

int main(int argc, char **argv)
{
#ifdef USE_MPI
    MPI_Init(&argc, &argv);
#endif
    // omp_set_num_threads(2);

    Parser parser(argc, argv);
    double L = parser.getL();
    double T = parser.getT();
    int N = parser.getN();
    int K = parser.getK();
    int steps = parser.getSteps();

#pragma omp parallel
    {
        if (omp_get_thread_num() == 0)
        {
            Printer::split_line();
            Printer::print("threads", omp_get_num_threads());
            Printer::print("L", L);
            Printer::print("T", T);
            Printer::print("N", N);
            Printer::print("K", K);
            Printer::print("steps", steps);
        }
    }

    Solver solver(Task(L, L, L, N, T, K, steps));
    auto solverTask = [&]()
    { solver.run(); };

#ifdef USE_MPI
    Timer timer(true);
    timer.run(solverTask);

    MPI_Finalize();
#else
    Timer timer;
    timer.run(solverTask);
#endif
    Printer::split_line();
    Printer::json();
    return 0;
}