#include "pt4.h"
#include "mpi.h"
void Solve()
{
    Task("MPI7Win6");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    double* A = new double[2 * size - 3];
    double* B = new double[rank];
    if (rank == 0) {
        for (int i = 0; i < 2 * size - 3; i++) pt >> A[i];
    }
    else {
        for (int i = 0; i < rank; i++) pt >> B[i];
    }
    MPI_Win window;
    MPI_Win_create(A, 8 * (2*size - 3), 8, MPI_INFO_NULL, MPI_COMM_WORLD, &window);
    MPI_Win_fence(0, window);
    if (rank != 0) {
        MPI_Accumulate(B, rank, MPI_DOUBLE, 0, rank - 1, rank, MPI_DOUBLE, MPI_SUM, window);
    }
    MPI_Win_fence(0, window);
    if (rank == 0) {
        for (int i = 0; i < 2*size - 3; i++) pt << A[i];
    }
    // try one 
}
