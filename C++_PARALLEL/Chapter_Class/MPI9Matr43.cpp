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
void Matr4GatherFile()
{
	c = new int[m0 * q0];
	for (int i = 0; i < m0 * q0; i++) {
		pt >> c[i];
	}
	char name[20];
	if (r == 0)
	{
		pt >> name;
	}
	MPI_Bcast(name, 20, MPI_CHAR, 0, MPI_COMM_WORLD);
	MPI_File f;
	MPI_File_open(MPI_COMM_WORLD, name,
		MPI_MODE_RDWR | MPI_MODE_CREATE, MPI_INFO_NULL, &f);


	Matr4CreateTypeBlock(m0, q0, q0 * k0, &MPI_BLOCK_C);
	char view[7] = "native";
	MPI_File_set_view(f, ((r % k0) * q0 + r / k0 * m0 * q0 * k0) * 4, MPI_INT, MPI_BLOCK_C, view,
		MPI_INFO_NULL);
	MPI_File_write_all(f, c, m0 * q0, MPI_INT, MPI_STATUSES_IGNORE);
}
void Solve()
{
	Task("MPI9Matr43");
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
	pt >> m0 >> q0;
	Matr4GatherFile();
}
