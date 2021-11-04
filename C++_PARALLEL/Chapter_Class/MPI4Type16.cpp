#include "pt4.h"
#include "mpi.h"
void Solve()
{
	Task("MPI4Type16");
	int flag;
	MPI_Initialized(&flag);
	if (flag == 0)
		return;
	int rank, size;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	int K = size - 1;

	if (rank != 0) {
		double* B = new double[K];
		for (int i = 0; i < K; i++) {
			pt >> B[i];
		}
		MPI_Send(B, K, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
	}
	else {
		double* A = new double[K * K];
		MPI_Datatype MPI_ROW, MPI_ROW_NEW;
		MPI_Type_create_resized(MPI_DOUBLE, 0, 8 * K, &MPI_ROW);
		MPI_Type_commit(&MPI_ROW);
		MPI_Type_contiguous(K, MPI_ROW, &MPI_ROW_NEW);
		MPI_Type_commit(&MPI_ROW_NEW);

		for (int i = 1; i < size; i++) {
			MPI_Recv(A + i-1, 1, MPI_ROW_NEW, i, 0, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
		}
		for (int i = 0; i < K * K; i++) {
			pt << A[i];
		}
	}
}
