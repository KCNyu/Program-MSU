#include "pt4.h"
#include "mpi.h"
#include <cmath>

int k;              // number of processes
int r;              // rank of the current process

int m, p, q;        // sizes of the given matrices
int na, nb;         // sizes of the matrix bands

int* a_, * b_, * c_;  // arrays to store matrices in the master process
int* a, * b, * c;     // arrays to store matrix bands in each process

MPI_Datatype MPI_COLS; // datatype for the band of the matrix B

MPI_Datatype MPI_BAND_B;
MPI_Datatype MPI_BAND_C;

void Matr2CreateTypeBand(int p, int n, int q, MPI_Datatype* t) {
	MPI_Type_vector(p, n, q, MPI_INT, t);
	MPI_Type_commit(t);
}
void Matr2ScatterData()
{
	int rank, k;
	MPI_Comm_size(MPI_COMM_WORLD, &k);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	int nums[3];
	if (rank == 0) {
		pt >> m >> p >> q;
		na = ceil(m / (double)k);
		nb = ceil(q / (double)k);
		nums[0] = na;
		nums[1] = p;
		nums[2] = nb;
		a_ = new int[na * k * p];
		b_ = new int[nb * k * p];
		for (int i = 0; i < m * p; i++) {
			pt >> a_[i];
		}
		for (int i = m * p; i < na * k * p; i++) {
			a_[i] = 0;
		}
		for (int i = 0; i < p; i++) {
			for (int j = 0; j < q; j++) {
				pt >> b_[i * nb * k + j];
			}
			for (int j = q; j < nb * k; j++) {
				b_[i * nb * k + j] = 0;
			}
		}
	}
	MPI_Bcast(nums, 3, MPI_INT, 0, MPI_COMM_WORLD);
	if (rank != 0) {
		na = nums[0];
		p = nums[1];
		nb = nums[2];
	}
	a = new int[na * p];
	b = new int[p * nb];
	c = new int[na * k * nb];
	MPI_Scatter(a_, na * p, MPI_INT, a, na * p, MPI_INT, 0, MPI_COMM_WORLD);
	Matr2CreateTypeBand(p, nb, nb * k, &MPI_BAND_B);
	if (rank == 0) {
		for (int i = 0; i < k; i++) {
			if (i == 0) MPI_Sendrecv(b_, 1, MPI_BAND_B, 0, 0, b, p * nb, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
			else MPI_Send(&b_[i * nb], 1, MPI_BAND_B, i, 0, MPI_COMM_WORLD);

		}
	}
	else
	{
		MPI_Recv(b, p * nb, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	}
	for (int i = 0; i < na * k * nb; i++) {
		c[i] = 0;
	}
}
void Matr2Calc(int step)
{
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
void Matr2GatherData()
{
	Matr2CreateTypeBand(na * k, nb, nb * k, &MPI_BAND_C);
	if (r == 0) {
		c_ = new int[na * k * nb * k];
		MPI_Sendrecv(c, na * k * nb, MPI_INT, 0, 0, c_, 1, MPI_BAND_C, 0, 0, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
	}
	else MPI_Send(c, na * k * nb, MPI_INT, 0, 0, MPI_COMM_WORLD);
	if (r == 0) {
		for (int i = 1; i < k; i++) {
			MPI_Recv(&c_[i * nb], 1, MPI_BAND_C, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		}
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < q; j++) {
				pt << c_[i * nb * k + j];
			}
		}
	}
}
void Solve()
{
	Task("MPI9Matr17");
	int flag;
	MPI_Initialized(&flag);
	if (flag == 0)
		return;
	int rank, size;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	k = size;
	r = rank;
	Matr2ScatterData();
	for (int i = 0; i < k; i++)
	{
		Matr2Calc(i);
		for (int i = 0; i < na * k * nb; i++) {
			pt << c[i];
		}
	}
	Matr2GatherData();
}
