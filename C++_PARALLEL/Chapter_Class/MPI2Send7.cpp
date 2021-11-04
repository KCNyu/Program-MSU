#include "pt4.h"
#include "mpi.h"
void Solve()
{
    Task("MPI2Send7");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int N;
    double num;
    const int MAX_NUM = 10;
    if (rank == 0) {
        pt >> N;
        for (int i = 1; i <= N; i++) {
            if (i < size-1) { 
                pt >> num;
                MPI_Send(&num, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD);
            }
            else {
                double numbers[MAX_NUM];
                for (int i = 0; i <= N - size + 1; i++) {
                    pt >> numbers[i];
                }
                MPI_Send(numbers, N-size+2, MPI_DOUBLE, size - 1, 0, MPI_COMM_WORLD);
                break;
            }
        }
    }
    else {
        int count;
        double nums[MAX_NUM];
        MPI_Status status;
        MPI_Recv(nums, MAX_NUM, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, &status);
        MPI_Get_count(&status, MPI_DOUBLE, &count);
        ShowLine("count = ", count);
        for (int i = 0; i < count; i++) {
            pt << nums[i];
        }
    }
}
