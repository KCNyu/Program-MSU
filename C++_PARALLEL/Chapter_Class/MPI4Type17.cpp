#include "pt4.h"
#include "mpi.h"
int index(int i, int j, int col) {
	return i * col + j;
}
void Solve()
{
	Task("MPI4Type17");
	int flag;
	MPI_Initialized(&flag);
	if (flag == 0)
		return;
	int rank, size;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	int N;
	pt >> N;
	if (rank != 0) {
		int* row = new int[N * N];
		for (int i = 0; i < N * N; i++) pt >> row[i];
		MPI_Send(row, N * N, MPI_INT, 0, 0, MPI_COMM_WORLD);
	}
	else {
		int* mat = new int[N * N * (size - 1)];
		MPI_Datatype MPI_MAT;
		MPI_Type_vector(N, N, N*3, MPI_INT, &MPI_MAT);
		MPI_Type_commit(&MPI_MAT);
		for (int i = 1; i <= (size - 1) / 3; i++) {
			for (int j = 0; j < 3; j++) {
				MPI_Recv(mat + j * N+(i-1)*N*N*3, 1, MPI_MAT, j+3*(i-1)+1, 0, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
			}
		}
		
		int row = N * 3, col = N * (size - 1) / 3;
		// commit one more time for save in the remote repo
		/*
		for (int l = 0; l < (size - 1) / 3; l++) {
			for (int i = 0; i < N; i++) {
				for (int j = 0; j < 3; j++) {
					for (int k = 0; k < N; k++) {
						pt << mat[k + j*N*N+i*N+l*3*N*N];
					}
				}
			}
		}
		*/
		for (int i = 0; i < row * col; i++) pt << mat[i];
	}

}
