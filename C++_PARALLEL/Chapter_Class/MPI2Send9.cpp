#include "pt4.h"
#include "mpi.h"
void Solve()
{
    Task("MPI2Send9");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int N;
    const int MAX_NUM = 100;
    double numbers[MAX_NUM];
    if (rank != 0) {  
        pt >> N;
        if (N == 0) return;
        for (int i = 0; i < N; i++) {
            pt >> numbers[i];
        }
        MPI_Send(numbers, N, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
    }
    else {
        MPI_Status status;
        MPI_Recv(numbers, MAX_NUM, MPI_DOUBLE, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
        int count;
        MPI_Get_count(&status, MPI_DOUBLE, &count);
        ShowLine(count);
        for (int i = 0; i < count; i++) {
            pt << numbers[i];
        }
        pt << status.MPI_SOURCE;
        ShowLine(status.MPI_SOURCE);
    }
}
