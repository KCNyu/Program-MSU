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
void Matr2Calc(int step) {
    int sum;
    for (int i = 0; i < na; i++) {
        for (int j = 0; j < nb; j++) {
            sum = 0;
            for (int k = 0; k < p; k++) {
                sum += a[i * p + k] * b[k * nb + j];
            }
            c[(r + k + step) % k * na * nb + i * nb + j] = sum;
        }
    }
    MPI_Sendrecv_replace(a, na * p, MPI_INT, (r + k - 1) % k, 0, (r + k + 1) % k, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
}
void Solve()
{
    Task("MPI9Matr14");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    k = size;
    r = rank;
    pt >> na >> p >> nb;
    a = new int[na * p];
    b = new int[p * nb];
    c = new int[na * k * nb];
    for (int i = 0; i < na * p; i++) {
        pt >> a[i];
    }
    for (int i = 0; i < p * nb; i++) {
        pt >> b[i];
    }
    for (int i = 0; i < na * k * nb; i++) {
        pt >> c[i];
    }
    Matr2Calc(0);
    Matr2Calc(1);
    for (int i = 0; i < na * k * nb; i++) {
        pt << c[i];
    }
    for (int i = 0; i < na * p; i++) {
        pt << a[i];
    }
}
