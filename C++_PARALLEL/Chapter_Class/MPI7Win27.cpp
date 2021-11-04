#include "pt4.h"
#include "mpi.h"
void Solve()
{
    Task("MPI7Win27");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    double a[2] = { 0, 0 };
    double res[2];
    if (rank) {
        pt >> a[0] >> a[1];
    }

    MPI_Win win;
    MPI_Win_create(a, 2 * 8, 8, MPI_INFO_NULL, MPI_COMM_WORLD, &win);

    if (rank == 0) {
        double a0[2] = { a[0],a[1] };
        for (int i = 1; i < size; ++i) {
            
            MPI_Win_lock(MPI_LOCK_SHARED, i, 0, win);
            MPI_Get(a0, 2, MPI_DOUBLE, i, 0, 2, MPI_DOUBLE, win);
            MPI_Win_unlock(i, win);
            ShowLine(a0[0]);
            ShowLine(a0[1]);
            if ((a0[0] * a0[0] + a0[1] * a0[1]) >= (a[0] * a[0] + a[1] * a[1])) {
                a[0] = a0[0];
                a[1] = a0[1];
            }
            /*
            ShowLine(a[0]);
            ShowLine(a[1]);
            */
        }
        MPI_Barrier(MPI_COMM_WORLD);

    }
    else {
        
        MPI_Barrier(MPI_COMM_WORLD);

        MPI_Win_lock(MPI_LOCK_SHARED, 0, 0, win);
        MPI_Get(res, 2, MPI_DOUBLE, 0, 0, 2, MPI_DOUBLE, win);
        MPI_Win_unlock(0, win);

        pt << res[0] << res[1];
    }
}
