#include "pt4.h"
#include "mpi.h"
void Solve()
{
	Task("MPI5Comm6");
	int flag;
	MPI_Initialized(&flag);
	if (flag == 0)
		return;
	int rank, size;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	int new_rank, new_size;
	MPI_Comm new_comm;

	if (rank == 0) {
		MPI_Comm_split(MPI_COMM_WORLD, 1, rank, &new_comm);
	}
	else {
		int N;
		pt >> N;
		if (N == 1) {
			MPI_Comm_split(MPI_COMM_WORLD, 1, rank, &new_comm);
		}
		else {
			MPI_Comm_split(MPI_COMM_WORLD, MPI_UNDEFINED, rank, &new_comm);
		}

	}
	if (MPI_COMM_NULL != new_comm) {
		MPI_Comm_size(new_comm, &new_size);
		MPI_Comm_rank(new_comm, &new_rank);
		ShowLine("new_rank: ", new_rank);
		ShowLine("new_size: ", new_size);
		double* sendBuf = new double[new_size];
		double* recvBuf = new double[1];
		int* sendCount = new int[new_size];
		int* recvCount = new int[new_size];
		int* sdispls = new int[new_size];
		int* rdispls = new int[new_size];
		if (new_rank == 0) {
			int K;
			pt >> K;

			for (int i = 0; i < K; i++) {
				pt >> sendBuf[i];
			}
			for (int i = 0; i < new_size; i++) {
				if (i == 0) {
					sendCount[i] = 0;
				}
				else {
					sendCount[i] = 1;
				}
				sdispls[i] = i - 1;
				recvCount[i] = 0;
				rdispls[i] = 0;
			}
		}
		else {
			for (int i = 0; i < new_size; i++) {
				if (i == 0) {
					recvCount[i] = 1;
				}
				else {
					recvCount[i] = 0;
				}
				sdispls[i] = 0;
				sendCount[i] = 0;
				rdispls[i] = 0;
			}
		}
		MPI_Alltoallv(sendBuf, sendCount, sdispls,MPI_DOUBLE, recvBuf, recvCount, rdispls, MPI_DOUBLE, new_comm);
		//MPI_Scatter(sendBuf, 1, MPI_DOUBLE, recvBuf, 1, MPI_DOUBLE, 0, new_comm);
		if (new_rank != 0) {
			pt << recvBuf[0];
		}
		
	}
}
