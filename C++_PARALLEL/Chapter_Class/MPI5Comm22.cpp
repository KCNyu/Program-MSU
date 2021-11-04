#include "pt4.h"
#include "mpi.h"
void Solve()
{
    Task("MPI5Comm22");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    double sendBuf[1];
    pt >> sendBuf[0];
    int dims[3] = { 2,2,size / 4 };
    int periods[3] = { true,true,true };
    int reorder = false;
    MPI_Comm cartesian_communicator;
    MPI_Cart_create(MPI_COMM_WORLD, 3, dims, periods, reorder, &cartesian_communicator);

    int remain_dims[3] = { true, true, false};
    MPI_Comm subgrid_communicator;
    MPI_Cart_sub(cartesian_communicator, remain_dims, &subgrid_communicator);
    int my_rank, my_size;
    MPI_Comm_rank(subgrid_communicator, &my_rank);
    MPI_Comm_size(subgrid_communicator, &my_size);
    double result[1];
    int* counts = new int[my_size];
    for (int i = 0; i < my_size; i++) {
        counts[i] = 1;
    }
    MPI_Reduce_scatter(sendBuf, result, counts, MPI_DOUBLE, MPI_SUM, subgrid_communicator);
    MPI_Bcast(result, 1, MPI_DOUBLE, 0, subgrid_communicator);
    pt << result[0];
    // try one more time to remote 
    // test
}
