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
char name_a[20], name_b[20], name_c[20];
void Matr2ScatterFile() {
	if (r == 0) {
		pt >> m >> p >> q >> name_a >> name_b;
	}
	MPI_Bcast(name_a, 20, MPI_CHAR, 0, MPI_COMM_WORLD);
	MPI_Bcast(name_b, 20, MPI_CHAR, 0, MPI_COMM_WORLD);
	int temp[3] = { p, q, m };
	MPI_Bcast(temp, 3, MPI_INT, 0, MPI_COMM_WORLD);
	p = temp[0];
	q = temp[1];
	m = temp[2];

	na = ceil((double)m / k);
	nb = ceil((double)q / k);

	a = new int[na * p];
	b = new int[p * nb];
	c = new int[na * k * nb];
	for (int i = 0; i < na * p; ++i) a[i] = 0;
	for (int i = 0; i < p * nb; ++i) b[i] = 0;
	for (int i = 0; i < na * k * nb; ++i) c[i] = 0;

	MPI_File f_a, f_b;

	MPI_File_open(MPI_COMM_WORLD, name_a, MPI_MODE_RDWR, MPI_INFO_NULL, &f_a);
	MPI_Offset offset = r * na * p * 4;
	MPI_File_seek(f_a, offset, MPI_SEEK_SET);
	MPI_File_read_all(f_a, a, na * p, MPI_INT, MPI_STATUSES_IGNORE);

	MPI_File_open(MPI_COMM_WORLD, name_b, MPI_MODE_RDWR, MPI_INFO_NULL, &f_b);
	Matr2CreateTypeBand(p, nb, nb * k, MPI_COLS);
	MPI_File_set_view(f_b, r * nb * 4, MPI_INT, MPI_COLS, (char*)"native", MPI_INFO_NULL);
	MPI_File_read_all(f_b, b, p * nb, MPI_INT, MPI_STATUS_IGNORE);
}
void Solve()
{
    Task("MPI9Matr18");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    k = size;
    r = rank;
	Matr2ScatterFile();
	pt << na << p << nb;
	for (int i = 0; i < na * p; ++i) pt << a[i];
	for (int i = 0; i < p * nb; ++i) pt << b[i];
	for (int i = 0; i < na * k * nb; ++i) pt << c[i];
}
