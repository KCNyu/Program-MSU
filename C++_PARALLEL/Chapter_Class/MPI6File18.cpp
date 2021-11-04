#include "pt4.h"
#include "mpi.h"
void Solve()
{
    Task("MPI6File18");
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

    int N;
    pt >> N;
    MPI_File f = MPI_FILE_NULL;
    int a = MPI_File_open(MPI_COMM_WORLD, name, MPI_MODE_CREATE | MPI_MODE_RDWR, MPI_INFO_NULL, &f);
    if (a != MPI_SUCCESS) ShowLine("failed");
    char view[7] = "native";
    MPI_File_set_view(f, rank * 5*4, MPI_INT, MPI_INT, view, MPI_INFO_NULL);
    MPI_File_write_at_all(f, N - 1, &rank, 1, MPI_INT, MPI_STATUSES_IGNORE);
}
