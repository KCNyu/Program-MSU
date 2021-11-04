#include "pt4.h"
#include "mpi.h"
void Solve()
{
    Task("MPI7Win7");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int* A = new int[(size-1) * 2];
    if (rank == 0) {
        for(int i = 0; i < (size-1)*2; i++)
        pt >> A[i];
    }
    MPI_Win window;
    int window_buffer[2];
    MPI_Win_create(window_buffer, 4 * 2, 4, MPI_INFO_NULL, MPI_COMM_WORLD, &window);
    MPI_Win_fence(0, window);
    if (rank == 0) {
        for (int i = 1; i < size; i++) {
            MPI_Put(A+(i-1)*2, 2, MPI_INT, i, 0, 2, MPI_INT, window);
        }
    }
    MPI_Win_fence(0, window);
    if (rank != 0) {
        for (int i = 0; i < 2; i++) pt << window_buffer[i];
    }
}
