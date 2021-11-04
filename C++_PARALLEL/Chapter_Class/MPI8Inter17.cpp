#include "pt4.h"
#include "mpi.h"
void Solve()
{
    Task("MPI8Inter17");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int root;
    double* A = new double[size / 2];
    
    MPI_Comm inter;
    MPI_Comm_get_parent(&inter);
    char str[10] = "ptprj.exe";
    if (inter == MPI_COMM_NULL)
    {
        MPI_Comm_spawn(str, NULL, 2, MPI_INFO_NULL, 0,
            MPI_COMM_WORLD, &inter, MPI_ERRCODES_IGNORE);
        if (rank == 0 || rank == 1)
        {
            for (int i = 0; i < size/2; i++)
            {
                pt >> A[i];
            }
        }
        root = 0;
    }
    else
    {
        root = MPI_ROOT;
    }

    MPI_Comm comm1;
    double res;
    if (root == MPI_ROOT)
    {
        int r;
        MPI_Comm_rank(inter, &r);
        //Show(r);

        MPI_Comm_split(inter, r % 2, r, &comm1);
        MPI_Comm_rank(comm1, &r);
        //Show(r);
        int sz;
        MPI_Comm_remote_size(comm1, &sz);
        double* buf = new double[sz];
        MPI_Recv(buf, sz, MPI_DOUBLE, 0, 0, comm1, MPI_STATUSES_IGNORE);
        for (int i = 0; i < sz; i++) Show(buf[i]);
       
        MPI_Scatter(buf, 1, MPI_DOUBLE, &res, 1, MPI_DOUBLE, root, comm1);
    }
    else
    {
        //Show(rank);

        MPI_Comm_split(inter, rank % 2, rank, &comm1);
        int r;
        MPI_Comm_rank(comm1, &r);
        //Show(r);

        if (r == 0)
        {
            MPI_Send(A, size / 2, MPI_DOUBLE, 0, 0, comm1);
        }
        MPI_Scatter(NULL, 1, MPI_DOUBLE, &res, 1, MPI_DOUBLE, root, comm1);
        pt << res;
    }
}
