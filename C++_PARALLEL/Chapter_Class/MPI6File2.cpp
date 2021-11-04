#include "pt4.h"
#include "mpi.h"
#include <map>
void Solve()
{
	Task("MPI6File2");
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
	MPI_File f = MPI_FILE_NULL;
	int a = MPI_File_open(MPI_COMM_WORLD, name, MPI_MODE_CREATE | MPI_MODE_RDWR, MPI_INFO_NULL, &f);
	char t[7] = "native";

	if (rank != 0) {

		int sz;
		pt >> sz;
		int* order = new int[sz];
		int* nums = new int[sz];
		for (int i = 0; i < sz; i++) {
			pt >> order[i] >> nums[i];
			ShowLine("order: ", order[i]);
		}

		MPI_Aint lb, type_size;
		//MPI_Type_size(MPI_INT, &type_size);
		MPI_Type_get_extent(MPI_INT, &lb,&type_size);
		ShowLine("typeSize: ", type_size);
		for (int i = 0; i < sz; i++) {
			MPI_File_write_at(f, (order[i] - 1) * type_size, nums + i, 1, MPI_INT, MPI_STATUSES_IGNORE);
		}

	}
	MPI_File_close(&f);
}
