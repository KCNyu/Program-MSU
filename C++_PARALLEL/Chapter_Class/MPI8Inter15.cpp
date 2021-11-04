#include "pt4.h"
#include "mpi.h"
void Solve()
{
    Task("MPI8Inter15");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    double a, sum;
    int root;
    MPI_Comm inter = MPI_COMM_NULL;
    MPI_Comm_get_parent(&inter);
    char str[10];
    strcpy_s(str, "ptprj.exe");
    if (inter == MPI_COMM_NULL)
    {
        MPI_Comm_spawn(str, NULL, 1, MPI_INFO_NULL, 0,
            MPI_COMM_WORLD, &inter, MPI_ERRCODES_IGNORE);
        pt >> a;
        root = 0;
    }
    else
        root = MPI_ROOT;
    MPI_Reduce(&a, &sum, 1, MPI_DOUBLE, MPI_SUM, root, inter);
    MPI_Bcast(&sum, 1, MPI_DOUBLE, root, inter);
    if (root == MPI_ROOT)
        Show(sum);
    else
        pt << sum;

}
