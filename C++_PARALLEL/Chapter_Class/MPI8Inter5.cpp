#include "pt4.h"
#include "mpi.h"
void Solve()
{
	Task("MPI8Inter5");
	int flag;
	MPI_Initialized(&flag);
	if (flag == 0)
		return;
	int rank, size;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	MPI_Comm peer;
	MPI_Comm_dup(MPI_COMM_WORLD, &peer);

	int X;
	pt >> X;

	MPI_Group group, g;
	MPI_Comm_group(MPI_COMM_WORLD, &group);
	int(*range)[3];

	range = (int(*)[3])malloc(sizeof(int) * size / 2 * 3);

	for (int i = 0; i < size / 2; i++)
	{
		if (rank < size / 2)
		{
			range[i][0] = i; range[i][1] = i; range[i][2] = 1;
		}
		else
		{
			range[i][0] = i + size / 2; range[i][1] = i + size / 2; range[i][2] = 1;
		}
	}
	MPI_Group_range_incl(group, size / 2, range, &g);
	MPI_Comm local;
	MPI_Comm_create(MPI_COMM_WORLD, g, &local);

	int R1;
	MPI_Comm_rank(local, &R1);

	pt << R1;
	MPI_Comm inter;
	int lead = 0;
	if (rank == 0)
	{
		lead = size / 2;
	}
	MPI_Intercomm_create(local, 0, MPI_COMM_WORLD, lead, 100, &inter);


	int* ranks = new int[size / 4];
	for (int i = 0; i < size / 4; i++)
	{
		if (rank < size / 2)
		{
			ranks[i] = i * 2;
		}
		else
		{
			ranks[size / 4 - i - 1] = i * 2 + 1;
		}
	}

	MPI_Group new_g;
	MPI_Group_incl(g, size / 4, ranks, &new_g);
	MPI_Comm inter2 = MPI_UNDEFINED;
	MPI_Comm_create(inter, new_g, &inter2);
	int R2;
	
	if (MPI_Comm_rank(inter2, &R2) == MPI_SUCCESS)
	{
		
		pt << R2;
		MPI_Send(&X, 1, MPI_INT, R2, 0, inter2);
		int buf;
		MPI_Recv(&buf, 1, MPI_INT, R2, 0, inter2, MPI_STATUSES_IGNORE);
		pt << buf;
	}
	
}
