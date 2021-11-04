#include "pt4.h"
#include "mpi.h"
void Solve()
{
	Task("MPI4Type22");
	int flag;
	MPI_Initialized(&flag);
	if (flag == 0)
		return;
	int rank, size;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	int K = size - 1;
	double* B = new double[K];
	double* A = new double[K * K];

	int* sendcounts = new int[size];
	int* sdispls = new int[size];
	int* recvcounts = new int[size];
	int* rdispls = new int[size];

	MPI_Datatype MPI_ROW, MPI_ROW_NEW;
	MPI_Type_create_resized(MPI_DOUBLE, 0, 8 * K, &MPI_ROW);
	MPI_Type_commit(&MPI_ROW);
	MPI_Type_contiguous(K, MPI_ROW, &MPI_ROW_NEW);
	MPI_Type_commit(&MPI_ROW_NEW);
	MPI_Datatype* sendtype = (MPI_Datatype*)malloc(sizeof(MPI_Datatype) * size);
	MPI_Datatype* recvtype = (MPI_Datatype*)malloc(sizeof(MPI_Datatype) * size);
	for (int i = 0; i < size; i++) {
		sendtype[i] = MPI_DOUBLE;
		recvtype[i] = MPI_ROW_NEW;
	}
	if (rank != 0) {
		for (int i = 0; i < K; i++) {
			pt >> B[i];
		}
		for (int i = 0; i < size; i++) {
			if (i == 0) sendcounts[i] = K;
			else sendcounts[i] = 0;
			sdispls[i] = 0;
			recvcounts[i] = 0;
			rdispls[i] = 0;
		}
		//MPI_Send(B, K, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
	}
	else {
		/*
		MPI_Datatype MPI_ROW, MPI_ROW_NEW;
		MPI_Type_create_resized(MPI_DOUBLE, 0, 8 * K, &MPI_ROW);
		MPI_Type_commit(&MPI_ROW);
		MPI_Type_contiguous(K, MPI_ROW, &MPI_ROW_NEW);
		MPI_Type_commit(&MPI_ROW_NEW);
		*/

		/*
		for (int i = 1; i < size; i++) {
			MPI_Recv(A + i-1, 1, MPI_ROW_NEW, i, 0, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
		}
		*/
		for (int i = 0; i < size; i++) {
			if (i == 0) {
				recvcounts[i] = 0;
				rdispls[i] = 0;
			}
			else {
				recvcounts[i] = 1;
				rdispls[i] = (i - 1)*8;
			}
			sendcounts[i] = 0;
			sdispls[i] = 0;
		}
	}

	MPI_Alltoallw(B, sendcounts, sdispls, sendtype, A, recvcounts, rdispls, recvtype, MPI_COMM_WORLD);
	if (rank == 0) {
		for (int i = 0; i < K * K; i++) {
			pt << A[i];
		}
	}
}