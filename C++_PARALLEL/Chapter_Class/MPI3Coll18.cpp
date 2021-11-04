#include "pt4.h"
#include "mpi.h"
void Solve()
{
    Task("MPI3Coll18");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    double* recvBuf = new double[size * 2];
    double* sendBuf = new double[size + 1];
    int* sendCount = new int[size];
    int* recvCount = new int[size];
    int* rdispls = new int[size];
    int* sdispls = new int[size];
    for (int i = 0; i < size; i++) {
        sendCount[i] = 2;
        recvCount[i] = 2;
        rdispls[i] = i * 2;
        sdispls[i] = size - i - 1;
    }
    for (int i = 0; i < size + 1; i++) {
        pt >> sendBuf[i];
    }
    MPI_Alltoallv(sendBuf, sendCount, sdispls, MPI_DOUBLE, recvBuf, recvCount, rdispls, MPI_DOUBLE, MPI_COMM_WORLD);
    for (int i = 0; i < size * 2; i++) {
        pt << recvBuf[i];
    }
}
