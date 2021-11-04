#include "pt4.h"
#include "mpi.h"
void Solve()
{
    Task("MPI6File15");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	char name[12];
	if (rank == 0) pt >> name;
	MPI_Bcast(name, 12, MPI_CHAR, 0, MPI_COMM_WORLD);

	int new_rank, new_size;
	MPI_Comm new_comm = MPI_COMM_NULL;

	if (rank % 2 == 1) {
		MPI_Comm_split(MPI_COMM_WORLD, 1, size-rank, &new_comm);
	}
	else {
		MPI_Comm_split(MPI_COMM_WORLD, MPI_UNDEFINED, rank, &new_comm);
	}
	if (MPI_COMM_NULL != new_comm) {
		MPI_File f = MPI_FILE_NULL;
		int a = MPI_File_open(new_comm, name, MPI_MODE_CREATE | MPI_MODE_RDWR, MPI_INFO_NULL, &f);
		if (a != MPI_SUCCESS) ShowLine("failed");
		MPI_Comm_size(new_comm, &new_size);
		MPI_Comm_rank(new_comm, &new_rank);
		ShowLine("new_rank: ", new_rank);
		double buf[2];

		MPI_File_seek_shared(f, -new_size * 8*2, MPI_SEEK_END);

		
		MPI_File_read_ordered(f, buf, 2, MPI_DOUBLE, MPI_STATUSES_IGNORE);
		pt << buf[0] << buf[1];
	}
}
