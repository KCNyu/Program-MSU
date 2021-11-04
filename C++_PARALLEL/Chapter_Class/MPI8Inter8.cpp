#include "pt4.h"
#include "mpi.h"
void Solve()
{
    Task("MPI8Inter8");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm peer;
    MPI_Comm_dup(MPI_COMM_WORLD, &peer);
    int C;
    pt >> C;
    MPI_Comm comm1;
    MPI_Comm_split(MPI_COMM_WORLD, rank % 2, rank, &comm1);
    int R1;
    MPI_Comm_rank(comm1, &R1);
    pt << R1;
    int lead = 0;
    if (rank == 0)
    {
        lead = 1;
    }
    MPI_Comm inter;
    MPI_Intercomm_create(comm1, 0, peer, lead, 100, &inter);
    int inter_rank;
    MPI_Comm_rank(inter, &inter_rank);
    MPI_Comm comm2;
    MPI_Comm_split(inter, C, inter_rank, &comm2);
    int R2;
    MPI_Comm_rank(comm2, &R2);
    pt << R2;
    int remote_size;
    MPI_Comm_remote_size(comm2, &remote_size);
    Show(remote_size);
    
    int buf;
    pt >> buf;
    for (int i = 0; i < remote_size; i++)
    {
        MPI_Send(&buf, 1, MPI_INT, i, 0, comm2);
        int res;
        MPI_Recv(&res, 1, MPI_INT, i, 0, comm2, MPI_STATUSES_IGNORE);
        pt << res;
    }
    
}
