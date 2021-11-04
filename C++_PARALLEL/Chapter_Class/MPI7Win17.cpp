#include "pt4.h"
#include "mpi.h"
void Solve()
{
	Task("MPI7Win17");
	int flag;
	MPI_Initialized(&flag);
	if (flag == 0)
		return;
	int rank, size;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	double* A = new double[size];
	double* B = new double[size];
	for (int i = 0; i < size; i++) pt >> A[i];
	pt >> B[0];
	for (int i = 0; i < size; i++) B[i] = B[0];
	MPI_Win window;
	MPI_Win_create(A, 8 * size, 8, MPI_INFO_NULL, MPI_COMM_WORLD, &window);
	MPI_Win_fence(0, window);
	MPI_Accumulate(B, size, MPI_DOUBLE, (rank - 1 + size) % size, 0, size, MPI_DOUBLE, MPI_MIN, window);
	MPI_Win_fence(0, window);
	for (int i = 0; i < size; i++) {
		//for (int j = 0; j < size; j++) {
		if (rank == 0) continue;
			MPI_Accumulate(A, 1, MPI_DOUBLE, i, rank, 1, MPI_DOUBLE, MPI_SUM, window);
		//}
	}
	MPI_Win_fence(0, window);
	for (int i = 0; i < size; i++) pt << A[i];
}
