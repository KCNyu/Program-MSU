#include "pt4.h"
#include "mpi.h"
void Solve()
{
    Task("MPI3Coll25");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    double* nums = new double[size * 2];
    for (int i = 0; i < size * 2; i++) {
        pt >> nums[i];
    }
    int* counts = new int[size];
    for (int i = 0; i < size; i++) {
        counts[i] = 2;
    }
    double result[2];
    MPI_Reduce_scatter(nums, result, counts, MPI_DOUBLE, MPI_MAX, MPI_COMM_WORLD);
    pt << result[0] << result[1];
}
