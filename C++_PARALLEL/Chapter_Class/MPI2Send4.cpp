#include "pt4.h"
#include "mpi.h"
void Solve()
{
    Task("MPI2Send4");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int N;
    const int MAX_NUMBERS = 100;
    int num[MAX_NUMBERS];
    if (rank != 0) {
        pt >> N;
        for (int i = 0; i < N; i++) {
            pt >> num[i];
        }
        int bsize = 0, bsize_t = 0;
        MPI_Pack_size(N, MPI_INT, MPI_COMM_WORLD, &bsize);
        int* tmpbuffer = (int*)malloc(bsize + 2 * MPI_BSEND_OVERHEAD);
        MPI_Buffer_attach(tmpbuffer, bsize + 2 * MPI_BSEND_OVERHEAD);
        MPI_Bsend(num, N, MPI_INT, 0, 0, MPI_COMM_WORLD);
        MPI_Buffer_detach(tmpbuffer, &bsize_t);
    }
    else {
        for (int i = 1; i < size; i++) {
            MPI_Status status;
            MPI_Recv(num, MAX_NUMBERS, MPI_INT, i, 0, MPI_COMM_WORLD, &status);
            MPI_Get_count(&status, MPI_INT, &N);
            for (int i = 0; i < N; i++) {
                pt << num[i];
            }
        } 
    }

}
