#include "pt4.h"
#include "mpi.h"
void Solve()
{
    Task("MPI2Send15");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    double A;
    int N;
    pt >> A >> N;
    if (N == rank) {
        pt << A << N;
        return;
    }
    else {
        MPI_Send(&A, 1, MPI_DOUBLE, N, 0, MPI_COMM_WORLD);
    }
    MPI_Status status;
    MPI_Recv(&A, 1, MPI_DOUBLE, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
    pt << A << status.MPI_SOURCE;
    // save to the remote repo failed...
}
