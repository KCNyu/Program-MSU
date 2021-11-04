#include "pt4.h"
#include "mpi.h"
void Print_comm(MPI_Comm new_comm, int A) {
	int new_rank, new_size;
	MPI_Comm_size(new_comm, &new_size);
	MPI_Comm_rank(new_comm, &new_rank);
	ShowLine("new_rank: ", new_rank);
	ShowLine("new_size: ", new_size);
	int* sendBuf = new int[1];
	int* recvBuf = new int[new_size];
	int* sendCount = new int[new_size];
	int* recvCount = new int[new_size];
	int* sdispls = new int[new_size];
	int* rdispls = new int[new_size];

	sendBuf[0] = A;
	for (int i = 0; i < new_size; i++) {
		sendCount[i] = 1;
		sdispls[i] = 0;
		recvCount[i] = 1;
		rdispls[i] = i;
	}


	MPI_Alltoallv(sendBuf, sendCount, sdispls, MPI_INT, recvBuf, recvCount, rdispls, MPI_INT, new_comm);
	//MPI_Scatter(sendBuf, 1, MPI_DOUBLE, recvBuf, 1, MPI_DOUBLE, 0, new_comm);
	for (int i = 0; i < new_size; i++) {
		pt << recvBuf[i];
	}
}
void Solve()
{
	Task("MPI5Comm10");
	int flag;
	MPI_Initialized(&flag);
	if (flag == 0)
		return;
	int rank, size;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	MPI_Comm new_comm1, new_comm2;
	int N, A;
	pt >> N >> A;
	if (N == 1) {
		MPI_Comm_split(MPI_COMM_WORLD, N, rank, &new_comm1);
		MPI_Comm_split(MPI_COMM_WORLD, MPI_UNDEFINED, rank, &new_comm2);
	}
	else {
		MPI_Comm_split(MPI_COMM_WORLD, MPI_UNDEFINED, rank, &new_comm1);
		MPI_Comm_split(MPI_COMM_WORLD, N, rank, &new_comm2);
	}

	if (MPI_COMM_NULL != new_comm1) {
		Print_comm(new_comm1, A);
	}
	else if (MPI_COMM_NULL != new_comm2) {
		Print_comm(new_comm2, A);
	}
}
