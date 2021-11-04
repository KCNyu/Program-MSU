#include "pt4.h"
#include "mpi.h"
void Solve()
{
	Task("MPI7Win26");
	int flag;
	MPI_Initialized(&flag);
	if (flag == 0)
		return;
	int rank, size;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Win window = MPI_UNDEFINED;

	double A[5], B[5];

	if (rank != 0) {
		MPI_Win_create(nullptr, 5 * 8, 8, MPI_INFO_NULL, MPI_COMM_WORLD, &window);
		for (int i = 0; i < 5; i++)
		{
			pt >> A[i];

		}

		/*
		for (int i = 0; i < 5; i++)
		{
			MPI_Win_lock(MPI_LOCK_SHARED, 0, 0, window);
			MPI_Accumulate(A + i, 1, MPI_DOUBLE, 0, i, 1, MPI_DOUBLE, MPI_MAX, window);
			MPI_Win_unlock(0, window);
		}
		*/
		MPI_Win_lock(MPI_LOCK_SHARED, 0, 0, window);
		MPI_Accumulate(A, 5, MPI_DOUBLE, 0, 0, 5, MPI_DOUBLE, MPI_MAX, window);
		MPI_Win_unlock(0, window);

		MPI_Barrier(MPI_COMM_WORLD);
		/*
		for (int i = 0; i < 5; i++)
		{
			MPI_Win_lock(MPI_LOCK_SHARED, 0, 0, window);
			MPI_Get(B + i, 1, MPI_DOUBLE, 0, i, 1, MPI_DOUBLE, window);
			MPI_Win_unlock(0, window);
		}
		*/
		
		MPI_Win_lock(MPI_LOCK_EXCLUSIVE, 0, 0, window);
		MPI_Get(B, 5, MPI_DOUBLE, 0, 0, 5, MPI_DOUBLE, window);
		MPI_Win_unlock(0, window);
		MPI_Barrier(MPI_COMM_WORLD);

		for (int i = 0; i < 5; i++)
		{
			pt << B[i];
		}
	}
	else
	{
		for (int i = 0; i < 5; i++)
		{
			B[i] = 0.0;
		}
		MPI_Win_create(B, 5 * 8, 8, MPI_INFO_NULL, MPI_COMM_WORLD, &window);
		MPI_Barrier(MPI_COMM_WORLD);
		for (int i = 0; i < 5; i++)
		{
			ShowLine(B[i]);
		}
		MPI_Barrier(MPI_COMM_WORLD);
	}


}
