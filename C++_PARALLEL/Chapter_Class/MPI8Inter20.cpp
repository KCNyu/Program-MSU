#include "pt4.h"
#include "mpi.h"
void Solve()
{
	Task("MPI8Inter20");
	int flag;
	MPI_Initialized(&flag);
	if (flag == 0)
		return;
	int rank, size;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	int root;
	int A;
	int r;
	int K0;
	MPI_Comm inter, comm1;
	MPI_Comm_get_parent(&inter);
	char str[10] = "ptprj.exe";
	if (inter == MPI_COMM_NULL)
	{
		int procs = 4 - size % 4;
		K0 = size + procs;
		MPI_Comm_spawn(str, NULL, procs, MPI_INFO_NULL, 0,
			MPI_COMM_WORLD, &inter, MPI_ERRCODES_IGNORE);
		pt >> A;
		root = 0;
		MPI_Intercomm_merge(inter, false, &comm1);
		MPI_Comm_rank(comm1, &r);
		//Show(r);
		//Show(K0);
	}
	else
	{
		A = -rank - 1;
		root = MPI_ROOT;
		MPI_Intercomm_merge(inter, true, &comm1);
		MPI_Comm_rank(comm1, &r);
		//Show(r);
		int sz;
		MPI_Comm_remote_size(inter, &sz);
		K0 = sz + 4 - sz % 4;
		//Show(K0);
	}
	int ndims = 2;
	int dims[2] = { K0 / 4, 4 };
	int periods[2] = { true, true };
	int reorder = false;
	MPI_Comm new_comm;
	//Show(K0 / 4);
	MPI_Cart_create(comm1, ndims, dims, periods, reorder, &new_comm);
	int new_rank;
	MPI_Comm_rank(new_comm, &new_rank);
	int my_coords[2];
	MPI_Cart_coords(new_comm, new_rank, 2, my_coords);
	Show(my_coords[0]); Show(my_coords[1]);
	int neigbours_ranks[2];
	MPI_Cart_shift(new_comm, 0, -1, &neigbours_ranks[0], &neigbours_ranks[1]);
	int recv;
	MPI_Sendrecv(&A, 1, MPI_INT, neigbours_ranks[1], 0, &recv, 1, MPI_INT, neigbours_ranks[0], 0, new_comm, MPI_STATUSES_IGNORE);

	pt << my_coords[0] << my_coords[1] << recv;
	Show(recv);

}
