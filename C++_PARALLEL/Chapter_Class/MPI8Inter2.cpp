#include "pt4.h"
#include "mpi.h"
void Solve()
{
	Task("MPI8Inter2");
	int flag;
	MPI_Initialized(&flag);
	if (flag == 0)
		return;
	int rank, size;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm peer;
	MPI_Comm_dup(MPI_COMM_WORLD, &peer);
	int c;
	pt >> c;
	MPI_Comm local;
	if (c == 0)
	{
		MPI_Comm_split(MPI_COMM_WORLD, c, rank, &local);
	}
	else
	{
		MPI_Comm_split(MPI_COMM_WORLD, c, size - rank - 1, &local);
	}
	int local_rank;
	MPI_Comm_rank(local, &local_rank);
	pt << local_rank;
	MPI_Comm inter;
	int lead = size-1;
	if (rank == size-1) lead = 0;
	MPI_Intercomm_create(local, 0, peer, lead, 100, &inter);
	
	MPI_Status s;
	double a, b;
	pt >> a;

	MPI_Send(&a, 1, MPI_DOUBLE, local_rank, 0, inter);
	MPI_Recv(&b, 1, MPI_DOUBLE, local_rank, 0, inter, &s);
	
	pt << b;
	


}
