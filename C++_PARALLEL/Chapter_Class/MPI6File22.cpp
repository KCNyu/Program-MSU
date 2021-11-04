#include "pt4.h"
#include "mpi.h"
void Solve()
{
    Task("MPI6File22");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    char name[20];
    if (rank == 0)
        pt >> name;
    MPI_Bcast(name, 20, MPI_CHAR, 0, MPI_COMM_WORLD);
    int nums[3];
    for (int i = 0; i < 3; i++) pt >> nums[i];
    MPI_File f;
    MPI_File_open(MPI_COMM_WORLD, name,
        MPI_MODE_WRONLY | MPI_MODE_CREATE, MPI_INFO_NULL, &f);
    char view[7] = "native";
    MPI_Datatype new_type;
    MPI_Type_create_resized(MPI_INT, 0, (size) * 4, &new_type);
    MPI_File_set_view(f, (size-rank-1)*4, MPI_INT, new_type, view,
        MPI_INFO_NULL);
    MPI_File_write_all(f, nums, 3, MPI_INT, MPI_STATUSES_IGNORE);
}
