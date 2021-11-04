#include "pt4.h"
#include "mpi.h"
#include <cmath>

int k;              // number of processes
int r;              // rank of the current process

int m, p, q;        // sizes of the given matrices
int m0, p0, q0;     // sizes of the matrix blocks
int k0;             // order of the Cartesian grid (equal to sqrt(k))

int *a_, *b_, *c_;  // arrays to store matrices in the master process
int *a, *b, *c, *t; // arrays to store matrix blocks in each process

MPI_Datatype MPI_BLOCK_A; // datatype for the block of the matrix A
MPI_Datatype MPI_BLOCK_B; // datatype for the block of the matrix B
MPI_Datatype MPI_BLOCK_C; // datatype for the block of the matrix C

MPI_Comm MPI_COMM_GRID = MPI_COMM_NULL;
             // communicator associated with a two-dimensional Cartesian grid
MPI_Comm MPI_COMM_ROW = MPI_COMM_NULL;
             // communicator associated with rows of a two-dimensional grid
MPI_Comm MPI_COMM_COL = MPI_COMM_NULL;
             // communicator associated with columns of a two-dimensional grid

void Matr4CreateTypeBlock(int m0, int p0, int p, MPI_Datatype* t) 
{
    MPI_Type_vector(m0, p0, p, MPI_INT, t);
    MPI_Type_commit(t);
}
void Solve()
{
    Task("MPI9Matr32");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    k = size;
    r = rank;
    k0 = (int)floor(sqrt((double)k) + 0.1);
    pt >> m >> p;
    m0 = m / k0;
    p0 = p / k0;
    Matr4CreateTypeBlock(m0, p0, p, &MPI_BLOCK_A);
    if (rank == 0) 
    {
        a_ = new int[m * p];
        for (int i = 0; i < m * p; i++) 
        {
            pt >> a_[i];
        }
    }
    int* sendcounts = new int[k];
    int* sdispls = new int[k];
    MPI_Datatype* sendtypes = new MPI_Datatype[k];
    int* recvcounts = new int[k];
    int* rdispls = new int[k];
    MPI_Datatype* recvtypes = new MPI_Datatype[k];
    MPI_Aint lb, extent;
    MPI_Type_get_extent(MPI_INT, &lb, &extent);
    for (int i = 0; i < k; i++)
    {
        if (rank == 0)
        {
            sendcounts[i] = 1;
            sdispls[i] = ((i%k0) * p0 + i/k0 * m0 * p0 * k0)* extent;
        }
        else
        {
            sendcounts[i] = 0;            
            sdispls[i] = 0;
        }
        sendtypes[i] = MPI_BLOCK_A;
        rdispls[i] = 0;
        recvtypes[i] = MPI_INT;
        recvcounts[i] = (i == 0) ? m0 * p0 : 0;
    }
    a = new int[m0 * p0];
    MPI_Alltoallw(a_, sendcounts, sdispls, sendtypes, a, recvcounts, rdispls, recvtypes, MPI_COMM_WORLD);
    for (int i = 0; i < m0 * p0; i++) 
    {
        pt << a[i];
    }
}
