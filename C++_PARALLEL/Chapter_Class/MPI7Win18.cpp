#include "pt4.h"
#include "mpi.h"
void Solve()
{
	Task("MPI7Win18");
	int flag;
	MPI_Initialized(&flag);
	if (flag == 0)
		return;
	int rank, size;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	int A[1], window_buffer[1];
	MPI_Win window = MPI_UNDEFINED;
	MPI_Group group, group_odd, group_even;
	int* ranks_odd = new int[size / 2];
	int* ranks_even = new int[size / 2];
	for (int i = 0; i < size / 2; i++)
	{
		ranks_even[i] = i * 2;
		ranks_odd[i] = i * 2 + 1;
	}
	MPI_Comm_group(MPI_COMM_WORLD, &group);
	MPI_Group_incl(group, size / 2, ranks_odd, &group_odd);
	MPI_Group_incl(group, size / 2, ranks_even, &group_even);
	MPI_Win_create(window_buffer, 4, 4, MPI_INFO_NULL, MPI_COMM_WORLD, &window);
	if (rank % 2 == 0)
	{
		pt >> A[0];


		MPI_Put(A, 1, MPI_INT, rank + 1, 0, 1, MPI_INT, window);
		MPI_Win_start(group_odd, 0, window);
		MPI_Win_complete(window);
	}
	else
	{


		MPI_Win_post(group_even, 0, window);
		MPI_Win_wait(window);
		pt << window_buffer[0];
	}
}
