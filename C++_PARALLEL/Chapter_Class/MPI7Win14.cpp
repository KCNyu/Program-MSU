#include "pt4.h"
#include "mpi.h"
void Solve()
{
	Task("MPI7Win14");
	int flag;
	MPI_Initialized(&flag);
	if (flag == 0)
		return;
	int rank, size;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	double* A = new double[size];
	double* window_buffer = new double[size];
	for (int i = 0; i < size; i++) {
		pt >> A[i];
	}
	MPI_Win window;

		MPI_Win_create(A, 8 * size, 8, MPI_INFO_NULL, MPI_COMM_WORLD, &window);
		MPI_Win_fence(0, window);

	for (int i = 0; i < size; i++) {
		MPI_Get(window_buffer + i, 1, MPI_DOUBLE, i, rank, 1, MPI_DOUBLE, window);
	}
	MPI_Win_fence(0, window);
	for (int i = 0; i < size; i++) {
		pt << window_buffer[i];
	}
}
