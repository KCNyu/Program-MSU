#include "pt4.h"
#include "mpi.h"
void Solve()
{
    Task("MPI5Comm13");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);        
    int N;
    if (rank == 0) {

        pt >> N;
    }
    MPI_Bcast(&N, 1, MPI_INT, 0, MPI_COMM_WORLD);
    int dims[2] = { N, size / N };

    ShowLine("dims[0] = ", dims[0]);
    ShowLine("dims[1] = ", dims[1]);

    int periods[2] = { true, true };
    int reorder = true;
    MPI_Comm new_comm;
    MPI_Cart_create(MPI_COMM_WORLD, 2, dims, periods, reorder, &new_comm);
    int new_rank;
    MPI_Comm_rank(new_comm, &new_rank);
    int my_coords[2];
    MPI_Cart_coords(new_comm, new_rank, 2, my_coords);
    pt << my_coords[0] << my_coords[1];
}
