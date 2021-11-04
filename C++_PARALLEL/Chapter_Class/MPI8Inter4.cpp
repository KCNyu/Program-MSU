#include "pt4.h"
#include "mpi.h"
void Solve()
{
	Task("MPI8Inter4");
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

	MPI_Comm_split(MPI_COMM_WORLD, c, rank, &local);

	int local_rank;
	MPI_Comm_rank(local, &local_rank);
	pt << local_rank;
	MPI_Comm inter1, inter2;
	int lead1 = 1, lead2 = 2;
	if (rank == 1)
	{
		lead1 = 0;
	}
	if (rank == 2)
	{
		lead2 = 0;
	}
	MPI_Intercomm_create(local, 0, peer, lead1, 100, &inter1);

	MPI_Intercomm_create(local, 0, peer, lead2, 100, &inter2);
	int a, b, res1, res2;
	pt >> a >> b;
	if (c == 0)
	{
		MPI_Send(&b, 1, MPI_INT, local_rank, 0, inter1);
		MPI_Send(&a, 1, MPI_INT, local_rank, 0, inter2);
	}
	else
	{
		MPI_Send(&a, 1, MPI_INT, local_rank, 0, inter1);
		MPI_Send(&b, 1, MPI_INT, local_rank, 0, inter2);
	}
	MPI_Recv(&res1, 1, MPI_INT, local_rank, 0, inter1, MPI_STATUSES_IGNORE);
	MPI_Recv(&res2, 1, MPI_INT, local_rank, 0, inter2, MPI_STATUSES_IGNORE);
	if (c == 0)
		pt << res2 << res1;
	else
		pt << res1 << res2;

}
