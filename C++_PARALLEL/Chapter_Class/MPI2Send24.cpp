#include "pt4.h"
#include "mpi.h"

#define MAX_NUM 100
template <typename T>
void sendrecv(int rank, int size, MPI_Datatype d, int step)
{
    T nums[MAX_NUM];
    for (int i = 0; i < size / 2; i++) {
        pt >> nums[i];
    }
    MPI_Send(nums, size / abs(step), d, (rank + step + size) % size, 0, MPI_COMM_WORLD);
    ShowLine((rank + step + size) % size);
    MPI_Recv(nums, size / abs(step), d, (rank - step + size) % size, 0, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
    ShowLine((rank + step + size) % size);
    for (int i = 0; i < size / 2; i++) {
        pt << nums[i];
    }
}
void Solve()
{
    Task("MPI2Send24");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);   
    if (rank % 2 == 0) {
        sendrecv<double>(rank, size, MPI_DOUBLE, 2);
    }
    else {
        sendrecv<int>(rank, size, MPI_INT, -2);
    }
}
