#include "pt4.h"
#include "mpi.h"
#include <vector>
void Solve()
{
    Task("MPI6File30");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    char name[20];
    int N;
    if (rank == 0) {
        pt >> name >> N;
    }
    MPI_Bcast(name, 20, MPI_CHAR, 0, MPI_COMM_WORLD);
    MPI_Bcast(&N, 1, MPI_INT, 0, MPI_COMM_WORLD);
    int I, J;
    pt >> I >> J;
    MPI_File f;

    MPI_File_open(MPI_COMM_WORLD, name,
        MPI_MODE_RDWR | MPI_MODE_CREATE, MPI_INFO_NULL, &f);
    char view[7] = "native";
    MPI_Datatype new_type;
    MPI_Type_contiguous(N, MPI_INT, &new_type);
    MPI_Type_create_resized(new_type, 0,  N*4*3, &new_type);
    //MPI_Type_vector(N, N, N * 3, MPI_INT, &new_type);
    MPI_File_set_view(f,((J-1)*N+(I-1)*N*N*3) * 4, MPI_INT, new_type, view,
        MPI_INFO_NULL);
    int* mat = new int[N * N];
    for (int i = 0; i < N * N; i++) mat[i] = rank;
    MPI_File_write_all(f, mat, N*N, MPI_INT, MPI_STATUSES_IGNORE);
    // try
}
