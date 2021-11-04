#include "pt4.h"
#include "mpi.h"
void Solve()
{
    Task("MPI2Send14");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int n1, n2, res1, res2;
    if (rank != 0) {
        MPI_Recv(&res1, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
        pt << res1;
    }
    pt >> n1 >> n2;
    MPI_Ssend(&n2, 1, MPI_INT, (rank + 1) % size, 0, MPI_COMM_WORLD);
    if (rank == 0) {
        MPI_Recv(&res1, 1, MPI_INT, size - 1, 0, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
        pt << res1;
        MPI_Ssend(&n1, 1, MPI_INT, size - 1, 0, MPI_COMM_WORLD);
        MPI_Recv(&res2, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
        pt << res2;
    }
    else{
        MPI_Recv(&res2, 1, MPI_INT, (rank + 1) % size, 0, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
        pt << res2;
        MPI_Ssend(&n1, 1, MPI_INT, (rank - 1) % size, 0, MPI_COMM_WORLD);
    }
    
}
