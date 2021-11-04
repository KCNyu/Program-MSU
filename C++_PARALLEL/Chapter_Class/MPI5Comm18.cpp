#include "pt4.h"
#include "mpi.h"
void Solve()
{
    Task("MPI5Comm18");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int N = size / 3;
    int* sendBuf = new int[N];
    if (rank < 3) {
        for (int i = 0; i < N; i++) {
            pt >> sendBuf[i];
        }
    }
    int dims[2] = { size / 3, 3 };
    int periods[2] = { true, true };
    int reorder = true;
    MPI_Comm cartesian_communicator;
    MPI_Cart_create(MPI_COMM_WORLD, 2, dims, periods, reorder, &cartesian_communicator);
    
    int remain_dims[2] = { true, false };
    MPI_Comm subgrid_communicator;
    MPI_Cart_sub(cartesian_communicator, remain_dims, &subgrid_communicator);
    int my_rank;
    MPI_Comm_rank(subgrid_communicator, &my_rank);
    int recvBuf[1];
    if (my_rank == 0) {
        MPI_Scatter(sendBuf, 1, MPI_INT, recvBuf, 1, MPI_INT, 0, subgrid_communicator);
    }
    else {
        MPI_Scatter(NULL, 1, MPI_INT, recvBuf, 1, MPI_INT, 0, subgrid_communicator);
    }
    pt << recvBuf[0];
    
}
