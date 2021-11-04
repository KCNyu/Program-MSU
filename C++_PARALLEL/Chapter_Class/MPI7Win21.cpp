#include "pt4.h"
#include "mpi.h"
void Solve()
{
	Task("MPI7Win21");
	int flag;
	MPI_Initialized(&flag);
	if (flag == 0)
		return;
	int rank, size;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	int sz = size / 2;
	int* N = new int[sz];
	double* A = new double[sz];
	double window_buffer[1];
	MPI_Win window;
	MPI_Group group, g;
	MPI_Comm_group(MPI_COMM_WORLD, &group);
	MPI_Win_create(window_buffer, 8, 8, MPI_INFO_NULL, MPI_COMM_WORLD, &window);
	if (rank == 0) {
		for (int i = 0; i < sz; i++)
		{
			pt >> A[i];
		}
		for (int i = 0; i < sz; i++)
		{
			pt >> N[i];
		}
		int a[1] = { 0 };
		MPI_Group_excl(group, 1, a, &g);
		MPI_Win_start(group, 0, window);
		for (int i = 0; i < sz; i++)
		{
			MPI_Put(A + i, 1, MPI_DOUBLE, N[i], 0, 1, MPI_DOUBLE, window);
		}
		
		MPI_Win_complete(window);
		//MPI_Win_fence(0, window);

	}
	else {
		window_buffer[0] = 0.0;

		
		int k[1] = { 0 };
		MPI_Group_incl(group, 1, k, &g);

		MPI_Win_post(g, 0, window);

		MPI_Win_wait(window);
		pt << window_buffer[0];
		//MPI_Win_fence(0, window);
		
	}

}
