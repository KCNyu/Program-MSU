#include "pt4.h"
#include "mpi.h"
#include <cmath>

int k;              // number of processes
int r;              // rank of the current process

int m, p, q;        // sizes of the given matrices
int na, nb;         // sizes of the matrix bands

int *a_, *b_, *c_;  // arrays to store matrices in the master process
int *a, *b, *c;     // arrays to store matrix bands in each process

MPI_Datatype MPI_COLS; // datatype for the band of the matrix B

void Solve()
{
    Task("MPI9Matr19");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    k = size;
    r = rank;

}
