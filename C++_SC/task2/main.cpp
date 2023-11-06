#include "parser.hpp"
#include "task.hpp"
#include "serial_solver.hpp"
#include "parallel_solver.hpp"
#include "timer.hpp"

int main(int argc, char **argv)
{
#ifdef USE_MPI
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
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
#ifdef USE_MPI
        if (omp_get_thread_num() == 0 && rank == 0)
#else
        if (omp_get_thread_num() == 0)
#endif
        {
            Printer::split_line();
#ifdef USE_MPI
            Printer::print("process", size);
#endif
            Printer::print("threads", omp_get_num_threads());
            Printer::print("L", L);
            Printer::print("T", T);
            Printer::print("N", N);
            Printer::print("K", K);
            Printer::print("steps", steps);
        }
    }

#ifdef USE_MPI
    Solver *solver = new ParallelSolver(Task(L, L, L, N, T, K, steps));
#else
    Solver *solver = new SerialSolver(Task(L, L, L, N, T, K, steps));
#endif
    auto solverTask = [&]()
    { solver->run(); };

#ifdef USE_MPI
    Timer timer(true);
    timer.run(solverTask);
    if (rank == 0)
    {
        Printer::split_line();
        Printer::json();
    }
    MPI_Finalize();
#else
    Timer timer;
    timer.run(solverTask);
    Printer::split_line();
    Printer::json();
#endif

    return 0;
}