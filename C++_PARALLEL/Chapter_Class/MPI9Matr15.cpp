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

void Matr2CreateTypeBand(int p, int n, int q, MPI_Datatype& t) {
	MPI_Type_vector(p, n, q, MPI_INT, &t);
	MPI_Type_commit(&t);
}
void Matr2Calc(int step) {
	int h = r + step >= k ? -1 * na * nb * (k - step) : na * nb * step;
	for (int i = 0; i < na; i++) {
		for (int j = 0; j < nb; j++) {
			c[na * nb * r + h + i * nb + j] = 0;
			for (int k = 0; k < p; k++) {
				c[na * nb * r + h + i * nb + j] += a[k + i * p] * b[j + k * nb];
			}
		}
	}
	MPI_Sendrecv_replace(a, na * p, MPI_INT, (r - 1 + k) % k, 0, (r + 1) % k, 0, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
}
void Solve()
{
    Task("MPI9Matr15");
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
	int sz_a = na * p,
		sz_b = nb * p,
		sz_c = na * k * nb;
	a = new int[sz_a];
	b = new int[sz_b];
	c = new int[sz_c];
	for (int i = 0; i < sz_a; ++i) {
		pt >> a[i];
	}
	for (int i = 0; i < sz_b; ++i) {
		pt >> b[i];
	}
	for (int i = 0; i < sz_c; ++i) {
		pt >> c[i];
	} 
	int l;
	pt >> l;
	for (int i = 0; i < l; ++i) {
		Matr2Calc(i);
	}
	for (int i = 0; i < sz_c; ++i) {
		pt << c[i];
	}
	for (int i = 0; i < sz_a; ++i) {
		pt << a[i];
	}
}
