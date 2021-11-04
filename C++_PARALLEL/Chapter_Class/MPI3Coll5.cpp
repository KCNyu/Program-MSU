#include "pt4.h"
#include "mpi.h"
void Solve()
{
    Task("MPI3Coll5");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    const int n = rank + 2;
    int* isend = new int[n];
    int* ircnt = new int[size];
    for (int i = 0; i < n; i++) {
        pt >> isend[i];
    }
    for (int i = 0; i < size; i++) {
        ircnt[i] = i + 2;
    }
    int* irecv = new int[size *(size+1)/2+size];

    int* idisp = new int[size];
    idisp[0] = 0;
    for (int i = 1; i < size; i++) {
        idisp[i] = idisp[i - 1] + i + 1;
        ShowLine(idisp[i]);
    }
    int iscnt = n;
    MPI_Gatherv(isend, iscnt, MPI_INT, irecv, ircnt, idisp,
        MPI_INT, 0, MPI_COMM_WORLD);
    if (rank == 0) {
        for (int i = 0; i < size * (size + 1) / 2 + size; i++)  pt << irecv[i];
    }
   
}
