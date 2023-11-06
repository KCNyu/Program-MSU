#include "task.hpp"
#include "solver.hpp"
#include "timer.hpp"

int main(int argc, char **argv)
{
#ifdef USE_MPI
    MPI_Init(&argc, &argv);
#endif
    // omp_set_num_threads(4);

    double L = argc > 1 ? std::stod(argv[1]) : M_PI;
    double T = argc > 2 ? std::stod(argv[2]) : 1.0;
    int N = argc > 3 ? std::stoi(argv[3]) : 128;
    int K = argc > 4 ? std::stoi(argv[4]) : 1000;
    int steps = argc > 5 ? std::stoi(argv[5]) : 20;

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