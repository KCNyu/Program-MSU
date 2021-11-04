#include "pt4.h"
#include "mpi.h"
void Solve()
{
    Task("MPI5Comm26");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    double send[1];
    pt >> send[0];

    int dims[2] = { 2, size/2 };
    int periods[2] = { true, true };
    int reorder = false;
    MPI_Comm cartesian_communicator;
    MPI_Cart_create(MPI_COMM_WORLD, 2, dims, periods, reorder, &cartesian_communicator);
    int neigbours_ranks[2];
    MPI_Cart_shift(cartesian_communicator, 1, 1, &neigbours_ranks[0], &neigbours_ranks[1]);
    ShowLine("left: ", neigbours_ranks[0]);
    ShowLine("right: ", neigbours_ranks[1]);
    double recv[1];
    MPI_Sendrecv(send, 1, MPI_DOUBLE, neigbours_ranks[1], 0, recv, 1, MPI_DOUBLE, neigbours_ranks[0], 0, cartesian_communicator, MPI_STATUSES_IGNORE);
    pt << recv[0];
}
