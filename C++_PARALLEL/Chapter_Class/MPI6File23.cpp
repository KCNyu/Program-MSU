#include "pt4.h"
#include "mpi.h"
void Solve()
{
    Task("MPI6File23");
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
    MPI_File f;
    MPI_File_open(MPI_COMM_WORLD, name,
        MPI_MODE_RDWR | MPI_MODE_CREATE, MPI_INFO_NULL, &f);
    char view[7] = "native";
    MPI_Datatype new_type;
    MPI_Type_contiguous(3, MPI_DOUBLE, &new_type);
    MPI_Type_create_resized(new_type, 0,   (3)*8*size, &new_type);
    MPI_File_set_view(f,  rank  * 8*3, MPI_DOUBLE, new_type, view,
        MPI_INFO_NULL);
    double nums[6];
    MPI_File_read_all(f, nums, 6, MPI_DOUBLE, MPI_STATUSES_IGNORE);
    for (int i = 0; i < 6; i++) pt << nums[i];
}
