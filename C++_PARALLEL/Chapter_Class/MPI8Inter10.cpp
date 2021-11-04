#include "pt4.h"
#include "mpi.h"
void Solve()
{
	Task("MPI8Inter10");
	int flag;
	MPI_Initialized(&flag);
	if (flag == 0)
		return;
	int rank, size;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm peer;
	MPI_Comm_dup(MPI_COMM_WORLD, &peer);
	int C;
	pt >> C;
	
	MPI_Comm comm1;
	
	if (C == 0)
	{
		MPI_Comm_split(MPI_COMM_WORLD, MPI_UNDEFINED, rank, &comm1);
		pt << -1;
		return;
	}
	else
	{
		MPI_Comm_split(MPI_COMM_WORLD, C, rank, &comm1);
	}
	
	int R;
	MPI_Comm_rank(comm1, &R);
	pt << R;
	MPI_Comm inter;
	int lead = 0;
	if (rank == 0)
	{
		lead = size / 2;
	}

	MPI_Intercomm_create(comm1, 0, peer, lead, 100, &inter);


	int R1, R2;
	pt >> R1 >> R2;
	int X[3];
	if (C == 1)
	{
		if (R == R1)
		{
			pt >> X[0] >> X[1] >> X[2];
			MPI_Bcast(X, 3, MPI_INT, MPI_ROOT, inter);
		}
		MPI_Bcast(X, 3, MPI_INT, MPI_PROC_NULL, inter);
		MPI_Bcast(X, 3, MPI_INT, R2, inter);
		
	}
	else
	{
		if (R == R2)
		{
			pt >> X[0] >> X[1] >> X[2];
			MPI_Bcast(X, 3, MPI_INT, MPI_ROOT, inter);
		}
		MPI_Bcast(X, 3, MPI_INT, MPI_PROC_NULL, inter);
		MPI_Bcast(X, 3, MPI_INT, R1, inter);
	}
	
	

	pt << X[0] << X[1] << X[2];


}
