#include "pt4.h"
#include "mpi.h"
void Solve()
{
    Task("MPI1Proc9");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int n;
    GetN(n);
    double num, sum = 0, mult = 1;
    for (int i = 0; i < n; i++) {
        GetD(num);
        sum += num;
        if (rank == 0) {
            mult *= num;
        }
    }
    if (rank == 0) {
        PutD(mult);
        return;
    }
    if (rank % 2 == 1) {
        sum /= n;
    }
    PutD(sum);
}
