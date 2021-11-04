#include "pt4.h"
#include "mpi.h"
void Solve()
{
    Task("MPI6File26");
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
    double a[4];
    for (int i = 0; i < 4; ++i)
        pt >> a[i];
    MPI_File f;
    MPI_File_open(MPI_COMM_WORLD, name,
        MPI_MODE_WRONLY | MPI_MODE_CREATE, MPI_INFO_NULL, &f);
    int dbl_sz;
    MPI_Type_size(MPI_DOUBLE, &dbl_sz);
    MPI_Datatype t0, t;
    MPI_Type_vector(2, 1, 2 * (size - rank) - 1, MPI_DOUBLE, &t0);
    MPI_Type_create_resized(t0, 0, 2 * size * dbl_sz, &t);
    char view[7] = "native";
    MPI_File_set_view(f, rank * dbl_sz, MPI_DOUBLE, t, view,
        MPI_INFO_NULL);
    MPI_File_write_all(f, a, 4, MPI_DOUBLE, MPI_STATUS_IGNORE);
    MPI_File_close(&f);
}
