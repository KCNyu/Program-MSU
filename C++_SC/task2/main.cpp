#include "parser.hpp"
#include "task.hpp"
#include "solver.hpp"
#include "timer.hpp"

int main(int argc, char **argv)
{
#ifdef USE_MPI
    MPI_Init(&argc, &argv);
#endif
    // omp_set_num_threads(4);

    Parser parser(argc, argv);
    double L = parser.getL();
    double T = parser.getT();
    int N = parser.getN();
    int K = parser.getK();
    int steps = parser.getSteps();

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

    return 0;
}