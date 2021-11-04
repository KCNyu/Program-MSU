#include "pt4.h"
#include "mpi.h"
void Solve()
{
    Task("MPI2Send21");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (rank != 0) {
        int L, N;
        double A;
        pt >> L;
        for (int i = 0; i < L; i++) {
            pt >> A >> N;
            MPI_Send(&A, 1, MPI_DOUBLE, 0, N, MPI_COMM_WORLD);
        }
    }
    else {
        double res;
        for (int i = 1; i <= size * 2; i++) {
            MPI_Recv(&res, 1, MPI_DOUBLE, MPI_ANY_SOURCE, i, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
            pt << res;
        }
    }
}
