#include "pt4.h"
#include "mpi.h"
#include <cmath>

int k;              // number of processes
int r;              // rank of the current process

int m, p, q;        // sizes of the given matrices
int m0, p0, q0;     // sizes of the matrix blocks
int k0;             // order of the Cartesian grid (equal to sqrt(k))

int* a_, * b_, * c_;  // arrays to store matrices in the master process
int* a, * b, * c, * t; // arrays to store matrix blocks in each process

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
void Matr4ScatterData()
{
	if (r == 0)
	{
		pt >> m >> p >> q;
	}
	int sz[3] = { m,p,q };
	MPI_Bcast(sz, 3, MPI_INT, 0, MPI_COMM_WORLD);
	m = sz[0]; p = sz[1]; q = sz[2];
	m0 = ceil(m * 1.0 / k0); p0 = ceil(p * 1.0 / k0); q0 = ceil(q * 1.0 / k0);
	a = new int[m0 * p0];
	b = new int[p0 * q0];
	c = new int[m0 * q0];
	t = new int[m0 * p0];

	a_ = new int[m0 * k0 * p0 * k0];
	b_ = new int[p0 * k0 * q0 * k0];
	if (r == 0)
	{
		for (int i = 0; i < m0 * k0; i++) {
			for (int j = 0; j < p0 * k0; j++) {
				if (i < m && j < p) pt >> a_[j + i * p0 * k0];
				else a_[j + i * p0 * k0] = 0;
			}
		}
		for (int i = 0; i < p0 * k0; i++) {
			for (int j = 0; j < q0 * k0; j++) {
				if (i < p && j < q) pt >> b_[j + i * q0 * k0];
				else b_[j + i * q0 * k0] = 0;
			}
		}
	}
	Matr4CreateTypeBlock(m0, p0, p0 * k0, &MPI_BLOCK_A);
	Matr4CreateTypeBlock(p0, q0, q0 * k0, &MPI_BLOCK_B);
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
		if (r == 0)
		{
			sendcounts[i] = 1;
			sdispls[i] = ((i % k0) * p0 + i / k0 * m0 * p0 * k0) * extent;
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
	MPI_Alltoallw(a_, sendcounts, sdispls, sendtypes, a, recvcounts, rdispls, recvtypes, MPI_COMM_WORLD);
	for (int i = 0; i < k; i++)
	{
		if (r == 0)
		{
			sendcounts[i] = 1;
			sdispls[i] = ((i % k0) * q0 + i / k0 * p0 * q0 * k0) * extent;
		}
		else
		{
			sendcounts[i] = 0;
			sdispls[i] = 0;
		}
		sendtypes[i] = MPI_BLOCK_B;
		rdispls[i] = 0;
		recvtypes[i] = MPI_INT;
		recvcounts[i] = (i == 0) ? p0 * q0 : 0;
	}
	MPI_Alltoallw(b_, sendcounts, sdispls, sendtypes, b, recvcounts, rdispls, recvtypes, MPI_COMM_WORLD);
}
void Solve()
{
	Task("MPI9Matr35");
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


	Matr4ScatterData();
	pt << m0 << p0 << q0;

	for (int i = 0; i < m0 * p0; i++) {
		pt << a[i];
	}
	for (int i = 0; i < p0 * q0; i++) {
		pt << b[i];
	}
	for (int i = 0; i < m0 * q0; i++) {
		c[i] = 0;
		pt << c[i];
	}
	for (int i = 0; i < m0 * p0; i++) {
		t[i] = 0;
		pt << t[i];
	}
}
