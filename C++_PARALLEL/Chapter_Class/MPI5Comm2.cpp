#include "pt4.h"
#include "mpi.h"
void Solve()
{
	Task("MPI5Comm2");
	int flag;
	MPI_Initialized(&flag);
	if (flag == 0)
		return;
	int rank, size;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	//ShowLine("size ", size);
	//ShowLine("rank ", rank);
	int n = size / 2;
	int* even = new int[n+1];
	for (int i = 0; i < n+1; i++) {
		even[i] = 2 * i;
	}
	MPI_Group group_all, group_odd;
	MPI_Comm_group(MPI_COMM_WORLD, &group_all);
	if (size % 2 == 0) {
		MPI_Group_excl(group_all, n, even, &group_odd);
	}
	else {
		MPI_Group_excl(group_all, n + 1, even, &group_odd);
	}
	MPI_Comm comm_odd;
	MPI_Comm_create(MPI_COMM_WORLD, group_odd, &comm_odd);

	int odd_rank = -1, odd_size = -1;

	if (MPI_COMM_NULL != comm_odd) {
		MPI_Comm_rank(comm_odd, &odd_rank);
		MPI_Comm_size(comm_odd, &odd_size);

		//ShowLine("odd_size ", odd_size);
		//ShowLine("odd_rank ", odd_rank);
		double* recvBuf = new double[odd_size * 2];
		double* sendBuf = new double[2];
		int* sendCount = new int[odd_size];
		int* recvCount = new int[odd_size];
		int* rdispls = new int[odd_size];
		int* sdispls = new int[odd_size];
		for (int i = 0; i < odd_size; i++) {
			sendCount[i] = 2;
			recvCount[i] = 2;
			rdispls[i] = i * 2;
			sdispls[i] = 0;
		}

		for (int i = 0; i < 2; i++) {
			pt >> sendBuf[i];
		}
		MPI_Alltoallv(sendBuf, sendCount, sdispls, MPI_DOUBLE, recvBuf, recvCount, rdispls, MPI_DOUBLE, comm_odd);
		for (int i = 0; i < odd_size * 2; i++) {
			pt << recvBuf[i];
		}
	}
}
