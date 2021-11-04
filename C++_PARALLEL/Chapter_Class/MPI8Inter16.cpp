#include "pt4.h"
#include "mpi.h"
void Solve()
{
    Task("MPI8Inter16");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int root;
    double* A = new double[size];
  
    MPI_Comm inter;
    MPI_Comm_get_parent(&inter);
    char str[10] = "ptprj.exe";
    if (inter == MPI_COMM_NULL)
    {
        MPI_Comm_spawn(str, NULL, size, MPI_INFO_NULL, 0,
            MPI_COMM_WORLD, &inter, MPI_ERRCODES_IGNORE);
        for (int i = 0; i < size; i++)
        {
            pt >> A[i];
        }
        root = 0;
    }
    else
    {
        root = MPI_ROOT;
    }

    double res;
    MPI_Reduce_scatter_block(A, &res, 1, MPI_DOUBLE, MPI_MAX, inter);

    if (root == MPI_ROOT)
    {
        MPI_Send(&res, 1, MPI_DOUBLE, rank, 0, inter);
        Show(res);
    }
    else
    {
        MPI_Recv(&res, 1, MPI_DOUBLE, rank, 0, inter, MPI_STATUSES_IGNORE);
        pt << res;
    }

}
