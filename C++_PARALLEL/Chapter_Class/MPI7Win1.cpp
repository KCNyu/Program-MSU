#include "pt4.h"
#include "mpi.h"
void Solve()
{
    Task("MPI7Win1");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    int* window_buffer = new int[size-1];
    if (rank != 0) {
        pt >> window_buffer[rank - 1];
    }
    MPI_Win window;
    MPI_Win_create(window_buffer, 4*(size-1), 4, MPI_INFO_NULL, MPI_COMM_WORLD, &window);
    MPI_Win_fence(0, window);
    if (rank != 0) {
        MPI_Put(window_buffer + rank - 1, 1, MPI_INT, 0, rank-1, 1, MPI_INT, window);
    }
    MPI_Win_fence(0, window);
    if (rank == 0) {
        for (int i = 0; i < size - 1; i++) pt << window_buffer[i];
    }
    // try
}
