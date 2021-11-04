#include "pt4.h"
#include "mpi.h"
void Solve()
{
    Task("MPI8Inter9");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm peer;
    MPI_Comm_dup(MPI_COMM_WORLD, &peer);
    int c;
    MPI_Comm local;
    pt >> c;
    if (c == 0)
        c = MPI_UNDEFINED;
    MPI_Comm_split(MPI_COMM_WORLD, c, rank, &local);
    if (local == MPI_COMM_NULL)
    {
        pt << -1;
        return;
    }
    int local_rank;
    MPI_Comm_rank(local, &local_rank);
    pt << local_rank;
    MPI_Comm inter;
    int lead = 0;
    if (rank == 0)
        lead = size / 2;
    MPI_Intercomm_create(local, 0, peer, lead, 100, &inter);
    int remote_size;
    MPI_Comm_remote_size(inter, &remote_size);
    Show(remote_size);
}
